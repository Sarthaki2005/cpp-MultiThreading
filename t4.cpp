#include<iostream>
#include<thread>
#include<chrono>
using namespace std::chrono;
using namespace std;

void run(int x){
while(x>0){
cout<<"Hello World\n";
x--;
}
this_thread::sleep_for(chrono::seconds(10));
}
int main(){
thread t1(run,20);
cout<<"Before detach\n";
t1.detach();
cout<<"Afetr detach\n";

}
