#include <fstream>

int main() {
    std::ofstream output_data("input/input3.txt", std::ios::binary);
    u_int64_t max_int = 16777261;
    u_int64_t curr_int = 1;
    while (curr_int <= max_int) {
        output_data << curr_int << '\n';
        ++curr_int;
    }
    return 0;
}