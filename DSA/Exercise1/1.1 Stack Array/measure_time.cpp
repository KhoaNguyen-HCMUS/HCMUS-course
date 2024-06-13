#include <chrono>
#include <iostream>

#include "recursive_stack.h"
#include "stack.h"
#define MAX 10000
using namespace std::chrono;
using namespace std;

int main() {
  Stack<int> st;
  Stack_Recur<int> st_recur;
  st.init(MAX);
  st_recur.init(MAX);
  for (int i = 0; i < MAX; i++) {
    st.push(i);
    st_recur.push(i);
  }
  Stack<int> st2;
  Stack_Recur<int> st_recur2;
  const int num_trials = 1000;  // Number of times to repeat the operation
  auto total_duration = 0;

  for (int i = 0; i < num_trials; ++i) {
    st2.init(MAX);
    auto start = high_resolution_clock::now();
    st2.copyStack(st);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
    st2.release();
  }
  cout << "Average time to copy stack (array) by loop with " << MAX
       << " elements: " << total_duration / num_trials << " microseconds"
       << endl;

  for (int i = 0; i < num_trials; ++i) {
    st_recur2.init(MAX);
    auto start = high_resolution_clock::now();
    st_recur2.copyStack(st_recur);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
    st_recur2.release();
  }
  cout << "Average time to copy stack (array) by recursion with " << MAX
       << " elements: " << total_duration / num_trials << " microseconds"
       << endl;

  st.release();
  st_recur.release();
  return 0;
}