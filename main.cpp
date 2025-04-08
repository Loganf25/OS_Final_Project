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

int** OPT(int* ref_List, int num_frames, int str_size) {
    //Table to hold all frames
    int** frame_table = new int*[str_size];
    for(int i = 0; i < str_size; i++) {
        frame_table[i] = new int[num_frames]; 
    }
 
    //Iterate through the reference list
    for(int i = 0; i < str_size; i++) {
        int* curr_frame = new int[num_frames]; 
        //Holds the current frame to be stored in table
        if (i != 0)
            curr_frame = frame_table[i-1];
        

        //Store current page number 
        int curr_page = ref_List[i];
        
        //Check if the page is already in the frame
        bool page_found = 0;
        for(int j = 0; i < num_frames; i++) {
            //Check if the page is in the frame
            if (curr_frame[j] == curr_page) {
                //Page is already in the frame, so break out of the loop
                page_found = 1;
                break; 
            }
            
        }

        //Check if the frame is full, add to the frame if not
        bool frame_full = 1;
        if(!page_found){
            for(int j = 0; j < num_frames; j++) {
                //Check if the frame is empty
                if (curr_frame[j] == -1) {
                    //Add the page to the frame
                    curr_frame[j] = curr_page;
                    //Add to table as thats the end of this iteration
                    frame_table[i] = curr_frame;
                    frame_full = 0;
                    break; 
                }
            }
        }

        //If the frame is full, we need to replace a page
        if(frame_full) {

            //Find the page to replace
            int page_to_replace = -1; 
            int farthest_index = -1; 
            for(int j = 0; j < num_frames; j++) {
                //Find the farthest page in the future
                for(int k = i + 1; k < sizeof(ref_List); k++) {
                    if (curr_frame[j] == ref_List[k]) {
                        //Check if this is the farthest page
                        if (k > farthest_index) {
                            farthest_index = k;
                            page_to_replace = curr_frame[j];
                        }
                    }
                }
            }

            //Replace the page
            for(int j = 0; j < num_frames; j++) {
                if (curr_frame[j] == page_to_replace) {
                    curr_frame[j] = curr_page;
                    //Add to table as thats the end of this iteration
                    frame_table[i] = curr_frame;
                    break; 
                }
            }
        }
    }
    return frame_table;
}

//Prints the Frame Table
//Input: frame_table - the table to print
//       num_frames - the number of frames
//       str_size - the size of the reference string
//Output: VOID
//Description: Prints the frame table to the console
void printTable(int** frame_table, int num_frames, int str_size) {
   
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
    
    for (int i = 0; i < str_size; i++) {
        cout << ref_List[i] << " "; 
    }

    //Initialize Frame Table 
    int** frame_table = new int*[str_size]; //Table to hold all frames
    for(int i = 0; i < str_size; i++) {
        frame_table[i] = new int[num_frames]; 
    }

    if(algo == "O"){
        frame_table = OPT(ref_List, num_frames, str_size);
    }
    else if (algo == " ")//Whichever of the two u chose
    {
    
    }
    else {//Invalid Algorithm
        cout << "Invalid Algorithm: " + algo << endl;
        return 1;
    }

    printTable(frame_table, num_frames, str_size); 
    cout << "page frames" << endl; //Final part of Output
}

