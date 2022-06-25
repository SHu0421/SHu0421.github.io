#include<iostream>
#include<string>
using namespace std;

struct Person{
    string name;
    int id;
    Person(string name_, int id_){
        name=name_;
        id=id_;
    }
	Person(){ //如果要用Person p来初始化结构体，一定要同时实现有参数和无参构造方法
    }
    // Person(string name_, int id_): name(name_), id(id_){}
    void greet(){
        cout<<"hello "<<name<<" your id is "<<id<<endl;
     
    }

};

int main(){
    // Person p("John", 1);
    // p.name="John";
    // p.id=1;
    p.greet();
    return 0;
}
