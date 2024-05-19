#include <fstream>

int main() {
    char symbol = 'a';
    std::ofstream output_data("data_fstream.txt", std::ios::binary);
    u_int64_t max_symbols = 16777261;
    u_int64_t current_symbol = 0;
    while (current_symbol < max_symbols) {
        ++current_symbol;
        output_data << symbol;
        ++symbol;
        if (symbol > 'z') {
            symbol = 'a';
        }
    }
    return 0;
}