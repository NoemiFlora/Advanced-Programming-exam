#ifndef __bst__
#define __bst__

#include<iostream>
#include<utility>
#include<memory>
#include<vector>
#include<cmath>
#include<string>
#include "Node.hpp"
#include "_iterator.hpp"

/*This is the class BST, "Binary Search Tree", it is templated on Key Type, Value Type
and the operator of comparison, which is put as std::less<KT> as default.*/
template<typename KT, typename VT, typename cmp = std::less<KT>>
class bst{
private:

  using pair_type = std::pair<const KT, VT>;
  using node_type = Node<pair_type>;
  using iterator = _iterator<node_type, typename node_type::pair_type>;
  using const_iterator=_iterator<node_type, const typename node_type::pair_type>;

  std::unique_ptr<node_type> root;	/*Unique pointer that points to the node at the top of the tree.*/
  cmp op;

  //Function that makes a deep copy of the tree, given the pointer to a node.
   void copy(const node_type* n){
     if(n){
     insert(n->val);
     if(n->left){copy((n->left).get());}
     if(n->right){copy((n->right).get());}
     }
   }

  //Function that, given a key and a pointer to a node, if the key is present ("under" the given node), returns an iterator to the proper node, end() otherwise.
  iterator find(const KT& x, node_type* n) noexcept{
    if(!n){return end();}
    else if(x == n->val.first){return iterator{n};}
    else if(op(x, n->val.first)){return find(x, n->left.get());}
    else {return find(x, n->right.get());}
  }

  //Function that, given a key and a pointer to a node, if the key is present (under the given node), returns a costant_iterator to the proper node, cend() otherwise.
  const_iterator find(const KT& x, node_type* n) const noexcept{
    if(!n){return cend();}
    else if(x == n->val.first){return const_iterator{n};}
    else if(op(x, n->val.first)){return find(x, n->left.get());}
    else {return find(x, n->right.get());}
  }

  //Function that, given a key and a pointer to a node, if the key is present, returns an iteretor to the proper node, otherwise return an iterator to the future parent.
  iterator where_to_place(const KT& x, node_type* n) const noexcept;

public:
//Costructors.
//We have two custom costructors. We decided to put the empty tree as a tree
//with just a nullpointer and nothing else.

  bst() noexcept = default;
  explicit bst(cmp x):op{x}{}

//Function that makes a deep copy of the tree, given the pointer to a node.
// void copy(const node_type* n);   //private???

//Copy constuctor, makes a deep copy.
  bst(const bst& _tree){copy(_tree.root.get());}

//Move constructor.
  bst(bst&& _tree) noexcept :root{std::move(_tree.root)}{}

//Destructor.
  ~bst() = default;

//Iterators that give us the point where to start to read the tree and as end()
//we set it to be an iterator with a pointer as nullpointer.
  iterator begin() noexcept{return iterator{left_nephew(root.get())};}
  iterator end() noexcept {return iterator{nullptr};}

  const_iterator begin() const noexcept {return const_iterator{left_nephew(root.get())};}
  const_iterator end() const noexcept {return const_iterator{nullptr};}

  const_iterator cbegin() const noexcept {return const_iterator{left_nephew(root.get())};}
  const_iterator cend() const noexcept {return const_iterator{nullptr};}


//Move assigment.
bst& operator=(bst&& _tree) noexcept {
    root = std::move(_tree.root);
    return *this;
  }

//Copy assigment.
bst& operator=(const bst& _tree){
  root.reset();
  auto tmp = _tree;
  (*this) = std::move(tmp);
  return *this;
}

//If the key is presents, returns an iterator to the proper node, end() otherwise.
iterator find(const KT& x) noexcept {return find(x, root.get());}

/*if the key is presents, returns a const_iterator to the proper node, cend() otherwise*/
const_iterator find(const KT& x) const {return find(x, root.get());}

//This function is used to insert a new node in the tree. It returns an iterator to the proper node and true if a new node is inserted, false if the node was already present.
std::pair<iterator,bool> insert(const pair_type& x);

std::pair<iterator,bool> insert(pair_type&& x);

//Use the iterators to read the key of the nodes.
friend
std::ostream& operator <<(std::ostream& os, const bst& t){
  auto stop=t.end();
  for(auto p=t.begin(); p!=stop; ++p){
    os << p->first << " ";
  }
  return os;
}

//Function that inserts a pair in the tree if it is not still present and it can
//be written in round brackets.
 template<class... Types>
 std::pair<iterator, bool> emplace(Types&&... args){
   pair_type s{std::forward<Types>(args)...};
 return insert(std::move(s));
   }

//It returns a reference to the value that is mapped to a key equivalent to x, performing an insertion if sach key does not already exist.
VT& operator[](const KT& x){
 if(find(x).Current()){return (find(x)->second);}
 else return {(insert({x, VT{}})).first->second};
}

VT& operator[](KT&& x)
{
  if(find(x).Current()){return (find(x)->second);}
  else return {(insert({std::move(x), VT{}})).first->second};
}

//Clear the content of the tree.
void clear() noexcept {root.reset();}

/*The function that balance the tree.*/
void balance();

/*function that removes the element (if one exists) with the key equivalent to key*/
void erase(const KT& x);

};


#include "impl_bst.hpp"
#endif
