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
	int counter = 0;
	
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
	}
	*/
};

// Add other stuff, if needed


std::ostream& operator<<(std::ostream& os, const Row& dt)
{
	os << dt.key; //något liknande men detta är fel, men man ska nå key
	return os;

}



/*
//Vi returnerar den minsta
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
Row& operator<(const Row& a, const Row& b)
{

	if(a.key < b.key)
	{
		return a;
	}else{
		return b;
	}

}

//Vi returnerar den minsta
bool operator<(const Compareble& a, const Row& b)
{

	if(a.key < b.key)
	{
		return true;
	}else{
		return false;
	}

}


//Vi returnerar den minsta
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
Row* insert( std::string x, Row* t) {

	if (t == nullptr) // insert after a leaf
	{
		std::string s = "";
		// förälder är nullptr i nuläget eftersom man inte vet vem föräldern är än
		t = new Row{ s, 0, nullptr, nullptr };

	}
	else if (x < t->key)		//(x < t->key)
	{
		Row* newRow = insert(x, t->left); // får en ny nod från if-satsen ovanför

		t->left = newRow; //t->left = förälder till NewNode

		newRow->parent = t; // tillger en förälder t till den nya noden newNode

	}
	else if (t->key < x)
	{
		Row* newRow = insert(x,t->right); // får en ny nod från översta if-satsen 

		t->right = newRow;  //t->right = förälder till NewNode

		newRow->parent = t; // tillger en förälder t till den nya noden newNode
	}
	else
	{
		;  // Duplicate; do nothing
	}
	return t;
}
*/



#endif

void exercise3() {
#ifdef TEST_EXERCISE3
    {

		std::string word = "";

        std::ifstream file("../code/text.txt");  // contains 56 unique words
        // std::ifstream file("../code/text_long.txt"); // contains 497 unique words

        if (!file) {
            std::cout << "Couldn't open file text.txt\n";
            // std::cout << "Couldn't open file text_long.txt\n";
            return;
        }

		// ADD CODE: exercise 3
		
		//SKA VI HA PAIR HÄR?
		std::vector<std::string> V;


        while(file >> word)
		{
        
         // för att to-low orden
		//Den 3 word.begin() säger att vi vill lägga in/override transformationen i början av ordet. Så Elin blir elin
		//Om vi hade haft word.end() där så hade det blivit ex Elinelin för vi börjar inserta i slutet av ordet
		std::transform(word.begin(), word.end(), word.begin(), [](char c) {return static_cast<char>(std::tolower(c)); });


		// std::remove(word.begin(), word.end(), ',' är en iterator med villkor, vad den ska göra
		// anropar next funktion, returnera nästa som är enligt krav
		// remove skapar en iteror som letar upp alla komma-tecken
		// erase använder iteratorn för att ta bort ','
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
		V.push_back(word);
		
		// Read all words in the file into a vector
		//std::vector<std::string> V{ std::istream_iterator<std::string>{word},
								  // std::istream_iterator<std::string>{} };


		file.close();



		std::cout << "\nMade Innan loop\n";


		// Create a tree
		BinarySearchTree<Row> t; //Binärt träd med rader.

		Row r;
		r.key = V[2];
		t.insert(r); //sätter in ett objekt från row r i tree t
	
		std::cout << "\nSTART TREE\n";
		// Display the tree
		std::cout << "Tree: \n";
		t.printTree();
		std::cout << '\n';
		std::cout << "\nEND TREE\n";
        }



    }
	
	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

    std::cout << "Success!!\n";
#endif		
}