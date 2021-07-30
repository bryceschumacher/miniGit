// implementation file
#include <iostream>
#include <fstream>
#include "miniGitDriver.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <experimental/filesystem>
#include <filesystem>


using namespace std;


miniGit::miniGit() {
    root = nullptr;
    
}

void miniGit::createFirstNode() {
    doublyNode * createdNode = new doublyNode;
    //head is singly linked list's head
    createdNode->head = nullptr; 
    createdNode->next = nullptr;
    createdNode->previous = nullptr;
    createdNode->commitNumber = 0;
    root = createdNode;

}

doublyNode* miniGit::findDLLNode(doublyNode*n1, int cn1) {

    while((n1->commitNumber != cn1) && (n1->next != nullptr)) {
        n1 = n1->next;
    }
    if(n1->commitNumber == cn1) {
        return n1;
    }
    else {
        return nullptr;
    }
}

singlyNode* miniGit::findSLLNode(doublyNode*n1, string file_name1) {

    singlyNode*crawler = n1->head;
    if(crawler == nullptr) {
        return nullptr;
    }
    else {
        // is equal to the SLL's head which is just nullptr. Haven't created a new node on SLL yet.
        while((crawler->fileName != file_name1) && (crawler->next != nullptr)) {
            crawler = crawler->next;
        }
        if(crawler->fileName == file_name1) {
            return crawler;
            // file is in SLL
        }
        else {
            return nullptr;
        }

    }
}

bool miniGit::fileExistsSLL(int cn, string file_name) {
    // we have the commit number which means we can find the correct DLL node to check.
    doublyNode*pointer_to_DLL_node = findDLLNode(root, cn);

    // we have the DLL node needed
    bool is_file_in_there = false;
    if(pointer_to_DLL_node != nullptr) {
        if(findSLLNode(pointer_to_DLL_node, file_name) != nullptr) {
            is_file_in_there = true;
        }
    }
    return is_file_in_there;
}


void miniGit::SLLadd(int cn1, string file_name, int versionNumber) {

    doublyNode*doubly_node_found = findDLLNode(root, cn1);
    singlyNode*crawler = doubly_node_found->head;

    if(crawler == nullptr) {
        singlyNode*temp = new singlyNode;
        temp->fileName = file_name;
        temp->fileVersion = versionNumber;
        temp->next = nullptr;
        doubly_node_found->head = temp;
    }
    else {
        while(crawler->next != nullptr) {
            crawler = crawler->next;
        }
        singlyNode*temp = new singlyNode;
        temp->fileName = file_name;
        temp->fileVersion = versionNumber;
        temp->next = nullptr;
        crawler->next = temp;
    }
}







void miniGit::deleteSLL(int cn1, string file_name) {
    doublyNode*dll_node = findDLLNode(root, cn1);
    // we have the correct DLL node. Now, we have a file_name and we need to delete the correct SLL node
    // cases: if dll_node->head is nullptr, which should never happen, we need to return an error
    // in order to delete these, because it's a SLL, we need to access the node BEFORE the node we're deleting
    // Theoretically, we have already checked that the SLL node is in there!! But we should put in stopping measures just in case..
    singlyNode*crawler = dll_node->head;
    if(crawler == nullptr) {
        cout << "an error occured. Attempted deleting SLL node, but found that there were no SLL nodes for the current commit number!" << endl;
    }
    else if(crawler->fileName == file_name || crawler->next == nullptr) {
        if(crawler->fileName == file_name) {
            // this is if it's the first one in the SLL!
            cout << "first node in SLL. We're deleting it now! NEed to check if this screws up because we're setting it to crawler->next which is nullptr" << endl;
            singlyNode*temp = crawler->next;
            delete crawler;
            dll_node->head = temp;
        }
        else if(crawler->next == nullptr) {
            cout << "SLL isn't in the list! first node wasn't it, and second node is null!" << endl;
        }
    }
    else {
        while(crawler->next->next != nullptr && crawler->next->fileName != file_name) {
            crawler = crawler->next;
        }
        // we check two in the front of, because we don't want to check the fileName of a nullptr node. That will throw an error
        // now, we can have two situations: either the next next is a nullptr OR the next's filename is the file we're looking for
        if(crawler->next->next == nullptr) {
            // we have to check if crawler->next is the fileName!! This is the case if the last element in the SLL is the one in which we are trying to delete
            if(crawler->next->fileName == file_name) {
                singlyNode*temp_singly = crawler->next;
                crawler->next = nullptr;
                delete temp_singly;
            }
            else {
                // file isn't in the SLL node!!!
                cout << "file isn't in the SLL!!! Nothing to delete!" << endl;
            }
        }
        else if(crawler->next->fileName == file_name) {
            // this is if we're deleting a node that is somewhere in the middle. ->next->next isn't nullptr. So we need to set the crawler's->next to a different node when deleting
            singlyNode*temp_singly = crawler->next;
            crawler->next = crawler->next->next;
            delete temp_singly;
        }
    }

}




