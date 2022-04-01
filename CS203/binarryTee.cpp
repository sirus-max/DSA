//
//  main.cpp
//  red_black_tree
//
//  Created by Pradeep Kumar on 05/10/21.
//

#include <iostream>
#include <queue>
using namespace std;

/*----------------------------- Node for Binary tree -------------------------------------------*/

class BinaryNode {
public:
    BinaryNode();
    int getdata();
    bool setData(int);
    BinaryNode* getParent();
    BinaryNode* getchildL();
    BinaryNode* getchildR();
    bool setParent(BinaryNode*);
    bool setChildL(BinaryNode*);
    bool setChildR(BinaryNode*);
    bool setLevel(int value);
    int getLevel();
    int color;
    bool setColor(int);
    int getColor();
   
    
private:
    int data;
    int Level;
    BinaryNode* parent;
    BinaryNode* childL;
    BinaryNode* childR;
};



//BinaryNode functions


BinaryNode::BinaryNode(){
    data = NULL;
    parent = nullptr;
    childL = nullptr;
    childR = nullptr;
    color = NULL;
}

int BinaryNode::getdata(){
    return data;
}
int BinaryNode::getLevel(){
    return Level;
}
bool BinaryNode::setData(int value){
    data = value;
    return true;
}

bool BinaryNode::setLevel(int value){
    Level = value;
    return true;
}

BinaryNode* BinaryNode::getParent(){
    return parent;
}

BinaryNode* BinaryNode::getchildL(){
    return childL;
}

BinaryNode* BinaryNode::getchildR(){
    return childR;
}

bool BinaryNode::setParent(BinaryNode * Nodeptr){
    parent = Nodeptr;
    return true;
}

bool BinaryNode::setChildL(BinaryNode * nodeptr){
    childL = nodeptr;
    return true;
}

bool BinaryNode::setChildR(BinaryNode * nodeptr){
    childR = nodeptr;
    return true;
}

bool BinaryNode::setColor(int value){
    color = value;
    return true;
}
int BinaryNode::getColor(){
    return color;
}
/*-----------------------------------------------------------------------------------------*/









/*----------------------------------- Binary Tree ---------------------------------------- */

class BinaryTree{
public:
    BinaryTree();
    bool isEmpty();
    void insert(BinaryNode* nodeptr);
    BinaryNode* Root;
    BinaryNode* root;
    
    void print(BinaryNode *x, int);
    
    
    void subtree(BinaryNode*);
    int ancestor(int, int);
    void leftRotate(BinaryNode* nodeptr);
    void  rightRotate(BinaryNode* nodeptr);
    BinaryNode* find(int value, BinaryNode* root1);
    BinaryNode* leaf;
    void insertFix(BinaryNode*);
};


//BinaryTree functions
BinaryTree::BinaryTree(){
    Root = nullptr;
    leaf = new BinaryNode();
    leaf -> setColor(0);
    
}

bool BinaryTree::isEmpty(){
    if (Root==nullptr) {
        return true;
    }
    return false;
}














void BinaryTree::insert(BinaryNode *z){
    if(isEmpty()){
        Root = z;
        Root->setParent(leaf);
        leaf->setChildL(Root);
        Root->setChildR(leaf);
        Root->setChildL(leaf);
        return;
    }
    BinaryNode* y = leaf;
    BinaryNode* x = Root;
    while( x != leaf){
        y = x;
        if (z->getdata() < x->getdata()){
            x = x->getchildL();
        }
        else {
            x = x->getchildR();
        }
    }
    z->setParent(y);
    if(y == leaf){
        Root = z;
    }
    else if( z->getdata() < y->getdata() ){
        y->setChildL(z);
    }
    else{
        y->setChildR(z);
    }
    z->setChildL(leaf);
    z->setChildR(leaf);
    z->setColor(1);
}

void BinaryTree::insertFix(BinaryNode* z) {
    Root->setColor(0);
    
    while( z->getParent()->getColor() == 1){
        if (z->getParent() == z->getParent()->getParent()->getchildL()){
            BinaryNode* y = z->getParent()->getParent()->getchildR();
            if(y->getColor() == 1){
                z->getParent()->setColor(0);
                y->setColor(0);
                z->getParent()->getParent()->setColor(1);
                z = z->getParent()->getParent();
            }
            else{
                if( z == z->getParent()->getchildR()){
                    z = z->getParent();
                    leftRotate(z);
                }
                
                z->getParent()->setColor(0);
                z->getParent()->getParent()->setColor(1);
                rightRotate(z->getParent()->getParent());
            }
        }



        else{
            BinaryNode* y = z->getParent()->getParent()->getchildL();
            if(y->getColor() == 1){
                z->getParent()->setColor(0);
                y->setColor(0);
                z->getParent()->getParent()->setColor(1);
                z = z->getParent()->getParent();
            }
            else{
                if( z == z->getParent()->getchildL()){
                    z = z->getParent();
                    rightRotate(z);
                }
                z->getParent()->setColor(0);
                z->getParent()->getParent()->setColor(1);
                leftRotate(z->getParent()->getParent());
            }
        }
    }
    Root->setColor(0);
}

void BinaryTree::leftRotate(BinaryNode *x){
    BinaryNode* y = x->getchildR();
    x->setChildR(y->getchildL());
    if( y->getchildL() != leaf){
        y->getchildL()->setParent(x);
    }
    y->setParent(x->getParent());
    if (x->getParent() == leaf){
        Root = y;
    }
    else if(x == x->getParent()->getchildL()){
        x->getParent()->setChildL(y);
    }
    else{
        x->getParent()->setChildR(y);
    }
        y->setChildL(x);
        x->setParent(y);
    
}

void BinaryTree::rightRotate(BinaryNode *x){
    BinaryNode* y = x->getchildL();
    x->setChildL(y->getchildR());
    
    
    if( y->getchildR() != leaf){
        y->getchildR()->setParent(x);
    }
    
    y->setParent(x->getParent());
    if (x->getParent() == leaf){
        Root = y;
    }
    else if(x == x->getParent()->getchildL()){
        x->getParent()->setChildL(y);
    }
    else{
        x->getParent()->setChildR(y);
    }
        y->setChildR(x);
        x->setParent(y);
    
}


BinaryNode* BinaryTree::find(int value, BinaryNode* root1){
    root = root1;
    while(root!=leaf){
        if (root->getdata()==value) {
            return root;
        }
        else if(root->getdata() < value){
            root =  root->getchildR();
        }
        else{
            root = root->getchildL();
        }
    }
    return nullptr;
}


void BinaryTree::print(BinaryNode *x, int n) {
    if(x == leaf){
        return;
    }
    cout<<x->getdata()<<" ";
    print(x->getchildL(),n);
    print(x->getchildR(),n);

}



int main() {
    BinaryTree tree;
    BinaryNode* node;
        

    int n,k;
    cin>>n;
    k = n;
    while(n--){
        int value;
        cin>>value;
        node = new BinaryNode();
        node->setData(value);
        node->setColor(1);
        tree.insert(node);
        tree.insertFix(node);
    }
    
    tree.print(tree.Root, k);
    
   
return 0;
}
