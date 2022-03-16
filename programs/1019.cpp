#include <bits/stdc++.h>

#define maxn 10
#define ANIMAL 1
#define GROUND 0
#define OBSTACLE -1
int zoo[maxn][maxn] = {0};
using namespace std;
int N, M, K, H;
typedef long long ll;
int cnt = 0;
ll num_solution = 0;
typedef long long ll;
unordered_set<ll> searched_states;
namespace std {
    template<>
    struct hash<pair<int, int>> {
        size_t operator()(const pair<int, int> &p) const {
            return (p.first - 1) * M + (p.second - 1);
        }
    };
}
int nx[4] = {1, 0, -1, 0};
int ny[4] = {0, 1, 0, -1};
ll animal_pos = 0;
bool vis[maxn][maxn] = {0};

bool has_been_searched(ll cur_state) {
    return searched_states.find(cur_state) != searched_states.end();
}

bool valid(int x, int in) {
    return x >= 1 && x <= in;
}

unordered_set<pair<int, int>> decode_state(ll state) {
    unordered_set<pair<int, int>> ret;
    while (state) {
        ll low_state = state & (-state);
        ll low_bit = ll(round(log2(low_state)));
        ret.insert(make_pair(low_bit / M + 1, low_bit % M + 1));
        state -= low_state;
    }
    return ret;
}

bool animal_separated(int r, int c) {
    queue<pair<int, int>> q;
    q.push(make_pair(r, c));
    vis[r][c] = 1;
    while (!q.empty()) {
        auto F = q.front();
        q.pop();
        if (zoo[F.first][F.second] == ANIMAL && (F.first != r || F.second != c))return false;
        for (int k = 0; k < 4; ++k) {
            int x = F.first + nx[k], y = F.second + ny[k];
            if (valid(x, N) && valid(y, M) && zoo[x][y] != OBSTACLE && !vis[x][y]) {
                vis[x][y] = 1;
                q.push(make_pair(x, y));
            }
        }
    }
    return true;
}

bool animals_separated() {
    memset(vis, 0, sizeof vis);
    auto animal_pos_set = decode_state(animal_pos);
    return all_of(animal_pos_set.begin(), animal_pos_set.end(), [](pair<int, int> animal) {
        return animal_separated(animal.first, animal.second);
    });
}


bool in_hole(int r, int c) {
    bool ret = true;
    queue<pair<int, int>> q;
    q.push(make_pair(r, c));
    vis[r][c] = 1;
    while (!q.empty()) {
        auto F = q.front();
        q.pop();
        if (ret && (F.first == 1 || F.first == N || F.second == 1 || F.second == M))ret = false;
        for (int k = 0; k < 4; ++k) {
            int x = F.first + nx[k], y = F.second + ny[k];
            if (valid(x, N) && valid(y, M) && zoo[x][y] != OBSTACLE && !vis[x][y]) {
                vis[x][y] = 1;
                q.push(make_pair(x, y));
            }
        }
    }
    return ret;
}

int cnt_hole() {
    memset(vis, 0, sizeof vis);
    int num_hole = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; j++) {
            if (zoo[i][j] == OBSTACLE || vis[i][j])continue;
            num_hole += in_hole(i, j);
        }
    }
    return num_hole;
}

bool judge() {
    return cnt_hole() == H && animals_separated();
}

ll encode_state(int r, int c) {
    return 1ll << std::hash<pair<int, int>>()(make_pair(r, c));
}


void search_solutions(int r, int c, ll cur_state) {
    ll nxt_state = cur_state | encode_state(r, c);
    if (has_been_searched(nxt_state))return;
    searched_states.insert(nxt_state);
    zoo[r][c] = OBSTACLE;
    cnt++;
    if (cnt == K) {
        if (judge())num_solution++;
    } else if (cnt < K) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; j++) {
                if (zoo[i][j] == OBSTACLE) {
                    for (int k = 0; k < 4; ++k) {
                        int x = nx[k] + i, y = ny[k] + j;
                        if (valid(x, N) && valid(y, M) && zoo[x][y] == GROUND)search_solutions(x, y, nxt_state);
                    }
                }
            }
        }
    }
    zoo[r][c] = GROUND;
    cnt--;
}

void solve() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; j++) {
            if (zoo[i][j] == ANIMAL)continue;
            search_solutions(i, j, 0);
        }
    }
    cout << num_solution;
}

int main() {
//    freopen("case.txt", "r", stdin);
    cin >> N >> M >> K >> H;
    getchar();
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            char c = getchar();
            if (c == 'O') {
//                index starting from 1
                animal_pos |= encode_state(i, j);
                zoo[i][j] = ANIMAL;
            }
        }
        getchar();
    }
    solve();
    return 0;
}