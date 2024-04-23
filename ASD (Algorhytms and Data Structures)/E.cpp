#include <bits/stdc++.h>

using namespace std;
int n,m,a,b,c,k,x[120][120], l[120], sum;
bool visited[60];
vector<int> neighbours[60];
vector<int> route_to_n;
bool dfs(int vertex) {
    visited[vertex] = 1;
    if(vertex == n) {
        route_to_n.push_back(vertex);
        return true;
    }
    bool res = 0;
    for(int i = 0; i < neighbours[vertex].size(); i++) {
        if(!visited[neighbours[vertex][i]]) {
            res = dfs(neighbours[vertex][i]);
            if(res) {
                route_to_n.push_back(vertex);
                return true;
            }
        }
    }
    return false;
}
int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        neighbours[b].push_back(a);
        neighbours[a].push_back(b);
    }
    cin >> k;
    for(int i = 0; i < k; i++) {
        cin >> l[i];
        for(int j = 0; j < l[i]; j++) {
            cin >> x[i][j];
        }
        for(int j = 0; j < l[i] - 2; j++) {
            x[i][j + l[i]] = x[i][l[i]-j-2];
        }
    }
    //We got reverse routes without 1 at the end
    if(!dfs(1)) {
        printf("-1");
        return 0;
    }
    sum = 0;
    for(int i = 0; i < k; i++) {
        sum += (2 * l[i] - 2);
    }
    sum += route_to_n.size();
    for(int i = 0; i < k; i++) {
        cout << sum << " ";
        for(int j = 0; j < 2 * l[i] - 2; j++) {
            cout << x[i][j] << " ";
        }
        for(int ii = 0; ii < k; ii++) {
            if(ii != i) {
                for(int j = 0; j < 2 * l[ii] - 2; j++) {
                    cout << x[ii][j] << " ";
                }
            }
        }
        for(int j = 0; j < route_to_n.size(); j++) {
            cout << route_to_n[route_to_n.size() - j - 1] << " ";
        }
        cout << endl;
    }
}