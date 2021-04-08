#ifndef MyDictionary_cpp
#define MyDictionary_cpp

#include "oatpp/core/macro/component.hpp"

class MyDictionary {
private:
              
public:
    unsigned char dictionaryParams[3]; //for test to be removed
    
    MyDictionary() {
        
        //code for test to be removed
        dictionaryParams[0] = 0;
        dictionaryParams[1] = 1;
        dictionaryParams[2] = 2;
        //
        
        //read a dictionary from a file and set member variables here
    }
    
};

#endif