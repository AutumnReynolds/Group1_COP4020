#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

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

    int choice;
    string fileName;
    std::unordered_set<string> dictionary;

    std::ifstream inFile("dictionary.txt");
    if (!inFile) {
        std::cerr << "Unable to open file dictionary.txt";
        return 1; // return with error
    }
    while(inFile) {
        string word;
        inFile >> word;
        dictionary.insert(word);
    }

    do{
        std::cout << "Please choose an option:" << endl;
        std::cout << "1. Open a file;" << endl;
        std::cout << "2. Save a file" << endl;
        std::cout << "3. Spell check a file" << endl;
        std::cout << "4. Exit" << endl;

        cin >> choice;  
        cin.ignore();  

        switch(choice){
            case 1:
                std::cout << "Please input the file name to open: ";
                std::getline(cin, fileName);
                if(fileName.empty()){
                    std::cout << "No file opened. Please open a file first." << endl;
                }
                else if(fileName == "back" || fileName == "Back"){
                continue;
                }
                else{
                    open(fileName);
                }
                break;
                
            case 2:
                std::cout << "Please input the file name to save: ";
                std::getline(cin, fileName);
                if(fileName.empty()){
                    std::cout << "No file opened. Please open a file first." << endl;
                }
                else if(fileName == "back" || fileName == "Back"){
                    break;
                }
                else{
                    save(fileName);
                }
                break;
            case 3:
                std::cout << "Please input the file name to spell check: ";
                std::getline(cin, fileName);
                if(fileName.empty()){
                    std::cout << "No file opened. Please open a file first." << endl;
                }
                else if(fileName == "back" || fileName == "Back"){
                    break;
                }
                else{
                    spellCheckHandler(fileName, dictionary);
                }
                break;
            case 4:
                std::cout << "Exiting the program." << endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << endl;
        }

    }while(choice != 4);

    return 0;
}