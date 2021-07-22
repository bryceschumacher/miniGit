// Header File

#ifndef MINIGIT_HPP
#define MINIGIT_HPP

#include <string>
using namespace std;
#include <vector>

struct singlyNode{
    string fileName;
    int fileVersion;
    singlyNode*next;
};


struct doublyNode {
    int commitNumber;
    singlyNode*head;
    doublyNode*previous;
    doublyNode*next;
};



class miniGit {

    public:

        miniGit();
        void createFirstNode();
        bool fileExistsSLL(int cn1, string file_name);
        singlyNode* findSLLNode(doublyNode*n1, string file_name1);
        doublyNode* findDLLNode(doublyNode*n1, int cn1);
        void SLLadd(int cn1, string file_name, int versionNumber);
        void deleteSLL(int cn1, string file_name);
        void commitChanges(int cn);
        void checkout(int checkout_num);
        void printNetwork();
        int getCheckedOutVersionNum();
        void setCheckedOutVersionNum(int num);

    private:
        doublyNode*root;
        int checkedOutVersionNum;

};

#endif
