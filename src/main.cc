#include<iostream>
#include "bst.hpp"

int main(){
 try{
 bst<int,int> t{};
 std::cout << "We constract an empty tree: " << t << std::endl;
 t.insert({30,9});
 t.insert({15,9});
 t.insert({45,9});
 t.insert({9,9});
 t.insert({22,9});
 t.insert({37,9});

 std::cout << "t after insert: " << t << std::endl;

t.emplace(7, 8);
t.emplace(10, 2);
t.emplace(15, 1);
t.emplace(60, 4);
t.emplace(1, 9);


 std::cout << "t after emplace: " << t << std::endl;

if(t.find(17) != t.end()) std::cout << "The key is present" << std::endl;
else std::cout << "The key is not present" << std::endl;

if(t.find(37) != t.end()) std::cout << "The key is present" << std::endl;
else std::cout << "The key is not present" << std::endl;

t.balance();

std::cout << "t after balance " << t << std::endl;
std::cout << "The value of the node with key 60 is " << t[60] << std::endl;
t[100];
std::cout << "t after the put to operator with a non present key " << t << std::endl;

bst<int,int> s{t};
std::cout << "We inizialize the tree s with t, s: " << s << std::endl;

bst<int,int> z{std::move(t)};
std::cout << "We \"move\" t in z, z:" << z << "t: " << t << std::endl;

bst<int,int> k{};
k = s;
std::cout << "We construct k and then assigned s to k, k: " << k << std::endl;
s.insert({5, 7});
std::cout << "If we modify s, k remains the same, " << "\n" << "s: "<< s << "\n" << "k: " << k << std::endl;

bst<int, int> j{};
j = std::move(k);
std::cout << "We construct an empty tree j, then we \"move\" k in j, k:" << k << " j: " << j << std::endl;

s.erase(5);
std::cout << "After erase of a leaf, s: " << s << std::endl;

s.erase(37);
std::cout << "After erase of a general node, s: " << s << std::endl;

s.erase(17);
std::cout << "After erase of the root, s: " << s << std::endl;

s.erase(13);
std::cout << "If the argument of erase is a not present key, the tree remains the same, " << "s: " << s << std::endl;

j.clear();
std::cout << "j after clear: " << j << std::endl;
return 0;
}
catch(...){
std::cout << "caught an exception";
return 1;
}
}
