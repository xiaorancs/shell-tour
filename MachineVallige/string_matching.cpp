#include <iostream>
#include <string>
#include <vector>

using namespace std;

int naive_match(string t, string p) {
    int ans = -1;
    int t_size = t.size();
    int p_size = p.size();
    if (t_size == 0) {
        return -1;
    }
    if (p_size == 0) {
        return 0;
    }
    if (p_size > t_size) {
        return -1;
    }
    for (int i = 0; i <= t_size - p_size; i ++) {
        int j = 0;
        for (j = 0; j < p_size; j ++) {
            if (t[i + j] != p[j]) {
                break;
            }
        }
        // cout << j << endl;
        if (j == p_size) {
            ans = i;
            break;
        }
    }
    return ans;
}

const int BASE = 256;
const int MOD = 101;
int rabin_karp_match(string t, string p) {
    int ans = -1;
    int t_size = t.size();
    int p_size = p.size();
    if (t_size == 0) {
        return -1;
    }
    if (p_size == 0) {
        return 0;
    }
    if (p_size > t_size) {
        return -1;
    }
    int t_hash = 0;
    int p_hash = 0;
    int h = 1;
    for (int i = 0; i < p_size; i ++) {
        if (i < p_size - 1) {
            h = h * BASE % MOD;
        }
        t_hash = (t_hash * BASE + int(t[i])) % MOD;
        p_hash = (p_hash * BASE + int(p[i])) % MOD;
    }
    for (int i = 0; i <= t_size - p_size; i ++) {
        if (t_hash == p_hash) { // 再次确认
            int j = 0;
            for (j = 0; j < p_size; j ++) {
                if (t[j + i] != p[j]) {
                    break;
                }
            }
            if (j == p_size) {
                ans = i;
                break;
            }
        }
        // 迭代更新
        t_hash = ((t_hash - (h * int(t[i]))) * BASE + int(t[i + p_size])) % MOD;
        if (t_hash < 0) {
            t_hash = t_hash + MOD;
        }
    }
    return ans;
}

void get_next(string p, vector<int>& next) {
    int n = p.size(), k = -1, j = 0;
    next.resize(n);
    std::fill(next.begin(), next.end(), -1);
    while (j < n - 1) {
        if (k == -1 || p[j] == p[k]) {
            ++k; ++j;
            if (p[j] != p[k]) {
                next[j] = k;
            }
            else {
                next[j] = next[k];
            }
        } else {
            k = next[k];
        }
    }
}

int kmp_match(string t, string p) {
    int ans = -1; 
    int t_size = t.size();
    int p_size = p.size();
    if (t_size == 0) {
        return -1;
    }
    if (p_size == 0) {
        return 0;
    }
    if (p_size > t_size) {
        return -1;
    }
    int i = 0;
    int j = 0;
    vector<int> next;
    get_next(p, next);
    while (i < t_size && j < p_size) {
        if (j == - 1 || t[i] == p[j]) {
            ++i; ++j;
        } else {
            j = next[j];
        }
    }
    return (j == p_size) ? i - j : ans;
}

int main()
{   
    cout << naive_match("abacd", "acd") << endl;
    cout << rabin_karp_match("abacd", "acd") << endl;
    cout << kmp_match("abacd", "acd") << endl;
    
    return 0;
}