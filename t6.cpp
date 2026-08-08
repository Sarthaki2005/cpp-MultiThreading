//std::mutex try_lock is member function of class  mutex .
//it tries to lock mutex ,...on successfull aquisition returns true otherwise returns false.
//1.if try_lock() is not able to lock the mutex then  it return back..
//does not gets blocked  hence it is called non-blocking .
//whereas m.lock() is waiting there still to  aquire the lock when it is free

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

int  counter=0;
std::mutex m;
void increase(){
for(int i=0;i<100000;i++){
if(m.try_lock()){
++counter;
m.unlock();
}
}
}


int main(){
std::thread t1(increase);
std::thread t2(increase);
t1.join();
t2.join();
cout<<"counter could increase upto: "<<counter<<endl;
return 0;
}
