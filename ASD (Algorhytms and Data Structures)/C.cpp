#include <bits/stdc++.h>

using namespace std;
int t;
string s;
bool apfelmann_win(string s) {
    int coconut;
    int left_position;
    int right_position;
    bool result = 0;
    if(s[0] == s[s.size() - 1]) return (s[0] == 'B');
    if(s[0] == 'C') return (s[s.size() - 1] == 'B');
    if(s[s.size() - 1] == 'C') return (s[0] == 'B');
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'C') coconut = i;
    }
    left_position = coconut - 1;
    right_position = coconut + 1;
    if(s[0] == 'A') {
        bool end = 0;
        while(!end) {
            if(s[left_position] == 'A') left_position--;
            else if(s[right_position] == 'A') right_position++;
            if(left_position == -1) {
                end = 1;
                result = 1;
            }
            if(right_position == s.size()) {
                end = 1;
                result = 0;
            }
            if(end) break;
            if(s[right_position] == 'B') right_position++;
            else if(s[left_position] == 'B') left_position--;
            if(left_position == -1) {
                end = 1;
                result = 1;
            }
            if(right_position == s.size()) {
                end = 1;
                result = 0;
            }
        }
    } else {
        bool end = 0;
        while(!end) {
            if(s[right_position] == 'A') right_position++;
            else if(s[left_position] == 'A') left_position--;
            if(left_position == -1) {
                end = 1;
                result = 0;
            }
            if(right_position == s.size()) {
                end = 1;
                result = 1;
            }
            if(end) break;
            if(s[left_position] == 'B') left_position--;
            else if(s[right_position] == 'B') right_position++;
            if(left_position == -1) {
                end = 1;
                result = 0;
            }
            if(right_position == s.size()) {
                end = 1;
                result = 1;
            }
        }        
    }

    return result;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> s;
        cout << (apfelmann_win(s) ? "Apfelmann" : "Bananenfrau") << endl;
    }
    return 0;
}