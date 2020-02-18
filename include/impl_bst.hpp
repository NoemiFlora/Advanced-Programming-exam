#ifndef __impl_bst__
#define __impl_bst__

#include "bst.hpp"

template<typename KT, typename VT, typename cmp>
typename bst<KT,VT,cmp>::iterator bst<KT,VT,cmp>::where_to_place(const KT& x, node_type* n) const noexcept {
if(n){
  /*if x is less than the key of the node, we check if the left child is present or not*/
  if(op(x,n->val.first)){
    if(n->left.get()!=nullptr){return where_to_place(x, n->left.get());}
    else{return iterator{n};}
  }
  else{
    if(n->right.get()!=nullptr){return where_to_place(x, n->right.get());}
    else{return iterator{n};}
  }
}
else {return iterator{n};}
}

template<typename KT, typename VT, typename cmp>
std::pair<typename bst<KT,VT,cmp>::iterator,bool> bst<KT,VT,cmp>::insert(const pair_type& x) {
  if(root){
    /*if the key is already present, the function returns an iterator to the proper node (using the function find), and false*/
    if(find(x.first).Current()){return {find(x.first), false};}
    else{
      /*if the key is not present, we call the function where to place to find the parent of the future node*/
      iterator position = where_to_place(x.first, root.get());
      /*we check if the new node is a left or right child*/
      if(op(x.first, position->first)){
        (position.Current()->left).reset(new node_type{x, position.Current()});
        return {iterator{(position.Current()->left).get()}, true};
      }
      else{
        (position.Current()->right).reset(new node_type{x, position.Current()});
        return {iterator{(position.Current()->right).get()}, true};
      }
    }
    }
  /* if the root is nullptr, the tree is empty, so the function insert the new root*/
  else{
    root.reset(new node_type{x});
    return {iterator{root.get()}, true};
  }
}

template<typename KT, typename VT, typename cmp>
std::pair<typename bst<KT,VT,cmp>::iterator,bool> bst<KT,VT,cmp>::insert(pair_type&& x){
  if(root){
    if(find((&x)->first).Current()){return {find((&x)->first), false};}
    else{
      iterator position = where_to_place((&x)->first, root.get());
      if(op((&x)->first, position->first)){
        (position.Current()->left).reset(new node_type{std::move(x), position.Current()});
        return {iterator{(position.Current()->left).get()}, true};
      }

      else{
        (position.Current()->right).reset(new node_type{std::move(x), position.Current()});
        return {iterator{(position.Current()->right).get()}, true};
      }
    }
    }
  else{
    root.reset(new node_type{std::move(x)});
    return {iterator{root.get()}, true};
  }
}

template<typename KT, typename VT, typename cmp>
void bst<KT,VT,cmp>::balance() {
  /*if the tree is empty do nothing*/
  if(!root){return;}
  else{
  /*Constructs a vector with the values (key and value) of the tree's nodes.*/
    std::vector<pair_type> Tree;
    auto stop=end();
    for(auto p=begin(); p!=stop; ++p){
      Tree.emplace_back(*p);
    }
    /*Clears the old tree and constructs a new tree using the old nodes.*/
      clear();
        unsigned int n_nodes = 0;
        unsigned int p2;  //powers of 2
        long double d2; //divisions for 2
        for(size_t i = 1; i <= log2(Tree.size()+1)+1; i++){
          p2 = 2<<i;
          d2 = (1.0)/p2;
          unsigned int n = 0;
          while(2 * n <= p2-1 && n_nodes <= Tree.size()){
            int j = (int)(Tree.size() * (1+2*n)*d2);
            if(insert(Tree[j]).second){n_nodes +=1;}
            n += 1;
          }
      }
    }
}

template<typename KT, typename VT, typename cmp>
void bst<KT,VT,cmp>::erase(const KT& x){
  if(find(x).Current()){
    /*if the node is a leaf, we simply reset the respective unique pointer*/
    if(!(find(x).Current()->left) && !(find(x).Current()->right)){
       if(find(x).Current() == (find(x).Current()->parent->left).get()){(find(x).Current()->parent->left).reset();}
       else{(find(x).Current()->parent->right).reset();}
     }
    else{
      /*the function copies the proper sub_tree*/
      bst<KT, VT, cmp> sub_tree{};
      sub_tree.copy((find(x).Current()->left).get());
      sub_tree.copy((find(x).Current()->right).get());
      sub_tree.balance();
      /*If we want to erase the root the new tree is the sub_tree*/
      if(find(x).Current()==root.get()){*this = std::move(sub_tree);}
      else{
        /*it is the iterator that points to the parent of the erase node*/
        iterator it{find(x).Current()->parent};
        if(find(x).Current() == (find(x).Current()->parent->left).get()){
          /*left pointer has to point to the root of the sub_tree*/
          (it.Current()->left).reset(sub_tree.root.release());
          /*the pointer parent of the first node of the sub_tree has to point to the new parent*/
          it.Current()->left->parent = std::move(it.Current());
        }
        else{
        (it.Current()->right).reset(sub_tree.root.release());
        it.Current()->right->parent = std::move(it.Current());
        }
      }
    }
  }
  else{std::cout << "key not found" << std::endl;}
  //else return;
}

#endif
