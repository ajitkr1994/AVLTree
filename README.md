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





#include<iostream>
#include<stdio.h>

using namespace std;


template <class T>
struct AVLNode
{
        T key1;
        AVLNode *left,*right,*parent;
        int height;
};







template <class T>
class AVLTree
{
    public:
AVLNode<T> *ptr,*root=NULL,*x,*y,*z,*p,*t,*X,*Y,*newptr;




AVLNode<T> * create(const T &key);                   //This function creates a new AVLNode.

AVLNode<T> * insert(const T &key);                   //This function Inserts the AVLNode in the tree

int height(AVLNode<T> * height_ptr);                 //Used to calculate the height of a particular AVLNode.

void updateHeight(AVLNode<T> * height_ptr);         //Used to update the height of a particular AVLNode after insertion of a AVLNode.

void inorderTraversalForHeightUpdate(AVLNode<T> * height_root);    //This function travels the whole tree 'inorder' and computes the height of each AVLNode.


void maintainAVL(AVLNode<T> * maintain_ptr);         //This function maintains the AVL property of the tree, so that it remains balanced.

void rightRotate(AVLNode<T> * X);                   //For right rotation around a particular AVLNode.

void leftRotate(AVLNode<T> * Y);                    //For left rotation around a particular AVLNode.

void inorderDisplay(AVLNode<T> * root1);            //Used to display the values of different AVLNodes traversing in order.

AVLNode<T> * lookup(const T &key);                   //The function which calls another function search() and returns the AVLNode pointer where the key is located.

AVLNode<T> * search(AVLNode<T> * root2,const T &key);   //This function actually searches for a given key in the tree recursively.

void remove(const T &key);                        //Used to delete a AVLNode.



};


template <class T>
int AVLTree<T>::height(AVLNode<T> * height_ptr1)
{
    if(height_ptr1==0)        //if(height_ptr1==NULL)
        return -1;
    else
        return height_ptr1->height;
}

template <class T>
void AVLTree<T>::updateHeight(AVLNode<T> * height_ptr)
{
    height_ptr->height=max(height(height_ptr->left),height(height_ptr->right)) +1;
}

//Traverses the tree inorder to update the height of each node.
template <class T>
void AVLTree<T>::inorderTraversalForHeightUpdate(AVLNode<T> * height_root)
{
    if(height_root!= 0)            //if(height_root!=NULL)
    {
        inorderTraversalForHeightUpdate(height_root->left);
        updateHeight(height_root);
        inorderTraversalForHeightUpdate(height_root->right);
    }
}

//Function creates a blank AVLNode by assigning NULL values to the left, right and parent AVLNodes.
template <class T>
AVLNode<T> * AVLTree<T>::create(const T &key)
{
    ptr=new AVLNode<T>;
    ptr->key1=key;
    ptr->left= 0;         //ptr->left=NULL;
    ptr->right=0;         //ptr->right=NULL;
    ptr->parent=0;        //ptr->parent=NULL;
    ptr->height=0;
    return ptr;
}

//Inserts a AVLNode with a given key in the tree, after checking if it is already present in the tree.
template <class T>
AVLNode<T> * AVLTree<T>::insert(const T &key)
{

        if(root==0)       //if(root==NULL)
            p=0;           //p=NULL; this is equivalent to 'AVLNode not found in the tree.'
        else
            p=search(root,key);           //searches for the given key  in the tree and finds whether that key is already existing in the tree or not.
        if(p==0)        //if(p==NULL)           //if the key is not found in the tree, then create a new AVLNode and insert it.
        {

            x=root;
            y=0;              //y=NULL;
            z=create(key);
            while(x!=NULL)
            {
                y=x;

                if(z->key1 < x->key1)    //used to check whether the AVLNode is to be inserted to the left or right of root.
                    x=x->left;
                else
                    x=x->right;

            }

            if(y==0)        //if(y==NULL)            //y would be NULL only when x=NULL which is when the first AVLNode is created. so that AVLNode is assigned the root.
                root=z;
            else if(z->key1 < y->key1)
                {
                    y->left=z;
                    z->parent=y;
                }
            else
                {
                    y->right=z;
                    z->parent=y;
                }

            inorderTraversalForHeightUpdate(root);  //Computes the height of each AVLNode in the tree.


            maintainAVL(z);                          //maintains the  AVL property of the tree.

            cout<<"Node inserted.\n";
            cout<<"Inorder traversal of the tree gives:\n";
            inorderDisplay(root);
            return z;
        }


        else                 //if the key is found in the tree , then return that AVLNode and don't insert anything.
        {
            cout<<"Key is already present in the tree.\n";
            cout<<"Inorder traversal of the tree gives:\n";
            inorderDisplay(root);
            return p;
        }
}


template <class T>
void AVLTree<T>::maintainAVL(AVLNode<T> * maintain_ptr)
{
    while(maintain_ptr!=0)             //while(maintain_ptr!=NULL)
    {
        updateHeight(maintain_ptr);

        if(height(maintain_ptr->right) >= height(maintain_ptr->left) +2)     //checks if the height of right subtree is greater than that of left subtree by 2.
            {
                if(height(maintain_ptr->right->right) >= height(maintain_ptr->right->left))    //checks if the right AVLNode is left heavy or right heavy.
                   {
                        rightRotate(maintain_ptr);
                        maintain_ptr=maintain_ptr->parent;            //move the pointer up the tree.
                   }
                else
                {
                    leftRotate(maintain_ptr->right);
                    rightRotate(maintain_ptr);
                    maintain_ptr=maintain_ptr->parent;
                }
            }

        else if(height(maintain_ptr->left) >= height(maintain_ptr->right) +2)      //checks if the height of left subtree is greater than that of right subtree.
        {
            if(height(maintain_ptr->left->left) >= height(maintain_ptr->left->right))
            {
                leftRotate(maintain_ptr);
                maintain_ptr=maintain_ptr->parent;
            }

            else
            {
                rightRotate(maintain_ptr->left);
                leftRotate(maintain_ptr);

                maintain_ptr=maintain_ptr->parent;
            }
        }

        maintain_ptr = maintain_ptr->parent;
    }
}

