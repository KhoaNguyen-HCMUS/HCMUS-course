#include <cstdio>
#include <iostream>
#include <string>

class Rope {
  std::string s;

 public:
  Rope(const std::string &s) : s(s) {}

  void process(int i, int j, int k) {
    // Extract the substring to be moved
    std::string to_move = s.substr(i, j - i + 1);

    // Erase the substring from its original position
    s.erase(i, j - i + 1);

    // Insert the substring at the new position
    s.insert(k, to_move);
  }

  std::string result() { return s; }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::string s;
  std::cin >> s;
  Rope rope(s);
  int actions;
  std::cin >> actions;
  for (int action_index = 0; action_index < actions; ++action_index) {
    int i, j, k;
    std::cin >> i >> j >> k;
    rope.process(i, j, k);
  }
  std::cout << rope.result() << std::endl;
}
