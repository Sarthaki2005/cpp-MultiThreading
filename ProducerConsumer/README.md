\# Producer–Consumer Problem in Modern C++



\## 📌 Overview



This project implements the classic \*\*Producer–Consumer Problem\*\* using modern C++ concurrency primitives:



\- `std::thread`

\- `std::mutex`

\- `std::condition\_variable`

\- `std::queue`

\- RAII-based locking (`lock\_guard`, `unique\_lock`)



It demonstrates safe communication between multiple producer and consumer threads using a bounded buffer.



---



\## 🧠 Problem Statement



Two types of threads share a fixed-size buffer:



\- \*\*Producer\*\* → Produces items and inserts them into the buffer.

\- \*\*Consumer\*\* → Removes items from the buffer.



Constraints:



\- Producer must wait if the buffer is full.

\- Consumer must wait if the buffer is empty.

\- Shared data must be protected from race conditions.

\- CPU should not be wasted in busy waiting.



---



\## 🏗 Design



\- Shared buffer: `std::queue<int>`

\- Buffer capacity: `N = 5`

\- Mutex `m` → protects buffer access

\- Mutex `it` → protects item generation

\- Condition Variables:

&nbsp; - `cv\_producer`

&nbsp; - `cv\_consumer`



Multiple producers and consumers are supported.



---



\## 🔐 Why Use `lock\_guard`?



```cpp

int produceItem(){

&nbsp;   lock\_guard<mutex> lock(it);

&nbsp;   return itemp;

}

