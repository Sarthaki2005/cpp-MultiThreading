//lock_gurad is a lightweight wrapper around the mutex whenever u want a scope based mutex that is whenever u enter
//the function lock the mutex --> do work --> unlock the mutex      u can do  it in one  line .
//lock_gurad<mutex> lock(m)  -> lock is object created and in it's constructor we lock the mutex and in its destructor we  unlock th mutex;

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex m;
int buffer=0;
void funct(const char c,int loopFor){
lock_guard<mutex> lock(m);
for(int i=0;i<loopFor;i++){
cout<<"Thread id: "<<c<<" "<<buffer++<<endl;
}
}

int main(){
thread t1(funct,'1',10);
thread t2(funct,'2',10);
t1.join();
t2.join();
cout<<buffer<<"\n";

}
