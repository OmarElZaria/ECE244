//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void get_value_after_current_space(stringstream &linestream);

//to store the value for each parts
string store_shape_name(string &name, stringstream &linestream);
string store_shape_type(string &type, stringstream &linestream);
int store_x_location(int &x_location, stringstream &linestream);
int store_y_location(int &y_location, stringstream &linestream);
int store_x_size(int &x_size, stringstream &linestream);
int store_y_size(int &y_size, stringstream &linestream);
int store_angle(int &rotation, stringstream &linestream);
bool check_valid_type(string &type);
bool check_valid_move(string &name, shape** shapeArray);
bool check_valid_draw_delete(string &name, shape** shapeArray);
bool check_valid_location(int &x_location, int &y_location);
bool check_valid_name(string &name, shape** shapeArray);
bool check_valid_size(int &x_size, int &y_size);
bool check_valid_rotation(int &rotatio);
bool check_valid_argument(stringstream &linestream);
bool check_number_of_arguments(stringstream &linestream);
bool too_many_arguments(stringstream &linestream);

int main() {

    string line;
    string command;
    string name;
    string type;
    string dummy;
    int loc1;
    int loc2;
    int size1;
    int size2;
    int angle;

    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        if (command == "maxShapes"){
            lineStream >> max_shapes;
            
            //checks if the input is invalid or not
            if (lineStream.fail()){
                cout<<"Error: invalid argument"<<endl;
            }else
                //builds new data base
                cout<< "New database: max shapes is "<<max_shapes<<endl;
                
                //assigns all members of the shapesArray to NULL
                shapesArray = new shape*[max_shapes];
                for(int i=0; i<max_shapes; i++){
                    shapesArray[i] = NULL;
                }
        }else if (command == "create"){
            //checks if array is full
            if(shapeCount == max_shapes){
                cout<<"Error: shape array is full"<<endl;
            }else{
                //stores value for the shape name, checks number of arguments, and if arguments is valid or not
                //repeat this for each parameter required to create a shape
                store_shape_name(name, lineStream);
                if (check_number_of_arguments(lineStream)){
                        cout<<"Error: too few arguments"<<endl;
                    }else{
                          store_shape_type(type, lineStream);
                        if (check_number_of_arguments(lineStream)){
                            cout<<"Error: too few arguments"<<endl;
                    }else{
                        store_x_location(loc1, lineStream);
                        if(check_valid_argument(lineStream)){
                    }else{
                        if (check_number_of_arguments(lineStream)){
                        cout<<"Error: too few arguments"<<endl;
                    }else{
                        store_y_location(loc2, lineStream);
                        if(check_valid_argument(lineStream)){
                        }else{
                            if (check_number_of_arguments(lineStream)){
                                cout<<"Error: too few arguments"<<endl;
                            }else{
                                store_x_size(size1, lineStream);
                                if(check_valid_argument(lineStream)){
                                }else{
                                    if (check_number_of_arguments(lineStream)){
                                        cout<<"Error: too few arguments"<<endl;
                                    }else{
                                        store_y_size(size2, lineStream);
                                        if (check_valid_argument(lineStream)){
                                        }else{
                                            if(too_many_arguments(lineStream)){
                                                cout<<"Error: too many arguments"<<endl;
                                            }else{
                                                // check if shape name and type are valid
                                                bool valid_name = check_valid_name(name, shapesArray);
                                                bool valid_type = check_valid_type(type);
                                                //check if location and size are valid
                                                bool valid_location = check_valid_location(loc1, loc2);
                                                bool valid_size = check_valid_size(size1, size2);
                                                
                                                //if everything is valid create a new shape
                                                if(valid_name && valid_type && valid_location && valid_size){
                                                    shapesArray[shapeCount] = new shape(name, type, loc1, loc2, size1, size2);
                    
                                                    cout<<"Created "<< name <<": "<< type <<" "<< loc1 <<" "<< loc2 <<" "<< size1 <<" "<< size2 <<endl;
                                         
                                                    shapeCount++;
                                                }
                                    
                                            }
                                        }
                                    }
                                }
                
                            }   
                        }
                    }
                }
                }
            }
            }
        }else if (command == "move"){
            //check number of arguments
            if (check_number_of_arguments(lineStream)){
                        cout<<"Error: too few arguments"<<endl;
             }else{
                    //stores value for the shape name, checks number of arguments, and if arguments is valid or not
                    //repeat this for each parameter
                    store_shape_name(name, lineStream);
                    if(!check_valid_move(name, shapesArray)){
                    }else{
                        if (check_number_of_arguments(lineStream)){
                            cout<<"Error: too few arguments"<<endl;
                        }else{
                            store_x_location(loc1, lineStream);
                            if(check_valid_argument(lineStream)){
                            }else{
                                if (check_number_of_arguments(lineStream)){
                                    cout<<"Error: too few arguments"<<endl;
                                }else{
                                    store_y_location(loc2, lineStream);
                                    if (check_valid_argument(lineStream)){
                                    }else{
                                        if(too_many_arguments(lineStream)){
                                            cout<<"Error: too many arguments"<<endl;
                                        }else{
                                            // check if new location is valid
                                            bool valid_location = check_valid_location(loc1, loc2);
                                            
                                            //if everything is valid move the shape successfully
                                            if ((check_valid_move(name, shapesArray)) && valid_location){
                                                for(int i=0; i<shapeCount; i++){
                                                    if(name == shapesArray[i]->getName()){
                                                        shapesArray[i]->setXlocation(loc1);
                                                        shapesArray[i]->setYlocation(loc2);
                                                        cout << "Moved "<< name <<" to "<<loc1<<" "<<loc2<<endl;
                                                    }
                                                }   
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
        }else if (command == "rotate"){
            store_shape_name(name, lineStream);
            
            if(check_number_of_arguments(lineStream)){
                cout<<"Error: too few arguments"<<endl;
            }else{
                    store_angle(angle, lineStream);
                    if(check_valid_argument (lineStream)){
                    }else{
                       if(too_many_arguments(lineStream)){
                        cout<<"Error: too many arguments"<<endl;
                    }else{
                        // check if move is valid and angle is valid
                        bool valid_move = check_valid_move(name, shapesArray);
                        bool valid_angle = check_valid_rotation(angle);
                        //if everything is valid, rotate the shape 
                        if (valid_move && valid_angle){   
                         for(int i=0; i<shapeCount; i++){
                            if(name == shapesArray[i]->getName()){
                                shapesArray[i]->setRotate(angle); 
                                 cout << "rotated "<< name <<" by "<<angle<<" degrees"<<endl;
                                }
                            }        
                        }
                    }
                }
                 
            }
        }else if (command == "draw"){
            //check number of arguments
            if(check_number_of_arguments(lineStream)){
                    cout<<"Error: too few arguments"<<endl;
               
            }else{
                name = store_shape_name(name, lineStream);
                // check if move is valid or not
                bool valid_move = check_valid_draw_delete(name, shapesArray);
                if(!valid_move){
                }else{
                    //if move is valid, check the number of arguments
                    if(too_many_arguments(lineStream)){
                    cout<<"Error: too many arguments"<<endl;
                }else{
                    //if all good, print either a single shape or all shapes depending on the user's input
                    if(name == "all"){
                    cout<<"Drew all shapes"<<" \n";
                    for(int i=0; i<shapeCount; i++){
                        if(shapesArray[i] != NULL){
                            shapesArray[i]->draw(); 
                        }
                    }
                }else{
                          bool valid_move = check_valid_draw_delete(name, shapesArray);
                          if(valid_move){
                                cout<<"Drew "<<name<<"\n";
                            for(int i=0; i<shapeCount; i++){
                                if(name == shapesArray[i]->getName()){
                                    shapesArray[i]->draw(); 
                                }
                            }
                        }
                    
                
                    }
                }
            }
            }
        }else if (command == "delete"){
            //check number of arguments
            if(check_number_of_arguments(lineStream)){
                cout<<"Error: too few arguments"<<endl;
            }else{
                name = store_shape_name(name, lineStream);
                //check if move is valid
                bool valid_move = check_valid_draw_delete(name, shapesArray);
                if(!valid_move){
                }else{
                    //if move is valid check if there is too many arguments
                    if(too_many_arguments(lineStream)){
                        cout<<"Error: too many arguments"<<endl; 
                    }else{
                        //if all is valid, delete all shapes or single shape depending on user's input
                        if(name == "all"){
                            for(int i=0; i<shapeCount; i++){
                                delete shapesArray[i];
                                shapesArray[i] = NULL;
                            }
                        cout<<"Deleted: all shapes"<<endl;
                    }else{
                        cout<<"Deleted shape "<<name<<endl;;
                            for(int i=0; i<shapeCount; i++){
                                if(dummy == shapesArray[i]->getName()){
                                    delete shapesArray[i];
                                    shapesArray[i] = NULL;
                                }
                            }
                        }
                    }
                }
            }
        }else{
            //if user doesn't enter any of the previous commands, then the command is invalid
            cout<<"Error: invalid command"<<endl;
        }
       
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

//checks if the arguments are valid
bool check_valid_argument(stringstream &linestream){
    
    if(linestream.fail()){
        cout<<"Error: invalid argument"<<endl;
        return true;
    }
    
    return false;
}

//checks if the angles are valid
bool check_valid_rotation(int &rotation){
    if(rotation >=0 && rotation <=360)
        return true;
    else{
        cout<<"Error: invalid value"<<endl;
        return false;
    }
}

bool check_valid_move(string &name, shape** shapeArray){
    for(int i=0; i<7; i++){
        if(name == keyWordsList[i]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    
    for(int i=0; i<3; i++){
        if(name == shapeTypesList[i]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    
    for(int i=0; i<shapeCount; i++){
        if((name == shapeArray[i]->getName()) && (shapeArray[i] != NULL)){
            return true;
        }
    }
    
    cout<<"Error: shape "<< name<< " not found"<<endl;
    return false;
    
}

//checks if the shape being moved is valid and exists
bool check_valid_draw_delete(string &name, shape** shapeArray){
    if (name == "all"){
        return true;
    }
    
    if(name == "maxShapes" | name == "move" | name == "draw" | name== "delete" | name == "rotate" | name == "create"){
        cout<<"Error: invalid shape name"<<endl;
        return false;
    }
    
    for(int i=0; i<3; i++){
        if(name == shapeTypesList[i]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    
    for(int i=0; i<shapeCount; i++){
        if((name == shapeArray[i]->getName()) && (shapeArray[i] != NULL)){
            return true;
        }
    }
    
    cout<<"Error: shape "<< name<< " not found"<<endl;
    return false;
    
}

//checks if the name is valid and doesn't already exist
bool check_valid_name(string &name, shape ** shapeArray){
    for(int i=0; i<7; i++){
        if(name == keyWordsList[i]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    
    for(int i=0; i<3; i++){
        if(name == shapeTypesList[i]){
            cout<<"Error: invalid shape name"<<endl;
            return false;
        }
    }
    
    if(shapeCount > 0){
        for(int i=0; i<shapeCount; i++){
            if(name == shapeArray[i]->getName()){
                cout<<"Error: shape name exists"<<endl;
                return false;
            }    
        }
    }
    
    return true;
}

//checks if type is valid
bool check_valid_type(string &type){
    if (type == "ellipse" | type == "rectangle" | type== "triangle"){ 
        return true;
    }else{
        cout<<"Error: invalid shape type"<<endl;
        return false;
    }
}

//gets the value in the stream that after the space
void get_value_after_current_space(stringstream &linestream)//basic function to get value after each spaces
{
    if(linestream.peek() == ' ')
    {
        linestream.get();
    }
}

//checks if there are too few arguments
bool check_number_of_arguments(stringstream &linestream){
    
    linestream>>std::ws;
    
    if(linestream.peek()== -1){
        return true;
    }
    else
        return false;
}

//checks if the user entered too many arguments
bool too_many_arguments(stringstream &linestream){
    
    linestream>>std::ws;
    
    if(linestream.peek()!= -1){
        return true;
    }
    else
        return false;
}

//checks if the locations are valid
bool check_valid_location(int &x_location, int &y_location){
 
    if(x_location < 0 | y_location < 0){
        cout<<"Error: invalid value"<<endl;
        return false;
    }else{
        return true;
    }
}

//checks if the sizes are valid
bool check_valid_size(int &x_size, int &y_size){
 
    if(x_size < 0 | y_size < 0){
        cout<<"Error: invalid value"<<endl;
        return false;
    }else{
        return true;
    }
}

//extracts a string from the linestream and assigns it to shape name
string store_shape_name(string &name, stringstream &linestream)//store the value for name
{
    if(linestream.peek() == ' ')
    {
        linestream.get();
        
    }//get value
    //output the value
    linestream >> name;
    
    return name;
}

//extracts a string from the linestream and assigns it to shape type
string store_shape_type(string &type, stringstream &linestream)//store the value for type
{
    get_value_after_current_space(linestream);//get value
    linestream >> type;//output the value
    
    return type;
}

//extracts a number from the linestream and assigns it to shape location
int store_x_location(int &x_location, stringstream &linestream)//store the value name_resistor
{
    get_value_after_current_space(linestream);//get value
    linestream >> x_location;//output the value

    return x_location;
}

//extracts a number from the linestream and assigns it to shape location
int store_y_location(int &y_location, stringstream &linestream)//store the value name_resistor
{
    get_value_after_current_space(linestream);//get value
    linestream >> y_location;//output the value

    return y_location;
}

//extracts a number from the linestream and assigns it to shape size
int store_x_size(int &x_size, stringstream &linestream)//store the value name_resistor
{
    get_value_after_current_space(linestream);//get value
    linestream >> x_size;//output the value

    return x_size;
}

//extracts a number from the linestream and assigns it to shape size
int store_y_size(int &y_size, stringstream &linestream)//store the value name_resistor
{
    get_value_after_current_space(linestream);//get value
    linestream >> y_size;//output the value
 
    return y_size;
}

int store_angle(int &rotation, stringstream &linestream){
     get_value_after_current_space(linestream);//get value
    linestream >> rotation;//output the value
    
    return rotation;
}