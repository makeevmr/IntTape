#include "src/ConvertFile/ConvertFile.h"
#include "src/DelayParse/DelayParse.h"
#include "src/SortTape/SortTape.h"
#include <gtest/gtest.h>

#define INPUT_TAPE "tmp/input_tape.txt"
#define OUTPUT_TAPE "tmp/output_tape.txt"
#define DELAY "config/delay.txt"

void sort(const char *input_file_name, const char *output_file_name) {
    TapeDelays delays = delayParse(DELAY);
    encode(input_file_name, INPUT_TAPE);
    SortTape::sort(INPUT_TAPE, OUTPUT_TAPE, delays);
    decode(OUTPUT_TAPE, output_file_name);
}

void compare(const char *input_file_name, const char *output_file_name) {
    std::ifstream input_file(input_file_name, std::ios::binary);
    std::vector<unsigned int> sorted_array;
    if (input_file.is_open()) {
        unsigned int new_number = 0;
        while (input_file.peek() != EOF) {
            input_file >> new_number;
            input_file.get();
            sorted_array.push_back(new_number);
        }
    }
    std::sort(sorted_array.begin(), sorted_array.end());
    std::size_t compr_ind = 0;
    std::ifstream output_file(output_file_name, std::ios::binary);
    if (output_file.is_open()) {
        unsigned int new_number = 0;
        while (output_file.peek() != EOF) {
            output_file >> new_number;
            output_file.get();
            EXPECT_EQ(sorted_array[compr_ind++], new_number);
        }
    }
    EXPECT_EQ(compr_ind, sorted_array.size());
    input_file.close();
    output_file.close();
}

TEST(TestTape, Input1) {
    const char *input_file_name = "input/input1.txt";
    const char *output_file_name = "output/output1.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input2) {
    const char *input_file_name = "input/input2.txt";
    const char *output_file_name = "output/output2.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input3) {
    const char *input_file_name = "input/input3.txt";
    const char *output_file_name = "output/output3.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input4) {
    const char *input_file_name = "input/input4.txt";
    const char *output_file_name = "output/output4.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input5) {
    const char *input_file_name = "input/input5.txt";
    const char *output_file_name = "output/output5.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input6) {
    const char *input_file_name = "input/input6.txt";
    const char *output_file_name = "output/output6.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input7) {
    const char *input_file_name = "input/input7.txt";
    const char *output_file_name = "output/output7.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}
TEST(TestTape, Input8) {
    const char *input_file_name = "input/input8.txt";
    const char *output_file_name = "output/output8.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input9) {
    const char *input_file_name = "input/input9.txt";
    const char *output_file_name = "output/output9.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input10) {
    const char *input_file_name = "input/input10.txt";
    const char *output_file_name = "output/output10.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input11) {
    const char *input_file_name = "input/input11.txt";
    const char *output_file_name = "output/output11.txt";
    sort(input_file_name, output_file_name);
    compare(input_file_name, output_file_name);
}

