#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
// Use quoted form of #include. See https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#sf12-prefer-the-quoted-form-of-include-for-files-relative-to-the-including-file-and-the-angle-bracket-form-everywhere-else.
#include "diff.h"
//#include <filesystem>

using namespace std;

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
Edit::Edit(Operation _operation, const string& _pre_line, const string& _pos_line) :
    operation(_operation), pre_line(_pre_line), pos_line(_pos_line) {
    // Construct an edit with specified operation and text. 
}

Edit::Edit() {
}

string Edit::strOperation(Operation op) {
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

/**
 * Display a human-readable version of this Edit.
 * @return text version
 */
string Edit::toString() const {
    string text;
    if (operation == Operation::DELETE) {
        text = pre_line;
    } else {
        text = pos_line;
    }
    return strOperation(operation) + " " + text;
}

//////////////////////////
//
// Differ Class
//
//////////////////////////

template <typename T>
Differ<T>::Differ(const T& o, const T& u)
    : input1 {o}, input2 {u} {

    /*
     *path is not available unitl MacOS 10.15
     */

    /*filesystem::path f1 = o;
    filesystem::path f2 = u;
    if (!exists(f1))
        throw filesystem_error{"File does not exist: ", o};
    if (!exists(f2))
        throw filesystem_error{"File does not exist: ", u};*/
}

template <typename T>
void Differ<T>::read() {
    parse_files();
}

template <typename T>
void Differ<T>::parse_files() {
    string line;

    ifstream original_ifs {input1};
    ifstream new_ifs {input2};
    if (original_ifs.is_open())
    {
        while (getline(original_ifs,line))
        {
            if (line.size() > 0) {
                original.push_back(line);
            }
        }
        original_ifs.close();
    }

    if (new_ifs.is_open())
    {
        while (getline(new_ifs,line))
        {
            if (line.size() > 0) {
                updated.push_back(line);
            }
        }
        new_ifs.close();
    }
}

template <typename T>
void Differ<T>::parse_text() {

}

template <typename T>
void Differ<T>::compare() {
    int n = original.size();
    int m = updated.size();
    int max = n + m;

    vector<int> v(2 * max + 1);
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
    return;
}

template <typename T>
void Differ<T>::output() {
    reverse(trace.begin(), trace.end());
    int d = trace.size() - 1;
    int x = original.size();
    int y = updated.size();
    int max = original.size() + updated.size();
    int k, prev_x, prev_k, prev_y;
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

    reverse(result.begin(), result.end());

    for (auto& t : result) {
        cout << t.toString() << endl;
    }
}


int main(int argc, const char* argv[]) {

    if (argc != 3) {
        cout << "Two arguments are expected\n.";
        return -1;
    }

    string file1 {argv[1]};
    string file2 {argv[2]};
    Differ<string> differ {file1, file2};
    differ.read();
    differ.compare();
    differ.output();
}
