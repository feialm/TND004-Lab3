#pragma once
//#include <vld.h>
#include <iostream>
#include <iomanip>
#include <cassert>  // used in node.h
#include <string>  // to print out tree


#include "dsexceptions.h"

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {

private:
	struct Node;  // nested class defined in node.h

public:
	class Iterator;  // Exercise 2: nested class to be defined in Iterator.h

	/**********************EXCERCISE 1 @Fei_Elin ***********************/
	//Tree = wors case list
	//Best case complete binary tree = height O(logn)

	//end() = O(1)
	Iterator end() //const
	{

		return Iterator(nullptr, this);
	}

	//begin() = O(n), eftersom den har findMin
	//FindMin = wors case O(n), best case O(1)
	Iterator begin()
	{
		if (isEmpty())return end();
		return Iterator(findMin(root), this);
	}

	//O(n) because contains is O(n)
	Iterator find(const Comparable& x)
	{
		if (contains(x, root) != nullptr)
		{
			return Iterator{ contains(x, root), this };
		}
		else {
			return end();
		}

	}

	// worst case: O(n^2) för det är ett while-loop samt callar på Min/Max som är O(n)
	std::pair<Comparable, Comparable> find_pred_succ(const Comparable& x) const
	{
		// comparable är ett interface, alla noder ärver det
		// auto fungerar också men get inte exmepel när man kodar
		//Node *t = this;

		Node* t = root;
		Comparable a = x;
		Comparable b = x;

		std::pair<Comparable, Comparable> aANDb = std::make_pair(a, b);
		//(t->left != nullptr) || (t->right != nullptr)
		while (t != nullptr) {

			if (x > t->element) {
				aANDb.first = t->element; // updatera a
				t = t->right;
			}
			else if (x < t->element) {
				aANDb.second = t->element; // updatera b
				t = t->left;
			}
			else if (x == t->element) {

				if ((t->right != nullptr) && (t->left != nullptr)) {

					Node* dummy1 = findMin(t->right);
					aANDb.second = dummy1->element; // updatera b

					Node* dummy2 = findMax(t->left);
					aANDb.first = dummy2->element; // updatera a
					//break; 
					t = nullptr;

				}
				if ((t->right == nullptr) && (t->left == nullptr)) {
					//break;
					t = nullptr;
				}
				else if (t->right == nullptr) {

					Node* dummy3 = findMax(t->left);
					aANDb.first = dummy3->element; // updatera a
					//break;
					t = nullptr;
				}
				else if (t->left == nullptr) {

					Node* dummy4 = findMin(t->right);
					aANDb.second = dummy4->element; // updatera b
					//break;
					t = nullptr;

				}

			}



		}
		return aANDb;

	} // end of find_pred_succ(const Comparable& x) const

	
	//O(n) om går igenom hela och det är en list
	Comparable get_parent(int x) {

		Node* temp = root;
		Node* child = contains(x, temp); //Skickar tillbaka nullptr om x inte finns


		if (child == nullptr) {
			return Comparable{};
		}
		else {
			Node* parentNode = child->parent;

			if (parentNode != nullptr) {
				return parentNode->element;
			}
			else {
				return Comparable{};
			}

		}

	}

	/********************************************************************/

	BinarySearchTree() : root{ nullptr } {
	}

	/**
	 * Copy constructor
	 */
	//O(1)
	BinarySearchTree(const BinarySearchTree& rhs) : root{ clone(rhs.root, nullptr) } {
	}

	/**
	 * Destructor for the tree
	 */
	//O(n) går igenom allt och tömmer
	~BinarySearchTree() {
		makeEmpty();
	}

	/**
	 * Copy assignment: copy and swap idiom
	 */
	//O(1)
	BinarySearchTree& operator=(BinarySearchTree _copy) {
		std::swap(root, _copy.root);
		return *this;
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	//O(n) worst case  O(1)= Throw UnderflowException if empty.
	const Comparable& findMin() const {
		if (isEmpty()) {
			throw UnderflowException{};
		}

		return findMin(root)->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	 //O(n) worst case  O(1)= Throw UnderflowException if empty.
	const Comparable& findMax() const {
		if (isEmpty()) {
			throw UnderflowException{};
		}

		return findMax(root)->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	 //O(n) kan gå igenom alla. Kallar på contains
	bool contains(const Comparable& x) const {
		return (contains(x, root) != nullptr);
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 */
	 // O(1)
	bool isEmpty() const {
		return root == nullptr;
	}

	/**
	 * Print the tree contents in sorted order.
	 */

	 // O(n)
	void printTree(std::ostream& out = std::cout) const {


		if (isEmpty()) {
			out << "Empty tree";
		}
		else {
			// inorder(root, out);
			int indent = 0;

			preorder(root, out, indent);
		}
	}



	/**
	 * Make the tree logically empty.
	 */

	// O(n) går igenom allt och tömmer
	void makeEmpty() {
		root = makeEmpty(root);
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */

	//O(n) in wors case O(1) in best case
	void insert(const Comparable& x) {
		root = insert(x, root);
	}

	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	 //O(n) in wors case O(1) in best case
	void remove(const Comparable& x) {
		root = remove(x, root);
	}

	/** Return total number of existing nodes
	 *
	 * Used for debug purposes
	 */

	 // O(1)
	static int get_count_nodes() {
		return Node::count_nodes;
	}

private:
	Node* root;


	/***********	Exercise 2	********/


	// successor - value closest after (value) Node
	// O(n) antingen findMin eller while-loop
	Node* find_successor(Node* t) const {
		//skriv om den

		if (t != nullptr) {

			if (t->right != nullptr) // t has a right sub-tree, go down in tree
			{
				return findMin(t->right);
			}
			else // successor is one of the ancestors
			{
				Node* child = t;
				Node* parent = child->parent;

				while (parent != nullptr && child == parent->right) {
					//std::cout << "parent: " << parent->element << " child: " << child->element;
					child = parent;
					parent = child->parent;
				}
				/*
				while (t != t->parent->left && t->parent != nullptr) {
					t = t->parent; // climbing up the tree, go up in tree
				}
				*/
				return parent;
			}

		}
		return t;

	}


	// predecessor - value closest before (value) Node
	// O(n) antingen findMin eller while-loop
	Node* find_predecessor(Node* t) const {


		if (t != nullptr) {

			if (t != nullptr && t->left != nullptr) // t has a left sub-tree, go down in tree
			{
				return findMax(t->left);
			}
			else // predecessor is one of the ancestors
			{
				Node* child = t;
				Node* parent = child->parent;

				while (parent != nullptr && child == parent->left) {
					child = parent;
					parent = child->parent;// climbing up the tree, go up in tree

				}
				return parent;
			}


		}
		return t;

	}

	/**
	 * Private member function to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Return a pointer to the node storing x.
	 */
	//O(n) kan gå genom hela
	Node* insert(const Comparable& x, Node* t) {

		if (t == nullptr) // insert after a leaf
		{
			// förälder är nullptr i nuläget eftersom man inte vet vem föräldern är än
			t = new Node{ x, nullptr, nullptr, nullptr };

		}
		else if (x < t->element)
		{
			Node* newNode = insert(x, t->left); // får en ny nod från if-satsen ovanför

			t->left = newNode; //t->left = förälder till NewNode

			newNode->parent = t; // tillger en förälder t till den nya noden newNode

		}
		else if (t->element < x)
		{
			Node* newNode = insert(x, t->right); // får en ny nod från översta if-satsen 

			t->right = newNode;  //t->right = förälder till NewNode

			newNode->parent = t; // tillger en förälder t till den nya noden newNode
		}
		else
		{
			;  // Duplicate; do nothing
		}
		return t;
	}

	/**
	 * Private member function to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Return a pointer to the new root of the subtree that had root x
	 */
	//O(n) kan gå genom hela
	Node* remove(const Comparable& x, Node* t) {
		
		if (t == nullptr) {
			return t;  // Searching through the whole tree, Item not found, (base case) 
		}
		if (x < t->element)
		{
			//dummynode för föräldrar
			Node* dummyNode = remove(x, t->left); //Vi går till vänster

			t->left = dummyNode;

			//Ifall vi är vid roten. Root har ingen förälder
			if (dummyNode != nullptr) {
				dummyNode->parent = t;
			}

		}
		else if (t->element < x)
		{
		
			Node* dummyNode = remove(x, t->right); //Går till höger

			t->right = dummyNode;

			//Ifall vi är vid roten. Root har ingen förälder
			if (dummyNode != nullptr) {
				dummyNode->parent = t;
			}

		}
		//Här är x = den vi är på
		else if (t->left != nullptr && t->right != nullptr)
		{
			// Two children
			// no removing, only switching nodes, parent and left child
			t->element = findMin(t->right)->element; //Måste hitta minsta värdet som är större än x. (t->right)= kollar höger sida = större än x. Byter elementet vi vill ta bort mot ett löv.
			t->right = remove(t->element, t->right);//vill nu ta bort ex 4. Skickar då in remove(4) som ligger på höger sidan om 3(3 ville vi ta bort förut)
		}
		else
		{	// if the node that should be rmeoved has one child, checks if child is a left child or right child
			Node* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right; //oldNode->left : OldNode->right

			//Kan ha leaks här?
			//oldNode->parent = nullptr; //är detta rätt?? Är detta enda?
			//oldNode->parent = t;



			/*
			if(t->left != nullptr) {
				//if true, att t->left INTE är nullptr
				t =  t->left;
			} else {
				r =  t->right;
			}
			*/


			delete oldNode;
		}
		return t;
	}

	/**
	 * Private member function to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	//O(n)
	Node* findMin(Node* t) const {
		if (t == nullptr) {
			return nullptr;
		}
		if (t->left == nullptr) {
			return t;
		}

		// Tail recursion can be easily replaced by a loop
		return findMin(t->left);  // recursive call
	}

	/**
	 * Private member function to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	//O(n)
	Node* findMax(Node* t) const {
		if (t != nullptr) {
			while (t->right != nullptr) {
				t = t->right;
			}
		}
		return t;
	}

	/**
	 * Private member function to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the subtree.
	 * Return a pointer to the node storing x, if x is found
	 * Otherwise, return nullptr
	 */

	//O(n) kan gå igenom alla
	Node* contains(const Comparable& x, Node* t) const {
		if (t == nullptr) {
			return t;
		}
		else if (x < t->element) {
			return contains(x, t->left);
		}
		else if (t->element < x) {
			return contains(x, t->right);
		}
		else {
			return t;  // Match
		}
	}

	/****** NONRECURSIVE VERSION*************************
	Node *contains(const Comparable &x, Node *t) const {
		while (t != nullptr) {
			if (x < t->element) {
				t = t->left;
			} else if (t->element < x) {
				t = t->right;
			} else {
				return t;  // Match
			}
		}
		return t;  // No match
	}
	*****************************************************/

	/**
	 * Private member function to make subtree empty.
	 */
	//O(n)
	Node* makeEmpty(Node* t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		return nullptr;
	}

	/**
	 * Private member function to print a subtree rooted at t in sorted order.
	 * In-order traversal is used
	 */
	 // O(n)
	void inorder(Node* t, std::ostream& out) const {
		if (t != nullptr) {
			inorder(t->left, out);
			out << t->element << '\n';
			inorder(t->right, out);
		}
	}


	/**********************EXCERCISE 1 @Fei_Elin ***********************/
	//O(n)
	void preorder(Node* t, std::ostream& out, int indent) const {



		if (t != nullptr) {
			// Do something: printar ut före den node den är i före går vidare i tree

			out << std::string(indent, ' ') << t->element << '\n';
			//std::cout << "HEHJHJKJSKD" << '\n';

			indent = indent + 2;
			preorder(t->left, out, indent);
			preorder(t->right, out, indent); //Går den först hela vänster sidan innan höger sida?
		}

	}

	/**
	 * Private member function to clone subtree.
	 *///

	//O(n) clonar hela trädet
	Node* clone(Node* t, Node* parent) const {


		if (t == nullptr) {
			return nullptr;
		}
		else {

			parent = new Node{ t->element, nullptr, nullptr, parent };
			parent->left = clone(t->left, parent);
			parent->right = clone(t->right, parent);

			return parent;

		}//t->parent föräldern är redan clonad så vi behöver ej skriva clone(t->parent)
	}
};

// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"