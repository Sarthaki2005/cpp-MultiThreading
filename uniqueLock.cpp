//unique_lock<mutex> is again wrapper on mutex m  with ownership.
//allows different locking strategies defer lock,try_to_lock(),adopt_lock
//#include<iostream>
//#include<thread>
//#include<mutex>
//using namespace std;
//
//mutex m;
//int buffer=0;
//
//void increment(const char c,int loopFor){
//std::unique_lock<mutex> lock(m);  //no strategy is mentined it will lock immediately
//for(int i=0;i<loopFor;i++){
//buffer++;
//cout<<"Thread "<<c<<" "<<buffer<<endl;
//}
////unlock automatically as scope is escaped
//}
//int main(){
//thread t1(increment,'1',10);
//thread t2(increment,'2',10);
//t1.join();
//t2.join();
//cout<<buffer<<"\n";
//return 0;
//}


//unique_lock<mutex>  lock(m,std::defer_lock)

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex m;
int buffer=0;
void increment(const char c,int loopFor){
unique_lock<mutex> lock(m,std::defer_lock);
lock.lock();  //u have to explicitly lock th mutex
for(int i=0;i<loopFor;i++){
buffer++;
cout<<"Thread "<<c<<" "<<buffer<<endl;
}
}

int main(){
thread t1(increment,'1',10);
thread t2(increment,'2',10);
t1.join();
t2.join();
return 0;
}
