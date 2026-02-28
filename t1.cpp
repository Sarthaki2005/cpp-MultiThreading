/*Find the sum of even and odd numbers from 1 to 19000000*/

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull OddSum = 0;
ull EvenSum = 0;

void findEven(ull start, ull end)
{
  for (ull i = start; i <= end; i++)
  {
    if ((i & 1) == 0)
    {
      EvenSum += i;
    }
  }
}

void findOdd(ull start, ull end)
{
  for (ull i = start; i <= end; i++)
  {
    if ((i & 1))
    {
      OddSum += i;
    }
  }
}

/*singel thread*/
int main()
{
  ull start = 1, end = 1900000000;
  auto start_time = high_resolution_clock::now();
  std::thread t1(findOdd, start, end);
  std::thread t2(findEven, start, end);

  //thread joining
  t1.join();
  t2.join();

  // findEven(start, end);
  // findOdd(start, end);
  auto stop_time = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(stop_time - start_time);
  cout << "OddSum : " << OddSum << endl;
  cout << "EvenSum: " << EvenSum << endl;
  cout << duration.count() << endl;
  return 0;
}
