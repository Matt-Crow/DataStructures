#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX = 175;

class DoubleHashTable
{
public:
    DoubleHashTable();
    void set(int k1, int k2, bool v);
    bool get(int k1, int k2);
    int getSize();
private:
    bool** vals; //2D array of bools
    int size;
};

int main()
{
    ifstream in = ifstream("nodeConn.csv");
    string s;
    int id1;
    int id2;
    getline(in, s); //get rid of header
    while(in.good()){
        in >> id1;
        in >> id2;
        cout << id1 << "=>" << id2 << endl;
    }
    return 0;
}

DoubleHashTable::DoubleHashTable()
{
    size = 0;
    vals = (bool**)(malloc(sizeof(bool) * MAX * MAX));
    memset(vals, false, MAX * MAX);
}
void DoubleHashTable::set(int k1, int k2, bool v)
{
    if(!get(k1, k2) && v){
        //increase size if we are adding to the table
        size++;
    } else if(get(k1, k2) && !v){
        //decrease if we are removing
        size--;
    }
    vals[k1][k2] = v;
}
bool DoubleHashTable::get(int k1, int k2)
{
    return vals[k1][k2];
}
int DoubleHashTable::getSize()
{
    return size;
}
