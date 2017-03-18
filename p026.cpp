#include <vector>

class Solution {
public:
  int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    int insert_pos = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] != nums[insert_pos]) {
        ++insert_pos;
        nums[insert_pos] = nums[i];
      }
    }
    return insert_pos + 1;
  }
};

int main() {
    return 0;
}
