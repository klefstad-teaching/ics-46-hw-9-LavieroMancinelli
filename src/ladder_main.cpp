#include "ladder.h"

int main() {
    string w1 = "john";
    string w2 = "doe";

    set<string> wordList;
    string fileName = "./src/words.txt";
    load_words(wordList, fileName);
    vector<string> ladder = generate_word_ladder(w1, w2, wordList);
    print_word_ladder(ladder);
    
    return 0;
}
