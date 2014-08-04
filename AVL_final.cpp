/*
    Author : Ajit Kumar
    Date : 4th March 2014



Project :
Implement a data structure AVLTree which realizes some basic operations on AVL-trees. The nodes of the tree shall store a key
attribute of type T which is a template parameter. Further attributes of nodes shall be left and right (pointers to the left
and right subtree, as well as height (the height of the subtree rooted at this node). For comparing keys, the standard compare
operators (<, == etc.) shall be used.

You data structure shall provide the following operations:

1. AVLNode<T> *lookup(const T &key)
    Searches for a node in the tree with the given key; if no such node exists, nullptr shall be returned.
2. AVLNode<T> *insert(const T &key)
    Inserts a new node with the given key and returns it; if this key is already contained in the tree, the node containing
    this key shall be returned.
3. void remove(const T &key)
    Removes the node with the given key from the tree; if no such node exists, nothing shall be done.

Add a little main program that demonstrates and tests your data structure.

*/





#include<iostream>
#include<stdio.h>
#include<conio.h>
using namespace std;



template <class T>
struct Node
{
    T key1;
    Node *left,*right,*parent;
    int height;
};
Node<int> *ptr,*root,*x,*y,*z,*p,*t,*X,*Y,*newptr;



template <class T>
Node<T> * Create(const T &key);
template <class T>
Node<T> * Insert(const T &key);
template <class T>
int height(Node<T> * height_ptr);
template <class T>
void update_height(Node<T> * height_ptr);
template <class T>
void inorder_traversal_for_height(Node<T> * height_root);

template <class T>
void maintainAVL(Node<T> * maintain_ptr);
template <class T>
void right_rotate(Node<T> * X);
template <class T>
void left_rotate(Node<T> * Y);
template <class T>
void inorder_display(Node<T> * root1);
template <class T>
Node<T> * lookup(const T &key);
template <class T>
Node<T> * Search(Node<T> * root2,const T &key);
template <class T>
void Remove(const T &key);

template <class T>
int height(Node<T> * height_ptr1)
{
    if(height_ptr1==NULL)
        return -1;
    else
        return height_ptr1->height;
}

template <class T>
void update_height(Node<T> * height_ptr)
{
    height_ptr->height=max(height(height_ptr->left),height(height_ptr->right)) +1;
}

template <class T>
void inorder_traversal_for_height(Node<T> * height_root)
{
    if(height_root!=NULL)
    {
        inorder_traversal_for_height(height_root->left);
        update_height(height_root);
        inorder_traversal_for_height(height_root->right);
    }
}

template <class T>
Node<T> * Create(const T &key)
{
    ptr=new Node<int>;     //ptr=new Node<T>;
    ptr->key1=key;
    ptr->left=NULL;
    ptr->right=NULL;
    ptr->parent=NULL;
    ptr->height=0;
    return ptr;
}

template <class T>
Node<T> * Insert(const T &key)
{
        x=root;   //Node<T> * x=root;
        y=NULL;    //Node<T> * y=NULL;
        z=Create(key);    //Node<T> * z=Create(key);
        while(x!=NULL)
        {
            y=x;

            if(z->key1 < x->key1)
                x=x->left;
            else
                x=x->right;

        }

        if(y==NULL)
            root=z;
        else if(z->key1 < y->key1)
            {y->left=z; z->parent=y;}
        else
            {y->right=z; z->parent=y;}

        //printf("Done before height traversal\n");
        inorder_traversal_for_height(root);
        //printf("Traversal done\n");


        //printf("AVL Tree before maintain: ");
        //inorder_display(root);
        //getch();
        maintainAVL(z);
        //printf("maintain AVL done\n");




}


template <class T>
void maintainAVL(Node<T> * maintain_ptr)
{
    while(maintain_ptr!=NULL)
    {
        update_height(maintain_ptr);

        if(height(maintain_ptr->right) >= height(maintain_ptr->left) +2)
            {
                //printf("maintain_ptr = %d\n",maintain_ptr->key1);
                //printf("Height of maintain_ptr=%d\n",height(maintain_ptr));
                //if(maintain_ptr->right!=NULL)
                //{printf("Right of maintain_ptr = %d\n",maintain_ptr->right->key1);
                //printf("Height of right ptr=%d\n",height(maintain_ptr->right));}
                //if(maintain_ptr->left!=NULL)
                //{printf("Left of maintain_ptr=%d\n",maintain_ptr->left->key1);
                //printf("Height of left ptr=%d\n",(maintain_ptr->left));}

                if(height(maintain_ptr->right->right) >= height(maintain_ptr->right->left))
                   {
                        //printf("Second If called\n");
                        right_rotate(maintain_ptr);
                        maintain_ptr=maintain_ptr->parent;
                   }
                else
                {
                    //printf("else called\n");
                    //printf("Left rotate of %d going to be done\n",maintain_ptr->right->key1);

                    left_rotate(maintain_ptr->right);

                    //printf("Left rotate has been done \n");
                    //printf("maintain_ptr = %d\n",maintain_ptr->key1);
                    //printf("Height of maintain_ptr=%d\n",height(maintain_ptr));
                    //if(maintain_ptr->right!=NULL)
                    //{   printf("Right of maintain_ptr = %d\n",maintain_ptr->right->key1);
                      //  printf("Height of right ptr=%d\n",height(maintain_ptr->right));}
                    //if(maintain_ptr->left!=NULL)
                    //{   printf("Left of maintain_ptr=%d\n",maintain_ptr->left->key1);
                      //  printf("Height of left ptr=%d\n",(maintain_ptr->left));}
                    //if(maintain_ptr->right->right!=NULL)
                    //{
                      //  printf("Right of right of maintain_ptr=%d\n",maintain_ptr->right->right->key1);
                        //printf("Height of right of right of maintain_ptr = %d\n",height(maintain_ptr->right->right));
                    //}

                    //printf("Right rotate of %d going to be done\n",maintain_ptr->key1);

                    right_rotate(maintain_ptr);


                    maintain_ptr=maintain_ptr->parent;
                }
            }
        else if(height(maintain_ptr->left) >= height(maintain_ptr->right) +2)
        {
            if(height(maintain_ptr->left->left) >= height(maintain_ptr->left->right))
            {
                left_rotate(maintain_ptr);
                maintain_ptr=maintain_ptr->parent;
            }

            else
            {
                right_rotate(maintain_ptr->left);
                left_rotate(maintain_ptr);

                maintain_ptr=maintain_ptr->parent;
            }
        }

        maintain_ptr = maintain_ptr->parent;
    }
}

