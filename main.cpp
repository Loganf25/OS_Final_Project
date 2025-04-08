#include <iostream>
#include <fstream>
#include "LinkedList.h"

using namespace std;

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
    file.close(); 

    //Parse the line into strings
    stringstream ss(line);

    //Get the first string (algorithm name)
    getline(ss, algo, ',');

    //Get the second string (number of frames) (First string, then to int)
    string num_frames_str;
    getline(ss, num_frames_str, ',');
    num_frames = stoi(num_frames_str);
    
    //Get the rest of the string (reference string)
    string page_number_s;
    while (getline(ss, page_number_s, ',')) {
        int page_number = stoi(page_number_s);
        ref_List.push_back(page_number);
    }
    //Values are stored by reference
}


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


}

