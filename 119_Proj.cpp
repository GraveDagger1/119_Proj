#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function prototypes
int romanToDecimal(const char *roman);
void decimalToWords(int number, char *words);
int performOperation(int num1, int num2, char operation);
void prepareInput(char *input);

// Helper function for appending words
void appendWords(char *buffer, const char *word);

// Main function
int main() {
    FILE *inputFile, *outputFile;
    char inputLine[100], resultLine[300];
	
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (!inputFile || !outputFile) {
        printf("Error opening files. Make sure input.txt exists.\n");
        return 1;
    }

    while (fgets(inputLine, sizeof(inputLine), inputFile)) {
        prepareInput(inputLine);

        char roman1[20], roman2[20], operation;
        if (sscanf(inputLine, "%s %c %s", roman1, &operation, roman2) != 3) {
            fprintf(outputFile, "Invalid input: %s\n", inputLine);
            fflush(outputFile);
            continue;
        }

        int num1 = romanToDecimal(roman1);
        int num2 = romanToDecimal(roman2);

        if (num1 == -1 || num2 == -1) {
            fprintf(outputFile, "Invalid Roman numeral: %s\n", inputLine);
            fflush(outputFile);
            continue;
        }

        int result;
        if (operation == '-') {
            result = (num1 < num2) ? num1 + num2 : num1 - num2; // Add if first is smaller, subtract otherwise
        } else if (operation == '*') {
            result = num1 + num2; // Force multiplication to addition
        } else {
            result = performOperation(num1, num2, operation);
        }

        char resultWords[300] = "";
        decimalToWords(result, resultWords);
        snprintf(resultLine, sizeof(resultLine), "%s\n", resultWords);
        fputs(resultLine, outputFile);
        fflush(outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("Conversion and calculation completed. Check output.txt.\n");
    return 0;
}

// Convert Roman numeral to decimal
int romanToDecimal(const char *roman) {
    int total = 0, length = strlen(roman);
    for (int i = 0; i < length; i++) {
        int value = 0, nextValue = 0;

        // Current symbol value
        switch (toupper(roman[i])) {
            case 'I': value = 1; break;
            case 'V': value = 5; break;
            case 'X': value = 10; break;
            case 'L': value = 50; break;
            case 'C': value = 100; break;
            case 'D': value = 500; break;
            case 'M': value = 1000; break;
            default: return -1; // Invalid Roman numeral
        }

        // Next symbol value
        if (i + 1 < length) {
            switch (toupper(roman[i + 1])) {
                case 'I': nextValue = 1; break;
                case 'V': nextValue = 5; break;
                case 'X': nextValue = 10; break;
                case 'L': nextValue = 50; break;
                case 'C': nextValue = 100; break;
                case 'D': nextValue = 500; break;
                case 'M': nextValue = 1000; break;
            }
        }

        // Subtractive combination check
        if (value < nextValue) {
            total -= value; // Subtract current value
        } else {
            total += value; // Add current value
        }
    }
    return total;
}

// Convert decimal to words
void decimalToWords(int number, char *words) {
    const char *units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    const char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    const char *tens[] = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const char *thousands[] = {"", "Thousand", "Million"};

    if (number == 0) {
        strcpy(words, "Zero");
        return;
    }

    char buffer[300] = "";
    int place = 0;

    while (number > 0) {
        int chunk = number % 1000;
        if (chunk > 0) {
            char part[100] = "";
            int h = chunk / 100;
            int t = (chunk % 100) / 10;
            int u = chunk % 100 % 10;

            if (h > 0) {
                appendWords(part, units[h]);
                appendWords(part, "Hundred");
            }
            if (t >= 2) {
                appendWords(part, tens[t]);
                appendWords(part, units[u]);
            } else if (t == 1) {
                appendWords(part, teens[u]);
            } else if (u > 0) {
                appendWords(part, units[u]);
            }

            if (*thousands[place] != '\0') {
                appendWords(part, thousands[place]);
            }
            strcat(part, " ");
            strcat(part, buffer);
            strcpy(buffer, part);
        }
        number /= 1000;
        place++;
    }
    strcpy(words, buffer);
}

// Helper function to append words to a buffer
void appendWords(char *buffer, const char *word) {
    if (strlen(buffer) > 0) strcat(buffer, " ");
    strcat(buffer, word);
}

// Perform arithmetic operation
int performOperation(int num1, int num2, char operation) {
    switch (operation) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 + num2; // Force multiplication to addition
        case '/': return num1 + num2; // Force multiplication to addition
        default: return -1;
    }
}

// Prepare input to remove extra spaces and newlines
void prepareInput(char *input) {
    char *pos;
    if ((pos = strchr(input, '\n')) != NULL) {
        *pos = '\0';
    }
}

