#include <iostream>
#include "TreeDB.h"

    //default constructor
    TreeDB::TreeDB(){
        probesCount = 0;
        root = NULL;
    }
    
    // the destructor, deletes all the entries in the database.
    TreeDB::~TreeDB(){
       clear();
    }
   
    bool TreeDB::insert_bt(DBentry* newEntry, TreeNode* root){
       //if the entry already exists, delete the new entry and make no changes
       if(root->getEntry()->getName() == newEntry->getName()){
           delete newEntry;
           return false;
       }
       
       if (newEntry->getName() > root->getEntry()->getName()){
           //if the right child is NULL, a new entry can be placed there
           if (root->getRight() == NULL){
               TreeNode* newNode = new TreeNode(newEntry);
               root->setRight(newNode);
               return true;
           }else{
               //keep moving right until you reach NULL
               return insert_bt(newEntry, root->getRight());
           }  
       }
       
       if (newEntry->getName() < root->getEntry()->getName()){
           //if the left child is NULL, a new entry can be placed there
           if (root->getLeft() == NULL){
               TreeNode* newNode = new TreeNode(newEntry);
               root->setLeft(newNode);
               return true;
           }else{
               //Keep moving left until you reach NULL
               return insert_bt(newEntry, root->getLeft());
           }  
       }
    } 
   
    DBentry* TreeDB::help_find(string name, TreeNode* current){
       probesCount++; 
       
       if(current == NULL){
           return NULL;
       }
       //if the name is found return the entry containing that name
       else if(current->getEntry()->getName() == name){
           return current->getEntry();
       }
       //if the name is greater than current move to the right
       else if (current->getEntry()->getName() < name){
           return help_find(name , current->getRight());
       }
       //if the name is greater than current move to the left
       else if (current->getEntry()->getName() > name){
           return help_find(name , current->getLeft());
       } 
    }

    void TreeDB::help_clear(TreeNode* root){
       //if the tree is empty, do nothing
       if(root == NULL)
           return;
       
       //clear all the nodes on the left and then clear everything on the right
       help_clear(root->getLeft());
       help_clear(root->getRight());
       
       //after all node deletion is complete, delete the root 
       delete root;
       root = NULL;
    }
    
    
    void TreeDB::help_count(TreeNode* current, int& count) const{
       if (current == NULL)
           return;
       
       //for every active status increment the counter by one
       if(current->getEntry()->getActive() == true){
           count++;
       }
       
       //check all the active status on the right and then check everything on the left
       help_count(current->getRight(), count);
       help_count(current->getLeft(), count);
    }

    // inserts the entry pointed to by newEntry into the database. 
    // If an entry with the same key as newEntry's exists 
    // in the database, it returns false. Otherwise, it returns true.
    bool TreeDB::insert(DBentry* newEntry){
       if(root == NULL){
           TreeNode* newNode = new TreeNode(newEntry);
           root = newNode;
           return true;
       }
       
       return insert_bt(newEntry, root);
    } 

    // searches the database for an entry with a key equal to name.
    // If the entry is found, a pointer to it is returned.
    // If the entry is not found, the NULL pointer is returned.
    // Also sets probesCount
    DBentry* TreeDB::find(string name){
       probesCount = 0;
       if(root == NULL)
           return NULL;
       
       return help_find(name, root);
    }
    
   // deletes the entry with the specified name (key)  from the database.
   // If the entry was indeed in the database, it returns true.
   // Returns false otherwise.
   // See section 6 of the lab handout for the *required* removal method.
   // If you do not use that removal method (replace deleted node by
   // maximum node in the left subtree when the deleted node has two children)
   // you will not match exercise's output.
    bool TreeDB::remove(string name){
        //send back true if the item was removed and false if not
        bool removed;
        //creates a pointer to a parent Node to give access to the Nodes of the tree
        TreeNode *parent = new TreeNode(NULL);
        
        if(root == NULL){
            return false;
        }

        parent->setLeft(root);
        removed = root->removeNode(name, parent);
        root = parent->getLeft();
    
        //delete pointer after the removal action is complete
        delete parent;
        parent = NULL;
        return removed;
    }
    
    // deletes all the entries in the database.
    void TreeDB::clear(){
        if(root == NULL)
            return;
        
        help_clear(root);
        root = NULL;
    }
   
   
    // prints the number of probes stored in probesCount
    void TreeDB::printProbes() const{
       cout<< probesCount <<endl;
    }
   
    // computes and prints out the total number of active entries
    // in the database (i.e. entries with active==true).
    void TreeDB::countActive () const{
       int count = 0;
       
       if(root== NULL){
           cout<< count <<endl;
       }else{
           
       TreeNode* StartNode;
       
       StartNode = root;
       
       help_count(StartNode, count);
       
       cout<< count << endl;
       }
    }
   
    // Prints the entire tree, in ascending order of key/name
    ostream& operator<< (ostream& out, const TreeDB& rhs) {
        if(rhs.root != NULL) 
            operator<<(out, rhs.root); 
    }

    ostream& operator<< (ostream& out, TreeNode* rhs) {
        if(rhs != NULL) { 
            operator<< (out, rhs->getLeft()); 
            operator<< (out, *rhs->getEntry());
            operator<< (out, rhs->getRight()); 
        }
    }

    