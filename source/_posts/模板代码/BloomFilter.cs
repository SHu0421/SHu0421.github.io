// ---------------------------------------------------------------------------
// <copyright file="BloomFilter.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// ---------------------------------------------------------------------------

namespace Microsoft.Substrate.SearchSettings.Common.Model.BloomFilter
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using Microsoft.Substrate.SearchSettings.Common.Utils;

    /// <summary>
    /// An immutable Bloom filter.
    /// </summary>
    /// <typeparam name="T">Type of the elements in the filter.</typeparam>
    public class BloomFilter<T> : IBloomFilter<T>
    {
        /// <summary>
        /// The bloom filter bit vector as a byte array
        /// </summary>
        private readonly byte[] bitVector;

        /// <summary>
        /// First hash function for the Bloom filter
        /// </summary>
        private readonly Func<T, int> firstHashFunction;

        /// <summary>
        /// Second hash function for the Bloom filter
        /// </summary>
        private readonly Func<T, int> secondHashFunction;

        /// <summary>
        /// Number of entries in the filter
        /// </summary>
        private readonly int entryCount;

        /// <summary>
        /// Number of bits to set to 1 per item added to the filter.
        /// </summary>
        private readonly int numberOfBitsToSet;

        /// <summary>
        /// Cache of the filter's data object
        /// </summary>
        private BloomFilterData dataCache;

        /// <summary>
        /// Bloom filter 'version' which is part of this filter's data object. This number can be used to discriminate
        /// which hash functions etc. are to be used.
        /// </summary>
        private int version;

        /// <inheritdoc/>
        public BloomFilterData Data => this.dataCache ?? (this.dataCache = this.ConstructData());

        /// <summary>
        /// Construct a new Bloom filter of the given size with the given entries
        /// </summary>
        /// <param name="entries">Number of entries in the filter</param>
        /// <param name="filterSizeBytes">Size of the filter in bytes</param>
        /// <param name="firstHashFunction">First hash function to use for the filter</param>
        /// <param name="secondHashFunction">Second hash function to use for the filter</param>
        /// <param name="version">Version number of the filter</param>
        public BloomFilter(IEnumerable<T> entries, int filterSizeBytes, Func<T, int> firstHashFunction, Func<T, int> secondHashFunction, int version)
            : this(entries, entries.Count(), filterSizeBytes, firstHashFunction, secondHashFunction, version)
        {
        }

        /// <summary>
        /// Construct a new Bloom filter of the given size with the given entries and entries count
        /// </summary>
        /// <param name="entries">entries in the filter</param>
        /// <param name="numberOfEntries">the number of entries</param>
        /// <param name="filterSizeBytes">Size of the filter in bytes</param>
        /// <param name="firstHashFunction">First hash function to use for the filter</param>
        /// <param name="secondHashFunction">Second hash function to use for the filter</param>
        /// <param name="version">Version number of the filter</param>
        public BloomFilter(IEnumerable<T> entries, int numberOfEntries, int filterSizeBytes, Func<T, int> firstHashFunction, Func<T, int> secondHashFunction, int version)
        {
            ArgumentValidator.ThrowIfNull(nameof(entries), entries);
            ArgumentValidator.ThrowIfInvalidValue(numberOfEntries, x => x < 0, () => $"{nameof(numberOfEntries)} cannot be negative");
            ArgumentValidator.ThrowIfInvalidValue(filterSizeBytes, x => x < 0, () => $"{nameof(filterSizeBytes)} cannot be negative");
            ArgumentValidator.ThrowIfNull(nameof(firstHashFunction), firstHashFunction);
            ArgumentValidator.ThrowIfNull(nameof(secondHashFunction), secondHashFunction);

            this.entryCount = numberOfEntries;
            this.bitVector = new byte[filterSizeBytes];
            this.numberOfBitsToSet = BloomFilterHelpers.CalcNumberOfBitsToSet(this.entryCount, this.bitVector.Length);
            this.firstHashFunction = firstHashFunction;
            this.secondHashFunction = secondHashFunction;
            this.version = version;

            foreach (var entry in entries)
            {
                this.Add(entry);
            }
        }

        /// <summary>
        /// Constructs a new Bloom filter with the given entries of a size that will allow the specified error rate.
        /// </summary>
        /// <param name="entries">Entries into the filter</param>
        /// <param name="errorRate">Filter error rate</param>
        /// <param name="firstHashFunction">First hash function to use for the filter</param>
        /// <param name="secondHashFunction">Second hash function to use for the filter</param>
        /// <param name="version">Version number of the filter</param>
        public BloomFilter(IEnumerable<T> entries, double errorRate, Func<T, int> firstHashFunction, Func<T, int> secondHashFunction, int version)
            : this(entries, BloomFilterHelpers.CalcFilterSize(entries.Count(), errorRate), firstHashFunction, secondHashFunction, version)
        {
        }

        /// <summary>
        /// Constructs a new Bloom filter from the given raw data
        /// </summary>
        /// <param name="data">Byte array of data</param>
        /// <param name="entryCount">Number of entries in the Bloom filter</param>
        /// <param name="firstHashFunction">First hash function to be used in the filter</param>
        /// <param name="secondHashFunction">Second hash function to be used by the filter</param>
        /// <param name="version">Version number of the filter</param>
        private BloomFilter(byte[] data, int entryCount, Func<T, int> firstHashFunction, Func<T, int> secondHashFunction, int version)
        {
            ArgumentValidator.ThrowIfNull(nameof(data), data);
            ArgumentValidator.ThrowIfInvalidValue(entryCount, x => x < 0, () => $"{nameof(entryCount)} must not be negative");
            ArgumentValidator.ThrowIfNull(nameof(firstHashFunction), firstHashFunction);
            ArgumentValidator.ThrowIfNull(nameof(secondHashFunction), secondHashFunction);

            this.bitVector = data;
            this.numberOfBitsToSet = BloomFilterHelpers.CalcNumberOfBitsToSet(entryCount, this.bitVector.Length);
            this.firstHashFunction = firstHashFunction;
            this.secondHashFunction = secondHashFunction;
            this.entryCount = entryCount;
            this.version = version;
        }

        /// <summary>
        /// Creates a Bloom filter from the given BloomFilterData object
        /// </summary>
        /// <param name="data">The data object</param>
        /// <param name="firstHashFunction">First hash function used by the filter</param>
        /// <param name="secondHashFunction">Second hash function used by the filter</param>
        /// <returns>The created Bloom filter</returns>
        public static BloomFilter<T> FromData(BloomFilterData data, Func<T, int> firstHashFunction, Func<T, int> secondHashFunction)
        {
            ArgumentValidator.ThrowIfNull(nameof(data), data);
            ArgumentValidator.ThrowIfNull(nameof(data.RawFilterData), data.RawFilterData);
            ArgumentValidator.ThrowIfNull(nameof(firstHashFunction), firstHashFunction);
            ArgumentValidator.ThrowIfNull(nameof(secondHashFunction), secondHashFunction);

            byte[] dataArray = Convert.FromBase64String(data.RawFilterData);
            return new BloomFilter<T>(dataArray, data.NumberOfElements, firstHashFunction, secondHashFunction, data.Version);
        }

        /// <summary>
        /// Upsert entries into filter
        /// </summary>
        /// <param name="entries">The entries to upsert</param>
        /// <returns>The (approxi entries count / design entries count) after upsert, if the value greater than 1 recommend to recalculate bloom filter</returns>
        public double Upsert(IEnumerable<T> entries)
        {
            foreach (var entry in entries)
            {
                this.Add(entry);
            }

            this.dataCache = this.ConstructData();

            if (this.entryCount == 0)
            {
                // return a big value because the design entries count is 0, need to recalculate bloom filter
                return int.MaxValue;
            }

            return (double)BloomFilterHelpers.CalcApproxiNumberOfEntries(this.bitVector, this.entryCount) / this.entryCount;
        }
        
        /// <summary>
        /// Determine whether the set represented by this Bloom filter may contain the element.
        /// </summary>
        /// <param name="valueToCheck">Value to check for contains</param>
        /// <returns>true if valueToCheck may be in the set; false if valueToCheck is definitely not in the set.</returns>
        public bool MayContain(T valueToCheck)
        {
            foreach (var index in this.GetBitsToSet(valueToCheck))
            {
                var byteForIndex = this.bitVector[index / 8];
                if ((byteForIndex & (1 << (index % 8))) == 0)
                {
                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Helper function that outputs the indices to be set when adding or checking an element's presence in the filter
        /// </summary>
        /// <param name="value">Value to find indices for</param>
        /// <returns>An array which can be used to index the bit vector</returns>
        private int[] GetBitsToSet(T value)
        {
            int[] output = new int[this.numberOfBitsToSet];
            var hash1 = this.firstHashFunction(value);
            var hash2 = this.secondHashFunction(value);

            for (int i = 0; i < output.Length; ++i)
            {
                var hash = hash1 + (i * hash2);
                output[i] = hash % (this.bitVector.Length * 8);

                if (output[i] < 0)
                {
                    output[i] += this.bitVector.Length * 8;
                }
            }

            return output;
        }

        /// <summary>
        /// Helper that creates the Bloom filter's data object.
        /// </summary>
        /// <returns>Created bloom filter data</returns>
        private BloomFilterData ConstructData()
        {
            return new BloomFilterData
            {
                NumberOfElements = this.entryCount,
                RawFilterData = Convert.ToBase64String(this.bitVector),
                Version = this.version,
            };
        }

        /// <summary>
        /// Adds the given element to the Bloom filter
        /// </summary>
        /// <param name="element">Element to add</param>
        private void Add(T element)
        {
            foreach (var bitLocation in this.GetBitsToSet(element))
            {
                this.bitVector[bitLocation / 8] |= (byte)(1 << (bitLocation % 8));
            }
        }
    }
}
