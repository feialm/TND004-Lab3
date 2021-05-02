#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>  //assert

#include <iterator>
#include <sstream>
#include <string>
#include <ostream>


#include "BinarySearchTree.h"

#define TEST_EXERCISE3

/* *********************************************
 * Exercise 3: frequency table
 ********************************************* */

#ifdef TEST_EXERCISE3


struct Row
{
	// ADD CODE: exercise 3

	std::string key = "";
	int counter = 1;

	// i insert() i binarysearchtree kollar man t->element
	// i en row är det t->element men eftersom en row har två värden
	// skapar man egna operatorer för att JÄMFÖRA key
	// insert() i binarysearch vet inte vad den ska jämföra och den kallar på dessa operator-funktioner

	bool operator<(const Row& rhs) const
	{
		if (key < rhs.key)
		{
			return true;
		}
		else {
			return false;
		}
	}


	bool operator>(const Row& rhs) const
	{
		if (key > rhs.key)
		{
			return true;
		}
		else {
			return false;
		}
	}


	bool operator==(const Row& rhs) const
	{
		if (key == rhs.key)
		{
			return true;
		}
		else {
			return false;
		}
	}

	
};

// Add other stuff, if needed

std::ostream& operator<<(std::ostream& os, const Row& dt)
{
	int indent = 10;
	os << dt.key << std::string(indent, ' ') << dt.counter; //något liknande men detta är fel, men man ska nå key
	return os;

}



#endif

void exercise3() {
#ifdef TEST_EXERCISE3
    {

		std::string word = "";

        std::ifstream file("../code/text.txt");  // contains 56 unique words
        //std::ifstream file("../code/text_long.txt"); // contains 497 unique words

        if (!file) {
            std::cout << "Couldn't open file text.txt\n";
          //std::cout << "Couldn't open file text_long.txt\n";
            return;
        }

		// ADD CODE: exercise 3
		

		// Create a tree
		BinarySearchTree<Row> table; //Binärt träd med rader.
		std::vector<Row>V;

        while(file >> word)
		{
        
		// den tredje argumentet word.begin --> säger att man vill lägga in/override transfomrationen o böjran av ordet
		// alltså att man ändrar från början till slut i order, Elin --> elin, HEJ --> hej

		//den tredje haft word.end() där så hade det blivit ex Elinelin för vi börjar inserta i slutet av ordet

		std::transform(word.begin(), word.end(), word.begin(), [](char c) {return static_cast<char>(std::tolower(c)); });


		// remove skapar en iteror som letar upp alla tecken
		// std::remove(word.begin(), word.end(), ',' är en iterator med villkor som letar upp det där tecknet
		// anropar next funktion, returnera nästa som är enligt krav
		// erase använder iteratorn för att ta bort 'tecken'
		// word.erase, det är funktionen erase som tar bort tecknen från objektet word
		
		word.erase(std::remove(word.begin(), word.end(), ','), word.end());
		word.erase(std::remove(word.begin(), word.end(), '.'), word.end());
		word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
		word.erase(std::remove(word.begin(), word.end(), '?'), word.end());
		word.erase(std::remove(word.begin(), word.end(), '!'), word.end());
		word.erase(std::remove(word.begin(), word.end(), ')'), word.end());
		word.erase(std::remove(word.begin(), word.end(), '('), word.end());
		word.erase(std::remove(word.begin(), word.end(), '/'), word.end());
		word.erase(std::remove(word.begin(), word.end(), ';'), word.end());
		word.erase(std::remove(word.begin(), word.end(), ':'), word.end());
		
		//remove_if kan man göra det i en linje


		Row r;
		r.key = word;

		// man gör en iterator och kollar om ordet word =r.key finns
		// om den inte finns får man tilbaka table.end()
		// eftersom man har gått igenom det man har av trädet just nu
		BinarySearchTree<Row>::Iterator compareWord = table.find(r);

			if (compareWord == table.end()) {

				table.insert(r); //sätter in ett objekt från row r i tree t eftersom det inte finns än

			}
			else {
				compareWord->counter++; // om ordet redan finns ökar counter på det ordet
			}

        }//while-loop ends




		for (auto i = table.begin(), end = table.end(); i != end; ++i) {
			auto counterV = *i; //transform an interator into a counter
			V.push_back(counterV);
		}


		file.close(); // stänger filen EFTER vi har insetat alla word till binary search

		// Display the tree
		std::cout << "---------Tree: -----------\n";
		table.printTree();
		std::cout << '\n';
		std::cout << "\nEND TREE\n\n";




		// Display the freq.table
		std::cout << "------ Table: ----------\n";

		// skapar en iterator som kan gå igenom vector V och ta fram key och counter
		for (std::vector<Row>::const_iterator j = V.begin(); j != V.end(); ++j) {

			// variabler som ger mellanslag mellan ord och counter
			const char separator = ' ';
			const int wordWidth = 25; //utrymme finns för 25 bokstäver i ett ord
			const int counterWidth = 3; //utrymme för counter

			// left gör att j->key och j->counte rbörja rtill vänster i sitt lilla utrymme
			std::cout << std::left << std::setw(wordWidth) << std::setfill(separator) << j->key;
			std::cout<< std::left << std::setw(counterWidth) << std::setfill(separator) << j->counter << "\n";

		}

		std::cout << "\nEND TABLE\n\n";



		// COMPARE FACIT WITH FACIT
		// för att kunna jämföra vectorerna ska man göra en vector av facit-filerna
		// jämför vector som skapats av binary tree, binary tree har skapats av textfiler
	
		std::ifstream file2("../code/frequency_table.txt");  // facit for text.txt
		//std::ifstream file2("../code/frequency_table_long.txt"); // facit for text_long.txt

		std::vector<Row> facit;
		std::string aWord;
		int counter2;

		while (file2 >> aWord >> counter2) {
			Row prepareForFacit;
			prepareForFacit.key = aWord;
			prepareForFacit.counter = counter2;
			facit.push_back(prepareForFacit);
		}

		 assert(V == facit); // COMPARE FACIT WITH FACIT

	}

	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

    std::cout << "Success!!\n";
#endif		
}





/*
Row& operator<(const Row& a, const Row& b)
{

	if(a.key < b.key)
	{
		return a;
	}else{
		return b;
	}

}


// returnerar den minsta
bool operator<(const Compareble& a, const Row& b)
{

	if(a.key < b.key)
	{
		return true;
	}else{
		return false;
	}

}


// returnerar den minsta
bool operator<(const Row& a, const Compareble& b)
{

	if(a.key < b.key)
	{
		return true;
	}else{
		return false;
	}

}
*/


/*
bool operator<(const Row& rhs)const {
	if (key < rhs.key) {
		return true;
	}
	else {
		return false;
	}
}*/



/*
// returnerar den minsta
bool operator<(const Row& a, const Row& b)
{

	if(a.key < b.key)
	{
		return true;
	}else{
		return false;
	}

}
*/
