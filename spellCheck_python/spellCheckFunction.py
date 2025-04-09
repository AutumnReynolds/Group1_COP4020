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

