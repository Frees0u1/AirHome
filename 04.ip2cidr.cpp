/*
题目：给一个IP地址范围，比如"10.10.1.1" - "10.12.235.12"，转换成其CIDR表示。CIDR（classless inter-domain routing）的定义可以自行google，这题的主要意思就是转换成一系列的CIDR地址，刚好覆盖给出的IP地址范围（不多不少）。

算法：
从一个简单的例子开始：
比如IP地址范围是 0.0.0.111 - 0.0.0.120，对应的二进制表示如下
1101111   - 111
1110000   - 112
   ...
1110111   - 119
1111000   - 120

显然 0.0.0.(11000000)/24可以覆盖整个地址区间。但是这个CIDR不是一个“合格”的CIDR，因为它的范围太大了，超出了输入的IP地址范围，所以我们要进一步缩小。

缩小的办法是把这个最大的CIDR对半分得到两个CIDR：
- 0.0.0.(11000000)/24
- 0.0.0.(11100000)/25
我们可以把输入的IP地址范围分到这两个CIDR中去，然后再递归求解，直到CIDR恰好覆盖IP区间，则得到合格的CIDR。
*/

#include "LeetcodeTools.h"
using namespace leetcode;

class Solution{
public:
    vector<string> ip2cidr(string& start, string& end){
        vector<string> result;
        uint32_t startIp = aton(start);
        uint32_t endIp = aton(end);

        int prefixLen = 0;
        while(prefixLen < 32) {
            uint32_t mask = 1 << (31 - prefixLen);
            if(mask & endIp) {
                break;
            }
            else {
                ++prefixLen;
            }
        }
        ip2cidrCore(startIp, endIp, 0, prefixLen, result);

        return result;
    }

    void ip2cidrCore(uint32_t startIp, uint32_t endIp, uint32_t prefixIp, int prefixLen, vector<string>& result) {
        int rangeStart = prefixIp;
        int rangeEnd = prefixIp + ((uint64_t)1 << (32 - prefixLen)) - 1;
        if(startIp == rangeStart && endIp == rangeEnd) {
            string cidr = ntoIp(prefixIp);
            cidr += "/" + to_string(prefixLen);
            result.push_back(cidr);
            return;
        }

        uint32_t newPrefix = prefixIp + (1 << (31 - prefixLen));
        if(endIp < newPrefix) {
            ip2cidrCore(startIp, endIp, prefixIp, prefixLen + 1, result);
        }
        else if(startIp >= newPrefix) {
            ip2cidrCore(startIp, endIp, newPrefix, prefixLen + 1, result);
        }
        else {
            ip2cidrCore(startIp, newPrefix - 1, prefixIp, prefixLen + 1, result);
            ip2cidrCore(newPrefix, endIp, newPrefix, prefixLen + 1, result);
        }
    }

    uint32_t aton(const string& ip){
        int l = 0, r = 0;
        uint32_t ans = 0;
        while(l < ip.size()) {
            int cur = 0;
            while(r < ip.size() && ip[r] != '.') {
                cur = cur * 10 + ip[r] - '0';
                r++;
            }

            ans = ans * 256 + cur;
            l = r + 1; r = l;
        }

        return ans;
    }

    string ntoIp(uint32_t ip) {
        string res;
        for (int i = 0; i < 4; ++i) {
                uint32_t mod = ip % 256;
                res = to_string(mod) + (i != 0 ? ".": "") + res;
                ip = ip >> 8;
        }
        return res;
    }
};

int main() {
    string ipStart = "0.0.0.111";
    string ipEnd = "0.0.0.121";
    Solution sol;
    
    printVector(sol.ip2cidr(ipStart, ipEnd), "\n");

    return 0;
}