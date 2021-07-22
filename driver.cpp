

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>

#include <experimental/filesystem>
using namespace std;
#include <filesystem>
#include "miniGit.hpp"
#include <vector>






int main() {
      

    // initializes commitNumber to 0
    int commitNumber = 0;



    // basic getline command, deciding whether or not to initialize repo
    string input_init_string = "";
    cout << "Would you like to initialize an empty repository in the current directory?" << endl;
    cout << "(yes), (no)" << endl;
    getline(cin,input_init_string);




    // if input is yes, creates subdirectory called .minigit    
    if(input_init_string == "yes") {
        filesystem::remove_all(".minigit"); 
        filesystem::create_directory(".minigit");
    }
    else if(input_init_string == "no") {
        cout << "Okay. goodbye!" << endl;
    }
    else {
        cout << "Invalid input. restart program and enter either \"yes\" or \"no\"" << endl;
    }

    

    // if we got this far, we're good to go! Creates new doublyNode
    // now, we have one doublyNode with pretty much no data besides the commit number being 0
    miniGit mg1;
    mg1.createFirstNode();



    int option = 0;
    string input_string = "";
    while (option != 6) {

        // gets input, stores in variable "option" after converting to int, runs while loop until option is 6 (corresponds with quitting the application)
        cout << "What would you like to do?" << endl;
        cout << "1. Add files to the current commit" << endl;
        cout << "2. Remove files from current commit" << endl;
        cout << "3. Commit changes" << endl;
        cout << "4. Check out a specific version" << endl;
        cout << "5. Print network" << endl;
        cout << "6. Quit" << endl;
        getline(cin, input_string);
        option = stoi(input_string);
        
        // switch statement, does specific action depending on input stored in "option" var
        switch(option) {
            // Corresponds to "Add files to the current commit"
            case 1:
                {
                if(commitNumber != mg1.getCheckedOutVersionNum()) {
                    cout << "Cannot add!!! Checked out number is not on current commit" << endl;
                }
                // We need to get a valid file name that is in the current directory
                string file_name = "";
                bool file_name_invalid = true;
                while (file_name_invalid) {
                    cout << "Enter a filename" << endl;
                    getline(cin, file_name);
                    bool is_in_direc = false;
                    // we need to come up w/ alternative for this path bs
                    for(auto& p: filesystem::directory_iterator("./")) {
                        if("./" + file_name == p.path()) {
                            is_in_direc = true;
                        }
                    }
                    if(!is_in_direc) {
                        cout << "file isn't in directory. Choose a different file" << endl;
                        
                    }
                    else if (is_in_direc) {
                        cout << "file is in directory!" << endl;
                        file_name_invalid = false;

                    }
                    
                }

                // now we have a file that was in the current directory. Need to check if it already exists in the current SLL corresponding to the DLL node we're on


                bool file_exists_already = mg1.fileExistsSLL(commitNumber, file_name);
                if(file_exists_already) {
                    cout << "File is already in SLL" << endl;
                } 
                else {
                    cout << "File was not in SLL. Adding to SLL" << endl;
                    // at this point, we have located a file that is in the current repository. We have ensured that the file is not already in the current version's commit
                    // adds to linked list


                    mg1.SLLadd(commitNumber, file_name, 0);



                }
                break;
                }

            // Corresponds to "Remove files from the current commit"
            case 2:
                {
                if(commitNumber != mg1.getCheckedOutVersionNum()) {
                    cout << "Cannot remove!!! Checked out number is not on current commit" << endl;
                }
                string incoming_string = "";
                cout << "What file would you like to remove?" << endl;
                getline(cin, incoming_string);

                bool file_in_repo = mg1.fileExistsSLL(commitNumber, incoming_string);
                if(file_in_repo) {
                    cout << "file in repo" << endl;
                    mg1.deleteSLL(commitNumber, incoming_string);

                }
                else {
                    cout << "file is not in repo" << endl;
                }
                break;
                }
            // Corresponds to "Commit changes"
            case 3:
                {
                if(commitNumber != mg1.getCheckedOutVersionNum()) {
                    cout << "Cannot commit!!! Checked out number is not on current commit" << endl;
                    // need to put in specific functionality so it actually doesn't let you do anything hah
                }

                    mg1.commitChanges(commitNumber);
                    commitNumber++;
                    mg1.setCheckedOutVersionNum(commitNumber);
                    
                break;
                }
            // Corresponds to "checkout a specific version"
            case 4:
                {
                    string inp_line = "";
                    string inp_line2 = "";
                    int opt_int = 0;
                    
                    cout << "Enter a commit number: (1 is the first commit) " << endl;
                    getline(cin, inp_line);
                    opt_int = stoi(inp_line);


                    cout << "Warning: this will revert back to a past commit" << endl;
                    cout << "Press enter to continue." << endl;
                    getline(cin,inp_line2);
                    
                    // implementing checkout: when a user checks out a different version number, they will be UNABLE to do any adds, deletes, commits until they go back to checking out the CURRENT version number. The ONLY thing checking out does is revert all old files back. It should not edit anything in the code itself
                    mg1.checkout(opt_int);
                    mg1.setCheckedOutVersionNum(opt_int);
                //
                break;
                }
            // Corresponds to print network, can get rid of later
            case 5:
                {
                    mg1.printNetwork();
                    break; 
                }
            // Quit
            case 6:
                {
                cout << "Goodbye!" << endl;
                break;
                }
            default:
                {
                cout << "Invalid input." << endl;
                break;
                }
        }
    }
}
