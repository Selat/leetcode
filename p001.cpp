#include <unordered_map>
#include <vector>
#include <iostream>
#include <cassert>

class Solution {
 public:
  std::vector<int> twoSum(const std::vector<int>& a, int target_sum) {
    std::unordered_map<int, int> nums;
    for (size_t i = 0; i < a.size(); ++i) {
      if (nums.count(target_sum - a[i])) {
        return {nums[target_sum - a[i]], i};
      }
      nums[a[i]] = i;
    }
    assert(false);
  }
};

template <typename T>
void AssertVectorsEqual(const std::vector<T>& v1, const std::vector<T>& v2) {
  assert(v1.size() == v2.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    assert(v1[i] == v2[i]);
  }
}

void RunTests() {
  Solution sol;
  AssertVectorsEqual(sol.twoSum({2, 7, 15, 10}, 9), {0, 1});
  AssertVectorsEqual(sol.twoSum({0, 15, 1, 2, 3, 0}, 0), {0, 5});
  std::cout << "All tests passed! :)" << std::endl;
}

int main() {
  RunTests();
  int n, target_sum;
  std::cin >> n >> target_sum;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  Solution sol;
  auto ans = sol.twoSum(a, target_sum);
  assert(ans.size() == 2);
  std::cout << ans[0] << " " << ans[1] << std::endl;
  return 0;
}
