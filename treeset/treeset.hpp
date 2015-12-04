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

	/**
	 * \brief Returns the height of the tree
	 */
	int height() const;

	/** 
	 * \brief Prints the relevant statistics about the tree
	 */ 
	std::ostream& showStatistics(std::ostream& out) const;

	/**
	 * \brief Recursively prints the tree
	 */
	std::ostream& print(std::ostream&) const;

	/**
	 * \brief Recursively checks Nodes, helper function for exists
	 */
	bool existsNode(const Node* node, const T& key) const;

	/**
	 * \brief Recursively inserts a Node, helper function for insert
	 */
	void insertNode(const Node* node, const T& key);

	/**
	 * \brief Recursively deletes all Nodes, helper function for destructor
	 */
	void deleteNode(const Node* node);



private:
	struct Node {
		T value_;
		Node* leftChild_;
		Node* rightChild_;
		size_t descendants_;

		Node(T& value);
	};

	Node* root_;
	size_t size_;
	int height_;

};

#include "treeset-private.hpp"

#endif // TREESET_HPP_INCLUDED