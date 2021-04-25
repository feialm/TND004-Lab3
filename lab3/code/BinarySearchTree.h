#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>  // used in node.h

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

	//get_parent och display har vi ej testat men f�rs�kt skriva, inga errors
	//Har ej kollat om vi har leaks
    // problem med clone


	std::pair<Comparable, Comparable> find_pred_succ(const Comparable& x) const
    {
        // comparable �r ett interface, alla noder �rver det
        // auto fungerar ocks� men get inte exmepel n�r man kodar
		Node t = root;
        Comparable a,b;
        
        
		if (x > t.value) {
			a = t.value;
			t = t->right;
		}
		else if (x < t.value) {
			b = t.value;
			t = t->left;
		}
		else if (x == t.value) {
			
            if ((t->right !=nullptr) && (t->left !=nullptr)) {
				a = findMax(t->left);
				a = findMin(t->right);
                
            }
			else if (t->right == nullptr) {
				b = findMin(t->right);
			}
			else if (t->left== nullptr) {
                a = findMax(t->left);
			}
			
		}


		return std::pair<a, b>;

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
    BinarySearchTree(const BinarySearchTree &rhs) : root{clone(rhs.root)} {
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
            inorder(root, out);
           // preorder (root, out);
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
			// f�r�lder �r nullptr i nul�get eftersom man inte vet vem f�r�ldern �r �n
            t = new Node{x, nullptr, nullptr, nullptr};  

        }
        else if (x < t->element)
        {
            Node *newNode = insert(x, t->left); // f�r en ny nod fr�n if-satsen ovanf�r
            
            t->left = newNode; //t->left = f�r�lder till NewNode

			newNode->parent = t; // tillger en f�r�lder t till den nya noden newNode

        }
        else if (t->element < x)
        {
            Node *newNode = insert(x, t->right); // f�r en ny nod fr�n �versta if-satsen 

            t->right = newNode;  //t->right = f�r�lder till NewNode

            newNode->parent = t; // tillger en f�r�lder t till den nya noden newNode
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

			//Ifall vi �r vid roten. Root har ingen f�r�lder
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

			//oldNode->parent = nullptr; //�r detta r�tt?? �r detta enda?
			//Kan ha leaks h�r?


            /*
            if(t->left != nullptr) {
                //if true, att t->left INTE �r nullptr
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

    void preorder(Node *t, std::ostream &out) const{
        
        // Do something: printar ut f�re den noden vi �r i f�re vi g�r vidare i tree
        out << t->element << '\n';

        if (t != nullptr) {
            preorder(t->left, out);
            preorder(t->right, out);//G�r den f�rst hela v�nster sidan innan h�ger sida?
        }
    }

    /**
     * Private member function to clone subtree.
     *////Denna funkar ej kolla vidare p�, debugg. F�r�lderna
    Node *clone(Node *t) const {


        if (t == nullptr) {
            return nullptr;
        } else {
            return new Node{t->element, clone(t->left), clone(t->right), clone(t->parent)};
        }//t->parent f�r�ldern �r redan clonad s� vi beh�ver ej skriva clone(t->parent)
    }
};

// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"