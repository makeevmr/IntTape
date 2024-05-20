#include "src/DelayParse/DelayParse.h"
#include "src/Encode/Encode.h"
#include "src/Tape/Tape.h"

int main(int argc, char *argv[]) {
    TapeDelays delays = delayParse(argv[argc - 1]);
    const char *tape_file = "tmp/tape.txt";
    // TODO add output_file and change input_file
    const char *input_file = argv[argc - 2];
    encode(input_file, tape_file);
    Tape int_tape(tape_file, delays);

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
            int_tape.shiftLeft();
            break;
        case '+':
            int_tape.shiftRight();
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
