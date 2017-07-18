#include <iostream>
#include "RBtree.h"

using namespace std;

int main() {
    RBtree* tree = new RBtree();

    tree->RBInsert(92);
    tree->RBInsert(57);
    tree->RBInsert(79);
    tree->RBInsert(66);
    tree->RBInsert(89);
    tree->RBInsert(46);
    tree->RBInsert(77);
    tree->RBInsert(72);
    tree->RBInsert(84);
    tree->RBInsert(19);
    tree->RBInsert(56);
    tree->RBInsert(97);
    tree->RBInsert(3);
    tree->printRBTree(tree->root, 0);


    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "*******" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    tree->RBdelete(79);
    tree->printRBTree(tree->root, 0);



    return 0;
}
