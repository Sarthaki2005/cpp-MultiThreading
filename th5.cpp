#include<iostream>
#include<chrono>
#include<thread>
#include<semaphore>
using namespace std;
//global binary semaphore instances
//object counts are set to zero this is diff
//between mutex and semaphores 
//mutex variables are set to 1 initially so that any process 
//wanting to aquire resource can go first
//however semaphores are signalling u start only when u are signalled 
//till then wait

std::binary_semaphore
     smphSignalMainToThread{0},
     smphSignalThreadToMain{0};


void ThreadProc(){
	//wait fro the signal from main function
	smphSignalMainToThread.acquire();

	std::cout<<"[thread] got the signal\n";
	this_thread::sleep_for(3s);

	cout<<"[thread] Send the signal\n";
	smphSignalThreadToMain.release();

}     

int main(){
	thread t1(ThreadProc);
	cout<<"[Main] Send the signal\n";

	smphSignalMainToThread.release();
	smphSignalThreadToMain.acquire();

	cout<<"[main] Got the Signal\n";
    t1.join();
}