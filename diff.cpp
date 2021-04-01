#include <string>
#include <vector>
#include <iostream>
#include <fstream>
//#include <filesystem>

/* create class to store the diff object (holding the result for each line)
 * consider character level vs line level diff
 * consier different output format
 */
using namespace std;

class Differ {
public:
    virtual void read() = 0;
    virtual void compare() = 0;
    virtual void output() = 0;
    virtual ~Differ() {}
};


class File_Differ : public Differ {
public:
    File_Differ(const string&, const string&);
    void read() override;
    void compare() override;
    void output() override;
    ~File_Differ() {};

private:
    const string& originf;
    const string& updatef;
    vector<string> origin;
    vector<string> update;
};

File_Differ::File_Differ(const string& o, const string& u) 
    : originf {o}, updatef {u} {
    /*filesystem::path f1 = o;
    filesystem::path f2 = u;
    if (!exists(f1))
        throw filesystem_error{"File does not exist: ", o};
    if (!exists(f2))
        throw filesystem_error{"File does not exist: ", u};*/
}


void File_Differ::read() {
    string line;

    //cout << "originf is: " << originf << "\n";
    //cout << "updatef is: " << updatef << "\n";

    ifstream origin_ifs {originf};
    ifstream new_ifs {updatef};
    if (origin_ifs.is_open())
    {
        while (getline(origin_ifs,line))
        {
            if (line.size() > 0) {
                origin.push_back(line);
            }
        }
        origin_ifs.close();
    }

    if (new_ifs.is_open())
    {
        while (getline(new_ifs,line))
        {
            if (line.size() > 0) {
                update.push_back(line);
            }
        }
        new_ifs.close();
    }
}

void File_Differ::compare() {
    cout << "compare is called.\n";
}

void File_Differ::output() {
    for (auto& l : origin) {
        cout << l << "\n";
    }
    for (auto& l : update) {
        cout << l << "\n";
    }
}


int main(int argc, const char* argv[]) {

    if (argc != 3) {
        cout << "Two files are expected\n.";
        return -1;
    }
    
    string file1 {argv[1]};
    string file2 {argv[2]};
    File_Differ differ {file1, file2};
    differ.read();
    differ.compare();
    differ.output();
}
