#include <string>
#include <vector>
#include <iostream>


class Differ {

public:
    Differ(string o, string u) :origin{o}, update{u} {}
    void read() const {};
    void compare() {};
    void output() {};
    ~Differ() {};

private:
    string origin, update;
    vector<string> origin;
    vector<update> update

}