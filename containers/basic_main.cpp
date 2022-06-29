/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_main.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:07:47 by hbaudet           #+#    #+#             */
/*   Updated: 2021/01/18 16:06:03 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "map.hpp"


using namespace ft;

template <class Key, class T>
void	print(map<Key, T>& lst)
{
	for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}

int main()
{
	pair<int, std::string>			my_pair(8, "salut");
	map<int, std::string>			test;
	map<int, std::string>::iterator	it;

	test.insert(my_pair);
	std::cout << "ICI" << std::endl;
	test.insert(pair<int, std::string>(-4, "bar"));
	std::cout << "ICI" << std::endl;
	test.insert(pair<int, std::string>(10, "machin"));
	std::cout << "ICI" << std::endl;
	test.insert(pair<int, std::string>(3, "foo"));
	std::cout << "ICI" << std::endl;
	test.insert(pair<int, std::string>(746, "Marcel"));
	std::cout << "ICI" << std::endl;
	test.insert(pair<int, std::string>(4, "truc"));
	std::cout << "ICI" << std::endl;
	it = test.begin();
	std::cout << '\n';

	while (it != test.end())
	{
		// std::cout << "start of while\n";
		std::cout << it->first << ", " << it->second << '\n';
		it++;
// 		std::cout << "iterator incremented\n";

// #ifndef STD
// 		std::cout << it.getPointer() << '\n';
// 		std::cout << test.end().getPointer() << '\n';
// #endif

	}
	std::cout << "End of display loop\n";
}
