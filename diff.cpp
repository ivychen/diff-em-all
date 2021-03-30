#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

/* create class to store the diff object (holding the result for each line)
 * consider character level vs line level diff
 * consier different output format
 */

class Differ {
public:
    virtual void read() {} = 0;
    virtual void compare() {} = 0;
    virtual void output() {} = 0;
    virtual ~Differ() {}
}


class File_Differ : public Differ {
public:
    File_Differ(string o, string u);
    void read() override;
    void compare() override;
    void output() override;
    ~Differ() {};

private:
    string originf, updatef;
    vector<string> origin;
    vector<string> update
}

File_Differ::File_Differ(string o, string u) {
    path f1 = o;
    path f2 = u;
    if (!exists(f1))
        throw filesystem_error{"File does not exist: ", o};
    if (!exists(f2))
        throw filesystem_error{"File does not exist: ", u};
    originf = o;
    updatef = u;
}


void File_Differ::read {
    string line;
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

void File_Differ::compare {

}

void File_Differ::output {

}


int main{
    Differ differ {"", ""};
    differ.read();
    differ.compare();
    differ.output();
}
