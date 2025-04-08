#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//File Reader
//Input: fileName - name of the file to read
//       ref_List - reference to the linked list to string contents
//       num_frames - reference to the number of frames
//       algo - reference to the algorithm name
//Output: VOID
//Description: Reads a file and store contents
int* fileReader(string fileName, int &num_frames, string &algo, int &str_size) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << endl;
        
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

    //Get size of reference string
    int size = 0;
    while (getline(ss, line, ',')) {
        size++;
    }
    //Account for 2 parameters at beginning
    size -= 2; 
    str_size = size;

    //Get the rest of the string (reference string)
    int* temp_list = new int[size]; 
    int i = 0; 
    string page_number_s;
    while (getline(ss, page_number_s, ',')) {
        //Change to int
        int page_number = stoi(page_number_s);
        //Store in the array
       temp_list[i] = page_number;
       //Array counter 
        i++;
    }

    //Values are stored by reference
    return temp_list;
}

void OPT(int* ref_List, int num_frames) {
    int* curr_frame = new int[num_frames]; 
    //Iterate through the reference list
    for(int i = 0; i < sizeof(ref_List); i++) {
        //Store current page number and remove from list
        //For next iteration, as we'll check new front
        int curr_page = ref_List[i];
        
        //Check if the page is already in the frame
        for(int j = 0; i < sizeof(curr_frame); i++) {
            //Check if the page is in the frame
            if (curr_frame[j] == curr_page) {
                //Page is already in the frame, so break out of the loop
                break; 
            }
            
        }
        //Check if the frame is full
        for(int j = 0; j < num_frames; j++) {
            //Check if the frame is empty
            if (curr_frame[j] == -1) {
                //Add the page to the frame
                curr_frame[j] = curr_page;
                break; 
            }
        }
    }
}

//Main Function
int main() {
    //Temp strings for file names
    string oFile = "OPT.txt";
    string fFile = ""; //Either FIFO.txt or LRU.txt

    //Initialize variables
    string algo = " "; 
    int num_frames = 0;
    int str_size = 0;

    //Read in and store file contents
    int* ref_List = fileReader(oFile, num_frames, algo, str_size); 

    //Print the Reference String (First Part of Output)
    cout << "Reference String: " << endl; 
    
    for (int i = 0; i < sizeof(ref_List); i++) {
        cout << ref_List[i] << " "; 
    }

    if(algo == "O"){

    }
    else if (algo == " ")//Whichever of the two u chose
    {
    
    }
    else {//Invalid Algorithm
        cout << "Invalid Algorithm: " + algo << endl;
        return 1;
    }

    cout << "page frames" << endl; //Final part of Output
}

