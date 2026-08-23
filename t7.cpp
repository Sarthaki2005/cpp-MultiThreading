//std::try_lock() is different from m.try_lock()  m is object of class 
//mutex and try_lock() is member function of that class
//std::try_lock() tries to lock all the lockable objects passed in it one by one in given order.

//1.on succcess it returns -1 otherwise it returns 0-based indexing of mutexes which it werent able to lock
//2.if it fails to lock any mutex all the before locked mutexexare releases
//3.if a call to try lock results in an exception unlock is called before rethrowing



#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>
using namespace std;

int  X=0,Y=0;
mutex m1,m2;

void doSomething(int sec) {std::this_thread::sleep_for(chrono::seconds(sec));}

void increment(int &XY,std::mutex &m,const char* desc){
for(int i=0;i<5;i++){
m.lock();
++XY;
cout<<desc<<" "<<XY<<"\n";
m.unlock();
doSomething(1);
}
}


void consume(){
int count=5;
int XplusY=0;
while(1){
int lockRes=try_lock(m1,m2);
if(lockRes==-1){
if(X!=0 && Y!=0){
--count;
XplusY=X+Y;
X=0;
Y=0;
cout<<"XplusY "<<XplusY<<"\n";
}
m1.unlock();
m2.unlock();
if(count==0) break;
}
}
}

int main(){
thread t1(increment,ref(X),ref(m1),"X");
thread t2(increment,ref(Y),ref(m2),"Y");
thread t3(consume);
t1.join();
t2.join();
t3.join();

return 0;
}
