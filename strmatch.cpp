#include <iostream>
#include <string>
#include <vector>

using namespace std;

string str = "safjaskjndlksanvcalwepoqjwfaklnvc,zxnckdshdoqweqowh";
string pattern = "poqjwfakl";

class strmatch
{
public:
    int BruteMatch(string str, string pattern){
        if (str.empty() || pattern.empty() || str.size() < pattern.size())
            return -1;
        for (int i = 0; i <= str.size() - pattern.size(); i++){
            int flag = 0;
            for (int j = 0; j < pattern.size(); j++)
                if (str[j + i] != pattern[j]){
                    flag++;
                    break;
                }
            if (flag == 0)
                return i;
        }
        return -1;
    }
    int RabinKarp(string str, string pattern){
        if (str.empty() || pattern.empty() || str.size() < pattern.size())
            return -1;
        //计算pattern的哈希值
        unsigned int pattern_hash = 0;
        unsigned int high_hash = 1;
        for (int i = 0; i < pattern.size(); i++){
            pattern_hash *= 256;
            pattern_hash += pattern[i];
            if (i != 0)
                high_hash = high_hash * 256;
        }
        //计算str的哈希值
        unsigned int str_hash = 0;
        for (int i = 0; i < pattern.size(); i++){
            str_hash *= 256;
            str_hash += str[i];
        }
        int begin = 0;
        do
        {
            if (pattern_hash == str_hash){
                int flag = 0;
                for (int j = 0; j < pattern.size(); j++){
                    if (str[begin + j] != pattern[j]){
                        flag += 1;
                        break;
                    }
                }
                if (flag == 0)
                    return begin;
            }
            if (begin < str.size() - pattern.size()){                
                str_hash -= str[begin] * high_hash;
                str_hash = str_hash * 256 + str[begin + pattern.size()];
            }
            begin++;
        } while (begin <= str.size() - pattern.size());
        return -1;
    }
    int KMPMatch(string str, string pattern){
        //构造转移矩阵
        vector<int> dp(pattern.size(), -1);
        int index = 0;
        int next = -1;
        while (index < pattern.size() - 1){
            if (next < 0 || pattern[index] == pattern[next]){
                dp[++index] = ++next;
            }
            else{
                next = dp[next];
            }
        }
        //进行匹配
        int str_index = 0;
        int pattern_index = 0;
        while (str_index < str.length() && pattern_index < pattern.length()){
            if (pattern_index < 0 || str[str_index] == pattern[pattern_index]){
                str_index++;
                pattern_index++;
            }
            else{
                pattern_index = dp[pattern_index];
            }
        }
        if (pattern_index == pattern.length())
            return str_index - pattern_index;
        else
            return -1;
    }
};
int main(){
    strmatch str_match;
    //测试暴力匹配法
    cout << str_match.BruteMatch(str, pattern) << endl;
    //测试Rabin-Karp法
    cout << str_match.RabinKarp(str, pattern) << endl;
    //测试KMP算法
    cout << str_match.BruteMatch(str, pattern) << endl;
    return 0;
}

