// #include <iostream>
// #include <chrono>
// #include <thread>
// using namespace std;
// using namespace std::chrono;

// void run(int x)
// {
//   while (x-- > 0)
//   {
//     cout << "CppNuts\n";
//   }
// }

// int main()
// {
//   thread t1(run, 10);
//   t1.join();
//   return 0;
// }

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;

void run(int x)
{
  while (x-- > 0)
  {
    cout << "CppNuts\n";
  }
  this_thread::sleep_for(chrono::seconds(3));
}

int main()
{
  thread t1(run, 10);
  cout << "main()\n";
  t1.join();
  cout << "After main()";
  return 0;
}
