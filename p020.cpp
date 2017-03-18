#include <map>
#include <stack>
#include <string>

class Solution {
public:
    std::map<char, int> brace_types = {
        {'(', 0}, {'{', 1}, {'[', 2},
        {')', 3}, {'}', 4}, {']', 5}};
    int getBraceType(char c) {
        return brace_types[c];
    }
    bool isValid(std::string str) {
        std::stack<int> s;
        for (char c : str) {
            int type = getBraceType(c);
            if (type < 3) {
                s.push(type);
            } else if (s.empty() || s.top() + 3 != type) {
                return false;
            } else {
                s.pop();
            }
        }
        return s.empty();
    }
};

int main() {
    return 0;
}
