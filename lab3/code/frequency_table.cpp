#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>  //assert

#include "BinarySearchTree.h"

#define TEST_EXERCISE3

/* *********************************************
 * Exercise 3: frequency table
 ********************************************* */

#ifdef TEST_EXERCISE3


struct Row {
    // ADD CODE: exercise 3

	std::string key = "";
	int counter = 0;
	Row* left = nullptr;
	Row* right = nullptr;


	 // Constructors
	Row(std::string& theWord, int theCount, Row* lt = nullptr, Row* rt = nullptr)
		: key{ theWord }, counter{ theCount }, left{ lt }, right{ rt }  {
		//heheheh
	}
	/*

	 //Copy constructors -- disallowed
    Row(const Row&) = delete;

    //Assignement operator -- disallowed
    Row& operator=(const Row&) = delete;

    // Destructor
    ~Row() {
        --count_nodes;
        assert(count_nodes >= 0);  // number of existing nodes can never be negative
    }

    static int count_nodes;  // total number of existing nodes -- to help to detect bugs in the code
	*/

private:

};


// Add other stuff, if needed
Row* insert(std::string key)
{

	// set count as 1 and left
	// and right children as NULL
	Row* newnode = new Row{"", 0, nullptr,nullptr}; //KOLLA VARF�R DETTA EJ FUNKAR
	newnode->key = key;
	newnode->counter = 1;
	newnode->left = newnode->right = NULL;

	return newnode;
}
/*
Row end() //const
{

	return Row(nullptr, nullptr);
}

Row begin()
{
	if (isEmpty())return end();
	return Row(findMin(root), this);
}
//Vad ska denna g�ra??
Row& operator=(BinarySearchTree _copy) {
		std::swap(root, _copy.root);
		return *this;
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

        while(file >> word){
        
         // f�r att to-low orden
		//Den 3 word.begin() s�ger att vi vill l�gga in/override transformationen i b�rjan av ordet. S� Elin blir elin
		//Om vi hade haft word.end() d�r s� hade det blivit ex Elinelin f�r vi b�rjar inserta i slutet av ordet
		//std::transform(word.begin(), word.end(), word.begin(), [](char c) {return static_cast<char>(std::tolower(c)); });



		// std::remove(word.begin(), word.end(), ',' �r en iterator med villkor, vad den ska g�ra
		// anropar next funktion, returnera n�sta som �r enligt krav
		// remove skapar en iteror som letar upp alla komma-tecken
		// erase anv�nder iteratorn f�r att ta bort ','
		// word.erase, det �r funktionen erase som tar bort tecknen fr�n objektet word
		/*
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
		*/
		//remove_if kan man g�ra det i en linje


        
        }



    }
	assert(BinarySearchTree<Row>::get_count_nodes() == 0);

    std::cout << "Success!!\n";
#endif		
}