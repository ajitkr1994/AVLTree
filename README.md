/*
    Author : Ajit Kumar
    Implementaion Date : 7th March 2014
    OS Used : Windows 7 Ultimate
    Complier used : GNU GCC Compiler


Project :
Implement a data structure AVLTree which realizes some basic operations on AVL-trees. The AVLNodes of the tree shall store a key
attribute of type T which is a template parameter. Further attributes of AVLNodes shall be left and right (pointers to the left
and right subtree, as well as height (the height of the subtree rooted at this AVLNode). For comparing keys, the standard compare
operators (<, == etc.) shall be used.

You data structure shall provide the following operations:

1. AVLNode<T> *lookup(const T &key)
    searches for a AVLNode in the tree with the given key; if no such AVLNode exists, nullptr shall be returned.
2. AVLNode<T> *insert(const T &key)
    Inserts a new AVLNode with the given key and returns it; if this key is already contained in the tree, the AVLNode containing
    this key shall be returned.
3. void remove(const T &key)
    removes the AVLNode with the given key from the tree; if no such AVLNode exists, nothing shall be done.

Add a little main program that demonstrates and tests your data structure.

*/
