#ifndef DIFF_H
#define DIFF_H

#include <list>
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
        Differ();

        /**
         * Read and parse inputs.
         */
        void read(const T&, const T&);

        /**
         * Find the differences between two text inputs.
         */
        void compare();

        /**
         * Find the differences between two text inputs.
         */
        void compare(T& input1, T& input2);

        /**
         * Outputs the diff result.
         */
        std::vector<Edit> output();
        
        ~Differ(){};

    private:
        std::vector<T> original;
        std::vector<T> updated;
        std::vector<std::vector<int>> trace;

        /**
         * Read and parse inputs from files.
         */
        void parse_files(const T&, const T&);

        /**
         * Read and parse inputs from raw text.
         */
        void parse_text();

        /**
         * Find the differences between two text inputs.
         */
        void compare(std::vector<T> original, std::vector<T> updated);
};

#endif // DIFF_H