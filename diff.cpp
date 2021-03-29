#include <string>
#include <vector>
#include <iostream>

/* create class to store the diff object (holding the result for each line)
 * consider character level vs line level diff
 * consier different output format
 */
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
    vector<string> update

}
