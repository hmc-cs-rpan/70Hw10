/**
 * \file treeset.hpp
 * \author Ricky Pan, Amy Huang
 *
 * \brief Provides TreesSet<T>, a set class template, using
 *		  a randomized binary search tree
 */

#ifndef TREESET_HPP_INCLUDED
#define TREESET_HPP_INCLUDED 1

#include <cstddef>
#include <iostream>

template <class T>
class TreeSet {


struct Node;

public:
	/// Default constructor
	TreeSet();

	/// Destructor
	~TreeSet();

	TreeSet(const TreeSet&) = delete;
	TreeSet operator=(const TreeSet&) = delete;

	/**
	 * \brief Returns the size of the tree
	 */
	size_t size() const;

	/**
	 * \brief Inserts an element into the tree
	 *
	 * \param T&, a templated object
	 */
	void insert(const T& key);

	/**
	 * \brief Checks if an element is in the tree
	 *
	 * \param T&, a templated object
	 *
	 * \returns true if T is present in the tree
	 */
	bool exists(const T& key) const;

	/// Returns the height of the tree
	int height() const;

	/// Prints the relevant statistics about the tree
	std::ostream& showStatistics(std::ostream& out) const;

	/// Recursively prints the tree
	std::ostream& print(std::ostream&) const;

	/// Recursively deletes Nodes, helper function for the destructor
	void deleteNode(const Node* node);

	/// Recursively checks Nodes, helper function for exists
	bool existsNode(const Node* node, const T& key) const;

	/// Recursively inserts a Node, helper function for insert
	void insertNode(Node*& node, const T& key);

	/// Insert a node at the root instead of the leaf
	void insertNodeAtRoot(Node*& node, const T& key);

	/// Left rotation about the node 
	void rotateLeft(Node*& top);

	/// Right rotation about the node 
	void rotateRight(Node*& top);


private:
	struct Node {
		T value_;
		Node* leftChild_;
		Node* rightChild_;
		size_t descendants_;

		Node(const T& value);
	};

	Node* root_;
	size_t size_;

};

#include "treeset-private.hpp"

#endif // TREESET_HPP_INCLUDED