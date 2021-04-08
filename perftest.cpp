#include <string>
#include <fstream>
#include <streambuf>
#include <chrono>
#include <iostream>
#include "diff.h"
using namespace std;

string readFile(string fname){
    ifstream t(fname);
    string str;

    t.seekg(0, ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, ios::beg);

    str.assign((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

    return str;
}

int main(int argc, char** argv){

    string fname1(argv[1]);
    string fname2(argv[2]);

    string str1 = readFile(fname1);
    string str2 = readFile(fname2);

    auto start = std::chrono::system_clock::now();
    Diff<string> diff;
    diff.compare(str1,str2);
    auto end = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Time elapsed : " << elapsed.count() << endl;
}