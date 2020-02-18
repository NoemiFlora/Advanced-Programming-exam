#ifndef ___iterator__
#define ___iterator__

#include<memory>
#include "Node.hpp"

/*The class iterator has a pointer to the node that it's pointing to.*/

template<typename node_t, typename T>
class _iterator{
private:
  node_t* current;

public:
  using pair_type = T;
  using reference = pair_type&;
  using pointer = pair_type*;
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;


/*We made a function that extracts the pointer pointing to the node, since
it is private.*/
node_t* Current() const noexcept {return current;}

/*Costructors
We made a default costructor and the one that has as argument a pointer to a node,
it will be useful when we have to return an iterator and we have a pointer to the respective node.*/
_iterator() noexcept = default;
explicit _iterator(node_t* x) noexcept:current{x} {}

/*Simply a default destructor.*/
~_iterator() = default;

/*Here we made two overload operators because we want to access to the pair and
not to the entire node, iterators don't need to know if a node has children or not.*/
reference operator*() const noexcept {return current->val;}
pointer operator->() const noexcept {return &(*(*this));}

/*We overloaded operators == and != to compair if two iterators are equal or not.*/
friend bool operator == (const _iterator& a, const _iterator& b){return a.current == b.current;}
friend bool operator != (const _iterator& a, const _iterator& b){return !(a==b);}

/*The following operator will be useful to read through the tree.*/
_iterator& operator++() noexcept{
  if(current){
    if(current->right){current = left_nephew(current->right.get());}
    else{
      while(current->parent && current == (current->parent->right).get()){current = current->parent;}
      current = current->parent;
    }
  }
  return *this;
  }
};


#endif
