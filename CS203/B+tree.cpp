// C++ program for implementing B+ Tree
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
int t,d;
int MAX;
 
// BP node
class Node {
    bool IS_LEAF;
    int *key, size;
    Node** ptr;
    friend class BPTree;
 
public:
    Node();
};
 
// BP tree
class BPTree {
    Node* root;
    void insertInternal(int,
                        Node*,
                        Node*);
    Node* findParent(Node*, Node*);
    int leaves;
    int index_nodes;
 
public:
    BPTree();
    void search(int);
    void insert(int);
    void display(Node*);
    Node* getRoot();
    int getLeaves();
    int getIndexes();
};
 
// Constructor of Node
Node::Node()
{
    key = new int[MAX];
    ptr = new Node*[MAX + 1];
}
 
// Initialise the BPTree Node
BPTree::BPTree()
{
    root = NULL;
    leaves=0;
    index_nodes=0;
}

int BPTree::getLeaves()
{
    return leaves;
}

int BPTree::getIndexes()
{
    return index_nodes;
}
 
// Function to find any element
// in B+ Tree
void BPTree::search(int x)
{
 
    // If tree is empty
    if (root == NULL) {
        cout << "Tree is empty\n";
    }
 
    // Traverse to find the value
    else {
 
        Node* cursor = root;
 
        // Till we reach leaf node
        while (cursor->IS_LEAF == false) {
 
            for (int i = 0;
                 i < cursor->size; i++) {
 
                // If the element to be
                // found is not present
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
 
                // If reaches end of the
                // cursor node
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
 
        // Traverse the cursor and find
        // the node with value x
        for (int i = 0;
             i < cursor->size; i++) {
 
            // If found then return
            if (cursor->key[i] == x) {
                cout << "Found\n";
                return;
            }
        }
 
        // Else element is not present
        cout << "Not found\n";
    }
}
 
// Function to implement the Insert
// Operation in B+ Tree
void BPTree::insert(int x)
{
 
    // If root is null then return
    // newly created node
    if (root == NULL) {
        root = new Node;
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
        leaves++;
    }
 
    // Traverse the B+ Tree
    else {
        Node* cursor = root;
        Node* parent;
 
        // Till cursor reaches the
        // leaf node
        while (cursor->IS_LEAF
               == false) {
 
            parent = cursor;
 
            // for (int i = 0;
            //      i < cursor->size;
            //      i++) {
 
            //     // If found the position
            //     // where we have to insert
            //     // node
            //     if (x < cursor->key[i]) {
            //         cursor
            //             = cursor->ptr[i];
            //         break;
            //     }
 
            //     // If reaches the end
            //     if (i == cursor->size - 1) {
            //         cursor
            //             = cursor->ptr[i + 1];
            //         break;
            //     }
            // }
            int i = 0;
            while (x > cursor->key[i]
                   && i < cursor->size) {
                i++;
            }
            cursor=cursor->ptr[i];
        }
 
        if (cursor->size < 2*d) {
            int i = 0;
            while (x > cursor->key[i]
                   && i < cursor->size) {
                i++;
            }
 
            for (int j = cursor->size;
                 j > i; j--) {
                cursor->key[j]
                    = cursor->key[j - 1];
            }
 
            cursor->key[i] = x;
            cursor->size++;
 
            cursor->ptr[cursor->size]
                = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        }
 
        else {
 
            // Create a newLeaf node
            Node* newLeaf = new Node;
            leaves++;
 
            int virtualNode[2*d + 1];
 
            // Update cursor to virtual
            // node created
            for (int i = 0; i < 2*d; i++) {
                virtualNode[i]
                    = cursor->key[i];
            }
            int i = 0, j;
 
            // Traverse to find where the new
            // node is to be inserted
            while (x > virtualNode[i]
                   && i < 2*d) {
                i++;
            }
 
            // Update the current virtual
            // Node to its previous
            for (int j = 2*d;
                 j > i; j--) {
                virtualNode[j]
                    = virtualNode[j - 1];
            }
 
            virtualNode[i] = x;
            newLeaf->IS_LEAF = true;
 
            cursor->size = d;
            newLeaf->size
                = d+1;
 
            cursor->ptr[cursor->size]
                = newLeaf;
 
            newLeaf->ptr[newLeaf->size]
                = cursor->ptr[2*d];
 
            cursor->ptr[2*d] = NULL;
 
            // Update the current virtual
            // Node's key to its previous
            for (i = 0;
                 i < cursor->size; i++) {
                cursor->key[i]
                    = virtualNode[i];
            }
 
            // Update the newLeaf key to
            // virtual Node
            for (i = 0, j = cursor->size;
                 i < newLeaf->size;
                 i++, j++) {
                newLeaf->key[i]
                    = virtualNode[j];
            }
 
            // If cursor is the root node
            if (cursor == root) {
 
                // Create a new Node
                Node* newRoot = new Node;
 
                // Update rest field of
                // B+ Tree Node
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                index_nodes++;
                newRoot->size = 1;
                root = newRoot;
            }
            else {
 
                // Recursive Call for
                // insert in internal
                insertInternal(newLeaf->key[0],
                               parent,
                               newLeaf);
            }
        }
    }
}
 
// Function to implement the Insert
// Internal Operation in B+ Tree
void BPTree::insertInternal(int x,
                            Node* cursor,
                            Node* child)
{
 
    // If we don't have overflow
    if (cursor->size < 2*t+1) {
        int i = 0;
 
        // Traverse the child node
        // for current cursor node
        while (x > cursor->key[i]
               && i < cursor->size) {
            i++;
        }
 
        // Traverse the cursor node
        // and update the current key
        // to its previous node key
        for (int j = cursor->size;
             j > i; j--) {
 
            cursor->key[j]
                = cursor->key[j - 1];
        }
 
        // Traverse the cursor node
        // and update the current ptr
        // to its previous node ptr
        for (int j = cursor->size + 1;
             j > i + 1; j--) {
            cursor->ptr[j]
                = cursor->ptr[j - 1];
        }
 
        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    }
 
    // For overflow, break the node
    else {
 
        // For new Interval
        Node* newInternal = new Node;
        index_nodes++;
        int virtualKey[2*t + 2];
        Node* virtualPtr[2*t + 3];
 
        // Insert the current list key
        // of cursor node to virtualKey
        for (int i = 0; i < 2*t+1; i++) {
            virtualKey[i] = cursor->key[i];
        }
 
        // Insert the current list ptr
        // of cursor node to virtualPtr
        for (int i = 0; i < 2*t + 2; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
 
        int i = 0, j;
 
        // Traverse to find where the new
        // node is to be inserted
        while (x > virtualKey[i]
               && i < 2*t+1) {
            i++;
        }
 
        // Traverse the virtualKey node
        // and update the current key
        // to its previous node key
        for (int j = 2*t + 1;
             j > i; j--) {
 
            virtualKey[j]
                = virtualKey[j - 1];
        }
 
        virtualKey[i] = x;
 
        // Traverse the virtualKey node
        // and update the current ptr
        // to its previous node ptr
        for (int j = 2*t + 2;
             j > i + 1; j--) {
            virtualPtr[j]
                = virtualPtr[j - 1];
        }
 
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
 
        cursor->size
            = t;
 
        newInternal->size
            = t+1;
 
        // Insert new node as an
        // internal node
        for (i = 0, j = cursor->size + 1;
             i < newInternal->size;
             i++, j++) {
 
            newInternal->key[i]
                = virtualKey[j];
        }
 
        for (i = 0, j = cursor->size + 1;
             i < newInternal->size + 1;
             i++, j++) {
 
            newInternal->ptr[i]
                = virtualPtr[j];
        }
 
        // If cursor is the root node
        if (cursor == root) {
 
            // Create a new root node
            Node* newRoot = new Node;
 
            // Update key value
            newRoot->key[0]
                = virtualKey[cursor->size];
 
            // Update rest field of
            // B+ Tree Node
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            index_nodes++;
            newRoot->size = 1;
            root = newRoot;
        }
 
        else {
 
            // Recursive Call to insert
            // the data
            insertInternal(virtualKey[cursor->size],
                           findParent(root,
                                      cursor),
                           newInternal);
        }
    }
}
 
// Function to find the parent node
Node* BPTree::findParent(Node* cursor,
                         Node* child)
{
    Node* parent;
 
    // If cursor reaches the end of Tree
    if (cursor->IS_LEAF
        || (cursor->ptr[0])->IS_LEAF) {
        return NULL;
    }
 
    // Traverse the current node with
    // all its child
    for (int i = 0;
         i < cursor->size + 1; i++) {
 
        // Update the parent for the
        // child Node
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        }
 
        // Else recursively traverse to
        // find child node
        else {
            parent
                = findParent(cursor->ptr[i],
                             child);
 
            // If parent is found, then
            // return that parent node
            if (parent != NULL)
                return parent;
        }
    }
 
    // Return parent node
    return parent;
}
 
// Function to get the root Node
Node* BPTree::getRoot()
{
    return root;
}

void BPTree::display(Node *dn){
    for(int z=0;z<dn->size;z++){
        cout<<dn->key[z]<<" ";
    }
    cout<<endl;
}
 
// Driver Code
int main()
{
    cin>>d>>t;
    MAX= max(2*d,2*t+1);
    BPTree node;
 
    // Create B+ Tree
    // node.insert(6);
    // node.insert(16);
    // node.insert(26);
    // node.insert(36);
    // node.insert(46);
 
    // Function Call to search node
    // with value 16
    //node.search(16);
    int t,x;
    while(1){
        cin>>t;
        if(t==1){
            cin>>x;
            node.insert(x);
        }else if(t==2){
            cout<<node.getIndexes()<<" "<<node.getLeaves()<<" ";
            node.display(node.getRoot());
        }else if(t==3){
            break;
        }
    }
 
    return 0;
}




// 2
// 1
// 1 100
// 1 200
// 1 300
// 1 400
// 1 500
// 1 600
// 1 700
// 1 800
// 1 150
// 1 350
// 1 250
// 1 251
// 1 252
// 1 253
// 1 450
// 1 425
// 1 750
// 1 480
// 1 470
// 1 490
// 1 460
// 1 850
// 1 825
// 1 494
// 1 498
// 2
// 3