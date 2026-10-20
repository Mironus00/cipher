#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <limits>

void encryptWord(const char* original, char* encrypted, int key) {
    int i = 0;

    while (original[i] != '\0') {
        encrypted[i] = static_cast<char>('a' + (original[i] - 'a' + key) % 26);
        i++;
    }

    encrypted[i] = '\0';
}

void revealOneLetter(const char* original, char* encrypted) {
    while (*original != '\0') {
        if (*original != *encrypted) {
            *encrypted = *original;
            return;
        }

        original++;
        encrypted++;
    }
}

bool checkAnswer(const char* userGuess, const char* original, int& attempts) {
    if (std::strcmp(userGuess, original) == 0) {
        return true;
    }

    attempts--;
    return false;
}

int main() {
    static const char original[] = "planet";
    char encrypted[sizeof(original)] = {};
    char userGuess[100] = {};
    int attempts = 3;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int key = std::rand() % 5 + 1;

    encryptWord(original, encrypted, key);

    std::cout << "guess the original word. you have 3 attempts.\n";
    std::cout << "use lowercase english letters.\n";
    std::cout << "type hint to reveal one letter without losing an attempt.\n";

    while (attempts > 0) {
        std::cout << "\ncipher: " << encrypted << '\n';
        std::cout << "attempts left: " << attempts << '\n';
        std::cout << "your answer: ";

        std::cin.getline(userGuess, sizeof(userGuess));

        if (std::cin.eof() || std::cin.bad()) {
            std::cout << "\ninput ended.\n";
            return 0;
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "input is too long. maximum: 99 characters.\n";
            continue;
        }

        if (std::strcmp(userGuess, "hint") == 0) {
            revealOneLetter(original, encrypted);
            std::cout << "hint: " << encrypted << '\n';
            continue;
        }

        if (checkAnswer(userGuess, original, attempts)) {
            std::cout << "you win! the word is: " << original << '\n';
            return 0;
        }

        std::cout << "wrong answer!\n";
    }

    std::cout << "you lose! the word was: " << original << '\n';
    return 0;
}