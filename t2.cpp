#include<iostream>
#include<thread>
using namespace std;
//Methods  to create threads
//1.Function as callable objects
//void run(int x){
//while(x>0) {
//cout<<x<<"\n";
//x--;
//}
//}
//2.Lambda functions
//int main(){
//auto f=[](int x){
//while(x>0){
//cout<<x<<"\n";
//x--;
//}
//};
//thread t1(f,10);
//t1.join();
//return 0;
//}

//3.Functors : function objects
//class F{
//public:
//void  operator()(int x){
//while(x>0){
//cout<<x<<"\n";
//x--;
//}
//}
//};


////int main(){
//F f;
//thread t1(f,10);
//t1.join();
//return 0;
//}


//4. non-static member functions
//class Base{
//public:
//void run(int x){
//while(x>0){
//cout<<x<<"\n";
//x--;
//}
//}
//};
//
//int main(){
//Base b;
//thread t1(&Base::run,&b,10);
//t1.join();
//return 0;
//
//
//}
//


//5. static member function dont need to specify the object in thread creation

class Base{
public:
static void run(int x){
while(x>0){
cout<<x<<"\n";
x--;
}
}
};


int main()
{
Base b;
thread t1(&Base::run,10);
t1.join();
return 0;
}
