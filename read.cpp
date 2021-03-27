#include <iostream>
#include <fstream>

using namespace std;

int main(){
    string line;
    ifstream origin_ifs {"origin.txt"};
    ifstream new_ifs {"new.txt"};

    if (origin_ifs.is_open())
    {
        while ( getline (origin_ifs,line) )
        {
            cout << line << '\n';
        }
        origin_ifs.close();
    }

    if (new_ifs.is_open())
    {
        while ( getline (new_ifs,line) )
        {
            cout << line << '\n';
        }
        new_ifs.close();
    }

    else cout << "Unable to open file"; 

    return 0;
}