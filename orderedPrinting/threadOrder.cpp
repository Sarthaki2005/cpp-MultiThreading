#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;
mutex m;
int turn=0;
condition_variable cva;
condition_variable cvb;
condition_variable cvc;

void printA(int times){
	
    while(times){
       unique_lock<mutex> lock(m);
       cva.wait(lock,[]{return turn == 0;});
       cout<<"A";
       times--;
       turn=1;
       lock.unlock();
       cvb.notify_one();
    }
}

void printB(int times){
	
	while(times--){
		unique_lock<mutex> lock(m);
		cvb.wait(lock,[]{return turn==1;});
		cout<<"B";
	
		turn=2;
		lock.unlock();
		cvc.notify_one();
	}
}

void printC(int times){

	while(times--){
		unique_lock<mutex> lock(m);
		cvc.wait(lock,[]{return turn==2;});
		cout<<"C";
		turn =0;
		lock.unlock();
		cva.notify_one();

	}
}

int main(){
	thread t1(printA,10);
	thread t2(printB,10);
	thread t3(printC,10);
	t1.join();
	t2.join();
	t3.join();
	return 0;
}