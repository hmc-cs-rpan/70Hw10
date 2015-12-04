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
	// Nothing to do here
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
	return height_;
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
void TreeSet<T>::insertNode(const Node* node, const T& key) 
{
	// Nothing to do here
}

template <class T>
void TreeSet<T>::deleteNode(const Node* node) 
{
	if(node != nullptr) {
		deleteNode(node->leftChild_);
		deleteNode(node->rightChild_);
		delete node;
	}
}

// --------------------------------------------
// Implementation of TreeSet::Node
// --------------------------------------------
//
template <class T>
TreeSet<T>::Node::Node(T& value) 
	: value_(value), leftChild_(nullptr), rightChild_(nullptr), descendants_(0)
{
	// Nothing to do here
}