#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point2i 
{
    int x;
    int y;
    Point2i(int _x, int _y) : x(_x), y(_y) {}
    Point2i() {}
    bool operator == (Point2i &v1);
};

bool
Point2i::operator == (Point2i &v1)
{
    if (this->x == v1.x && this->y == v1.y)
    {
        return true;
    }
    else
        return false;
}

void
PrintMap(vector<vector<char>> &map)
{
    for (auto it = map.begin(); it != map.end(); it++)
    {
        for (auto jt = it->begin(); jt != it->end(); jt++)
        {
            cout << *jt << " ";
        }
        cout << endl;
    }
    cout << "=================" << endl;
}

vector<vector<char>>
ReadFromFile(char* filename, vector<Point2i> &checkpoints)
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

    int checkpointsNum;
    file >> checkpointsNum;

    for (int i = 0; i < checkpointsNum; i++)
    {
        int x, y;
        file >> y >> x;
        checkpoints.push_back(Point2i(x, y));
    }

    file.close();

    return result;
}

bool
CheckPoint(vector<vector<char>> &map, vector<vector<char>> &checked, Point2i point)
{
    if (checked[point.x][point.y] != 'v')
    {
        checked[point.x][point.y] = 'v';
        if (map[point.x][point.y] == 'O')
        {
            return true;
        }
        else
        {
            return false;
        }
    }    
}

void CreatePond(vector<vector<char>> &map, vector<vector<char>> &checked, vector<Point2i> &pond, Point2i point)
{
    int height = map.size();
    int width = map[0].size();
    
    if (CheckPoint(map, checked, point))
    {
        pond.push_back(point);
        if ((point.x + 1) < height)
        {
            CreatePond(map, checked, pond, Point2i(point.x + 1, point.y));
        }

        if ((point.y + 1) < width)
        {
            CreatePond(map, checked, pond, Point2i(point.x, point.y + 1));
        }

        if ((point.x - 1) >= 0)
        {
            CreatePond(map, checked, pond, Point2i(point.x - 1, point.y));
        }
        
        if ((point.y - 1) >= 0)
        {
            CreatePond(map, checked, pond, Point2i(point.x, point.y - 1));
        }
    }
}

vector<vector<Point2i>>
FindAllPonds(vector<vector<char>> &map, vector<vector<char>> &checked)
{
    vector<vector<Point2i>> ponds;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j] == 'O')
            {
                vector<Point2i> pond;
                CreatePond(map, checked, pond, Point2i(i, j));
                if (!pond.empty())
                    ponds.push_back(pond);
            }
        }
    }
    return ponds;
}

int
GetPondSizeAtPoint(vector<vector<Point2i>> &ponds, Point2i checkpoint)
{
    for (auto it = ponds.begin(); it != ponds.end(); it++)
    {
        for (auto jt = it->begin(); jt != it->end(); jt++)
        {
            if (*jt == checkpoint)
            {
                return it->size();
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[]) 
{
    vector<Point2i> checkpoints;
    vector<vector<char>> map = ReadFromFile(argv[1], checkpoints);
    PrintMap(map);

    vector<vector<char>> checked;
    checked.assign(map.begin(), map.end());
    for (auto it = checked.begin(); it != checked.end(); it++)
    {
        for (auto jt = it->begin(); jt != it->end(); jt++)
        {
            *jt = 'n';
        }
    }
    
    vector<vector<Point2i>> ponds = FindAllPonds(map, checked);

    for (auto it = checkpoints.begin(); it != checkpoints.end(); it++) 
    {
            cout << "Pond size at point (" << it->x << ":" << it->y << ") is " << GetPondSizeAtPoint(ponds, *it) << endl;
    }
    
    return 0;
}