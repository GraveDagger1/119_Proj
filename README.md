# README
This program processes a text file (input.txt) containing Roman numeral arithmetic expressions and outputs the results in English words to another text file (output.txt).
# Functionality
The program reads each line from input.txt, which should be in the format
"RomanNumeral1 Operator RomanNumeral2" (e.g., "IX + XI"). It then performs the following steps:

1.Input Preparation: Removes trailing newline characters from the input line.

2.Roman to Decimal Conversion: Converts the Roman numerals to their decimal equivalents
using the romanToDecimal function. Handles subtractive notation (e.g., IV = 4). Invalid Roman numerals result in an error message.

3.Arithmetic Operation: Performs the specified arithmetic operation (+, -, *, /). 
Note that multiplication and division are incorrectly implemented as addition.

4.Decimal to Words Conversion: Converts the decimal result to its 
English word representation using the decimalToWords function.

5.Output: Writes the result in words to output.txt. 
Invalid input lines generate error messages in the output file.

# Compilation and Execution
To compile and run the code (assuming you have a C compiler like VS code):
Save the code as a .c file (e.g., romanCalculate.c).
Create an input.txt file with your Roman numeral expressions, one per line.
Compile and Run

![image](https://github.com/user-attachments/assets/b605dc7f-5b44-4537-a1f9-d906484d5621)

The results will be written to output.txt.

![image](https://github.com/user-attachments/assets/d5a88438-723b-4a13-89de-3b3b00408c87)

