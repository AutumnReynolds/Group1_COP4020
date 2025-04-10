import os

def main():
    dictionary = set()

    try:
        with open("spellCheck_python/dictionary.txt", "r") as f:
            for line in f:
                dictionary.add(line.strip())
    except FileNotFoundError:
        print("Dictionary file not found.")
        return 1
    
    choice = None

    while choice != "4":
        print("1. Open a file")
        print("2. Save a file")
        print("3. Spell check a file")
        print("4. Exit")
        choice = input("Enter your choice: ")

        if choice == "1":
            fileName = input("Enter a file to open: ")
            if not fileName:
                print("Error: No file selected")
            elif fileName.lower() == "back":
                continue
            else:
                open(fileName)

        elif choice == "2":
            fileName = input("Enter a file to save: ")
            if not fileName:
                print("Error: No file selected")
            elif fileName.lower() == "back":
                continue
            else:
                save(fileName)

        elif choice == "3":
            fileName = input("Enter a file to spell check: ")
            if not fileName:
                print("Error: No file selected")
            elif fileName.lower() == "back":
                continue
            else:
                spellCheckHandler(fileName, dictionary)
        elif choice == "4":
            print("Exiting...")
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main()


def spellCheckHandler(fileName: str, dictionary: set[str]):
    import string

    try:
        with open(fileName, 'r') as file:
            input_text = file.read()
    except FileNotFoundError:
        print(f"Error: File '{fileName}' not found.")
        return

    # Convert input to lowercase
    lower_input = input_text.lower()

    # Split words by delimiters
    delimiters = set(" \n\t.,;!?-")
    words = []
    start = 0
    for i, char in enumerate(lower_input):
        if char in delimiters:
            if start != i:
                words.append(lower_input[start:i])
            start = i + 1
    if start < len(lower_input):
        words.append(lower_input[start:])

    # Adjacent keys mapping (QWERTY)
    adjacent_keys = {
        # Top row of keyboard
        'q': ['w'], 
        'w': ['q', 'e'], 
        'e': ['w', 'r'], 
        'r': ['e', 't'], 
        't': ['r', 'y'],
        'y': ['t', 'u'], 
        'u': ['y', 'i'], 
        'i': ['u', 'o'], 
        'o': ['i', 'p'], 
        'p': ['o'],

        # Middle row of keyboard
        'a': ['s'], 
        's': ['a', 'd'], 
        'd': ['s', 'f'], 
        'f': ['d', 'g'], 
        'g': ['f', 'h'],
        'h': ['g', 'j'], 
        'j': ['h', 'k'], 
        'k': ['j', 'l'], 
        'l': ['k'],

        # Bottom row of keyboard
        'z': ['x'], 
        'x': ['z', 'c'], 
        'c': ['x', 'v'], 
        'v': ['c', 'b'],
        'b': ['v', 'n'], 
        'n': ['b', 'm'], 
        'm': ['n']
    }

    for word in words:
        if word and word not in dictionary:
            misspelled_words = set()

            # One letter added
            for i in range(len(word) + 1):
                for d in string.ascii_lowercase:
                    new_word = word[:i] + d + word[i:]
                    if new_word in dictionary:
                        misspelled_words.add(new_word)

            # One letter missing
            for i in range(len(word)):
                new_word = word[:i] + word[i + 1:]
                if new_word in dictionary:
                    misspelled_words.add(new_word)

            # One letter swapped with adjacent key
            for i, char in enumerate(word):
                if char in adjacent_keys:
                    for adjacent in adjacent_keys[char]:
                        swapped = word[:i] + adjacent + word[i+1:]
                        if swapped in dictionary:
                            misspelled_words.add(swapped)

            # Two adjacent letters swapped (transposition)
            for i in range(len(word) - 1):
                transposed = list(word)
                transposed[i], transposed[i + 1] = transposed[i + 1], transposed[i]
                transposed_word = ''.join(transposed)
                if transposed_word in dictionary:
                    misspelled_words.add(transposed_word)

            if misspelled_words:
                print(f"Misspelling: {word}\nSuggestions: {' '.join(misspelled_words)}\n")