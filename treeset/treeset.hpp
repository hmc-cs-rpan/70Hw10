/**
 * \file treeset.hpp
 * \author Ricky Pan, Amy Huang
 *
 * \brief Provides TreesSet<T>, a set class template, using
 *        a randomized binary search tree
 */

#ifndef TREESET_HPP_INCLUDED
#define TREESET_HPP_INCLUDED 1

#include <cstddef>
#include <iostream>
#include <random>

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
     * \param T& key, the templated object to insert
     *
     * \details For each recursive step, there is a probability
     *          of 1/(number of descendants of the current node + 1)
     *          that the element will be inserted at that node
     */
    void insert(const T& key);

    /**
     * \brief Checks if an element is in the tree
     *
     * \param T& key, the templated object to search for
     *
     * \returns true if T is present in the tree
     */
    bool exists(const T& key) const;

    /// Returns the height of the tree
    int height() const;

    /// Prints the size and height of the tree
    std::ostream& showStatistics(std::ostream& out) const;

    /// Recursively prints the tree
    std::ostream& print(std::ostream&) const;


    // --------------------------------------------
    // Helper functions
    // --------------------------------------------

    /// Recursively delete Nodes, helper function for the destructor
    void deleteNode(const Node* node);

    /// Recursively check if a Node exists, helper function for exists
    bool existsNode(const Node* node, const T& key) const;

    /// Recursively insert a Node, helper function for insert
    void insertNode(Node*& node, const T& key);

    /// Insert a node at the root instead of the leaf
    void insertNodeAtRoot(Node*& node, const T& key);

    /// Helper function for height()
    int heightNode(const Node* node) const;

    /// Helper function to print a node
    void printNode(const Node* node, std::ostream& out) const;

    /// Left rotation about the node 
    void rotateLeft(Node*& top);

    /// Right rotation about the node 
    void rotateRight(Node*& top);

    /// Generate random numbers
    float getRandomFloat();


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

    std::uniform_real_distribution<> dis_;
    std::mt19937 gen_;

    void seed();

};

#include "treeset-private.hpp"

#endif // TREESET_HPP_INCLUDED
