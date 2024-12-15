#include <iostream>

extern "C" {
    void rusL() {
        setlocale(LC_ALL, "RUS");
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
