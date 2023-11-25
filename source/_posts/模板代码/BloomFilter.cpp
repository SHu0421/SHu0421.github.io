
class BloomFilter{
    int bitVector = new byte[this.filterSize];
    public:
    vector<int> calBitsToInsert(int key){
        // 每个值生成多少个output也是自己定义的
        vector<int> output(this.numberOfBitsToSet); //通过错误率来计算 以及filterSize
        int value1 = hashfunc1(key);
        int value2 = hashfunc2(key);
        for (int i = 0; i < output.size(); i++)
        {
            int index = value1 + i * value2;
            index = index % (this.bitVector.length() * 8);
            if(index<0){
                index += this.bitVector.length() * 8;
            }
            output[i]=index;
        }
        return output;
    }


    void insert(int key){
        vector<int> output = calBitsToInsert(key);
        for (int i = 0; i < this.numberOfBitsToSet;i++){
            this.bitVector[output[i] / 8] |= (byte)1<< this.bitVector[output[i] % 8];
        }
    }

    bool Contains(int key){
        vector<int> output = calBitsToInsert(key);
        for (int i = 0; i < this.numberOfBitsToSet;i++){
            if(this.bitVector[output[i] / 8]&(1<<(output[i] % 8)))==0){
                return false;
            }
        }
        return true;
    }
}

