#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    long int file_ind = 0;
    std::ifstream operations_file("operations.txt", std::ios::binary);
    std::ofstream result_file("result_fstream.txt", std::ios::binary);
    std::fstream data_file;
    data_file.open("data_fstream.txt", std::ios::in | std::ios::out | std::ios::binary);
    // data_file.open("log.txt", std::ios::in | std::ios::out | std::ios::binary);
    auto start_pos = data_file.tellg();
    data_file.seekg(0, std::ios::end);
    auto file_size = data_file.tellg() - start_pos;
    std::cout << file_size << '\n';
    data_file.seekg(0, std::ios::beg);
    if (data_file.is_open() && operations_file.is_open() && result_file.is_open()) {
        char operation = 0;
        char new_symbol = 0;
        while (operations_file.peek() != EOF) {
            operations_file.get(operation);
            switch (operation) {
            case '-':
                if (file_ind > 0) {
                    data_file.seekg(-1, std::ios::cur);
                    --file_ind;
                }
                break;
            case '+':
                if (file_ind < file_size - 1) {
                    data_file.seekg(1, std::ios::cur);
                    ++file_ind;
                }
                break;
            case 'r':
                result_file << static_cast<char>(data_file.get());
                data_file.seekg(-1, std::ios::cur);
                break;
            case 'w':
                operations_file.get(new_symbol);
                data_file << new_symbol;
                data_file.seekg(-1, std::ios::cur);
                break;
            }
        }
    }
    data_file.close();
    operations_file.close();
    result_file.close();
}
