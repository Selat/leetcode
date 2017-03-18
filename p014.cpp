#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
  std::string longestCommonPrefix(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    if (strs.size() == 1) return strs[0];
    int n = strs.size();
    std::sort(strs.begin(), strs.end());
    int rightmost_id = 0;
    while (rightmost_id < strs[0].size() && rightmost_id < strs[n - 1].size()
           && strs[0][rightmost_id] == strs[n - 1][rightmost_id]) ++rightmost_id;
    return strs[0].substr(0, rightmost_id);
  }
};

int main() {
  return 0;
}
