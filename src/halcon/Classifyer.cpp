#include "Classifyer.hpp"

//#include <iostream>
//#include <vector>
//#include <fstream>

using namespace std;

//Classifyer::Classifyer() {}

Classifyer::Classifyer(MyDictionary *myDictionary) {
    myDictionaryPtr =  myDictionary;
    
    //initialization for test() to be removed for the actual code
    boxVector = {};
    boxVector.push_back({0,1,0.5,0.5,0.3,0.1,1});
    boxVector.push_back({1,0.99,0.01,0.01,0.1,0.15,0});
    //
    
    //add Halcon initalization code here
}

void Classifyer::execute(char const *jpegData, int size) {
    /*
    ofstream myfile;
    myfile.open("/home/xavier/test.jpeg");
    for (int i =0; i < size; i++){
        myfile << jpegData[i];
    }
    myfile.close();
    */
    
    //Replace the following test() by the actual code invoking Halcon object detection function
    //The input is given by the parameter of this function
    //Set the classification results to a member varialble, boxVector
    //boxVecor must be reset by boxVector = {}
    //then call boxVector.push_back({sex, score, top, left, height, width, down, righ, increase}) the number of times to add boxes

    test();
}

void Classifyer::test() {
    /*
    for (int i = 0; i < 3; i++) {
        OATPP_LOGD(TAG, "myDictionary->dictionaryParams[%d] = %d", i, myDictionaryPtr->dictionaryParams[i]);
    }
    */
    for (int i = 0; i < boxVector.size(); i++) {
        boxVector[i][8] = rand() % 2;
        boxVector[i][1] = rand() % 100 / 100.0;
        boxVector[i][2] = rand() % 80 / 100.0;
        boxVector[i][3] = rand() % 80 / 100.0;
        boxVector[i][4] = (rand() % 10 + 10) / 100.0;
        boxVector[i][5] = (rand() % 10 + 10) / 100.0;
        
        //usleep(100 * 1000); //sleep 200 miliseconds
    }
}