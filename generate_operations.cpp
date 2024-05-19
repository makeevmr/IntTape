#include <fstream>
#include <random>

int main() {
    srand(time(NULL));
    std::ofstream output_file("operations.txt", std::ios::binary);
    char operation = 'r';
    u_int64_t max_symbols = 16777261;
    u_int64_t curr_symbol = 0;
    while (curr_symbol < max_symbols) {
        int operation = (rand() % 4);
        switch (operation) {
        case 0:
            output_file << 'r';
            break;
        case 1:
            output_file << '-';
            break;
        case 2:
            output_file << '+';
            break;
        case 3:
            output_file << 'w';
            output_file << static_cast<char>((rand() % 26) + 97);
        }
        ++curr_symbol;
    }
    output_file.close();
    // std::ofstream output_file("operations.txt", std::ios::binary);
    // u_int64_t max_symbols = 2 * 16777261 - 1;
    // u_int64_t curr_symbol = 0;
    // while (curr_symbol < max_symbols) {
    //     if (curr_symbol % 2 == 0) {
    //         output_file << 'r';
    //     } else {
    //         output_file << '+';
    //     }
    //     ++curr_symbol;
    // }
    // curr_symbol = 0;
    // while (curr_symbol < max_symbols) {
    //     if (curr_symbol % 2 == 0) {
    //         output_file << 'r';
    //     } else {
    //         output_file << '-';
    //     }
    //     ++curr_symbol;
    // }
    // output_file.close();
    return 0;
}