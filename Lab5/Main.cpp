/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: elzariao
 *
 * Created on November 24, 2018, 2:39 PM
 */


#include <iostream>
#include <string>
#include <sstream>
#include "DBentry.h"
#include "TreeDB.h"
#include "TreeNode.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    TreeDB tree;
    string line;
    string command;
    
    cout<<"> ";
    
    getline(cin, line);
    
    while(!cin.eof()){
        stringstream lineStream (line);
        
        lineStream >> command;
        
        string name;
        unsigned int IPaddress;
        string status;
        bool status_in;
        
        if (command == "insert"){
           lineStream>> name;
           lineStream>> IPaddress;
           lineStream>> status;
           
           if(status == "active")
               status_in = true;
           else if(status == "inactive")
               status_in = false;
           
           DBentry* newEntry = new DBentry(name, IPaddress, status_in);
           
           if(!(tree.insert(newEntry)))
               cout<<"Error: entry already exists"<<endl; 
           else
               cout<<"Success"<<endl;
        }else if (command == "find"){
            lineStream >> name;
            
            DBentry* existing_entry = tree.find(name);
            
            if(existing_entry!=NULL)
                cout<< *existing_entry <<endl;
            else
                cout<<"Error: entry does not exist"<<endl;
            
        }else if (command == "remove"){
            lineStream >> name;
            DBentry* existing_entry = tree.find(name);
            
            if(existing_entry==NULL)
                cout<<"Error: entry does not exist"<<endl;
            else{
                tree.remove(name);
                cout<<"Success"<<endl;
            }
                
        }else if (command == "printall"){
            operator<<(cout, tree);
        }else if (command == "printprobes"){
            lineStream >> name;
            DBentry* existing_entry = tree.find(name);
            
            if(existing_entry == NULL)
                cout<<"Error: entry does not exist"<<endl;
            else
                tree.printProbes();
            
        }else if (command == "removeall"){
            tree.clear();
            cout<<"Success"<<endl;
        }else if (command == "countactive"){
            tree.countActive();
        }else if (command == "updatestatus"){
            lineStream >> name;
            lineStream >> status;
            DBentry* existing_entry = tree.find(name);
            
            if(existing_entry==NULL)
                cout<<"Error: entry does not exist"<<endl;
            else{
                if(status == "active")
                    status_in = true;
                else if(status == "inactive")
                    status_in = false;
                
                existing_entry->setActive(status_in);
                cout<<"Success"<<endl;
            }
            
        }else
            cout<< "Error: Invalid command"<<endl;
        
        lineStream.clear();
        lineStream.ignore(1000, '\n');
        
        cout<<"> ";
        
        getline(cin, line);
        
    }
    
    tree.clear();
    return 0;
}

