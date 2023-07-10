#include<iostream>
using namespace std;

class singleTonClass{
    private:
        singleTonClass();
        static singleTonClass objectSingle;

    public:
        static singleTonClass getObject(){
            return objectSingle;
        };
};

int main(){
    singleTonClass target = singleTonClass::getObject(); //函数是类公用，没有静态指针
    return 0;
}