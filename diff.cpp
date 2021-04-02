#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
//#include <filesystem>

using namespace std;

struct Edit {
    string type;
    string pre_line;
    string pos_line;
};

class Differ {
public:
    virtual void read() = 0;
    virtual int compare() = 0;
    virtual void output(int) = 0;
    virtual ~Differ() {}
};


class File_Differ : public Differ {
public:
    File_Differ(const string&, const string&);
    void read() override;
    int compare() override;
    void output(int) override;
    ~File_Differ() {};

private:
    const string& originf;
    const string& updatef;
    vector<string> origin;
    vector<string> update;
    vector<vector<int>> trace;
    vector<Edit> result;
};

File_Differ::File_Differ(const string& o, const string& u) 
    : originf {o}, updatef {u} {

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


void File_Differ::read() {
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

int File_Differ::compare() {
    
    int n = origin.size();
    int m = update.size();
    int max = n + m;
    //cout << "max is: " << max << "\n";

    vector<int> v(2 * max + 1);
    v[1+max] = 0;
    int d, k, x, y;

    for (d = 0; d <= max; d=d+1) {
        for (k = -d; k <= d; k=k+2) {
            //cout << "k: " << k << "\n";
            if ( k == -d || (k != d && v[k - 1 + max] < v[k + 1 + max])) {
                x = v[k + 1 + max];
            }
            else {
                x = v[k - 1 + max] + 1;
            }
            y = x - k;

            while (x < n && y < m && origin[x] == update[y]) {
                x = x + 1;
                y = y + 1;
            }
            //cout << "x: " << x << "\n";
            v[k + max] = x;
            if (x >= n && y >= m) {
                //cout << "d: " << d << "\n";
                trace.push_back(v);
                return d;
            }
        }
        trace.push_back(v);
        //cout << "--------\n";
    }
    return max;
}

void File_Differ::output(int real_d) {
    //cout << "size of trace: " << trace.size() << "\n";
    reverse(trace.begin(), trace.end());
    /*for (auto& t : trace) {
        for (auto& v : t) {
            cout << v << ",";
        }
        cout <<"\n";
    }*/
    int x = origin.size();
    int y = update.size();
    int max = origin.size() + update.size();
    int k, prev_x, prev_k, prev_y;
    for (int i = 0; i < trace.size() - 1; i++) {
        //cout << "i: " << i << "\n";
        k = x - y;
        if (k == -(real_d - i) || (k != real_d && trace[i][k - 1 + max] < trace[i][k + 1 + max])) {
            prev_k = k + 1;
        }
        else {
            prev_k = k -1;
        }
        //cout << "prev_k: " << prev_k << "\n";
        prev_x = trace[i+1][prev_k + max];
        prev_y = prev_x - prev_k;
        /*cout << "prev_k: " << prev_k << "\n";
        cout << "prev_x: " << prev_x << "\n";
        cout << "prev_y: " << prev_y << "\n";*/

        while (x > prev_x && y > prev_y) {
            //cout << "while loop is called.\n";
            //cout << x - 1 << y - 1 << x << y << "\n";
            result.push_back(Edit{"eql", origin[x-1], update[y-1]});
            x = x - 1;
            y = y - 1;
        }
        //cout << prev_x << prev_y << x << y << "\n";
        if (x == prev_x) {
            result.push_back(Edit{"ins", "", update[prev_y]});
        }
        else if (y == prev_y) {
            result.push_back(Edit{"del", origin[prev_x], ""});
        }
        x = prev_x;
        y = prev_y;
    }

    reverse(result.begin(), result.end());

    for (auto& t : result) {
        if (t.type == "del") {
            cout << "- " << t.pre_line << "\n";
        }
        else if (t.type == "ins") {
            cout << "+ " << t.pos_line << "\n";
        }
        else {
            cout << "  " << t.pre_line << "\n";
        }
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
    int d = differ.compare();
    differ.output(d);
}
