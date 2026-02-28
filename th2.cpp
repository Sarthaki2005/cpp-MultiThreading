#include<iostream>
#include<thread>
#include<future>
using namespace std;
typedef unsigned long long ull;
void findOdd(std::promise<ull> &&OddSumPromise,ull start,ull end){
	ull OddSum=0;
	for(ull i=start;i<=end;i++){
		if(i & 1){
			OddSum+=i;
		}
	}
	OddSumPromise.set_value(OddSum);
}

int main(){
	ull start=1,end=1900000000;
	promise<ull> OddSum;
	future<ull>  OddFuture=OddSum.get_future();
	cout<<"Thread is created !"<<endl;
	thread t1(findOdd,move(OddSum),start,end);
	cout<<"Waiting for result"<<endl;
	cout<<"OddSum : "<<OddFuture.get()<<endl;

	cout<<"Completed"<<endl;
	t1.join();
	return 0;
}