void addFileToRepo(string file_name, int fileVersionBeingCommitted) {
    // inputted readme.txt
    int file_name_length = file_name.length();
    string s = to_string(fileVersionBeingCommitted);
    if(fileVersionBeingCommitted < 10) {
        s = "0" + s;
    }
    ofstream myfileout;
    string str1 = "./.minigit/" + file_name.substr(0, file_name_length-4) + s + file_name.substr(file_name_length-4, file_name_length);
    myfileout.open(str1, std::ios_base::app);
    ifstream myfilein;
    myfilein.open(file_name);
    string input_line;
    while (getline(myfilein, input_line)) {
        myfileout << input_line << endl;
    }
    
    myfileout.close();
    myfilein.close();



}



bool compareFiles(string file_name1, string file_name2) {
    // compare two files.. if any differences, return true.
    // first file is in main file, second file is in .minigit

    cout << file_name1 << endl;
    cout << file_name2 << endl;

    ifstream myfilemain;
    myfilemain.open(file_name1);

    ifstream myfilemini;
    myfilemini.open("./.minigit/" + file_name2);
    cout << "B" << endl;
    string input_line;
    string input_line2;
    vector<string> file1_lines;
    vector<string> file2_lines;
    while (getline(myfilemain, input_line)) {
        file1_lines.push_back(input_line);
    }
    while(getline(myfilemini, input_line2)) {
        file2_lines.push_back(input_line2);
            
    }

    // if files have different amount of lines, we know they are automatically different. Return true
    if(file1_lines.size() != file2_lines.size()) {
        return true;
    }

    for(int i = 0; i < file1_lines.size(); i++) {
        if(file1_lines[i] != file2_lines[i]) {
            return true;
        }
    }
    return false;


}



