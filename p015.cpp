#include <vector>
#include <algorithm>

class Solution {
public:
  static void advance(int& id, int dir, const std::vector<int>& nums) {
    int v = nums[id];
    id += dir;
    while (id + dir >= 0 && id + dir < nums.size() && nums[id] == v) {
      id += dir;
    }
  }
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> ans;
    for (int i = 0; i + 2 < nums.size();) {
      int l = i + 1;
      int r = nums.size() - 1;
      while (l < r) {
        int sum = nums[i] + nums[l] + nums[r];
        if (sum < 0) {
          advance(l, 1, nums);
        } else if (sum > 0) {
          advance(r, -1, nums);
        } else {
          ans.push_back({nums[i], nums[l], nums[r]});
          advance(l, 1, nums);
          advance(r, -1, nums);
        }
      }
      advance(i, 1, nums);
    }
    return ans;
  }
};

int main() {
  return 0;
}
