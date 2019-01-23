#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<char>>
ReadMap(const string &filename)
{
    int width, height;
    ifstream file(filename);
    file >> width >> height;

    vector<vector<char>> result;
    for (int i = 0; i < height; i++)
    {
        vector<char> buf;
        for (int j = 0; j < width; j++) 
        {
            char sym;
            file >> sym;
            buf.push_back(sym);
        }
        result.push_back(buf);
    }
    return result;
}

void 
DebugPrint(const vector<vector<char>> &map) 
{
    for (auto it = map.begin(); it != map.end(); it++)
    {
        for (auto jt = it->begin(); jt != it->end(); jt++)
        {
            cout << *jt << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> map = ReadMap("tests/test4.txt");
    DebugPrint(map);
    return 0;
}