void miniGit::commitChanges(int cn) {
    doublyNode*current_DLL = findDLLNode(root, cn);
    singlyNode*crawler = current_DLL->head;

    vector<string> files_that_have_changed;
    // need to traverse through SLL
    while(crawler != nullptr) {
        // now, need to check if a file is in the .minigit repository
        // can traverse files in the repository now. Can check if any of them have the base name of the file
        // naming convention will be fileName_00
        int length_of_curr_file_version = crawler->fileName.length();
        bool file_exists_in_minigit = false;
        for(auto& p: filesystem::directory_iterator("./.minigit")) {
            string temp_str = p.path();
            temp_str = temp_str.substr(11, 11+length_of_curr_file_version);
            bool curr_file_same = true;
            // for each file in .miniGit repo
            for(int i = 0; i < length_of_curr_file_version-4; i++) {
                // check and see if each character is the same as fileName of crawler
                if (temp_str[i] != crawler->fileName[i]) {
                    curr_file_same = false;
                    break;
                }
            }
            if (curr_file_same) {
                file_exists_in_minigit = true;
                // can do something here while we're still on this file
            }
        }
        if (!file_exists_in_minigit) {
            cout << "File does NOT exist in miniGit!" << endl;
            // file does not exist in miniGit
            addFileToRepo(crawler->fileName, crawler->fileVersion);
        }
        else {
            cout << "File does exist in miniGit!" << endl;
            // now, need to check if file has changed or not. Then, if file HAS changed, need to add file with new version number
            string curr_file = crawler->fileName;
            int curr_file_length = curr_file.length();
            string s_num = to_string(crawler->fileVersion);
            if(crawler->fileVersion < 10) {
                s_num = "0" + s_num;
            }
            // will be something like readme.txt
            string curr_file_mini = curr_file.substr(0, curr_file_length-4) + s_num + curr_file.substr(curr_file_length-4, curr_file_length);
            bool is_file_changed = compareFiles(curr_file, curr_file_mini);
            if (is_file_changed) {
                cout << "File has changed!" << endl;
                addFileToRepo(crawler->fileName, crawler->fileVersion+1);
                files_that_have_changed.push_back(crawler->fileName);
            }
            else {
                cout << "File has not changed." << endl;
            }

        }





        crawler = crawler->next;
    }
    // at this point, we have traversed entire SLL. We have determined which files have changed, which were never added to miniGit. We have changed miniGit folder accordingly
    // now, we must create a new DLL node.
    // currently double node is current_DLL
    doublyNode*newDoublyNode = new doublyNode;
    newDoublyNode->head = nullptr;
    newDoublyNode->next = nullptr;
    newDoublyNode->commitNumber = current_DLL->commitNumber+1;
    newDoublyNode->previous = current_DLL;
    current_DLL->next = newDoublyNode;

    // now, need to copy all SLL nodes in, add 1 to versionNumber if they've changed......

    // we have a vector, filesThatHaveChanged of all files that have changed. Need to update their version numbers in new SLL
    singlyNode*n_crawler = current_DLL->head;

    while(n_crawler != nullptr) {
        bool is_updated = false;
        for(int x = 0; x < files_that_have_changed.size(); x++) {
            if(files_that_have_changed[x] == n_crawler->fileName) {
                is_updated = true;
            }
        }
        if(is_updated) {
            SLLadd(cn+1, n_crawler->fileName, n_crawler->fileVersion+1);
        }
        else {
            SLLadd(cn+1, n_crawler->fileName, n_crawler->fileVersion);
        }
        n_crawler = n_crawler->next;

    }


}
void miniGit::printNetwork() {



        doublyNode*DLL_node = root;
        singlyNode*singly_node_ptr;
        singlyNode*singly_node_ptr2;
        int n = 1;
        int z = 1;
        while(DLL_node != nullptr) {
            cout << "Doubly node " << n << endl;
            cout << "Commit number: " << DLL_node->commitNumber << endl << endl;

            singly_node_ptr = DLL_node->head;
            while(singly_node_ptr != nullptr) {
                cout << "Singly node " << z << endl;
                cout << "File name: " << singly_node_ptr->fileName << endl;
                cout << "File version: " << singly_node_ptr->fileVersion << endl << endl;
                singly_node_ptr = singly_node_ptr->next;
                z++;
            }
            cout << endl << endl;
            z = 1;
            DLL_node = DLL_node->next;
            n++;

        }

}

// thought process behind this: commitNumber in driver file will be the commitNumber it's supposed to be on without any checking out. checkedOutVersionNum will be whichever num we're currently on
void miniGit::setCheckedOutVersionNum(int num) {
    checkedOutVersionNum = num;
}


int miniGit::getCheckedOutVersionNum() {
    return checkedOutVersionNum;
}

void miniGit::checkout(int checkout_num) {
    // all we're gonna do here is change files. Go to specific commit number's DLL, iterate through and get all files in that we want
    cout << "New checkout level is " << checkout_num << endl;
    doublyNode*dll_node = findDLLNode(root, checkout_num);
    // now that we have the right DLL node, need to iterate through it and get correct files.
    singlyNode*crawler = dll_node->head;


    // removes all files besides minigit directory
    for (const auto & entry : filesystem::directory_iterator("./")) {
        if(entry.path() != "./.minigit") {
            remove(entry.path());
        }
    }


    while(crawler != nullptr) {
        string file_name_to_load = crawler->fileName;
        cout << file_name_to_load << endl;
        
        ofstream myfileout;
        myfileout.open("./" + file_name_to_load, std::ios_base::app);
        ifstream myfilein;


            
        int curr_file_length = file_name_to_load.length();
        string s_num = to_string(crawler->fileVersion);
        if(crawler->fileVersion < 10) {
            s_num = "0" + s_num;
        }
        string curr_file_mini = file_name_to_load.substr(0, curr_file_length-4) + s_num + file_name_to_load.substr(curr_file_length-4, curr_file_length);
        myfilein.open("./.minigit/" + curr_file_mini);
        string input_line;
        while (getline(myfilein, input_line)) {
            myfileout << input_line << endl;
        }
        myfileout.close();
        myfilein.close();
        





        crawler = crawler->next;
    }
}



//
