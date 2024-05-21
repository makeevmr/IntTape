#include "src/ConvertFile/ConvertFile.h"
#include "src/DelayParse/DelayParse.h"
#include "src/SortTape/SortTape.h"

#define INPUT_TAPE "tmp/input_tape.txt"
#define OUTPUT_TAPE "tmp/output_tape.txt"

int main(int argc, char *argv[]) {
    const char *input_tape_file = INPUT_TAPE;
    const char *output_tape_file = OUTPUT_TAPE;
    TapeDelays delays = delayParse("config/delay.txt");
    const char *output_file = "output/output3.txt";
    const char *input_file = "input/input3.txt";
    // TapeDelays delays = delayParse(argv[argc - 1]);
    // const char *output_file = argv[argc - 2];
    // const char *input_file = argv[argc - 3];
    // std::cout << "Parsed\n";
    // encode(input_file, input_tape_file);
    encode(input_file, INPUT_TAPE);
    // std::cout << "Encoded\n";
    // Tape int_tape(input_tape_file, delays);
    // SortTape::sort(input_tape_file, output_tape_file, delays);
    SortTape::sort(INPUT_TAPE, OUTPUT_TAPE, delays);
    // std::cout << "Sorted\n";
    decode(OUTPUT_TAPE, output_file);
    // std::cout << "Decoded\n";
    // TapeDelays delays = delayParse("config/delay.txt");
    // const char *input_file = "input/input5.txt";
    // const char *output_file = "output/output5.txt";
    // std::cout << "Encode complete\n";
    // std::cout << "Tape formed\n";
    // std::cout << "sort\n";

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
