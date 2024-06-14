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
  st.init();
  st_recur.init();
  for (int i = 0; i < MAX; i++) {
    st.push(i);
    st_recur.push(i);
  }
  Stack<int> st2;
  Stack_Recur<int> st_recur2;
  const int num_trials = 1000;
  auto total_duration = 0;
  cout << "\nAverage time to copy stack (linked list) with " << MAX
       << " elements: " << endl;
  for (int i = 0; i < num_trials; ++i) {
    st2.init();
    auto start = high_resolution_clock::now();
    st2.copyStack(st);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
    st2.release();
  }
  cout << "Loop version: \t\t" << total_duration / num_trials << " microseconds"
       << endl;

  for (int i = 0; i < num_trials; ++i) {
    st_recur2.init();
    auto start = high_resolution_clock::now();
    st_recur2.copyStack(st_recur);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
    st_recur2.release();
  }
  cout << "Recursive version: \t" << total_duration / num_trials
       << " microseconds" << endl;

  //----------------------------------------------------------------
  cout << "\nAverage time to release stack (linked list) with " << MAX
       << " elements: " << endl;
  for (int i = 0; i < num_trials; ++i) {
    st2.init();
    st2.copyStack(st);
    auto start = high_resolution_clock::now();
    st2.release();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
  }
  cout << "Loop version: \t\t" << total_duration / num_trials << " microseconds"
       << endl;

  for (int i = 0; i < num_trials; ++i) {
    st_recur2.init();
    st_recur2.copyStack(st_recur);
    auto start = high_resolution_clock::now();
    st_recur2.release();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
  }
  cout << "Recursive version: \t" << total_duration / num_trials
       << " microseconds" << endl;
  cout << endl;
  st.release();
  st_recur.release();
  return 0;
}