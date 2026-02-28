/*
    Author: Sarthaki Bhoir
    Project: ThreadPool Implementation
    Language: C++17
    Concepts: RAII, Multithreading, Perfect Forwarding
*/
#include<iostream>
#include<vector>
#include<queue>
#include<thread>
#include<functional>
#include<sstream>
#include<mutex>
#include<condition_variable>
#include<chrono>


using namespace std;

class ThreadPool{
	vector<thread> workers;
	queue<function<void()>> tasks;
	mutex queueMutex;
	condition_variable cv;
	bool stop;
public:
	ThreadPool(size_t threadNum):stop(false){
	for(size_t i=0;i<threadNum;i++){
           workers.emplace_back([this] {
           	for(;;){
           		unique_lock<mutex> lock(queueMutex);
           		cv.wait(lock,[this]{ return stop || !tasks.empty();});
           		if(stop && tasks.empty()){
           			return;
           		}
           		auto task=move(tasks.front());
           		tasks.pop();
           		lock.unlock();
           		task();

           	}
           });
	}
}

template<class T>
void enqueue(T&& task){
	unique_lock<mutex> lock(queueMutex);
	tasks.emplace(forward<T>(task));
	lock.unlock();
	cv.notify_one();
}

~ThreadPool(){
	unique_lock<mutex> lock(queueMutex);
	stop=true;
	lock.unlock();
	cv.notify_all();
	for(auto &worker:workers){
		worker.join();
	}

}
};

string get_thread_id(){
	auto myid=this_thread::get_id();
	stringstream ss;
	ss<<myid;
	return ss.str();
}
int main(){
	ThreadPool pool(4);
	for(int i=0;i<8;i++){
		pool.enqueue([i]{
			printf("Task %d executed by thread %s\n",i,get_thread_id().c_str());
			this_thread::sleep_for(chrono::seconds(1));
		});
	}
	return 0;
}
