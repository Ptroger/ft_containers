#include <iostream>
#include <map>

#include "map.hpp"

using namespace ft;


void	create_header(std::string const title) {
		std::cout << std::endl << std::endl << "|****" ;
		for (size_t i = 0; i < title.length(); i++) {
			std::cout << "*";
		}
		std::cout << "****|" << std::endl
			<< "|*   " << title << "   *|" << std::endl
			<< "|****" ;
		for (size_t i = 0; i < title.length(); i++) {
			std::cout << "*";
		}
		std::cout << "****|" << std::endl;
}

template <typename T, typename U>
void	printMap(map<T, U> &x) {
	for (typename map<T, U>::iterator it = x.begin();
		it != x.end(); it++) {
			std::cout << it->first << " ==> " << it->second << std::endl;
		}
}


void	mapMegaTest() {
	{
		create_header("Constructors");

		map<int,int> first;

		first[12] = 23;
		first[34] = 243;
		first[1] = 5523;
		first[2] = 123;

		map<int, int> second(first.begin(), first.end());
		map<int, int> third(second);

		std::cout << "\tFirst" << std::endl;
		printMap(first);
		std::cout << "\tSecond" << std::endl;
		printMap(second);
		std::cout << "\tThird" << std::endl;
		printMap(third);

	}
	/****************************/
	/*			Capacity		*/
	/****************************/
	{
		create_header("Empty");
		map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		while (!mymap.empty())
		{
			std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
			mymap.erase(mymap.begin());
		}
	}
	{
		create_header("Size");
		map<char,int> mymap;
		mymap['a']=101;
		mymap['b']=202;
		mymap['c']=302;

		std::cout << "mymap.size() is " << mymap.size() << '\n';
	}
	{
		create_header("Max_size");
		int i;
		map<int,int> mymap;

		if (mymap.max_size()>1000)
		{
			for (i=0; i<1000; i++) mymap[i]=0;
			std::cout << "The map contains 1000 elements.\n";
		}
		else std::cout << "The map could not hold 1000 elements.\n";
	}
	/****************************/
	/*		Element access		*/
	/****************************/
	{
		create_header("operator []");
		map<char,std::string> mymap;

		mymap['a']="an element";
		mymap['b']="another element";
		mymap['c']=mymap['b'];

		std::cout << "mymap['a'] is " << mymap['a'] << '\n';
		std::cout << "mymap['b'] is " << mymap['b'] << '\n';
		std::cout << "mymap['c'] is " << mymap['c'] << '\n';
		std::cout << "mymap['d'] is " << mymap['d'] << '\n';

		mymap['b']="pouet";
		std::cout << "change mymap['b'] to \"pouet\" : " << mymap['b'] << std::endl;
		std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	}
	/****************************/
	/*			Modifiers		*/
	/****************************/
	{
		create_header("Insert");
		map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( pair<char,int>('a',100) );
		mymap.insert ( pair<char,int>('z',200) );

		pair<map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( pair<char,int>('z',500) );
		if (ret.second==false) {
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting

		// third insert function version (range insertion):
		map<char,int> anothermap;
		anothermap.insert(mymap.begin(),mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		create_header("Erase");
		map<char,int> mymap;
		map<char,int>::iterator it;

		// insert some values:
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		mymap['d']=40;
		mymap['e']=50;
		mymap['f']=60;

		it=mymap.find('b');
		mymap.erase (it);                   // erasing by iterator
		mymap.erase (mymap.end());                   // erasing by iterator

		mymap.erase ('c');                  // erasing by key
		mymap.erase ('z');                  // erasing by key

		it=mymap.find ('e');
		mymap.erase ( it, mymap.end() );    // erasing by range

		// show content:
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		create_header("Swap");
		map<char,int> foo,bar;

		foo['x']=100;
		foo['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;

		foo.swap(bar);

		std::cout << "foo contains:\n";
		for (map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "bar contains:\n";
		for (map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		create_header("Clear");
		map<char,int> mymap;

		mymap['x']=100;
		mymap['y']=200;
		mymap['z']=300;

		std::cout << "mymap contains:\n";
		for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		mymap.clear();
		mymap['a']=1101;
		mymap['b']=2202;

		std::cout << "mymap contains:\n";
		for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	/****************************/
	/*			Observers		*/
	/****************************/
	{
		create_header("Key_comp");
		map<char,int> mymap;

		map<char,int>::key_compare mycomp = mymap.key_comp();

		mymap['a']=100;
		mymap['b']=200;
		mymap['c']=300;

		std::cout << "mymap contains:\n";

		char highest = mymap.rbegin()->first;     // key value of last element

		map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( mycomp((*it++).first, highest) );

		std::cout << '\n';
	}
	{
		create_header("Value_comp");
		map<char,int> mymap;

		mymap['x']=1001;
		mymap['y']=2002;
		mymap['z']=3003;

		std::cout << "mymap contains:\n";

		pair<char,int> highest = *mymap.rbegin();          // last element

		map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( mymap.value_comp()(*it++, highest) );
	}

	/****************************/
	/*			Operations		*/
	/****************************/
	{
		create_header("Find");
		map<char,int> mymap;
		map<char,int>::iterator it;

		mymap['a']=50;
		mymap['b']=100;
		mymap['c']=150;
		mymap['d']=200;

		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase (it);

		// print content:
		std::cout << "elements in mymap:" << '\n';
		std::cout << "a => " << mymap.find('a')->second << '\n';
		std::cout << "c => " << mymap.find('c')->second << '\n';
		std::cout << "d => " << mymap.find('d')->second << '\n';
	}
	{
		create_header("Count");
		map<char,int> mymap;
		char c;

		mymap ['a']=101;
		mymap ['c']=202;
		mymap ['f']=303;

		for (c='a'; c<'h'; c++)
		{
			std::cout << c;
			if (mymap.count(c)>0)
			std::cout << " is an element of mymap.\n";
			else 
			std::cout << " is not an element of mymap.\n";
		}
	}
	{
		create_header("Lower and upper bound");
		map<char,int> mymap;
		map<char,int>::iterator itlow,itup;

		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;

		itlow=mymap.lower_bound ('b');  // itlow points to b
		itup=mymap.upper_bound ('d');   // itup points to e (not d!)

		mymap.erase(itlow,itup);        // erases [itlow,itup)

		// print content:
		for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		create_header("Equal range");
		map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		pair<map<char,int>::iterator,map<char,int>::iterator> ret;
		ret = mymap.equal_range('b');

		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';

		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
	}
	create_header("Diff <int,int> and <char,int>");
	{
		create_header("Map with <int, int>");
		map<int, int> b;

		b.insert( pair<int, int>(7, 1));
		b.insert( pair<int, int>(1, 20));
		b.insert( pair<int, int>(1, 22));
		b.insert( pair<int, int>(76, 15));
		b.insert( pair<int, int>(12, 2));
		b.insert( pair<int, int>(867, 234));
		b.insert( pair<int, int>(123, 123));
		b.insert( pair<int, int>(22, 1));
		b.insert( pair<int, int>(56, 5));

		printMap(b);
		std::cout << std::endl;

		std::cout << "count(76) true => " << b.count(76) << std::endl 
				<< "count(1234) false => " << b.count(1234) << std::endl;
		std::cout << "find(76) 15 => " << b.find(76)->second << std::endl
				<< "find(1234)  => " << b.find(1234)->second << std::endl;

		map<int, int>::iterator debut = b.begin();
		map<int, int>::iterator end = b.end();

		std::cout << "Print begin() and end()" << std::endl
			<< debut->first << " ==> " << debut->second << std::endl
			<< end->first << " ==> " << end->second << std::endl;

		// ++(++debut);
		// --(--end);
		std::cout << "Size before big erase " << b.size() << std::endl;
		b.erase(debut, end);
		std::cout << "Size after big erase " << b.size() << std::endl;
		printMap(b);

		pair<int, int> start = *end;
		std::cout << start.first << std::endl;
	}
	{
		create_header("Map with <char, int>");
		map<char, int> b;

		b.insert(ft::pair<char, int>('c', 11));
		b.insert(ft::pair<char, int>('a', 21));
		b.insert(ft::pair<char, int>('z', 41));
		b.insert(ft::pair<char, int>('t', 331));

		map<char, int>::iterator debut = b.begin();
		map<char, int>::iterator end = b.end();

		std::cout << "Print begin() and end()" << std::endl
			<< debut->first << " ==> " << debut->second << std::endl
			<< end->first << " ==> " << end->second << std::endl;

		std::cout << std::endl << "remove first el : " << debut->first << std::endl;
		b.erase(debut);
		b.erase(b.begin());
		printMap(b);

		std::cout << "size of b " << b.size() << std::endl;
		b.clear();
		std::cout << "size of b " << b.size() << std::endl;
		printMap(b);
	}

	{
		create_header("Insert with hint");
		map<int, int> b;

		b.insert(ft::pair<int, int>(4, 12));
		b.insert(ft::pair<int, int>(12, 442));
		b.insert(ft::pair<int, int>(1, 1122));
		b.insert(ft::pair<int, int>(10, 1122));
		b.insert(ft::pair<int, int>(14, 1122));
		b.insert(ft::pair<int, int>(34, 1122));

		b.insert(b.find(12), ft::pair<int, int>(13, 98));
		b.insert(b.find(12), ft::pair<int, int>(99, 298));
		b.insert(b.end(), ft::pair<int, int>(9, 298));
		b.insert(b.begin(), ft::pair<int, int>(19, 298));

		printMap(b);
	}
}


int	main() {
	mapMegaTest();
}