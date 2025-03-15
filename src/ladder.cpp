#include "ladder.h"

bool is_adjacent(const string& word1, const string& word2) {
    int len = word1.length();
    if (len != word2.length()) return edit_distance_within(word1, word2, 1);
    int differences = 0;
    for (int i = 0; i < len; ++i) {
        if (word1[i] != word2[i]) {
            differences++;
            if (differences > 1) return false;
        }
    }
    return true;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string s; in >> s;) word_list.insert(s);
}

void print_word_ladder(const vector<string>& ladder) {
    for (auto& s : ladder)
        cout << s << " ";
    cout << endl;
}

// distance used is <= 1
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    /*queue<vector<int>> queue;
    int m = str1.length(), n = str2.length();
    queue.push({m,n,0});

    while (!queue.empty()) {
        vector<int> cur = queue.front();
        int i = cur[0], j = cur[1], w = cur[2]; // index in str1, str2, and weight
        queue.pop();
        if (w > d) continue;            // ignore if exceeds max distance
        if (i == 0) return w + j <= d;
        if (j == 0) return w + i <= d;
        if (str1[i-1] == str2[j-1])     // chars match, no distance added
            queue.push({i-1, j-1, w});
        else {
            if (w + 1 <= d) queue.push({i, j-1, w+1});      // insert 
            if (w + 1 <= d) queue.push({i-1, j, w+1});      // remove
            if (w + 1 <= d) queue.push({i-1, j-1, w+1});    // susbtitute
        }
    }

    return false;
    */
    // adapted from geeksforfeeks
    int m = str1.length(), n = str2.length();
    // [0][0] is empty string
    vector<vector<int>> distance(m+1, vector<int>(n+1)); // distance from m to n up to this char
    
    for (int i = 0; i <= m; ++i) distance[i][0] = i; // distance from empty to this char
    for (int i = 0; i <= n; ++i) distance[0][i] = i;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i-1] == str2[j-1]) distance[i][j] = distance[i-1][j-1];
            else distance[i][j] = 1 + min(distance[i-1][j], min(distance[i-1][j-1], distance[i][j-1]));
        }
    }

    return distance[m][n] <= d;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {end_word};
    if (word_list.find(end_word) == word_list.end()) return {};

    set<string> not_visited = word_list;
    not_visited.erase(begin_word);
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = *(--ladder.end());
        for (auto it = not_visited.begin(); it != not_visited.end();) {
            string word = *it;
            if (is_adjacent(last_word, word)) {
                it = not_visited.erase(it);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
            } else ++it;
        }
    }
    return {}; // empty vector<string>
}

void error(string word1, string word2, string msg) {
    if (word1 != "" && word2 != "") cerr << "ERROR: " << word1 << " and " << word2 << " " << msg << endl;
    else cerr << "ERROR: " << msg << endl;
}

void verify_word_ladder() {
 // not sure what this is meant to do because no params or return
}