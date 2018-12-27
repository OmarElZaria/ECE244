#include <iostream>
#include <valarray>
#include "TreeNode.h"

// A useful constructor
    TreeNode::TreeNode(DBentry* _entryPtr){
        entryPtr = _entryPtr;
        right = NULL;
        left = NULL;
    }

    // the destructor
    TreeNode::~TreeNode(){
        delete entryPtr;
        entryPtr = NULL;
    }

    // sets the left child of the TreeNode.
    void TreeNode::setLeft(TreeNode* newLeft){
        left = newLeft;
    }

    // sets the right child of the TreeNode
    void TreeNode::setRight(TreeNode* newRight){
        right = newRight;
    }

    // gets the left child of the TreeNode.
    TreeNode* TreeNode:: getLeft() const{
        return left;
    }

    // gets the right child of the TreeNode
    TreeNode* TreeNode:: getRight() const{
        return right;
    }

    // returns a pointer to the DBentry the TreeNode contains. 
    DBentry* TreeNode::getEntry() const{
        return entryPtr;
    }
    
    //finds the maximum left node
    TreeNode* TreeNode::left_maximum(){
        if(right == NULL)
            return this;
        return right->left_maximum();
    }
    
    //removes the requested Node
    bool TreeNode::removeNode(string name, TreeNode* Node){
        // if there is no NODE to remove then do nothing and return false
        if(this == NULL)
            return 0;
        
        //If the name of the entry is found do the following
        if(name == entryPtr->getName()){
            //four possible cases can occur
            
            //case 1: Both the left and right side is NULL
            if(left == NULL && right == NULL){
                //in this case just delete this and set it to NULL
                delete this;
                this == NULL;
                
                //set the right and left sides to NULL as well to avoid memory leaks
                if(this == Node->getRight())
                    Node->setRight(NULL);
                if(this == Node->getLeft())
                    Node->setLeft(NULL);
            // Case 2: the right child of the parent is NULL    
            }else if(right == NULL){
                // in this case set both the left and right to be the left child
                if(this == Node->getRight())
                    Node->setRight(left);
                if(this == Node->getLeft())
                    Node->setLeft(left);
                
                //delete the requested node to be removed 
                delete this;
                this == NULL;
            // Case 3: the left child of the parent is NULL  
            }else if(left == NULL){
                // in this case set both the left and right to be the right child
                if(this == Node->getRight())
                    Node->setRight(right);
                if(this == Node->getLeft())
                    Node->setLeft(right);
                
                //delete the requested node to be removed
                delete this;
                this==NULL;
            //Case 4: if the parent has both a right and a left child
            }else if(right != NULL && left != NULL){
                //find the maximum left node
                TreeNode* maximum_left = left->left_maximum();
                
                //Move all the information from the maximum left node to the node we are at right now
                entryPtr->setName(maximum_left->getEntry()->getName());
                entryPtr->setIPaddress(maximum_left->getEntry()->getIPaddress());
                entryPtr->setActive(maximum_left->getEntry()->getActive());
                //recursively remove the left maximum node
                left->removeNode(maximum_left->getEntry()->getName(), this);
            }
            return 1;
        }if(name < entryPtr->getName()){
            return left->removeNode(name, this);
        }if(name > entryPtr->getName()){
            return right->removeNode(name, this);
        }   
    }
    