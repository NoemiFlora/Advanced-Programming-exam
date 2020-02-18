#ifndef __Node__
#define __Node__

#include<memory>

/*The struct node has a pair made of a key and a value and three pointers.
The first pointer is a pointer to a node, more precisly to its parent. It is
just a raw pointer because we don't need any responsability in this case. The other
two pointers, which are one for the right and the other for the left child, are
unique pointer because we want that only the parent is responsable for them
(this means to have ownership).*/

template<typename T>
struct Node {
  using pair_type = T;
  T val;
  Node* parent = nullptr;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;

  Node() = default;
/*Costructors.
We decided to make these two custom constructors. The first one has as argument the pair
of key and value and all the pointers are set to nullptr. The second one has as argument
the pair and its parent, meanwhile the children are set to be zero.*/
  explicit Node(T _val):val{_val}{}
  Node(T _val, Node* p):val{_val}, parent{p}{}

/*We simply use a default destructor.*/
  ~Node() = default;

};

/*Function that returns a pointer to the leftmost node.*/
template <typename T>
Node<T>* left_nephew(Node<T>* n) noexcept{
  if(!n){return n;}
  else{
    if(n->left){return left_nephew(n->left.get());}
    else {return n;}
  }
}

#endif
