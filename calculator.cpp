#define _CRT_SECURE_NO_WARNINGS
#include "inf_int.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    cout << "Calculator Program (Type '0' to exit)" << endl;

    while (true) {
        cout << "Input: ";
        string input;
        getline(cin, input);

        if (input == "0") {
            break;
        }

        const char* input_cstr = input.c_str();

        
        const char* operand1_cstr = input_cstr;
        const char* op_cstr = strchr(input_cstr, ' ');

        if (!op_cstr) {
            cout << "Invalid input. Please enter a valid expression." << endl;
            continue;
        }

        int operand1_length = op_cstr - operand1_cstr;
        char* operand1_copy = new char[operand1_length + 1];
        strncpy(operand1_copy, operand1_cstr, operand1_length);
        operand1_copy[operand1_length] = '\0';

        const char* operand2_cstr = op_cstr + 3;  

        inf_int num1(operand1_copy);
        inf_int num2(operand2_cstr);

        delete[] operand1_copy;

        inf_int result;
        bool valid = true;

        inf_int rnum1 = num1;
        inf_int rnum2 = num2;

        switch (op_cstr[1]) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        default:
            cout << "Invalid operator. Please use +, -, or *." << endl;
            valid = false;
            break;
        }

        if (valid) {
            if (rnum1 == num1 && rnum2 == num2) {
                cout << "Result: " << result << endl;
            }
        }
    }

    cout << "Program terminated." << endl;

    return 0;
}
