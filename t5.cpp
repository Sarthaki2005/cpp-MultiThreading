//Topic: Mutex in C++
//Race condition is a situation where two or more threads try to read same data and atleast one of them modifies it.
//the data is known as critical section.
//we need to protect it.using mutex-->mutual exclusion mutex m;
//m.lock()  do work m.unlock() 
#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
std::mutex m;
int myAmount=0;
void AddMoney(){
m.lock();
++myAmount;
m.unlock();
}

int main(){
thread t1(AddMoney);
thread t2(AddMoney);
t1.join();
t2.join();
cout<<myAmount<<"\n";

}
