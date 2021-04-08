#ifndef Calssifyer_hpp
#define Calssifyer_hpp

#include <vector>
//#include <iostream>
#include <unistd.h> //for sleep()

//#include <opencv2/core/core.hpp>

//#include "/opt/halcon/include/halconcpp/HalconCpp.h"
//#include <opencv2/core/core.hpp> //it is necessary for uchar

#include "halcon/MyDictionary.cpp"

//using namespace HalconCpp;

class Classifyer {
    private:
        constexpr static const char* TAG = "Classifyer";
    
        MyDictionary* myDictionaryPtr;
    
        void test(); //used for the test
    
    public:
        std::vector<std::vector<float> > boxVector;

        Classifyer();
        Classifyer(MyDictionary* myDictionary);
        void execute(const char* jpegData);
    
        
};

#endif
