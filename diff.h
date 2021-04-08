#ifndef DIFF_H
#define DIFF_H

#include <fstream>
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
enum Operation {
    INSERT = 1,
    DELETE = -1,
    EQUAL = 0,
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

        static std::string opPrefix(Operation op);
        static std::string opColor(Operation op);
};

/**
 * Class encapsulating diff logic.
 */
template <typename T>
class Diff {

    public:
        // Default configuration.
        Mode diff_mode = Mode::LINE;

    public:
        Diff();

        /**
         * Find the differences between two text inputs.
         */
        std::vector<Edit> compare(const T& input1, const T& input2);

        ~Diff();

    private:
        std::vector<std::vector<int> > trace;

        /**
         * Find the differences between two text inputs.
         */
        std::vector<Edit> compare(std::vector<T> original, std::vector<T> updated);

        /**
         * Computes the diff trace.
         */
        void compute_trace(std::vector<T> original, std::vector<T> updated);
};

#endif // DIFF_H