template <class T>
void AVLTree<T>::rightRotate(AVLNode<T> * X)
{
    //Here I have supposed that there is a subtree with X at root. Y is the right son of X. B is the left son of Y.
    Y=X->right;

    //for AVLNodes higher than X
    if(X->parent!=NULL)
    {

        if(X== X->parent->left)             //check if X is the left child of it's parent.
            {
                X->parent->left=Y;
                Y->parent=X->parent;
            }
        else
            {
                X->parent->right=Y;
                Y->parent=X->parent;
            }
    }
    else                         //this else loop is called when rotating about the root.
    {
        Y->parent=NULL;
        root=Y;
    }
    //for X and B . Check that B is not NULL
    if(Y->left!=0)            //if(Y->left!=NULL)                    //to make B the right child of X.
    {
        X->right=Y->left;
        Y->left->parent=X;
    }
    else
        X->right=0;               //X->right=NULL;

    //for X and Y
    Y->left=X;
    X->parent=Y;

    //update heights of X and Y
    updateHeight(X);             //First we need to update X's height because Y's height depends on X's height.
    updateHeight(Y);
}


template <class T>
void AVLTree<T>::leftRotate(AVLNode<T> * Y)
{
    //Here I have assumed that Y is the root of a subtree. X is the left child of Y. B is the right child of X.
    X=Y->left;

    //for AVLNodes higher than Y
    if(Y->parent!=NULL)
    {

        if(Y==Y->parent->left)
        {
            Y->parent->left=X;
            X->parent=Y->parent;
        }
        else
        {
            Y->parent->right=X;
            X->parent=Y->parent;
        }
    }
    else
    {
        X->parent=NULL;
        root=X;
    }

    //for B and Y . First check that B is not NULL
    if(X->right!=0)              //if(X->right!=NULL)
    {
        Y->left=X->right;
        X->right->parent=Y;
    }
    else
        Y->left=0;              //Y->left=NULL;

    //for X and Y
    X->right=Y;
    Y->parent=X;

    updateHeight(Y);  //First we need to update Y's height because X's height depends on Y's height.
    updateHeight(X);

}



template <class T>
void AVLTree<T>::inorderDisplay(AVLNode<T> * root1)
{
    if(root1!=0)                //if(root1!=NULL)
    {
        inorderDisplay(root1->left);

        if(root1->key1!=-143)                   //-143 is just a random value. It can be set to any garbage value. This concept helps me in deleting a pointer.
            cout<<root1->key1<<" ";

        inorderDisplay(root1->right);
    }

}

template <class T>
AVLNode<T> * AVLTree<T>::lookup(const T &key)               //lookup calls search and takes input only the key so that it is easier for the user because the user need not pass the root.
{
    return search(root,key);
}

template <class T>
AVLNode<T> * AVLTree<T>::search(AVLNode<T> * root2,const T &key)     //does the search recursively by starting at the root.
{


    if(root2->key1 == key)
        return root2;
    else if(root2->key1 < key)
    {
        if(root2->right!=0)                    //if(root2->right!=NULL)
            return search(root2->right,key);     //if key  is greater than root's key, just search in the right subtree or search in the left subtree.
        else
            return 0;                       //return NULL;
    }
    else
    {
        if(root2->left!=0)            //if(root2->left!=NULL)
            return search(root2->left,key);
        else
            return 0;               //return NULL;
    }

}

template <class T>
void AVLTree<T>::remove(const T & key)
{
    p=search(root,key);          //searches if the node is present in the tree or not.

    if(p!=0)               //if(p!=NULL)
    {

        p->key1 = -143;       //Whenever i want to delete a AVLNode, I just set it's key value to -143 and then ignore that AVLNode while traversing the tree.
        cout<<"Node deleted.\n";
        cout<<"Inorder traversal of the tree gives :\n";
        inorderDisplay(root);
    }
    else
    {
        cout<<"Key not present in the tree.\n";
        cout<<"Inorder traversal of the tree gives: \n";
        inorderDisplay(root);
    }

}

int main()
{
    AVLNode<int> * newnode;       //create a new AVLNode so as to save the pointer returned by the insert function.
    AVLTree<int> tree;

    char ch='y';
    int a;
    cout<<"Enter the values for the tree : \n";
    while(ch=='y'||ch=='Y')
    {
        cin>>a;
        newnode=tree.insert(a);
        cout<<"\nWanna enter more ? y/n : ";
        cin>>ch;
    }

    ch='y';
    while(ch=='y'||ch=='Y')
    {
        cout<<endl;
        cout<<"\nEnter the key of the Node to be searched.\n";
        cin>>a;

        newnode= tree.lookup(a);

        if(newnode!=0)             //if(newptr!=NULL)
        {
            cout<<"Key found.\n";
            cout<<"Node specifications :\n";
            cout<<"Key = "<<newnode->key1<<endl;
            cout<<"Height of Node = "<<tree.height(newnode)<<endl;
        }

        else
            cout<<"Key not found.\n";

        cout<<"Want to search for some more Nodes ? y/n : ";
        cin>>ch;

    }

    ch='y';
    while(ch=='y')
    {

        cout<<"\nNow enter the key of the Node you wanna delete.\n";
        cin>>a;
        tree.remove(a);
        cout<<"\nWant to delete some more Nodes ? y/n :";
        cin>>ch;
    }


    return 0;

}
