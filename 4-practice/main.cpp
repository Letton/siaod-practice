#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>

const int N[3] = {10000, 100000, 1000000};

std::vector<int> PrefixFunction(const std::string &str) {
    auto m = str.length();
    std::vector<int> prefix(m, 0);
    int k = 0;
    for (int q = 1; q < m; q++) {
        while (k > 0 && str[k] != str[q]) {
            k = prefix[k - 1];
        }
        if (str[k] == str[q]) {
            k++;
        }
        prefix[q] = k;
    }
    return prefix;
}


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::ifstream input_file("sample.txt");
    if (!input_file.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }
    std::string file_contents;
    std::string line;
    while (std::getline(input_file, line)) {
        file_contents += line + '\n';
    }
    input_file.close();
    std::cout << "Choose task:\n"
                 "1 - First task\n"
                 "2 - Second task\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        for (int i: N) {
            std::string str = file_contents.substr(0, i);
            bool sentence_end = false;
            bool word_flag = false;
            bool sentence_flag = false;
            std::string str_out;
            for (char c: str) {
                if (std::isspace(c)) {
                    if (sentence_end) {
                        if (!sentence_flag) {
                            str_out += "  ";
                            sentence_flag = true;
                        }
                    } else {
                        if (!word_flag) {
                            str_out += ' ';
                            word_flag = true;
                        }
                    }
                } else if (c == '.' || c == '!' || c == '?') {
                    sentence_end = true;
                    str_out += c;
                } else {
                    sentence_flag = false;
                    word_flag = false;
                    sentence_end = false;
                    str_out += c;
                }
            }
            std::cout << str_out;
        }
    } else if (choice == 2) {
        for (int i: N) {
            std::string str = file_contents.substr(0, N[1]);
            std::vector<int> prefix = PrefixFunction(str);
            std::ofstream output_file("prefix_" + std::to_string(i) + ".txt");
            output_file << "π[i] = [";
            for (auto j = 0; j < prefix.size() - 1; ++j) {
                output_file << prefix[j] << ", ";
            }
            output_file << prefix[prefix.size() - 1] << "]";
            output_file.close();
        }
    }
    return 0;
}