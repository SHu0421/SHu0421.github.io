#include<iostream>
#include<vector>


using namespace std;

// find the index of the smallest value
int findReverseTimes(vector<long long> &arr){
    int left = 0, right = arr.size() - 1;
    while(left<right){
        int mid=left+(right-left)/2;
        if(arr[mid]==arr[right]){
            right--;
        }else if(arr[mid]<arr[right]){
            right = mid;
        }else{
            left = mid + 1;
        }
    }
    return right;
}


int main(){
    vector<long long> arr = {9, 8, 7};
    vector<long long> arr2 = {1, 3, 5, 6};
    vector<long long> arr3 = {1};
    vector<long long> arr4 = {};
    vector<long long>arr5 = {INT_MAX+INT_MAX,INT_MAX+1};
    vector<long long> arr6 = {1, 3, 5, 5, 6, 6, 7, 1};
    vector<long long> arr7 = {-1, 0, 1, 3, 5, 5, 6, 6, 7};
    

    cout<<findReverseTimes(arr)<<endl;
    cout<<findReverseTimes(arr2)<<endl;
    cout<<findReverseTimes(arr3)<<endl;
    cout<<findReverseTimes(arr4)<<endl;
    cout<<findReverseTimes(arr5)<<endl;
    cout<<findReverseTimes(arr6)<<endl;
    cout<<findReverseTimes(arr7)<<endl;
    
    // cout << res << endl;
    return 0;
}