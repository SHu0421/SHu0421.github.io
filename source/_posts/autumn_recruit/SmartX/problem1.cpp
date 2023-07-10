#include<iostream>
#include<vector>

using namespace std;
 vector<vector<int>> insert( vector<vector<int>>  arr, vector<int> interval){
     int a = interval[0];
     int b = interval[1];
     vector<vector<int>> res;
     int index = arr.size();
     for (int i = 0; i < arr.size(); i++)
     {
         if (a<=arr[i][1]&&b>=arr[i][0]){
             a = min(arr[i][0], a);
             b = max(arr[i][1], b);
         }else{
            if(arr[i][1]<a){
                res.push_back(arr[i]);
            }else{
                res.push_back({a, b});
                index = i;
                break;
            }
        }
     }

     if(index!=arr.size()){
         for (int i = index; i < arr.size();i++){
             res.push_back(arr[i]);
         }
     }else{
        res.push_back({a, b});
     }
     cout << res.size() << endl;
     return res;
 }

int main(){
    vector<vector<int>> arr = {};
    vector<int> interval = {13, 14};
    vector<vector<int>> res = insert(arr, interval);
    for (int i = 0; i < res.size();i++){
        cout << res[i][0] << " " << res[i][1] << endl;
    }
    return 0;
}