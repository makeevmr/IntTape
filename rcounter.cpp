#include <fstream>
#include <iostream>

int main() {
    std::ifstream input_file("operations.txt", std::ios::binary);
    char new_symbol = 0;
    u_int64_t r_counter = 0;
    if (input_file.is_open()) {
        while (input_file.peek() != EOF) {
            input_file.get(new_symbol);
            if (new_symbol == 'r') {
                ++r_counter;
            }
        }
    }
    std::cout << r_counter << '\n';
    input_file.close();
    return 0;
}