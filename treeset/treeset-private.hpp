/** 
 * \file treeset-private.hpp
 *
 * \authors Ricky Pan, Amy Huang
 *
 * \brief Implements TreeSet<T>, a binary search tree class template
 */

template <class T>
TreeSet<T>::TreeSet() : root_(nullptr), size_(0), height_(-1)
{
	// Nothing to do here
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
	return 0;
}

template <class T>
std::ostream& TreeSet<T>::showStatistics(std::ostream& out) const 
{
	// Nothing to do here
}

template <class T>
std::ostream& TreeSet<T>::print(std::ostream& out) const
{
	// Print
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
	++node->descendants_;

	double randomNum = rand() % 100;

	if (node == nullptr) {
		node = new Node{key};
	}
	// There is a 1/(descendants_+1) probability of inserting at root
	else if (randomNum < 100.0/node->descendants_) {
		insertNodeAtRoot(node, key);
	}
	else if (key < node->value_) {
		insertNode(node->leftChild_, key);
	}
	else {
		insertNode(node->rightChild_, key);
	}
}

template <class T>
void TreeSet<T>::deleteNode(const Node* node) 
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
		node = new TreeSet<T>::Node(key);
	}
	else if (key < node->value_) {
		insertNodeAtRoot(node->leftChild_, key);
		rotateRight(node);
	}
	else {
		insertNodeAtRoot(node->rightChild_, key);
		rotateLeft(node);
	}
}

template <class T>
void TreeSet<T>::rotateLeft(Node*& top) 
{
	Node* newTop = top->rightChild_;		// Value of new root
	top->rightChild_ = newTop->leftChild_;
	newTop->leftChild_ = top;
	top = newTop;

	// Update descendant counts
	top->descendants_ += 2 + top->leftChild_->leftChild_->descendants_;
	top->leftChild_ -= (2 + top->rightChild_->descendants_);
}

template <class T>
void TreeSet<T>::rotateRight(Node*& top) 
{
	Node* newTop = top->leftChild_;		// Value of new root
	top->leftChild_ = newTop->rightChild_;
	newTop->rightChild_ = top;
	top = newTop;

	// Update descendant counts
	top->descendants_ += 2 + top->rightChild_->rightChild_->descendants_;
	top->rightChild_ -= (2 + top->leftChild_->descendants_);
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