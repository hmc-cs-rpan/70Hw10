/** 
 * \file treeset-private.hpp
 *
 * \authors Ricky Pan, Amy Huang
 *
 * \brief Implements TreeSet<T>, a binary search tree class template
 */

#include <random>

template <class T>
TreeSet<T>::TreeSet() : root_(nullptr), size_(0), dis_(0,1)
{
	seed();
}

template <class T>
TreeSet<T>::~TreeSet() 
{
	deleteNode(root_);
}

template <class T>
size_t TreeSet<T>::size() const 
{
	return size_;
}

template <class T>
void TreeSet<T>::insert(const T& key) 
{
	insertNode(root_, key);
	++size_;
}

template <class T>
bool TreeSet<T>::exists(const T& key) const 
{
	if(size_ == 0) {
		return false;
	}
	return existsNode(root_, key);
}

template <class T>
int TreeSet<T>::height() const 
{
	return heightNode(root_);
}

template <class T>
std::ostream& TreeSet<T>::showStatistics(std::ostream& out) const 
{
	out << size_ << " nodes, height " << height() << std::endl;
	return out;
}

template <class T>
std::ostream& TreeSet<T>::print(std::ostream& out) const
{
	printNode(root_, out);
	return out;
}

template <class T>
bool TreeSet<T>::existsNode(const Node* node, const T& key) const
{
	if (node == nullptr) {
		return false;
	}
	else if (key < node->value_) {
		return existsNode(node->leftChild_, key);
	}
	else if (node->value_ < key) {
		return existsNode(node->rightChild_, key);
	}
	else {
		return true;
	}
}

template <class T>
void TreeSet<T>::insertNode(Node*& node, const T& key) 
{
	double randomNum = getRandomFloat();

	if (node == nullptr) {
		node = new Node{key};
	}
	// There is a 1/(descendants_+1) probability of inserting at root
	else if (randomNum < 1.0/(node->descendants_+1)) {
		insertNodeAtRoot(node, key);
	}
	else if (key < node->value_) {
		++node->descendants_;
		insertNode(node->leftChild_, key);
	}
	else {
		++node->descendants_;
		insertNode(node->rightChild_, key);
	}
}

template <class T>
void TreeSet<T>::deleteNode(Node* node) 
{
	if (node != nullptr) {
		deleteNode(node->leftChild_);
		deleteNode(node->rightChild_);
		delete node;
	}
}

template <class T>
void TreeSet<T>::insertNodeAtRoot(Node*& node, const T& key)
{
	if (node == nullptr) {
		node = new Node{key};
	}
	else if (key < node->value_) {
		++node->descendants_;
		insertNodeAtRoot(node->leftChild_, key);
		rotateRight(node);
	}
	else {
		++node->descendants_;
		insertNodeAtRoot(node->rightChild_, key);
		rotateLeft(node);
	}
}

template <class T>
int TreeSet<T>::heightNode(const Node* node) const
{
	if (node == nullptr) {
		return -1;
	}
	else {
		return 1 + std::max(heightNode(node->leftChild_), 
			heightNode(node->rightChild_));
	}
}

template <class T>
void TreeSet<T>::printNode(const Node* node, std::ostream& out) const
{
	if (node == nullptr) {
		out << "-";
	}
	else {
		out << "(";
		printNode(node->leftChild_, out);
		out << ", ";
		out << node->value_ << ", ";
		printNode(node->rightChild_, out);
		out << ")"; 
	}
}

template <class T>
void TreeSet<T>::rotateLeft(Node*& top) 
{
	Node* newTop = top->rightChild_;		// Value of new root
	top->rightChild_ = newTop->leftChild_;
	newTop->leftChild_ = top;
	top = newTop;

	// Update descendant counts, as long as Nodes exist
	top->descendants_ += 1;
	top->leftChild_->descendants_ -= 1;
	if (top->leftChild_->leftChild_ != nullptr) {
		top->descendants_ += 1 + top->leftChild_->leftChild_->descendants_;
	}
	if (top->rightChild_ != nullptr) {
		top->leftChild_->descendants_ -= 1 + top->rightChild_->descendants_;
	}
}

template <class T>
void TreeSet<T>::rotateRight(Node*& top) 
{
	Node* newTop = top->leftChild_;		// Value of new root
	top->leftChild_ = newTop->rightChild_;
	newTop->rightChild_ = top;
	top = newTop;

	// Update descendant counts, as long as Nodes exist
	top->descendants_ += 1;
	top->rightChild_->descendants_ -= 1;
	if (top->rightChild_->rightChild_ != nullptr) {
		top->descendants_ += 1 + top->rightChild_->rightChild_->descendants_;
	}
	if (top->leftChild_ != nullptr) {
		top->rightChild_->descendants_ -= 1 + top->leftChild_->descendants_;
	}
}

template <class T>
void TreeSet<T>::seed()
{
    std::random_device rd;
    gen_.seed(rd());
}

template <class T>
float TreeSet<T>::getRandomFloat()
{
    return dis_(gen_);
}

// --------------------------------------------
// Implementation of TreeSet::Node
// --------------------------------------------
//
template <class T>
TreeSet<T>::Node::Node(const T& value) 
	: value_(value), leftChild_(nullptr), rightChild_(nullptr), descendants_(0)
{
	// Nothing to do here
}