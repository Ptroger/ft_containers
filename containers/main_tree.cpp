#include "map.hpp"

int main()
{
    ft::map<int, std::string> test;
    ft::pair<int, std::string>              pair(1, "1");
    ft::pair<int, std::string>              pair2(7, "7");
    ft::pair<int, std::string>              pair3(4, "4");
    ft::pair<int, std::string>              pair4(3, "3");
    ft::pair<int, std::string>              pair5(2, "2");
    ft::map<int, std::string>::iterator it;
    
    test.insert(pair);
    test.insert(pair2);
    test.insert(pair3);
    test.insert(pair4);
    test.insert(pair5);
       test.printTree();
    
    while (!test.empty())
  {
    std::cout << test.begin()->first << " => " << test.begin()->second << '\n';
    test.erase(test.begin());
  }
     it = test.begin();
    std::cout << "\n\n-----coucou------ == " << test.empty() << "\n\n";
    // it--;
    it--;
    it--;
    it--;
    it--;
    std::cout << "\n\n" << it->first << "\n\n";
    test.erase(it);
    std::cout << "\n\n------------ AFTER DELETION ------------\n\n";
    test.printTree();
}