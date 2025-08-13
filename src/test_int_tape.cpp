#include "convert_file/convert_file.hpp"
#include "delay_parse/delay_parse.hpp"
#include "sort_tape/sort_tape.hpp"

#include <fstream>

#include <gtest/gtest.h>

static constexpr const char* kTmpInputTape = "../tmp/input_tape.txt";
static constexpr const char* kTmpOutputTape = "../tmp/output_tape.txt";
static constexpr const char* kDelay = "../config/delay.txt";

void sort(const char* input_file_name, const char* output_file_name,
          const std::size_t max_ram_used) {
    TapeDelays delays = delayParse(kDelay);
    encode(input_file_name, kTmpInputTape);
    SortTape::sortTape(kTmpInputTape, kTmpOutputTape, max_ram_used, delays);
    decode(kTmpOutputTape, output_file_name);
}

void compare(const char* correct_file_name, const char* output_file_name) {
    std::ifstream correct_file(correct_file_name, std::ios::binary);
    std::ifstream output_file(output_file_name, std::ios::binary);
    EXPECT_TRUE(correct_file.is_open());
    EXPECT_TRUE(output_file.is_open());
    uint32_t correct_file_num = 0;
    uint32_t output_file_num = 0;
    while ((correct_file.peek() != EOF) && (output_file.peek() != EOF)) {
        correct_file >> correct_file_num;
        output_file >> output_file_num;
        EXPECT_EQ(correct_file_num, output_file_num);
    }
    EXPECT_TRUE(correct_file.peek() == EOF);
    EXPECT_TRUE(output_file.peek() == EOF);
    correct_file.close();
    output_file.close();
}

TEST(TestTape, Input1) {
    const char* input_file_name = "../input/input1.txt";
    const char* output_file_name = "../output/output1.txt";
    const char* correct_file_name = "../output/correct1.txt";
    std::size_t max_ram_used = 10;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input2) {
    const char* input_file_name = "../input/input2.txt";
    const char* output_file_name = "../output/output2.txt";
    const char* correct_file_name = "../output/correct2.txt";
    std::size_t max_ram_used = 0;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input3) {
    const char* input_file_name = "../input/input3.txt";
    const char* output_file_name = "../output/output3.txt";
    const char* correct_file_name = "../output/correct3.txt";
    std::size_t max_ram_used = 8;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input4) {
    const char* input_file_name = "../input/input4.txt";
    const char* output_file_name = "../output/output4.txt";
    const char* correct_file_name = "../output/correct4.txt";
    std::size_t max_ram_used = 7;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input5) {
    const char* input_file_name = "../input/input5.txt";
    const char* output_file_name = "../output/output5.txt";
    const char* correct_file_name = "../output/correct5.txt";
    std::size_t max_ram_used = 0;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input6) {
    const char* input_file_name = "../input/input6.txt";
    const char* output_file_name = "../output/output6.txt";
    const char* correct_file_name = "../output/correct6.txt";
    std::size_t max_ram_used = 1000;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input7) {
    const char* input_file_name = "../input/input7.txt";
    const char* output_file_name = "../output/output7.txt";
    const char* correct_file_name = "../output/correct7.txt";
    std::size_t max_ram_used = 1024;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input8) {
    const char* input_file_name = "../input/input8.txt";
    const char* output_file_name = "../output/output8.txt";
    const char* correct_file_name = "../output/correct8.txt";
    std::size_t max_ram_used = 5000;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input9) {
    const char* input_file_name = "../input/input9.txt";
    const char* output_file_name = "../output/output9.txt";
    const char* correct_file_name = "../output/correct9.txt";
    std::size_t max_ram_used = 5000;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input10) {
    const char* input_file_name = "../input/input10.txt";
    const char* output_file_name = "../output/output10.txt";
    const char* correct_file_name = "../output/correct10.txt";
    std::size_t max_ram_used = 5500;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input11) {
    const char* input_file_name = "../input/input11.txt";
    const char* output_file_name = "../output/output11.txt";
    const char* correct_file_name = "../output/correct11.txt";
    std::size_t max_ram_used = 6000;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input12) {
    const char* input_file_name = "../input/input12.txt";
    const char* output_file_name = "../output/output12.txt";
    const char* correct_file_name = "../output/correct12.txt";
    std::size_t max_ram_used = 6500;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input13) {
    const char* input_file_name = "../input/input13.txt";
    const char* output_file_name = "../output/output13.txt";
    const char* correct_file_name = "../output/correct13.txt";
    std::size_t max_ram_used = 7000;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

TEST(TestTape, Input14) {
    const char* input_file_name = "../input/input14.txt";
    const char* output_file_name = "../output/output14.txt";
    const char* correct_file_name = "../output/correct14.txt";
    std::size_t max_ram_used = 7500;
    EXPECT_NO_THROW(sort(input_file_name, output_file_name, max_ram_used));
    compare(correct_file_name, output_file_name);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
