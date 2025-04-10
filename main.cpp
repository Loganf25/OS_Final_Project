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
    stringstream ss2(line);
    while (getline(ss2, line, ',')) {
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

int** OPT(int* ref_List, bool* &fault_array, int num_frames, int str_size) {
    //Table to hold all frames
    int** frame_table = new int*[str_size];
    for(int i = 0; i < str_size; i++) {
        frame_table[i] = new int[num_frames]; 
        // Now, initialize the inner array with -1 for check later on
        for (int j = 0; j < num_frames; j++) {
            frame_table[i][j] = -1;
        }
    }

    //Iterate through the reference list
    for(int i = 0; i < str_size; i++) {
        //Set current frame to previous to test against
        if (i > 0){
            for (int j = 0; j < num_frames; j++) {
                frame_table[i][j] = frame_table[i - 1][j];
            }
        }
        
        //Store current page number 
        int curr_page = ref_List[i];
        
        //Check if the page is already in the frame
        bool page_found = 0;
        for(int j = 0; j < num_frames; j++) {
            //Check if the page is in the frame
            if (frame_table[i][j] == curr_page) {
                //Page is already in the frame, so break out of the loop
                page_found = 1;
                break; 
            }
        }

        //Check if the frame is full, add to the frame if not
        bool frame_full = 1;
        if(!page_found){
            //IF the page is not found
            //Its a fault
            fault_array[i] = 1;

            for(int j = 0; j < num_frames; j++) {
                //Check if the frame is empty
                if (frame_table[i][j] == -1) {
                    //Add the page to the frame
                    frame_table[i][j] = curr_page;
                    frame_full = 0;
                    break; 
                }
            }
        }

        //If the frame is full, we need to replace a page
        if(frame_full && !page_found) {
            //Find the page to replace
            int Rpage_index = 0; 
            int farthest_index = i; 

            for(int j = 0; j < num_frames; j++) {
                //Find the farthest page in the future
                int curr_dist = str_size + 1;
                //Start at one after current page 
                for(int k = i + 1; k < str_size; k++) {
                    if (frame_table[i][j] == ref_List[k]) {
                        curr_dist = k; 
                        break;
                    }
                }

                 //Check if this is the farthest page
                 if (curr_dist > farthest_index) {
                    //If so, save index and page to replace for later
                    farthest_index = curr_dist;
                    Rpage_index = j;
                }
            }

            //Replace the page
            frame_table[i][Rpage_index] = curr_page;
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
void printTable(int** frame_table, bool* fault_array, int num_frames, int str_size) {
    //Print top of table
    for (int i = 0; i <= (str_size * 2); i ++)
    {
        cout << "_"; 
    }
    //Print each row of table
    for(int r = 0; r < num_frames; r++)
    {
        cout << endl << "|"; 
        for(int i = 0; i < str_size; i++)
        {
            //Only print page faults
            if (fault_array[i] == 1)
            {
                if (frame_table[i][r] == -1) {
                    cout << " |"; 
                }
                else {
                    cout << frame_table[i][r] << "|"; 
                }
            }
            else {
                cout << " |"; 
            }
        }
    }
    //Final line of table 
    cout << endl;
    for (int i = 0; i <= (str_size * 2); i ++)
    {
        cout << "_"; 
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
    
    for (int i = 0; i < str_size; i++) {
        cout << ref_List[i] << " "; 
    }
    cout << endl;

    //Initialize Frame Table 
    int** frame_table = nullptr; 
    bool * fault_array = new bool[str_size];
    for(int i = 0; i < str_size; i++) fault_array[i] = 0;

    if(algo == "O"){
        frame_table = OPT(ref_List, fault_array, num_frames, str_size);
    }
    else if (algo == " ")//Whichever of the two u chose
    {
        //You'll want your algo to populate and return a 2D int array of the frame table   
        //See initialization above
    }
    else {//Invalid Algorithm
        cout << "Invalid Algorithm: " + algo << endl;
        delete[] ref_List;
        delete[] fault_array;
        return 1;
    }

    printTable(frame_table, fault_array, num_frames, str_size); 
    cout << endl << "page frames" << endl; //Final part of Output

    //Free memory
    delete[] ref_List; 
    delete[] fault_array;
    for (int i = 0; i < str_size; i++) {
        delete[] frame_table[i]; 
    }
    delete[] frame_table;

    return 0;
}

