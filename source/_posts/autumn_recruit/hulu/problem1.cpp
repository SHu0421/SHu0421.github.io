#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<unordered_map>
using namespace std;

struct node{
    string name;
    string date;
};


bool cmp(node &a, node &b){
    if(a.date!=b.date){
        return a.date < b.date;
    }
    return a.name < b.name;
}

int getNum(string left, string right){
    int year1 = stoi (left.substr(0, 3));
    int month1 = stoi (left.substr(5, 6));
    int day1 = stoi (left.substr(8, 9));

    int year2 = stoi (right.substr(0, 3));
    int month2 = stoi (right.substr(5, 6));
    int day2 = stoi (right.substr(8, 9));
    // cout << day2 << " " << day1 << endl;
    // cout << (year1 - year1) << endl;
    // cout << (month2 - month1)<< endl;
     
    return (year2 - year1) * 365 + (month2 - month1) * 30  + (day2 - day1) + 1;
}

int main()
{
    int n, k;
    scanf("%d", &n);
    vector<node> vec;
    for (int i = 0; i < n; i++)
    {
        string name, date;
        cin >> name;
        cin >> date;
        node a;
        a.name = name;
        a.date = date;
        vec.push_back(a);
    }
    scanf("%d", &k);
    sort(vec.begin(), vec.end(), cmp);
    int size = vec.size();
    unordered_map<string, int> num;
    int count = 0;
    int left = 0, right = 0;
    int res = INT_MAX;
    while (right < size)
    {
        num[vec[right].name]++;
        if(num[vec[right].name]==1){
            count++;
            if(count>=k){
                // cout<<right<<" "<<left<<" "<<getNum(vec[left].date, vec[right].date)<<endl;
                res = min(res, getNum(vec[left].date, vec[right].date));
            }
            while(count>=k){
                num[vec[left].name]--;
                if(num[vec[left].name]==0){
                    count--;
                }
                left++;
            }
        }
        right++;
    }
    if(res==INT_MAX){
        cout<<-1<<endl;
    }
    cout << res << endl;
    return 0;
}