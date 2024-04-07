#include <bits/stdc++.h>
#define MAX_VERTICES 100506
#define INF 1000002137
#define st first
#define nd second
using namespace std;
int t,n, p[MAX_VERTICES], v[MAX_VERTICES], tree_pow2, tree[4 * MAX_VERTICES], priority_to_id[MAX_VERTICES];
int start_ind[MAX_VERTICES], end_ind[MAX_VERTICES];
pair<int, int> given_priorities[MAX_VERTICES];
vector <int> sons[MAX_VERTICES];
void scale_priorities() {
    for(int i = 0; i < n; i++) {
        given_priorities[i].st = v[i + 1];
        given_priorities[i].nd = i + 1;
    }
    sort(given_priorities, given_priorities + n);
    for(int i = 0; i < n; i++) {
        v[given_priorities[i].nd] = i + 1;
        priority_to_id[i + 1] = given_priorities[i].nd;
    }
}
void initialize_tree(int size) {
    tree_pow2 = 1;
    while(tree_pow2 <= size + 1) tree_pow2 *= 2;
    for(int i = 1; i < 2 * tree_pow2; i++) {
        tree[i] = INF;
    }
}
void tree_insert(int position, int value) {
    position += tree_pow2;
    tree[position] = value;
    position /= 2;
    while(position != 0) {
        tree[position] = min(tree[2 * position], tree[2 * position + 1]);
        position /= 2;
    }
}
int tree_query(int begin, int end) {
    if(begin > end) return INF;
    if(begin == end) return tree[begin + tree_pow2];
    begin += tree_pow2;
    end += tree_pow2;
    int result = INF;
    result = min(result, tree[begin]);
    result = min(result, tree[end]);
    while(end - begin > 1) {
        if(begin % 2 == 0) result = min(result, tree[begin + 1]);
        if(end % 2 == 1) result = min(result, tree[end - 1]);
        begin /= 2;
        end /= 2;
    }
    return result;
}
int prefix_postfix_rec(int id, int entry_id) {
    int end_id = entry_id;
    start_ind[id] = entry_id;
    for(int i = 0; i < sons[id].size(); i++) {
        end_id = prefix_postfix_rec(sons[id][i], end_id + 1);
    }
    end_ind[id] = end_id;
    return end_id;
}
void prefix_postfix() {
    prefix_postfix_rec(1, 0);
}
void insert_initial_values() {
    initialize_tree(n);
    for(int i = 1; i <= n; i++) {
        tree_insert(start_ind[i], v[i]);
    }
}
//Exclude the root
int lowest_in_subtree_exclude(int vertex) {
    return tree_query(start_ind[vertex] + 1, end_ind[vertex]);
}
int lowest_in_subtree(int vertex) {
    return tree_query(start_ind[vertex], end_ind[vertex]);    
}
void write_result(int root) {
    while(lowest_in_subtree_exclude(root) != INF) {
        write_result(priority_to_id[lowest_in_subtree_exclude(root)]);
    }
    cout << root << " ";
    tree_insert(start_ind[root], INF);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 2; i <= n; i++) {
        cin >> p[i];
        sons[p[i]].push_back(i);
    }
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    scale_priorities();
    prefix_postfix();
    insert_initial_values();
    write_result(1);

}