#include <map>
#include <string>
#include <cassert>

class Solution {
public:
    int romanToInt(std::string s) {
        std::map<std::string, int> romanToInt = {
            {"I", 1}, {"IV", 4}, {"V", 5},
            {"IX", 9}, {"X", 10}, {"XL", 40},
            {"L", 50}, {"XC", 90}, {"C", 100},
            {"CD", 400}, {"D", 500}, {"CM", 900}, {"M", 1000}
        };
        int id = 0;
        int res  = 0;
        while (id < s.length()) {
            if (id + 1 < s.length() && romanToInt.count(s.substr(id, 2))) {
                res += romanToInt[s.substr(id, 2)];
                id += 2;
            } else if (romanToInt.count(s.substr(id, 1))) {
                res += romanToInt[s.substr(id, 1)];
                ++id;
            } else {
                assert(0);
            }
        }
        return res;
    }
};

int main() {
   return 0;
}
