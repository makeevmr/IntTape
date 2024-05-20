#include "src/ConvertFile/ConvertFile.h"
#include "src/DelayParse/DelayParse.h"
#include "src/SortTape/SortTape.h"

// ./IntTape input/input2.txt output/output2.txt config/delay.txt
int main(int argc, char *argv[]) {
    const char *tape_file = "tmp/tape.txt";
    TapeDelays delays = delayParse(argv[argc - 1]);
    const char *input_file = argv[argc - 3];
    const char *output_file = argv[argc - 2];
    encode(input_file, tape_file);
    Tape int_tape(tape_file, delays);
    SortTape::sort(int_tape);
    decode(tape_file, output_file);

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
    // std::cout << "READY\n";
    // char operation = 0;
    // unsigned int number = 0;
    // while (true) {
    //     std::cin >> operation;
    //     switch (operation) {
    //     case '-':
    //         int_tape.shiftLeft();
    //         break;
    //     case '+':
    //         int_tape.shiftRight();
    //         break;
    //     case 'L':
    //         std::cin >> number;
    //         int_tape.rewindLeft(number);
    //         break;
    //     case 'R':
    //         std::cin >> number;
    //         int_tape.rewindRight(number);
    //         break;
    //     case 'r':
    //         std::cout << int_tape.read() << '\n';
    //         break;
    //     case 'w':
    //         std::cin >> number;
    //         int_tape.write(number);
    //         break;
    //     }
    // }
    return 0;
}
