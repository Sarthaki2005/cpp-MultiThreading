#include<iostream>
#include<thread>
#include<mutex>
#include<deque>
#include<condition_variable>
using namespace std;
mutex m1;

condition_variable cond;
deque<int> Buffer;
int maxBufferSize=50;
using namespace std;

void producer(int val){
	while(val--){
         unique_lock<mutex> locker(m1);
         cond.wait(locker,[]{return Buffer.size()<maxBufferSize;});
         Buffer.push_back(val);
         cout<<"Value pushed: "<<val<<endl;
         locker.unlock();
         cond.notify_one();
	}
}
void consumer(){
	while(true){
		unique_lock<mutex> locker(m1);
		cond.wait(locker,[]{return Buffer.size()>0;});
		int val=Buffer.front();
		cout<<"Value popped: "<<val<<endl;
		Buffer.pop_front();
		locker.unlock();
		cond.notify_one();

	}
}
int main(){
thread t1(producer,100);
thread t2(consumer);
t1.join();
t2.join();
return 0;
}