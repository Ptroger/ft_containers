#include <map>
#include <iostream>
#include <vector>

using namespace std;

struct  Cmp_By_len {
    bool operator() (const string &s1, const string &s2) const {
        return (s1.length() < s2.length());
    }
};

int main()
{
    map<string, int, Cmp_By_len> m;

    m["toto"] = 1;
    m["totto"] = 2;
    m["to"] = 3;
    m["t"] = 4;
    m["tutututu"] = 5;
    //m[""] = 6;
    cout << m.begin()->first << endl;
    return (0);
}
