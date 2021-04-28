#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
public:
    // Some properties for Iterator  -- so that Iterator can be used with STL-algorithms
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Comparable;
    using pointer           = Comparable*;  // or also value_type*
    using reference         = Comparable&;  // or also value_type&

	//Från länken om iteratorer i labbbeskrivningen @ElinFei

	// contructor 2 st one public, one private
	// default
	Iterator() : p(nullptr) {}

	//reference operator*() const { return *m_ptr; }
	//pointer operator->() { return m_ptr; }
	
	//Iterator& operator++() {p++; return *this; } // Prefix increment
	Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }  // Postfix increment

	//Iterator& operator--() { p--; return *this; } // Prefix increment
	Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }  // Postfix increment
	friend bool operator== (const Iterator& a, const Iterator& b) { return a.p == b.p; };
	friend bool operator!= (const Iterator& a, const Iterator& b) { return a.p != b.p; };


	// Exercise 2: ADD CODE 

	Iterator& operator++()
	{
		
		p = pointTree->find_successor(p);
		return *this;
	}

	Iterator& operator--()
	{
		 p = pointTree->find_predecessor(p);
		return *this;
	}

	/////////////////////////////////////////
	//Ta bort alla current!!! 
	// return value node is pointing at
	Comparable& operator*()
	{
		Node* current = p;
		return current->element;
	}

	// a reference to a value
	Comparable* operator->()
	{
		Node* current = p;
		return &(current->element); //memroy location
	}

	/*

	bool operator==(Iterator a, Iterator b)
	{

		if (a == b)
		{
			return true;
		}
		else {
			return false;
		}

	}

	bool operator!=(Iterator a, Iterator b)
	{
		if (a == b)
		{
			return false;
		}
		else {
			return true;
		}
	}
	*/

private:
	Node* p;
	BinarySearchTree* pointTree;

	//Var ska end och begin vara?
	//Iterator begin();
	//Iterator end();

	//constructor
	// tree is pointing to tree
	// t is pointing to node
	Iterator(Node* point, BinarySearchTree* tree) : p{ point }, pointTree{tree} {
		//Sök efter p = den du är på 
		//pointtree = trädet
		//++count_nodes;
	}


    /* ****************************************************************** */
	template <typename Comparable>
    friend class BinarySearchTree;



	

}; // end of class BinarySearchTree<Comparable>::Iterator