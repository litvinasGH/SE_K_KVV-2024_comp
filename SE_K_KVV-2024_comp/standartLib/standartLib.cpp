#include <iostream>

extern "C" {
    void rusL() {
        setlocale(LC_ALL, "RUS");
    }

    bool strEq(char* a, char* b) {
        if (a[1] != b[1])
            return false;
        for (int i = 1; a[i - 1] != '\0' && b[i - 1] != '\0'; i++) {
            if (a[i] != b[i])
                return false;
        }
        return true;
    }

    char* findWord(char* a, int n) {
        int j = 0;
        char* result = new char[255];
        int sym = 0;
        for (int i = 0; ; i++) {
            if (a[i] == ' ') {
                j++;
            }
            else if (a[i] == '\0') {
                return (char*)"";
            }
            if (j == n - 1) {
                for (int k = i + 1; a[k] != '\0' && a[k] != ' '; k++) {
                    result[sym++] == a[k];
                }
                result[sym] == '\0';
                break;
            }
        }
        return result;
    }

    void OutputInt(int i) {
        std::cout << i << std::endl;
    }

    void OutputChar(char* ptr) {
        if (ptr == nullptr) {
            return;
        }
        for (int i = 0; ptr[i] != '\0'; i++) {
            std::cout << ptr[i];
        }
        std::cout << std::endl;
    }

    int InputInt() {
        int r;
        std::cin >> r;
        return r;
    }
}
