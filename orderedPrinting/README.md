\# Multithreaded Ordered Printing (ABC)



A C++11 implementation demonstrating thread synchronization using \*\*Condition Variables\*\* and \*\*Mutexes\*\*. The program coordinates three concurrent threads to print the characters 'A', 'B', and 'C' in a strict, repeating sequence.



\## 📋 Problem Description

The goal is to create 3 threads that print their respective characters in a specific order (`ABCABC...`) repeated 10 times. Without synchronization, threads would execute unpredictably (e.g., `AAABBC...`).



\## 🛠 Features

\- \*\*Strict Ordering\*\*: Uses a state-based `turn` variable to enforce sequence.

\- \*\*Thread Safety\*\*: Employs `std::mutex` to prevent data races.

\- \*\*Efficiency\*\*: Uses `std::condition\_variable` to put threads to sleep when it isn't their turn, saving CPU cycles compared to busy-waiting.



\## 🏗 System Architecture







The logic follows a state-machine pattern:

1\. \*\*Thread A\*\* waits for `turn == 0`, prints 'A', sets `turn = 1`, and notifies \*\*Thread B\*\*.

2\. \*\*Thread B\*\* waits for `turn == 1`, prints 'B', sets `turn = 2`, and notifies \*\*Thread C\*\*.

3\. \*\*Thread C\*\* waits for `turn == 2`, prints 'C', sets `turn = 0`, and notifies \*\*Thread A\*\*.



| Thread | Target Character | Condition | Next State | Signal Sent To |

| :--- | :--- | :--- | :--- | :--- |

| \*\*t1\*\* | 'A' | `turn == 0` | `turn = 1` | `cvb` |

| \*\*t2\*\* | 'B' | `turn == 1` | `turn = 2` | `cvc` |

| \*\*t3\*\* | 'C' | `turn == 2` | `turn = 0` | `cva` |



\## 🚀 Getting Started



\### Prerequisites

\- A C++ compiler supporting \*\*C++11\*\* or higher (GCC, Clang, or MSVC).

\- (Linux/macOS) The `pthread` library.



\### Compilation

Use the following command to compile the code using `g++`:



```bash

g++ -std=c++11 -pthread main.cpp -o ordered\_print

