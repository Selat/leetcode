#include <vector>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        int insert_pos = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != val) {
                nums[insert_pos++] = nums[i];
            }
        }
        return insert_pos;
    }
};

int main() {
    return 0;
}
