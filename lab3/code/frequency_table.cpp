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

	// returnerar den minsta
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
	os << dt.key << std::string(indent, ' ') << dt.counter; //n�got liknande men detta �r fel, men man ska n� key
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
		BinarySearchTree<Row> table; //Bin�rt tr�d med rader.
		std::vector<Row>V;

        while(file >> word)
		{
        
        // f�r att to-low orden
		//Den 3 word.begin() s�ger att vi vill l�gga in/override transformationen i b�rjan av ordet. S� Elin blir elin
		//Om vi hade haft word.end() d�r s� hade det blivit ex Elinelin f�r vi b�rjar inserta i slutet av ordet
		std::transform(word.begin(), word.end(), word.begin(), [](char c) {return static_cast<char>(std::tolower(c)); });


		// std::remove(word.begin(), word.end(), ',' �r en iterator med villkor, vad den ska g�ra
		// anropar next funktion, returnera n�sta som �r enligt krav
		// remove skapar en iteror som letar upp alla n�got-tecken
		// erase anv�nder iteratorn f�r att ta bort 'tecken'
		// word.erase, det �r funktionen erase som tar bort tecknen fr�n objektet word
		
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
		
		//remove_if kan man g�ra det i en linje

		
		// Read all words in the file into a vector
		//std::vector<std::string> V{ std::istream_iterator<std::string>{word},
								  // std::istream_iterator<std::string>{} };



		BinarySearchTree<Row>::Iterator compareWord = table.begin();
		Row r;
		r.key = word;

		//BinarySearchTree<Row>::Iterator compareWord = table.find(r);
		compareWord = table.find(r);

			// ifsats
			if (compareWord == table.end()) {

				table.insert(r); //s�tter in ett objekt fr�n row r i tree t
				//push_back(word);
			}
			else {
				compareWord->counter++; // om ordet redan finns �kar counter
			}

	
        }//while-loop ends

		
		/*
		BinarySearchTree<Row>::Iterator p; 


		// put values from table (Binary search tree) into a vector
		for (p = table.begin(); p != table.end(); p++) {
			Row toVector;
			toVector.key = p->key;
			toVector.counter = p->counter;
			V.push_back(toVector);
		}*/


		for (auto i = table.begin(), end = table.end(); i != end; ++i) {
			auto counterV = *i; //transform an interator into a counter
			V.push_back(counterV);
		}


		file.close(); // st�nger filen EFTER vi har insetat alla word till binary search

		// Display the tree
		std::cout << "---------Tree: -----------\n";
		table.printTree();
		std::cout << '\n';
		std::cout << "\nEND TREE\n\n";


		/*
		// Display the freq.table
		std::cout << "------ Table: ----------\n";
		table.printTable();
		std::cout << '\n';
		std::cout << "\nEND TABLE\n\n";
		*/

		// Display the freq.table
		std::cout << "------ Table: ----------\n";

		// skapar en iterator som kan g� igenom vector V och ta fram key och counter
		for (std::vector<Row>::const_iterator j = V.begin(); j != V.end(); ++j) {

			// variabler som ger mellanslag mellan ord och counter
			const char separator = ' ';
			const int wordWidth = 25; //utrymme finns f�r 25 bokst�ver i ett ord
			const int counterWidth = 3; //utrymme f�r counter

			// left g�r att j->key och j->counte rb�rja rtill v�nster i sitt lilla utrymme
			std::cout << std::left << std::setw(wordWidth) << std::setfill(separator) << j->key;
			std::cout<< std::left << std::setw(counterWidth) << std::setfill(separator) << j->counter << "\n";

		}

		std::cout << "\nEND TABLE\n\n";



		// COMPARE FACIT WITH FACIT
	
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
Row* insert( std::string x, Row* t) {

	if (t == nullptr) // insert after a leaf
	{
		std::string s = "";
		// f�r�lder �r nullptr i nul�get eftersom man inte vet vem f�r�ldern �r �n
		t = new Row{ s, 0, nullptr, nullptr };

	}
	else if (x < t->key)		//(x < t->key)
	{
		Row* newRow = insert(x, t->left); // f�r en ny nod fr�n if-satsen ovanf�r

		t->left = newRow; //t->left = f�r�lder till NewNode

		newRow->parent = t; // tillger en f�r�lder t till den nya noden newNode

	}
	else if (t->key < x)
	{
		Row* newRow = insert(x,t->right); // f�r en ny nod fr�n �versta if-satsen

		t->right = newRow;  //t->right = f�r�lder till NewNode

		newRow->parent = t; // tillger en f�r�lder t till den nya noden newNode
	}
	else
	{
		;  // Duplicate; do nothing
	}
	return t;
}
*/


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
// Constructors
Row(std::string word, int number)
	: key{ word }, counter{ number }{
	//++count_nodes;
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

/*
bool operator>(const Row& a, const Row& b)
{

	if (a.key > b.key)
	{
		return true;
	}
	else {
		return false;
	}

}*/