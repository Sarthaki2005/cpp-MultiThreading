#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>
#include<queue>
#include<condition_variable>
using namespace std;

const int N=5;
queue<int> buffer;
mutex m;
condition_variable cv_producer;
condition_variable cv_consumer;
int itemp=0;
mutex it;
int produceItem(){
lock_guard<mutex> lock(it);

return itemp;
}

void producer(int thid){
	
	while(true){
		int item=produceItem();
		unique_lock<mutex> lock(m);

		cv_producer.wait(lock,[]{return buffer.size()<N;});
		buffer.push(item);
		cout<<"Producer "<<thid<<"produced item: "<<item<<"\n";
		item++;
		lock.unlock();
		cv_consumer.notify_one();
		this_thread::sleep_for(chrono::milliseconds(400));
	}
}
void consumer(int thid){
	int itemc;
	while(true){
		unique_lock<mutex> lock(m);
		cv_consumer.wait(lock,[]{return !buffer.empty();});
		itemc=buffer.front();
		buffer.pop();
		cout<<"consumer "<<thid<<" consumed itemc: "<<itemc<<"\n";
		lock.unlock();
		cv_producer.notify_one();
		this_thread::sleep_for(chrono::milliseconds(400));
         
	}
}
int main(){
   thread t1(producer,1);
   thread t2(producer,2);
   thread t3(consumer,1);
   thread t4(consumer,2);
   t1.join();
   t2.join();
   t3.join();
   t4.join();
   return 0;

}