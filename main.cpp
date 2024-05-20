#include "src/Encode/Encode.h"
#include "src/Tape/Tape.h"

int main() {
    encode("input/input2.txt");
    Tape int_tape("tmp/tape.txt");
    char operation = 0;
    while (true) {
        std::cin >> operation;
        switch (operation) {
        case '-':
            int_tape.moveLeft();
            break;
        case '+':
            int_tape.moveRight();
            break;
        case 'r':
            std::cout << int_tape.read() << '\n';
            break;
        case 'w':
            unsigned int new_number = 0;
            std::cin >> new_number;
            int_tape.write(new_number);
            break;
        }
    }
    return 0;
}
