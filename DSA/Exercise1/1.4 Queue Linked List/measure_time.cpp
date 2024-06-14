#include <chrono>
#include <iostream>

#include "queue.h"
#include "recursive_queue.h"
#define MAX 10000
using namespace std::chrono;
using namespace std;

int main() {
  Queue<int> q;
  Queue_Recur<int> q_recur;
  q.init();
  q_recur.init();
  for (int i = 0; i < MAX; i++) {
    q.enqueue(i);
    q_recur.enqueue(i);
  }
  Queue<int> q2;
  Queue_Recur<int> q_recur2;
  const int num_trials = 1000;  // Number of times to repeat the operation
  auto total_duration = 0;
  cout << "\nAverage time to copy queue (linked list) with " << MAX
       << " elements: " << endl;
  for (int i = 0; i < num_trials; ++i) {
    q2.init();
    auto start = high_resolution_clock::now();
    q2.copyQueue(q);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
    q2.release();
  }
  cout << "Loop version: \t\t" << total_duration / num_trials << " microseconds"
       << endl;

  for (int i = 0; i < num_trials; ++i) {
    q_recur2.init();
    auto start = high_resolution_clock::now();
    q_recur2.copyQueue(q_recur);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
    q_recur2.release();
  }
  cout << "Recursive version: \t" << total_duration / num_trials
       << " microseconds" << endl;

  //----------------------------------------------------------------
  cout << "\nAverage time to release queue (linked list) with " << MAX
       << " elements: " << endl;
  for (int i = 0; i < num_trials; ++i) {
    q2.init();
    q2.copyQueue(q);
    auto start = high_resolution_clock::now();
    q2.release();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
  }
  cout << "Loop version: \t\t" << total_duration / num_trials << " microseconds"
       << endl;

  for (int i = 0; i < num_trials; ++i) {
    q_recur2.init();
    q_recur2.copyQueue(q_recur);
    auto start = high_resolution_clock::now();
    q_recur2.release();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    total_duration += duration.count();
  }
  cout << "Recursive version: \t" << total_duration / num_trials
       << " microseconds" << endl;
  cout << endl;
  q.release();
  q_recur.release();
  return 0;
}