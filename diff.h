#ifndef DIFF_H
#define DIFF_H

#include <string>
#include <vector>

// Avoid "using namespace std;" at global scope in header.
// See https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#sf7-dont-write-using-namespace-at-global-scope-in-a-header-file.

/**
 * Functions for performing diffs.
 * Computes the difference between two text inputs.
 */

/**
 * Enum represents diff operation.
 * Prefer class enum, see https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#enum3-prefer-class-enums-over-plain-enums.
 */
enum class Operation {
    INSERT,
    DELETE,
    EQUAL,
};

/**
 * Enum represents diff mode.
 */
enum class Mode {
    CHARACTER,
    LINE,
};

/**
 * Class representing a single diff edit operation.
 */
class Edit {
    public:
        Operation operation; // One of: INSERT, DELETE, EQUAL.
        std::string pre_line;     // The original text associated with this diff operation.
        std::string pos_line;     // The new text associated with this diff operation.

        /**
         * Constructor. Initialized the diff with the provided values.
         * @param operation One of INSERT, DELETE, EQUAL.
         * @param pre_line The original text associated with this operation.
         * @param pos_line The new text associated with this operation.
         */
        Edit(Operation _operation, const std::string& _pre_line, const std::string& _pos_line);
        Edit();
        std::string toString() const;

        static std::string strOperation(Operation op);
};

/**
 * Class representing a differ that executes diff logic.
 */
template <typename T>
class Differ {

    public:
        // Default configuration.
        Mode diff_mode = Mode::LINE;

    public:
        Differ(const T&, const T&);
        Differ();

        /**
         * Read and parse inputs.
         */
        void read();

        /**
         * Find the differences between two text inputs.
         */
        void compare();

        /**
         * Outputs the diff result.
         */
        void output();
        
        ~Differ(){};

    private:
        const T& input1;
        const T& input2;
        std::vector<T> original;
        std::vector<T> updated;
        std::vector<std::vector<int>> trace;
        std::vector<Edit> result;

        /**
         * Read and parse inputs from files.
         */
        void parse_files();

        /**
         * Read and parse inputs from raw text.
         */
        void parse_text();

};

#endif // DIFF_H