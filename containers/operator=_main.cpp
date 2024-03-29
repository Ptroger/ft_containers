/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator=_main.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2021/01/18 16:05:11 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

using namespace ft;

template <class Key, class T>
void	print(map<Key, T>& lst)
{
	for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

int main ()
{
  map<char,int> first;
  map<char,int> second;

  first['x']=8;
  first['y']=16;
  first['z']=32;
  std::cout << "TEST" << std::endl;

  second=first;                // second now contains 3 ints
  std::cout << "TEST" << std::endl;
  first=map<char,int>();  // and first is now empty
  std::cout << "TEST" << std::endl;


  std::cout << "Size of first: " << first.size() << '\n';
  std::cout << "Size of second: " << second.size() << '\n';
  return 0;
}
