#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
mutex m1,m2;

void task_a(){
	while(1){
		std::lock(m1,m2);
		cout<<"a\n";
		m2.unlock();
		m1.unlock();
	}
}

void task_b(){
	while(1){
		std::lock(m1,m2);
		cout<<"b\n";
		m2.unlock();
		m1.unlock();
	}
}


int main(){
	thread t1(task_a);
	thread t2(task_b);
	t1.join();
	t2.join();
	return 0;
}