//join  joinable  whenever thread is created it starts running and control returns back to main.We want main to wait
//until thread finishes.   Double join leads to termination. //better to ask t1.joinable()  then only join

#include<iostream>
#include<thread>
#include<chrono>
using namespace std;
using namespace std::chrono;
void run(int x){
while(x>0){
cout<<"Hello World\n";
x--;
}
this_thread::sleep_for(chrono::seconds(3));
}
int main(){
thread t1(run,20);
cout<<"Before join\n";
t1.join();
cout<<"After join\n";
if(t1.joinable()){
t1.join();
}
return 0;
}
