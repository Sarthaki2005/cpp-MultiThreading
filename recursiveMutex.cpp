//recursive mutex
#include<iostream>
#include<chrono>
#include<thread>
#include<mutex>
using namespace std;
recursive_mutex m;
int buffer=0;
void recursion(char c,int loopFor){
if(loopFor<0){
return;
}
m.lock();
cout<<"Thread id: "<<c<<" "<<buffer++<<endl;
recursion(c,--loopFor);
m.unlock();
cout<<"Thread id: "<<c<<" unlocked"<<endl;
}

int main(){
thread t1(recursion,'1',10);
thread t2(recursion,'2',10);
t1.join();
t2.join();
return 0;
}
