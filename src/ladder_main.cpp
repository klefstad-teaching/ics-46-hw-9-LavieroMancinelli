#include "ladder.h"

int main() {
    
    string w1 = "cat";
    string w2 = "dog";

    set<string> wordList;
    string fileName = "./src/words.txt";
    load_words(wordList, fileName);
    vector<string> ladder = generate_word_ladder(w1, w2, wordList);
    print_word_ladder(ladder);
    
    verify_word_ladder();
    return 0;
}
