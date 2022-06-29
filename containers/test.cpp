#include "include.hpp"

#include <map>

int main()
{
    std::map<int, int>  toto;
    std::map<int, int>::iterator it;

    std::cout << "\nici\n";
    toto.insert(std::pair<int, int>(7, 1));
	toto.insert(std::pair<int, int>(1, 20));
	toto.insert(std::pair<int, int>(1, 22));
	toto.insert(std::pair<int, int>(76, 15));
	toto.insert(std::pair<int, int>(12, 2));
	toto.insert(std::pair<int, int>(867, 234));
	toto.insert(std::pair<int, int>(123, 123));
	toto.insert(std::pair<int, int>(22, 1));
	toto.insert(std::pair<int, int>(56, 5));

    std::cout << "\nici\n";
    it = toto.end();
    std::cout << "\nici\n";
    std::cout << "\n " << it->first << " => " << it->second << "\n";

}