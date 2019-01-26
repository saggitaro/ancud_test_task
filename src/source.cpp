#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct IndexPair 
{
    int x;
    int y;
    IndexPair(int _x, int _y) : x(_x), y(_y) {}
    IndexPair() {}
    bool operator == (IndexPair &v1);
};

bool
IndexPair::operator == (IndexPair &v1)
{
    if (this->x == v1.x && this->y == v1.y)
    {
        return true;
    }
    else
        return false;
}

vector<vector<char>>
ReadMap(const string &filename)
{
    int width, height;
    ifstream file(filename);
    file >> height >> width;

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
    cout << "===========" << endl;
}

bool
CheckOneCell(vector<vector<char>> &map, vector<vector<char>> &checked, IndexPair cell)
{
    if (checked[cell.x][cell.y] != 'v')
    {
        checked[cell.x][cell.y] = 'v';
        if (map[cell.x][cell.y] == 'O')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int
GetWaterSquare(vector<vector<char>> &map, vector<vector<char>> &checked, IndexPair cell)
{
    int square = 0;
    int height = map.size();
    int width = map[0].size();
    if (!CheckOneCell(map, checked, cell))
    {
        return square;
    }
    else
    {
        square++;
        if ( (cell.x + 1) < height)
        {
            square += GetWaterSquare(map, checked, IndexPair(cell.x + 1, cell.y));
        }
        if ( (cell.y + 1) < width)
        {
            square += GetWaterSquare(map, checked, IndexPair(cell.x, cell.y + 1));
        }
        if ( (cell.x - 1) >= 0)
        {
            square += GetWaterSquare(map, checked, IndexPair(cell.x - 1, cell.y));
        }
        if ( (cell.y - 1) >= 0)
        {
            square += GetWaterSquare(map, checked, IndexPair(cell.x, cell.y - 1));
        }
        return square;
    }
}

void CreatePond(vector<vector<char>> &map, vector<vector<char>> &checked, vector<IndexPair> &pond, IndexPair cell)
{
    int height = map.size();
    int width = map[0].size();
    
    if (CheckOneCell(map, checked, cell))
    {
        pond.push_back(cell);
        if ((cell.x + 1) < height)
        {
            CreatePond(map, checked, pond, IndexPair(cell.x + 1, cell.y));
        }
        if ((cell.y + 1) < width)
        {
            CreatePond(map, checked, pond, IndexPair(cell.x, cell.y + 1));
        }
        if ((cell.x - 1) >= 0)
        {
            CreatePond(map, checked, pond, IndexPair(cell.x - 1, cell.y));
        }
        if ((cell.y - 1) >= 0)
        {
            CreatePond(map, checked, pond, IndexPair(cell.x, cell.y - 1));
        }
    }
}

int main() 
{
    vector<vector<char>> map = ReadMap("./tests/test2.txt");
    //DebugPrint(map);
    int checkpointCount;
    cout << "Enter number of checkpoints: ";
    cin >> checkpointCount; cin.ignore();
    vector<IndexPair> checkpoints(checkpointCount);

    for (auto it = checkpoints.begin(); it != checkpoints.end(); it++)
    {
        cin >> it->x >> it->y;
    }

    vector<vector<char>> checked;
    checked.assign(map.begin(), map.end());
    for (auto it = checked.begin(); it != checked.end(); it++)
    {
        for (auto jt = it->begin(); jt != it->end(); jt++)
        {
            *jt = 'n';
        }
    }
    vector<vector<IndexPair>> ponds;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 'O')
            {
                vector<IndexPair> pond;
                CreatePond(map, checked, pond, IndexPair(i, j));
                if (!pond.empty())
                    ponds.push_back(pond);
            }
        }
    }

    for (auto it = ponds.begin(); it != ponds.end(); it++) 
    {
        cout << "Pond" << endl << "================" << endl;
        for (auto jt = it->begin(); jt != it->end(); jt++)
        {
            cout << jt->x << " " << jt->y << endl;
        }
    }
    
    //DebugPrint(checked);
    return 0;
}