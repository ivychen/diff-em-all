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
        std::cout << "Two arguments are expected." << std::endl;
        return -1;
    }
    
    std::ifstream old_ifs(argv[1]);
    std::ifstream new_ifs(argv[2]);

    std::string original = slurp(old_ifs);
    std::string updated = slurp(new_ifs);

    // Add differ code here.
    
    Diff<std::string> differ;
    auto result = differ.compare(original, updated);

    for (auto& edit: result) {
        std::cout << edit.toString() << std::flush;
    }
    return 0;
}
