#include<iostream>
using namespace std;
int main(){
    int n;
    scanf("%d", &n);
    while(n--){
        int a, b;
        scanf("%d%d", &a, &b);
        int bigger=a;
        int smaller=b;
        if(b>a){
            bigger=b;
            smaller=a;
        }
        if(bigger-smaller>smaller){
            cout<< smaller<<endl;
        }else{
            int result = (bigger+smaller)/3;
            cout<< smaller<<endl;
        }

    }
    return 0;
}