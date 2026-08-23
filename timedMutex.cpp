//timed_mutex  If a thread wants to wait for a specified amount of time before returning 
#include<iostream>
#include<chrono>
#include<utility>
#include<mutex>
#include<thread>
using namespace std;
timed_mutex m;
int amount=0;
void increment(int i){
if(m.try_lock_for(chrono::seconds(2))){
++amount;
this_thread::sleep_for(chrono::seconds(1));
cout<<"Thread "<<i<<" could enter\n";
m.unlock();
}else{
cout<<"Thread "<<i<<" could not entered\n";
}
}
int main(){
thread t1(increment,1);
thread t2(increment,2);
t1.join();
t2.join();
cout<<amount<<endl;
}
