#include <iostream>
#include <fstream>
#include "LinkedList.h"

using namespace std;
//Main Function
int main() {
    //Temp strings for file names
    string oFile = "OPT.txt";
    string fFile = ""; //Either FIFO.txt or LRU.txt

    //Initialize variables
    string algo = " "; 
    int num_frames = 0;
    LinkedList<int> ref_List;

    //Read in and store file contents
    fileReader(oFile, ref_List, num_frames, algo); 

    //Print the Reference String
    cout << "Reference String: " << endl; 
    cout << ref_List.toString() << endl;

    if (algo == "O"){
        //Run the OPT algorithm
    }
    else if (algo == " "){ //Add whatever letter you chose

    }
    else {
        cout << "Invalid algorithm: " << algo << endl;
        return 1; // Exit with error code
    }
}

//File Reader
//Input: fileName - name of the file to read
//       ref_List - reference to the linked list to string contents
//       num_frames - reference to the number of frames
//       algo - reference to the algorithm name
//Output: VOID
//Description: Reads a file and store contents
void fileReader(string fileName, LinkedList<int> &ref_List, int &num_frames, string &algo) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << endl;
        return;
    }
    //Read the first and only line of the file
    string line;
    getline(file, line);
    //Parse the line into strings
    stringstream ss(line);
    //Get the first string (algorithm name)
    ss >> algo;
    //Get the second string (number of frames)
    ss >> num_frames;
    //Get the rest of the string (reference string)
    int page_number;
    while (ss >> page_number) {
        ref_List.push_back(page_number);
    }
    //Values are stored by reference
    //So, just close file
    file.close();
}
