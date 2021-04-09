#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
// Use quoted form of #include. See https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#sf12-prefer-the-quoted-form-of-include-for-files-relative-to-the-including-file-and-the-angle-bracket-form-everywhere-else.
#include "diff.h"
//#include <filesystem>

// The following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

//////////////////////////
//
// Edit Class
//
//////////////////////////

/**
 * Constructor. Initialized the diff with the provided values.
 * @param operation One of INSERT, DELETE, EQUAL.
 * @param pre_line The original text associated with this operation.
 * @param pos_line The new text associated with this operation.
 */
Edit::Edit(Operation _operation, const std::string& _pre_line, const std::string& _pos_line) :
    operation(_operation), pre_line(_pre_line), pos_line(_pos_line) {
    // Construct an edit with specified operation and text. 
}

Edit::Edit() {
}

std::string Edit::opPrefix(Operation op) {
    switch(op) {
        case Operation::INSERT:
            return "+";
        case Operation::DELETE:
            return "-";
        case Operation::EQUAL:
            return " ";
    }
    throw "Invalid operation.";
}

std::string Edit::opColor(const Operation op) {
    switch(op) {
        case Operation::INSERT:
            return GREEN;
        case Operation::DELETE:
            return RED;
        case Operation::EQUAL:
            return RESET;
    }
    throw "Invalid operation.";
}

/**
 * Display a human-readable version of this Edit.
 * @return text version
 */
std::string Edit::toString() const {
    std::string text;
    if (operation == Operation::DELETE) {
        text = pre_line;
    } else {
        text = pos_line;
    }
    return opColor(operation) + opPrefix(operation) + " " + text + RESET;
}

//////////////////////////
//
// Diff Class
//
//////////////////////////

template <typename T>
Diff<T>::Diff() :
    diff_mode(Mode::LINE) {
}

template <typename T>
Diff<T>::~Diff() {
}

template <typename T>
std::vector<Edit> Diff<T>::compare(const T& input1, const T& input2) {
    std::vector<T> original;
    std::vector<T> updated;

    if (diff_mode == Mode::CHARACTER) {
        // Convert lines to characters.
        for (auto c : input1) {
            std::string s(1, c);
            original.push_back(s);
        }

        for (auto c : input2) {
            std::string s(1, c);
            updated.push_back(s);
        }
    } else {
        // Convert lines.
        std::istringstream i1(input1);
        std::istringstream i2(input2);
        std::string line;
        
        while (std::getline(i1, line)) {
            line.push_back('\n');
            original.push_back(line);
        }

        while (std::getline(i2, line)) {
            line.push_back('\n');
            updated.push_back(line);
        }
    }

    // Perform diff.
    return compare(original, updated);
}

template <typename T>
std::vector<Edit> Diff<T>::compare(std::vector<T> original, std::vector<T> updated) {
    // Compute the trace.
    compute_trace(original, updated);

    // Compute the diff result.
    std::vector<Edit> result;

    // Reverse the trace.
    reverse(trace.begin(), trace.end());

    int d = trace.size() - 1;
    int x = original.size();
    int y = updated.size();
    int max = original.size() + updated.size();
    int k, prev_x, prev_k, prev_y;

    // Iterate through the reversed trace to get the diff output.
    for (int i = 0; i < trace.size() - 1; i++) {
        k = x - y;
        if (k == -(d - i) || (k != d && trace[i][k - 1 + max] < trace[i][k + 1 + max])) {
            prev_k = k + 1;
        }
        else {
            prev_k = k -1;
        }
        prev_x = trace[i+1][prev_k + max];
        prev_y = prev_x - prev_k;
        while (x > prev_x && y > prev_y) {
            result.push_back(Edit(Operation::EQUAL, original[x-1], updated[y-1]));
            x = x - 1;
            y = y - 1;
        }
        if (x == prev_x) {
            result.push_back(Edit(Operation::INSERT, "", updated[prev_y]));
        }
        else if (y == prev_y) {
            result.push_back(Edit(Operation::DELETE, original[prev_x], ""));
        }
        x = prev_x;
        y = prev_y;
    }

    // At the end of the trace run, x should equal y. We may have remaining tokens (all EQUAL operations) to include in the result so we iterate until both x and y are exhausted.
    while (x == y && x > 0 && y > 0) {
        result.push_back(Edit(Operation::EQUAL, original[x-1], updated[y-1]));
        x--;
        y--;
    }

    reverse(result.begin(), result.end());
    return result;
}

template <typename T>
void Diff<T>::compute_trace(std::vector<T> original, std::vector<T> updated) {
    int n = original.size();
    int m = updated.size();
    int max = n + m;

    // Compute the trace.
    std::vector<int> v(2 * max + 1);
    v[1+max] = 0;
    int d, k, x, y;
    for (d = 0; d <= max; d=d+1) {
        for (k = -d; k <= d; k=k+2) {
            if ( k == -d || (k != d && v[k - 1 + max] < v[k + 1 + max])) {
                x = v[k + 1 + max];
            }
            else {
                x = v[k - 1 + max] + 1;
            }
            y = x - k;
            while (x < n && y < m && original[x] == updated[y]) {
                // Skip over common substring
                x = x + 1;
                y = y + 1;
            }
            v[k + max] = x;
            if (x >= n && y >= m) {
                trace.push_back(v);
                return;
            }
        }
        trace.push_back(v);
    }
}

// See https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function.
template class Diff<std::string>;