#pragma once

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

	//get_parent och display har vi ej testat men försökt skriva, inga errors
	//Har ej kollat om vi har leaks
    // problem med clone


	std::pair<Comparable, Comparable> find_pred_succ(const Comparable& x) const
    {
        // comparable är ett interface, alla noder ärver det
        // auto fungerar också men get inte exmepel när man kodar
		//Node *t = this;

		
		Node *t = root;
        Comparable a = -100000;
        Comparable b = 100000;
		
        std::pair<Comparable, Comparable> aANDb = std::make_pair(a,b);
        
        while ((t->left != nullptr) && (t->right != nullptr) ) {

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

                }
                else if (t->right == nullptr) {

                    Node* dummy3 = findMax(t->left);
                    aANDb.first = dummy3->element; // updatera a
                }
                else if (t->left == nullptr) {

                    Node* dummy4 = findMin(t->right);
                    aANDb.second = dummy4->element; // updatera b
                     
                }

            }



        }
        return aANDb;

    } // end of find_pred_succ(const Comparable& x) const

	Comparable get_parent(int x) {

		Node *temp = root;
		Node *child = contains(x, temp); //Skickar tillbaka nullptr om x inte finns
		
        
        if (child == nullptr) {
			return Comparable{};
		}
        else{
			Node* parentNode = child->parent;
                
            if(parentNode != nullptr){
                    return parentNode->element;
			}
			else {
				return Comparable{};
			}
   
        }

	}

	/********************************************************************/

    BinarySearchTree() : root{nullptr} {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{clone(rhs.root, nullptr)} {
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree &operator=(BinarySearchTree _copy) {
        std::swap(root, _copy.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMin(root)->element;
    }
	
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const {
        return (contains(x, root) != nullptr);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(std::ostream &out = std::cout) const {
        
        
        if (isEmpty()) {
            out << "Empty tree";
        } else {
           // inorder(root, out);
           int indent = 0;

           preorder (root, out, indent);
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty() {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x) {
        root = insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        root = remove(x, root);
    }

    /** Return total number of existing nodes
     *
     * Used for debug purposes
     */
    static int get_count_nodes() {
        return Node::count_nodes;
    }

private:
    Node *root;

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    Node *insert(const Comparable &x, Node *t) {

        if (t == nullptr) // insert after a leaf
        {
			// förälder är nullptr i nuläget eftersom man inte vet vem föräldern är än
            t = new Node{x, nullptr, nullptr, nullptr};  

        }
        else if (x < t->element)
        {
            Node *newNode = insert(x, t->left); // får en ny nod från if-satsen ovanför
            
            t->left = newNode; //t->left = förälder till NewNode

			newNode->parent = t; // tillger en förälder t till den nya noden newNode

        }
        else if (t->element < x)
        {
            Node *newNode = insert(x, t->right); // får en ny nod från översta if-satsen 

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
    Node *remove(const Comparable &x, Node *t) {
        if (t == nullptr) {
            return t;  // Item not found
        }
        if (x < t->element)
        {

            Node *dummyNode =  remove(x, t->left);
            
            t->left = dummyNode; 

			if(dummyNode != nullptr){
                dummyNode->parent = t;
            }

            //t->left = remove(x, t->left);
        }
        else if (t->element < x)
        {
            Node *dummyNode =  remove(x, t->right);
            
            t->right = dummyNode; 

			//Ifall vi är vid roten. Root har ingen förälder
			if (dummyNode != nullptr) {
				dummyNode->parent = t;
			}
			    
        
            //t->right = remove(x, t->right);
        }
        else if (t->left != nullptr && t->right != nullptr)
        {  
            // Two children
            // no removing, only switching nodes, parent and left child
            t->element = findMin(t->right)->element;
            t->right = remove(t->element, t->right);
        }
        else
        {
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right; //oldNode->left : OldNode->right

			//oldNode->parent = nullptr; //är detta rätt?? Är detta enda?
			//Kan ha leaks här?


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
    Node *findMin(Node *t) const {
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
    Node *findMax(Node *t) const {
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
    Node *contains(const Comparable &x, Node *t) const {
        if (t == nullptr) {
            return t;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
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
    Node *makeEmpty(Node *t) {
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
    void inorder(Node *t, std::ostream &out) const {
        if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }
    }


    /**********************EXCERCISE 1 @Fei_Elin ***********************/

    void preorder(Node *t, std::ostream &out, int indent) const{

        

        if (t != nullptr) {
            // Do something: printar ut före den noden vi är i före vi går vidare i tree
            
            out << std::string(indent, ' ')<< t->element << '\n';
            //std::cout << "HEHJHJKJSKD" << '\n';

            indent= indent +2;
            preorder(t->left, out, indent);
            preorder(t->right, out, indent); //Går den först hela vänster sidan innan höger sida?
        }
 
    }

    /**
     * Private member function to clone subtree.
     *////Denna funkar ej kolla vidare på, debugg. Förälderna
    Node *clone(Node *t, Node* parent) const {


        if (t == nullptr) {
            return nullptr;
        } else {

            parent = new Node{t->element, nullptr, nullptr, parent};
            parent->left = clone(t->left, parent);
            parent->right = clone(t->right, parent);

            return parent;

        }//t->parent föräldern är redan clonad så vi behöver ej skriva clone(t->parent)
    }
};

// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"