#include "ladder.h"

bool is_adjacent(const string& word1, const string& word2) {
    int len = word1.length();
    if (len != word2.length()) return edit_distance_within(word1, word2, 1);
    int differences = 0;
    for (int i = 0; i < len; ++i) {
        if (word1[i] != word2[i]) {
            ++differences;
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
    if (ladder.size() > 0) {
        cout << "Word ladder found: ";
        for (auto& s : ladder)
            cout << s << " ";
    } else 
        cout << "No word ladder found.";
    cout << endl;
}

// distance used is <= 1
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int i = 0, j = 0, len1 = str1.length(), len2 = str2.length(), differences = 0;
    if (abs(len2-len1) > 1) return false;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            differences++;
            if (differences > d) return false;
            if (len1 > len2) ++i;
            else if (len1 < len2) ++j;
            else { ++i; ++j; };
        } else {
            ++i;
            ++j;
        }
    }
    return differences + (len1 - i) + (len2 - j) <= d;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};
    if (word_list.find(end_word) == word_list.end()) return {};
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = *(--ladder.end());
        for (auto word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {}; // empty vector<string>
}

void error(string word1, string word2, string msg) {
    if (word1 != "" && word2 != "") cerr << "ERROR: " << word1 << " and " << word2 << " " << msg << endl;
    else cerr << "ERROR: " << msg << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}