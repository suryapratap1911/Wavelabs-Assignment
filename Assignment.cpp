//Assignment SET-4


#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph(n);
    vector<int> ids(n, -1);
    vector<int> lows(n, -1);
    unordered_map<int, int> visited;
    vector<vector<int>> res;

    for (auto& c : connections) {
        graph[c[0]].push_back(c[1]);
        graph[c[1]].push_back(c[0]);
    }

    function<void(int, int)> dfs = [&](int cur, int prev) {
       
        visited[cur] = 1;
        ids[cur] = lows[cur] = visited.size();

        
        for (int nei : graph[cur]) {
            if (nei == prev) continue; 
            if (visited.count(nei) == 0) {
                dfs(nei, cur);
                lows[cur] = min(lows[cur], lows[nei]);
                if (lows[nei] > ids[cur])
                    res.push_back({cur, nei});
            } else {
                lows[cur] = min(lows[cur], ids[nei]);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (visited.count(i) == 0)
            dfs(i, -1);
    }

    return res;
}

int main() {
    int n = 4;
    vector<vector<int>> connections = {{0,1},{1,2},{2,0},{1,3}};
    vector<vector<int>> res = criticalConnections(n, connections);
    for (auto& c : res) {
        cout << "[" << c[0] << "," << c[1] << "]" << endl;
    }
    return 0;
}
