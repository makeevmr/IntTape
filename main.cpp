#include "src/Encode/Encode.h"
#include "src/Tape/Tape.h"

int main() {
    encode("input/input3.txt");
    Tape int_tape("tmp/tape.txt");
    // int_tape.moveRight();
    // unsigned int iterations = 16777261;
    // unsigned int curr_iter = 2;
    // while (curr_iter < iterations) {
    //     unsigned int curr_number = int_tape.read();
    //     int_tape.moveRight();
    //     if (curr_number != curr_iter) {
    //         std::cout << "ERROR\n";
    //     }
    //     ++curr_iter;
    // }
    std::cout << "READY\n";
    char operation = 0;
    unsigned int number = 0;
    while (true) {
        std::cin >> operation;
        switch (operation) {
        case '-':
            int_tape.moveLeft();
            break;
        case '+':
            int_tape.moveRight();
            break;
        case 'L':
            std::cin >> number;
            int_tape.rewindLeft(number);
            break;
        case 'R':
            std::cin >> number;
            int_tape.rewindRight(number);
            break;
        case 'r':
            std::cout << int_tape.read() << '\n';
            break;
        case 'w':
            std::cin >> number;
            int_tape.write(number);
            break;
        }
    }
    return 0;
}
