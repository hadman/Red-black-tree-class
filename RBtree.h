//
// Created by musta on 9/29/2016.
//

#ifndef RED_BLACK_TREE_CLASS_RBTREE_H
#define RED_BLACK_TREE_CLASS_RBTREE_H

#endif //RED_BLACK_TREE_CLASS_RBTREE_H

// 1) корень дерева - черный
// 2) каждый лист - черный
// 3) если узел красный - оба сына черные
// 4) для каждого узла все простые пути от него до листьев,
// являющихся его потомками, содержат одинаковое кол-во черных  узлов

struct node{
    char color;
    int key;
    node* p;                    // parent
    node* childLeft;
    node* childRight;
};

class RBtree {
private:
    node* root;
    node* nil;                  // ограничитель
public:
    RBtree(){
        root = new node;
        nil = new node;
        nil->color = 'B';
    }
    void RBInsert(int key){            // добавить узел
        node* y = this->nil;
        node* x = this->root;
        node* newNode = new node;
        newNode->key = key;

        while (x != this->nil){
            y = x;
            if ( newNode->key < x->key){
                x = x->childLeft;
            } else{
                x = x->childRight;
            }
        }
//
//        newNode->p = y;
//
//        if( y == this->nil){
//            this->root = newNode;
//        } else{
//            if(newNode->key < y->key){
//                y->childLeft = newNode;
//            } else{
//                y->childRight = newNode;
//            }
//        }
//        newNode->childLeft = this->nil;
//        newNode->childRight = this->nil;
//        newNode->color = 'R';
//        this->RBInsertFixup(newNode);
    }

    void rightRotate(node* x){

    }

    void leftRotate(node* x){
        node* y = x->childRight;
        x->childRight = y->childLeft;

        if (y->childLeft != this->nil){
            y->childLeft->p = x;
        }

        y->p = x;

        if(x->p == this->root)
        {
            this->root = y;
        } else {
            if (x == x->p->childLeft){
                x->p->childLeft = y;
            } else{
                x->p->childRight = y;
            }
        }
        x->p = y;
    }

    int bh(node* x){            // черная высота узла

    }

    void RBInsertFixup(node* z){
        while (z->p->color == 'R'){
            if (z->p == z->p->p->childLeft){
                node* y = z->p->p->childRight;
                if(y->color == 'R'){
                    z->p->color = 'B';
                    y->color = 'B';
                    z->p->p->color = 'R';
                    z = z->p->p;
                } else {
                    if(z == z->p->childRight){
                        z = z->p;
                        leftRotate(z);
                    }
                    z->p->color = 'B';
                    z->p->p->color = 'R';
                    rightRotate(z->p->p);
                }
            } else{
                node* y = z->p->p->childLeft;
                if(y->color == 'R'){
                    z->p->color = 'B';
                    y->color = 'B';
                    z->p->p->color = 'R';
                    z = z->p->p;
                } else {
                    if(z == z->p->childLeft){
                        z = z->p;
                        leftRotate(z);
                    }
                    z->p->color = 'B';
                    z->p->p->color = 'R';
                    rightRotate(z->p->p);
                }
            }
        }
        root->color = 'B';
    }

    void printRBTree(node* z, int h){
        if(z != this->nil){
            printRBTree(z->childLeft, h+1);
            for (int i = 1; i < h; ++i) {
                std::cout << " ";
            }
            std::cout << z->key;
            printRBTree(z->childRight, h+1);
        }
    }
};
