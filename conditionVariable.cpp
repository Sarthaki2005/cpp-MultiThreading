//condition variables allows running wait on some condition and notify other threads
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;
std::condition_variable cv;
std::mutex m;
int balance=0;
void addMoney(int money){
std::lock_guard<mutex> lock(m);
balance+=money;
cout<<"Added balance. Current Balance= "<<balance<<endl;
cv.notify_one(); 
}

void withdraw(int money){
std::unique_lock<mutex> ul(m);
cv.wait(ul,[]{ return balance!=0? true:false;});
if(balance>=money){
balance-=money;
cout<<"Money successfully withdrwan\n";
cout<<"Current Balance: "<<balance<<endl;
}else{
cout<<"No sufficient balance.\n";
}
}

int main(){
thread t1(withdraw,600);
thread t2(addMoney,500);
t1.join();
t2.join();
return 0;
}
