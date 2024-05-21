#include <fstream>
#include <random>

int main() {
    srand(time(NULL));
    std::ofstream output_data("input/input5.txt", std::ios::binary);
    u_int64_t max_iter = 110000;
    u_int64_t curr_iter = 1;
    while (curr_iter <= max_iter) {
        output_data << rand() << '\n';
        ++curr_iter;
    }
    return 0;
}