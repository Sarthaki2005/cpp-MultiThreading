#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>
#include<vector>
#include<condition_variable>
using namespace std;

class MyPrinter{
string str;
int char_count;
int thread_count;
int allowed_thread;
vector<thread> threads;
mutex m1;
condition_variable cv;
int next_char;

public:
	MyPrinter(string str,int c,int t):str(str),char_count(c),thread_count(t),allowed_thread(0),next_char(0){}

	void run(){
		for(int i=0;i<thread_count;i++){
			threads.emplace_back(&MyPrinter::print_thread,this,i);
		}
		for(auto &t : threads){
			t.join();
		}
	}


	void print_thread(int id){
		unique_lock<mutex> lock(m1);
		cv.wait(lock,[this,id]{return id==allowed_thread;});
         print_chars(id);
         allowed_thread=(allowed_thread+1)%thread_count;

         lock.unlock();
         cv.notify_all();
	}

	void print_chars(int id){
		cout<<"Thread_id: "<<id<<" : ";
		for(int i=0;i<char_count;i++){
			cout<<str[next_char];
			next_char=(next_char+1)%str.length();
		}
		cout<<endl;
	}
};

int main(int argc,char* argv[]){
	if(argc!=4){
		cout<<"Enter 3 arguments: string s,char_count,thread count";
		return 1;
	}

	string s=argv[1];
	int char_count=atoi(argv[2]);
	int thread_count=atoi(argv[3]);
	MyPrinter p(s,char_count,thread_count);
	p.run();
	return 0;
}