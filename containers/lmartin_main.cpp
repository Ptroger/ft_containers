/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aaaaalmartin_main.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2021/01/20 21:35:46 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <map>
#include <cstdio>
#include <iomanip>

/*
** This is a minimal set of ANSI/VT100 color codes
*/
# define _END			"\x1b[0m"
# define _BOLD			"\x1b[1m"
# define _UNDER			"\x1b[4m"
# define _REV			"\x1b[7m"

/*
** Colors
*/
# define _GREY			"\x1b[30m"
# define _RED			"\x1b[31m"
# define _GREEN			"\x1b[32m"
# define _YELLOW		"\x1b[33m"
# define _BLUE			"\x1b[34m"
# define _PURPLE		"\x1b[35m"
# define _CYAN			"\x1b[36m"
# define _WHITE			"\x1b[37m"

/*
** Inverted, i.e. colored backgrounds
*/
# define _IGREY			"\x1b[40m"
# define _IRED			"\x1b[41m"
# define _IGREEN		"\x1b[42m"
# define _IYELLOW		"\x1b[43m"
# define _IBLUE			"\x1b[44m"
# define _IPURPLE		"\x1b[45m"
# define _ICYAN			"\x1b[46m"
# define _IWHITE		"\x1b[47m"

template <class Key, class T>
void	print(ft::map<Key, T>& lst)
{
	std::cout << "printing a map : \n";
	for (typename ft::map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

int main()
{
	std::cout << _WHITE << "# test_map" << _END << std::endl;
	std::cout << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                          "<< _WHITE << "BASIC TESTS" << _YELLOW << "                                   */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	std::cout << std::endl;


	ft::map<std::string, int> mymap;
	print(mymap);


	std::cout << "mymap<" << _PURPLE << "std::string" << _END << ", " << _PURPLE << "int" << _END <<"> mymap;" << std::endl;

	std::cout << std::endl;
	std::cout << "mymap.max_size(): " << (mymap.max_size() > 10000) << std::endl;
	print(mymap);
	std::cout << std::endl;


	print(mymap);
	mymap.insert(ft::pair<std::string, int>("ft", 42));

	print(mymap);
	mymap.insert(ft::pair<std::string, int>("one", 1));


	std::cout << _WHITE << "# testing upper/lower_bound" << _END << std::endl;
	ft::map<std::string, int>::iterator mit;
	ft::map<std::string, int>::iterator it;
	print(mymap);
	it = mymap.lower_bound("aaa");
	print(mymap);
	std::cout << std::setw(40) << "mymap.lower_bound(\"aaa\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.lower_bound("one");
	print(mymap);
	std::cout << std::setw(40) << "mymap.lower_bound(\"one\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.lower_bound("oae");
	print(mymap);
	std::cout << std::setw(40) << "mymap.lower_bound(\"oae\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.lower_bound("ft");
	print(mymap);
	std::cout << std::setw(40) << "mymap.lower_bound(\"ft\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.lower_bound("zzz");
	print(mymap);
	
	std::cout << "\n\n ----------------1------------- \n\n";
	if (it == mymap.end())
		std::cout << std::setw(40) << "mymap.lower_bound(\"zzz\"): mymap.end()" << std::endl;
	std::cout << std::endl;
	print(mymap);
	it = mymap.upper_bound("aaa");
	
	print(mymap);
	std::cout << std::setw(40) << "mymap.upper_bound(\"aaa\"): " << it->first << ":" << it->second << std::endl;;
	std::cout << std::endl;
	print(mymap);
	it = mymap.upper_bound("oae");
	print(mymap);
	std::cout << std::setw(40) << "mymap.upper_bound(\"oae\"): " << it->first << ":" << it->second << std::endl;;
	std::cout << std::endl;
	print(mymap);
	it = mymap.upper_bound("one");
	
	std::cout << "\n\n ----------------2------------- \n\n";
	if (it == mymap.end())
		std::cout << std::setw(40) << "mymap.upper_bound(\"one\"): mymap.end()" << std::endl;
	print(mymap);
	std::cout << std::endl;
	it = mymap.upper_bound("ft");
	print(mymap);
	std::cout << std::setw(40) << "mymap.upper_bound(\"ft\"): " << it->first << ":" << it->second << std::endl;;
	std::cout << std::endl;
	print(mymap);
	it = mymap.upper_bound("zzz");
	
	std::cout << "\n\n ----------------3------------- \n\n";
	if (it == mymap.end())
		std::cout << std::setw(40) << "mymap.upper_bound(\"zzz\"): mymap.end()" << std::endl;
	print(mymap);
	std::cout << std::endl;

	print(mymap);
	mymap.erase("undefined");
	print(mymap);
	mymap.erase("ft");
	print(mymap);
	std::cout << _WHITE << "# double clear" << _END << std::endl;
	mymap.clear();
	print(mymap);
	mymap.clear();
	print(mymap);
	mymap["lol"];
	print(mymap);
	mymap.insert(ft::pair<std::string, int>("xD", 123));
	print(mymap);
	mymap.insert(mymap.end(), ft::pair<std::string, int>("uch", 442));
	print(mymap);
	mymap.insert(mymap.begin(), ft::pair<std::string, int>("uch", 22));
	print(mymap);
	mymap.insert(mymap.end(), ft::pair<std::string, int>("uch", 23));
	print(mymap);
	mymap.insert(ft::pair<std::string, int>("uch", 23));
	print(mymap);
	mymap["lol"] = 8;

	std::cout << "\n\n ----------------4------------- \n\n";
	print(mymap);
	ft::map<std::string, int> map2;

	print(mymap);
	print(map2);
	std::cout << "mymap<" << _PURPLE << "std::string" << _END << ", " << _PURPLE << "int" << _END <<"> mymap2;" << std::endl;
	print(mymap);
	std::cout << "empty line\n";
	print(map2);
	std::cout << "empty line2\n";

	swap(mymap, map2);
	std::cout << "empty line3\n";
	print(mymap);
	std::cout << "empty line4\n";
	print(map2);
	std::cout << "empty line5\n";

	mymap = map2;
	print(mymap);
	print(map2);

	std::cout << std::setw(40) << "map == map2: " << (mymap == map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;
	std::cout << "\n\n ----------------1------------- \n\n";

	mymap.clear();
	print(mymap);
	print(map2);
	
	std::cout << "\n\n ----------------5------------- \n\n";
	mymap["satan"] = 666;
	print(mymap);
	print(map2);
	std::cout << std::setw(40) << "mymap == map2: " << (mymap == map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap <= map2: " << (mymap <= map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap >= map2: " << (mymap >= map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap > map2: " << (mymap > map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap < map2: " << (mymap > map2) << std::endl;
	print(mymap);
	print(map2);
	std::cout << std::endl;

	return 0;
}