template <class T>
void right_rotate(Node<T> * X)
{
    Y=X->right;      //Node<T> * Y=X->right;
    //for nodes higher than X
    if(X== X->parent->left)
        {
            X->parent->left=Y;
            Y->parent=X->parent;
        }
    else
        {
            X->parent->right=Y;
            Y->parent=X->parent;
        }

    //for X and B . Check that B is not NULL
    if(Y->left!=NULL)
    {
        X->right=Y->left;
        Y->left->parent=X;
    }
    else
        X->right=NULL;

    //for X and Y
    Y->left=X;
    X->parent=Y;

    //update heights of X and Y
    update_height(X);
    update_height(Y);
}


template <class T>
void left_rotate(Node<T> * Y)
{
    X=Y->left;          //Node<T> * X=Y->left;

    //for nodes higher than Y
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

    //for B and Y . First check that B is not NULL
    if(X->right!=NULL)
    {
        Y->left=X->right;
        X->right->parent=Y;
    }
    else
        Y->left=NULL;

    //for X and Y
    X->right=Y;
    Y->parent=X;

    //update heights of X and Y
    //printf("Height of Y before update = %d",height(Y));

    update_height(Y);

    //if(Y->right!=NULL)
      //  printf("Right of Y= %d",Y->right->key1);
    //if(Y->left!=NULL)
      //  printf("Left of Y= %d",Y->left->key1);
    //printf("Y= %d\n",Y->key1);
    //printf("Height of Y after update =%d\n",height(Y));

    update_height(X);

    //printf("X= %d\n",X->key1);
    //printf("Height of X=%d\n",height(X));
}



template <class T>
void inorder_display(Node<T> * root1)
{
    if(root1!=NULL)
    {
        inorder_display(root1->left);

        if(root1->key1!=-143)                   //-143 is just a random value. We can set it to anything else too.
            cout<<root1->key1<<" ";

        inorder_display(root1->right);
    }
    //printf("\n\n");
}

template <class T>
Node<T> * lookup(const T &key)
{
    return Search(root,key);
}

template <class T>
Node<T> * Search(Node<T> * root2,const T &key)
{
    if(root2->key1 == key)
        return root2;
    else if(root2->key1 < key)
    {
        if(root2->right!=NULL)
            return Search(root2->right,key);
        else
            return NULL;
    }
    else
    {
        if(root2->left!=NULL)
            return Search(root2->left,key);
        else
            return NULL;
    }
}

template <class T>
void Remove(const T & key)
{
    //p=new Node<int>;          //Node<T> * p = new Node<T>;
    //t = new Node<int>;         //Node<T> *t = new Node<T>;
    p=Search(root,key);
    //printf("Search returned : ");
    //cout<<p->key1<<endl;
    //cout<<"Right of "<<p->key1<<"="<<p->right->key1;
    //cout<<"Left of right of "<<p->key1<<"="<<p->right->left->key1;
    //cout<<"Right of right of "<<p->key1<<"="<<p->right->right->key1;
    if(p!=NULL)
        p->key1 = -143;       // -143 is just a random value. We can set it to anything we want.
}

int main()
{
    //Node<int> * f= new Node<int>;
    root=ptr=NULL;
    char ch='y';
    int a;
    cout<<"Enter the values for the tree : \n";
    while(ch=='y')
    {
        cin>>a;
        Insert(a);
        cout<<"Wanna enter more ? y/n : ";
        cin>>ch;
    }

    printf("The inorder traversal of the tree gives :\n ");
    inorder_display(root);

    ch='y';
    while(ch=='y')
    {
        printf("\n\n");
        printf("\nEnter the key of the node to be searched.\n");
        scanf("%d",&a);
        //Node<int> * newptr= new Node<int>;
        newptr= lookup(a);

        if(newptr!=NULL)
        {
            printf("Key found.\n");
            printf("Node specifications :\n");
            printf("Key = %d\n",newptr->key1);
            printf("Height of node = %d\n",newptr->height);
        }
        else
            printf("Key not found.\n");

        printf("Want to search for some more nodes ? y/n :\n");
        cin>>ch;

    }

    ch='y';
    while(ch=='y')
    {

        printf("\nNow enter the key of the node you wanna delete.\n");
        scanf("%d",&a);
        Remove(a);
        printf("\nThe inorder traversal of the remaining tree gives :\n ");
        if(root!=NULL)
            inorder_display(root);
        else
            printf("Tree is empty.\n");


        printf("\nWant to delete some more nodes ? y/n :\n");
        cin>>ch;
    }


    return 0;

}

