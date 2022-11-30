#include <iostream>
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here
void swap(char *str,int i,int j);
void combine(char *floating, int start, int end, const std::string& in, const std::set<std::string>& dict, std::set<std::string> &ret);
void world(std::vector<char> &str, int start, int end, const std::set<std::string>& dict, std::set<std::string> &ret);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> r;
    if (in.empty()) return r;

    int count = 0;
    std::vector<char> f;
    for(auto c : in) {
        if (c == '-') {
            count++;
            if (floating.size() >= count) {
                f.push_back(floating[count - 1]);
            } else {
                f.push_back('-');
            }
        }
    }

    if (count >= floating.size()) {
        combine(f.data(), 0, f.size(), in, dict, r);
    } else {
        cout << "Combination Error" << endl;
    }

    return r;
}


void combine(char *floating, int start, int end, const std::string& in, const std::set<std::string>& dict, std::set<std::string> &r)
{
    if (start == end){
        int idx = 0;
        std::vector<char> newStr;
        for (int i = 0; i < in.size(); i++) {
            if (in[i] == '-') {
                newStr.push_back(floating[idx++]);
            } else {
                newStr.push_back(in[i]);
            }
        }
        world(newStr, 0, in.size(), dict, r);
    } else {
        for(int i = start; i < end; i++){
            if (floating[start] == floating[i] && start != i) continue;
            swap(floating, start, i);
            combine(floating,start + 1, end, in, dict, r);
            swap(floating, start, i);
        }
    }
}

char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
void world(std::vector<char> &str, int start, int end, const std::set<std::string>& dict, std::set<std::string> &r)
{
    if (start == end){
        std::string w(str.begin(), str.end());
        if (dict.count(w)) {
            ret.insert(w);
        }
    }else{
        if (str[start] != '-'){
            world(str, start + 1, end, dict, r);
        } else {
            for (char c : alphabet) {
                str[start] = c;
                world(str, start + 1, end, dict, r);
                str[start] = '-';
            }
        }
    }
}


void swap(char *str,int a,int b)
{
    char tmp = str[a];
    str[a] = str[b];
    str[b] = tmp;
}

// Define any helper functions here