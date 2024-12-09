#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void displayWord(char word[], int length, int correctGuesses[]) {
    for (int i = 0; i < length; i++) {
        if (correctGuesses[i]) {
            printf("%c", word[i]);
        } else {
            printf("_");
        }
    }
    printf("\n");
}

void displayEnhancedHangman(int wrongGuesses, int maxAttempts) {
    const char *stages[] = {
        "  _______\n  |     |\n  |\n  |\n  |\n__|__\n",                  // Stage 0
        "  _______\n  |     |\n  |     O\n  |\n  |\n__|__\n",               // Stage 1
        "  _______\n  |     |\n  |     O\n  |     |\n  |\n__|__\n",          // Stage 2
        "  _______\n  |     |\n  |     O\n  |    /|\n  |\n__|__\n",          // Stage 3
        "  _______\n  |     |\n  |     O\n  |    /|\\\n  |\n__|__\n",         // Stage 4
        "  _______\n  |     |\n  |     O\n  |    /|\\\n  |    /\n__|__\n",    // Stage 5
        "  _______\n  |     |\n  |     O\n  |    /|\\\n  |    / \\\n__|__\n"  // Final stage
    };

    int numStages = sizeof(stages) / sizeof(stages[0]);
    int scaledIndex = (wrongGuesses * (numStages - 1)) / maxAttempts;
    printf("%s\n", stages[scaledIndex]);
}

void selectWord(char word[]) {
    const char *wordList[] = {"programming", "hangman", "difficulty", "challenge", "computer", "function", "eastwest"};
    int wordCount = sizeof(wordList) / sizeof(wordList[0]);

    srand(time(NULL));
    strcpy(word, wordList[rand() % wordCount]);
}

void playGame() {
    char word[50];
    selectWord(word);
    int length = strlen(word);

    int correctGuesses[length];
    for (int i = 0; i < length; i++) {
        correctGuesses[i] = 0;
    }

    int maxAttempts;
    int difficulty;

    printf("Select difficulty level:\n");
    printf("1. Easy (6 chances)\n");
    printf("2. Medium (4 chances)\n");
    printf("3. Hard (3 chances)\n");
    printf("Enter your choice: ");
    scanf("%d", &difficulty);

    if (difficulty == 1) {
        maxAttempts = 6;
    } else if (difficulty == 2) {
        maxAttempts = 4;
    } else {
        maxAttempts = 3;
    }

    int wrongGuesses = 0;
    char guess;
    int correct = 0;

    printf("\nGuess the word:\n");

    while (wrongGuesses < maxAttempts && correct < length) {
        displayWord(word, length, correctGuesses);
        displayEnhancedHangman(wrongGuesses, maxAttempts);
        printf("You have %d chances left.\n", maxAttempts - wrongGuesses);
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (!isalpha(guess)) {
            printf("Invalid input! Please enter a letter.\n");
            continue;
        }

        int found = 0;
        for (int i = 0; i < length; i++) {
            if (word[i] == guess && !correctGuesses[i]) {
                correctGuesses[i] = 1;
                correct++;
                found = 1;
            }
        }

        if (!found) {
            wrongGuesses++;
            printf("Incorrect guess! The man is closer to being hanged.\n");
        } else {
            printf("Good guess!\n");
        }

        printf("\n");
    }

    if (correct == length) {
        printf("Congratulations! You've saved the man!\n");
    } else {
        displayEnhancedHangman(maxAttempts, maxAttempts);
        printf("Sorry, you've run out of chances. The man is hanged.\n");
    }

    printf("The word was: %s\n", word);
}

int main() {
    char playAgain;

    do {
        printf("Welcome to Hangman!\n");
        playGame();
        printf("\nWould you like to play again? (y/n): ");
        scanf(" %c", &playAgain);
        playAgain = tolower(playAgain);
    } while (playAgain == 'y');

    printf("Thank you for playing Hangman! Goodbye!\n");
    return 0;
}
