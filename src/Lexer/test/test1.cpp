#include <iostream>

using namespace std;

// Positive String and Char TestCases

int main() {
    // ✅ Valid character literals
    char a = 'A';
    char b = '9';
    char c = '\n';   // Newline character
    char d = '\'';   // Single quote inside char
    char e = '\\';   // Backslash inside char

    // ✅ Valid string literals
    string str1 = "Hello, World!";
    string str2 = "String with escape sequences: \t \n \" \\ ";
    string str3 = "This is a long string to test lexing.";
    string str4 = "";  // Empty string (valid)
    string str5 = "dfe\"eds\'fes'"

    // ✅ Multi-line raw string (C++11+)
    string multiline = R"(Thi\ns is a
    mult\ni-line
    st\nring.)";

    string multiline2 = "Th\nis is a\
    mul\ni-line\
    st\tring.";


    return 0;
}
