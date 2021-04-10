# Diff Em All

## Tutorial

The Diff library implements Myer's diff algorithm for performing text diffs.

Include the library:

```cpp
#include "diff.h"
```

Instantiate `Diff`. By default, `Diff` will produce a line-based diff. This setting can be configured to produce a char-based diff.

```cpp
Diff<std::string> differ; // default diff_mode = Mode::LINE

// To configure to produce a char-based diff:
differ.diff_mode = Mode::CHARACTER;
```

Run the compare method.

```cpp
std::vector<Edit> result = differ.compare(original, updated);
```

The result of the `compare()` method produces a vector of `Edit` operations. Each `Edit` operation encapsulates the operation and the text associated with the operation.

### Sample program

```cpp
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
```