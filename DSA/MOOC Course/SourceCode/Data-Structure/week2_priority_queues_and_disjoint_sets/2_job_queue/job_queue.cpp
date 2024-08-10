#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  vector<int> assigned_workers_;
  vector<long long> start_times_;

  struct Worker {
    int id;
    long long next_free_time;

    bool operator>(const Worker& other) const {
      if (next_free_time == other.next_free_time) return id > other.id;
      return next_free_time > other.next_free_time;
    }
  };

 public:
  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for (int i = 0; i < m; ++i) cin >> jobs_[i];
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    priority_queue<Worker, vector<Worker>, greater<Worker>> pq;

    for (int i = 0; i < num_workers_; ++i) {
      pq.push({i, 0});
    }

    for (int i = 0; i < jobs_.size(); ++i) {
      Worker best_worker = pq.top();
      pq.pop();

      assigned_workers_[i] = best_worker.id;
      start_times_[i] = best_worker.next_free_time;

      best_worker.next_free_time += jobs_[i];
      pq.push(best_worker);
    }
  }

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}