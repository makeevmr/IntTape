#include "convert_file/include/convert_file.hpp"
#include "delay_parse/include/delay_parse.hpp"
#include "sort_tape/include/sort_tape.hpp"

#include <fstream>

#include <gtest/gtest.h>

static constexpr const char* kTmpInputTape = "../tmp/input_tape.txt";
static constexpr const char* kTmpOutputTape = "../tmp/output_tape.txt";
static constexpr const char* kDelay = "../config/delay.txt";

void sort(const char* input_file_name, const char* output_file_name) {
    TapeDelays delays = delayParse(kDelay);
    encode(input_file_name, kTmpInputTape);
    SortTape::sort(kTmpInputTape, kTmpOutputTape, delays);
    decode(kTmpOutputTape, output_file_name);
}

void compare(const char* input_file_name, const char* output_file_name) {
    std::ifstream input_file(input_file_name, std::ios::binary);
    std::vector<uint32_t> sorted_array;
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
    const char* input_file_name = "../input/input1.txt";
    const char* output_file_name = "../output/output1.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input2) {
    const char* input_file_name = "../input/input2.txt";
    const char* output_file_name = "../output/output2.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input3) {
    const char* input_file_name = "../input/input3.txt";
    const char* output_file_name = "../output/output3.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input4) {
    const char* input_file_name = "../input/input4.txt";
    const char* output_file_name = "../output/output4.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input5) {
    const char* input_file_name = "../input/input5.txt";
    const char* output_file_name = "../output/output5.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input6) {
    const char* input_file_name = "../input/input6.txt";
    const char* output_file_name = "../output/output6.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input7) {
    const char* input_file_name = "../input/input7.txt";
    const char* output_file_name = "../output/output7.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}
TEST(TestTape, Input8) {
    const char* input_file_name = "../input/input8.txt";
    const char* output_file_name = "../output/output8.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input9) {
    const char* input_file_name = "../input/input9.txt";
    const char* output_file_name = "../output/output9.txt";
    compare(input_file_name, output_file_name);
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input10) {
    const char* input_file_name = "../input/input10.txt";
    const char* output_file_name = "../output/output10.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input11) {
    const char* input_file_name = "../input/input11.txt";
    const char* output_file_name = "../output/output11.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input12) {
    const char* input_file_name = "../input/input12.txt";
    const char* output_file_name = "../output/output12.txt";
    try {
        sort(input_file_name, output_file_name);
        compare(input_file_name, output_file_name);
    } catch (const std::exception& err) {
        std::cerr << err.what();
    }
}

TEST(TestTape, Input13) {
    const char* input_file_name = "../input/input13.txt";
    const char* output_file_name = "../output/output13.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

TEST(TestTape, Input14) {
    const char* input_file_name = "../input/input14.txt";
    const char* output_file_name = "../output/output14.txt";
    EXPECT_NO_THROW(sort(input_file_name, output_file_name));
    compare(input_file_name, output_file_name);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
