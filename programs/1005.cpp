#include <bits/stdc++.h>

using namespace std;
int N;
string str, d;
#define maxl 1048580

int preprocess() {
    int max_val = 0;
    string tmp = str;
    sort(tmp.begin(), tmp.end());
    auto l = unique(tmp.begin(), tmp.end()) - tmp.begin();
    for (char &i: str) {
        i = lower_bound(tmp.begin(), tmp.begin() + l, i) - tmp.begin() + 1;
        max_val = max(max_val, (int) i);
    }
    return max_val;
}

int sa[maxl];
int rk[maxl];
int lcp[maxl];

void doubling() {
    int len = str.length(), rk_thr = 0;
//    int tmp_sa[len + 3];
//    int cntRank[len + 3], rk1[len + 3], rk2[len + 3];
    int *cntRank = new int[len + 3];
    int *rk1 = new int[len + 3], *rk2 = new int[len + 3], *tmp_sa = new int[len + 3];
    auto tmp = str;
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < len; ++i)rk[i] = lower_bound(tmp.begin(), tmp.end(), str[i]) - tmp.begin();

    for (int l = 1; l < len; l <<= 1) {
        for (int i = 0; i < len; ++i) {
            rk1[i] = rk[i];
            rk2[i] = i + l < len ? rk[i + l] : 0;
        }
        memset(cntRank, 0, sizeof(int) * (len + 3));
        rk_thr = 0;
        for (int i = 0; i < len; rk_thr = max(rk_thr, rk2[i]), i++)cntRank[rk2[i]]++;
        for (int i = 1; i <= rk_thr; i++)cntRank[i] += cntRank[i - 1];
        for (int i = len - 1; i >= 0; i--)tmp_sa[--cntRank[rk2[i]]] = i;

        memset(cntRank, 0, sizeof(int) * (len + 3));
        rk_thr = 0;
        for (int i = 0; i < len; rk_thr = max(rk_thr, rk1[i]), i++)cntRank[rk1[i]]++;
        for (int i = 1; i <= rk_thr; i++)cntRank[i] += cntRank[i - 1];
        for (int i = len - 1; i >= 0; i--)sa[--cntRank[rk1[tmp_sa[i]]]] = tmp_sa[i];

        rk[sa[0]] = 0;
        for (int i = 1; i < len; i++) {
            rk[sa[i]] = rk[sa[i - 1]];
            if (rk1[sa[i]] != rk1[sa[i - 1]] || rk2[sa[i]] != rk2[sa[i - 1]])rk[sa[i]]++;
        }
    }
    delete[] cntRank, tmp_sa, rk1, rk2;
}

void get_lcp() {
    int len = str.length();
    int L = 0;
    for (int i = 0; i < len; i++) {
        if (rk[i] > 0) {
            int j = sa[rk[i] - 1];
            while (i + L < len && j + L < len && str[i + L] == str[j + L])L++;
            lcp[rk[i]] = L;
            if (L > 0)L--;
        }
    }
}

struct Solution {
    string str;
    int val;
};
Solution s{"", -1};

void solve() {
    int len = str.length();
    bool f = 0;
    int ans_val = 0;
    string ans_str = "";
    for (int i = 0; i <= len; ++i) {
        if (lcp[i] >= N) {
            if (f) {
                ans_val++;
            } else {
                ans_val = 2;
                f = 1;
                ans_str = d.substr(sa[i], N);
            }
        } else {
            if (f) {
                if (s.val < ans_val) {
                    s.val = ans_val;
                    s.str = ans_str;
                } else if (s.val == ans_val && s.str > ans_str) {
                    s.str = ans_str;
                }
                f = 0;
            }
        }
    }
}

int main() {
//    freopen("case.txt", "r", stdin);
    cin >> N;
    getchar();
    getline(cin, str);
//    unordered_map<string, int> m;
//    string max_str;
//    int max_cnt = 0;
//    for (int i = 0; i < str.length() - N + 1; ++i) {
//        m[str.substr(i, N)]++;
//        if (m[str.substr(i, N)] > max_cnt) {
//            max_str = str.substr(i, N);
//            max_cnt = m[str.substr(i, N)];
//        } else if (m[str.substr(i, N)] == max_cnt && max_str < str.substr(i, N)) {
//            max_str = str.substr(i, N);
//        }
//    }
//    printf("%s %d", max_str.c_str(), max_cnt);
    str.push_back(1);
    d = str;
    doubling();
    get_lcp();
    solve();
    printf("%s %d", s.str.c_str(), s.val);
    return 0;
}