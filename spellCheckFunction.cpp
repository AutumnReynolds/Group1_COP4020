#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

void spellCheckHandler(const string& inputText, const unordered_set<string>& dictionary) {
    // Convert input text to lowercase for easier use
    string lowerInput = inputText;
    transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
    
    vector<string> words;
    size_t start = 0;
    size_t end;

    while ((end = lowerInput.find_first_of(" \n\t.,;!?-", start)) != std::string::npos) {
        if (start != end) {
            words.push_back(lowerInput.substr(start, end - start));
        }
        start = end + 1;
    }
    if (start < lowerInput.size()) {
        words.push_back(lowerInput.substr(start));
    }

    // Adjacent keys for U.S. keyboard
    unordered_map<char, std::vector<char> > adjacentKeys;
    // top row of keyboard
    adjacentKeys['q'] = {'w'}; 
    adjacentKeys['w'] = {'q', 'e'};
    adjacentKeys['e'] = {'w', 'r'};
    adjacentKeys['r'] = {'e', 't'};
    adjacentKeys['t'] = {'r', 'y'};
    adjacentKeys['y'] = {'t', 'u'};
    adjacentKeys['u'] = {'y', 'i'};
    adjacentKeys['i'] = {'u', 'o'};
    adjacentKeys['o'] = {'i', 'p'}; 
    adjacentKeys['p'] = {'o'};

    // middle row of keyboard
    adjacentKeys['a'] = {'s'}; 
    adjacentKeys['s'] = {'a', 'd'}; 
    adjacentKeys['d'] = {'s', 'f'};
    adjacentKeys['f'] = {'d', 'g'};
    adjacentKeys['g'] = {'f', 'h'}; 
    adjacentKeys['h'] = {'g', 'j'};
    adjacentKeys['j'] = {'h', 'k'}; 
    adjacentKeys['k'] = {'j', 'l'}; 
    adjacentKeys['l'] = {'k'};
    
    // bottom row of keyboard
    adjacentKeys['z'] = {'x'}; 
    adjacentKeys['x'] = {'z', 'c'}; 
    adjacentKeys['c'] = {'x', 'v'}; 
    adjacentKeys['v'] = {'c', 'b'}; 
    adjacentKeys['b'] = {'v', 'n'}; 
    adjacentKeys['n'] = {'b', 'm'};
    adjacentKeys['m'] = {'n'};
    


    for (const auto& word : words) {
        if (!dictionary.count(word)) {
            std::unordered_set<std::string> misspelledWords;

            // One letter added case
            for (size_t i = 0; i <= word.length(); ++i) {
                for (char d = 'a'; d <= 'z'; ++d) {
                    std::string newWord = word.substr(0, i) + d + word.substr(i);
                    if (dictionary.count(newWord)) {
                        misspelledWords.insert(newWord);

                    }
                }
                
            }

            // One letter missing case
            for (size_t i = 0; i < word.length(); ++i) {
                std::string newWord = word.substr(0, i) + word.substr(i + 1);
                if (dictionary.count(newWord)) {
                    misspelledWords.insert(newWord);
                }
            }

            // One letter swapped with an adjacent key case
            for (size_t i = 0; i < word.length(); ++i) {                
                char currentChar = word[i];
                if (adjacentKeys.count(currentChar)) {
                    for (char next : adjacentKeys[currentChar]) {
                        std::string swapped = word;
                        swapped[i] = next;
                        if (dictionary.count(swapped)) {
                            misspelledWords.insert(swapped);
                        }
                    }
                }
            }

            // Two adjacent letters swapped (transposition case)
            for (size_t i = 0; i < word.length() - 1; ++i) {
                std::string transposed = word;
                std::swap(transposed[i], transposed[i + 1]);
                if (dictionary.count(transposed)) {
                    misspelledWords.insert(transposed);
                }
            }

            // Output suggestions to terminal
            if (!misspelledWords.empty()) {
                std::cout << "Misspelling: " << word << "\nSuggestions: ";
                for (const auto& suggestion : misspelledWords) {
                    std::cout << suggestion << " ";
                }
                std::cout << "\n";
            }
        }
    }
}

int main() {
    // Example usage
    std::unordered_set<std::string> dictionary = {"hello", "world", "how", "are", "you", "neighbor", "today", "document", "word", "i", "am", "fine", "labor", "this", "just", "to", "see", "hope", "having", "a", "good", "day", "the", "weather", "weekend", "will", "be", "fabulous", "we", "spell", "check"};
    std::string inputText = "hello worl, how are you. We will spelll check this docuemnt just to see. I hope you are having a good day. The weather this weekend will be flabulous.";
    spellCheckHandler(inputText, dictionary);
    return 0;
}