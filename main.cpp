#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "diff.h"

std::string slurp(std::ifstream& in) {
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        std::cout << "Two arguments are expected\n.";
        return -1;
    }

    std::string input1(argv[1]);
    std::string input2(argv[2]);

    std::ifstream original_ifs(input1);
    std::ifstream new_ifs(input2);

    std::string original = slurp(original_ifs);
    std::string updated = slurp(new_ifs);

    Diff<std::string> differ;
    auto result = differ.compare(original, updated);

    for (auto& edit : result) {
        std::cout << edit.toString() << std::flush;
    }
    return 0;
}