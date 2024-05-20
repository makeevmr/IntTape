#include "src/Encode/Encode.h"
#include "src/Tape/Tape.h"

int main() {
    // encode("input/input3.txt");
    Tape int_tape("tmp/tape.txt");
    unsigned int prev_number = int_tape.read();
    int_tape.moveRight();
    unsigned int iterations = 16777261;
    unsigned int curr_iter = 2;
    while (curr_iter < iterations) {
        unsigned int curr_number = int_tape.read();
        int_tape.moveRight();
        if (curr_number < prev_number) {
            std::cout << "ERROR\n";
        }
        prev_number = curr_number;
        ++curr_iter;
    }
    // char operation = 0;
    // while (true) {
    //     std::cin >> operation;
    //     switch (operation) {
    //     case '-':
    //         int_tape.moveLeft();
    //         break;
    //     case '+':
    //         int_tape.moveRight();
    //         break;
    //     case 'r':
    //         std::cout << int_tape.read() << '\n';
    //         break;
    //     case 'w':
    //         unsigned int new_number = 0;
    //         std::cin >> new_number;
    //         int_tape.write(new_number);
    //         break;
    //     }
    // }
    return 0;
}
