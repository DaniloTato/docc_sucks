#include <fstream>
#include <iostream>
#include <sstream>

#include "checks.hpp"

const vector<string> TRANSMISSIONS = {"transmission1.txt", "transmission2.txt"};

const vector<string> MCODES = {"mcode1.txt", "mcode2.txt", "mcode3.txt"};

range make_range(size_t l, size_t r) { return std::make_pair(l, r); }

optstring read_contents(const string &path) {
    std::ifstream fs(path, std::ios::binary);
    if (!fs) {
        std::cerr << "Error: Could not open file: " << path << std::endl;
        return std::nullopt;
    }

    std::ostringstream buffer;
    buffer << fs.rdbuf();

    if (fs.bad()) {
        std::cerr << "Error: Failed while reading file: " << path << std::endl;
        return std::nullopt;
    }

    return buffer.str();
}

void test_transmission(const string &trans, const vector<string> &mcodes) {
    for (size_t i = 0; i < mcodes.size(); i++) {
        int substr_start = is_substr(trans, mcodes[i]);
        std::cout << "MCODE " << i + 1 << ": "
                  << (substr_start == -1 ? "false" : "true");
        if (substr_start > -1)
            std::cout << " " << substr_start + 1;
        std::cout << std::endl;
    }
    range lps = longest_palindromic_substr(trans);
    std::cout << "Longest palindromic substring" << std::endl;
    if (lps.second == 0) // empty transmission
        std::cout << "No palindromic substring";
    else
        std::cout << lps.first << " " << lps.second - 1;
    std::cout << std::endl;
}

void compare_transmissions(const string &trans_a, const string &trans_b) {
    range lcs = longest_common_substr(trans_a, trans_b);
    if (lcs.second - lcs.first <= 0) {
        std::cout << "No common substring" << std::endl;
        return;
    }
    std::cout << "[" << lcs.first + 1 << " - " << lcs.second + 1 << "]"
              << std::endl;
}

int main(int argc, char *argv[]) {
    string dir = argc > 1 ? argv[1] : "./";
    optstring contents;

    vector<string> mcodes;
    for (auto filename : MCODES) {
        string path = dir + filename;
        contents = read_contents(path);
        if (!contents)
            return EXIT_FAILURE;
        mcodes.push_back(*contents);
    }

    vector<string> transmissions;
    for (auto filename : TRANSMISSIONS) {
        string path = dir + filename;
        contents = read_contents(path);
        if (!contents)
            return EXIT_FAILURE;
        transmissions.push_back(*contents);
    }

    for (size_t i = 0; i < transmissions.size(); i++) {
        std::cout << "Test transmission " << i + 1 << std::endl;
        test_transmission(transmissions[i], mcodes);
        if (i + 1 < transmissions.size()) {
            std::cout << "Comparison between transmissions " << i + 1 << " and "
                      << i + 2 << std::endl;
            compare_transmissions(transmissions[i], transmissions[i + 1]);
        }
    }
    return 0;
}
