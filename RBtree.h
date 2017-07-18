//
// Created by musta on 9/29/2016.
//

#ifndef RED_BLACK_TREE_CLASS_RBTREE_H
#define RED_BLACK_TREE_CLASS_RBTREE_H

#endif //RED_BLACK_TREE_CLASS_RBTREE_H

// 1) корень дерева - черный (0)
// 2) каждый лист - черный
// 3) если узел красный (1) - оба сына черные
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
    node* nil;                  // ограничитель
    void rightRotate(node* x){
        node* y = x->childLeft;
        x->childLeft = y->childRight;

        if (y->childRight != nil){
            y->childRight->p = x;
        }

        y->p = x->p;

        if(x->p == nil)
        {
            root = y;
        } else {
            if (x == x->p->childRight){
                x->p->childRight = y;
            } else{
                x->p->childLeft = y;
            }
        }
        y->childRight = x;
        if(x != nil){
            x->p = y;
        }
    }

    void leftRotate(node* x){
        node* y = x->childRight;
        x->childRight = y->childLeft;

        if (y->childLeft != nil){
            y->childLeft->p = x;
        }

        y->p = x->p;

        if(x->p == nil)
        {
            root = y;
        } else {
            if (x == x->p->childLeft){
                x->p->childLeft = y;
            } else{
                x->p->childRight = y;
            }
        }
        y->childLeft = x;
        if(x != nil){
            x->p = y;
        }
    }


    void RBInsertFixup(node* z){
        while (z != root && z->p->color == '1') {
            /* we have a violation */
            if (z->p == z->p->p->childLeft) {
                node *y = z->p->p->childRight; // временный дядя справа
                if (y->color == '1') {

                    /* uncle is RED */
                    z->p->color = '0';
                    y->color = '0';
                    z->p->p->color = '1';
                    z = z->p->p; // переход в деда
                } else {

                    /* uncle is BLACK */
                    if (z == z->p->childRight) {
                        /* make x a left child */
                        z = z->p;
                        leftRotate(z);
                    }

                    /* recolor and rotate */
                    z->p->color = '0';
                    z->p->p->color = '1';
                    rightRotate(z->p->p);
                }
            } else {

                /* mirror image of above code */
                node *y = z->p->p->childLeft;
                if (y->color == '1') {

                    /* uncle is RED */
                    z->p->color = '0';
                    y->color = '0';
                    z->p->p->color = '1';
                    z = z->p->p;
                } else {

                    /* uncle is BLACK */
                    if (z == z->p->childLeft) {
                        z = z->p;
                        rightRotate(z);
                    }
                    z->p->color = '0';
                    z->p->p->color = '1';
                    leftRotate(z->p->p);
                }
            }
        }
        root->color = '0';
    }

    void deleteFixup(node* x){
        /*************************************
    *  maintain Red-Black tree balance  *
    *  after deleting node x            *
    *************************************/

        while (x != root && x->color == '0') {
            if (x == x->p->childLeft) {
                node *w = x->p->childRight;
                if (w->color == '1') {
                    w->color = '0';
                    x->p->color = '1';
                    leftRotate (x->p);
                    w = x->p->childRight;
                }
                if (w->childLeft->color == '0' && w->childRight->color == '0') {
                    w->color = '1';
                    x = x->p;
                } else {
                    if (w->childRight->color == '0') {
                        w->childLeft->color = '0';
                        w->color = '1';
                        rightRotate (w);
                        w = x->p->childRight;
                    }
                    w->color = x->p->color;
                    x->p->color = '0';
                    w->childRight->color = '0';
                    leftRotate (x->p);
                    x = root;
                }
            } else {
                node *w = x->p->childLeft;
                if (w->color == '1') {
                    w->color = '0';
                    x->p->color = '1';
                    rightRotate (x->p);
                    w = x->p->childLeft;
                }
                if (w->childRight->color == '0' && w->childLeft->color == '0') {
                    w->color = '1';
                    x = x->p;
                } else {
                    if (w->childLeft->color == '0') {
                        w->childRight->color = '0';
                        w->color = '1';
                        leftRotate (w);
                        w = x->p->childLeft;
                    }
                    w->color = x->p->color;
                    x->p->color = '0';
                    w->childLeft->color = '0';
                    rightRotate (x->p);
                    x = root;
                }
            }
        }
        x->color = '0';
    }
    node *findNode(int data) {

        /*******************************
         *  find node containing data  *
         *******************************/

        node *current = root;
        while(current != nil)
            if(data == current->key)
                return (current);
            else
                current = (data < current->key) ?
                          current->childLeft : current->childRight;
        return(0);
    }


public:
    node* root;

    RBtree(){
        nil = new node;
        nil->color = '0';
        root = nil;
    }
    node* RBInsert(int key){            // добавить узел
        node* curr, *prev, *x;

        curr = root;
        prev = nil;
        while (curr != nil){
            if(key == curr->key) return curr;
            prev = curr;
            curr = (key < curr->key) ? curr->childLeft : curr->childRight;
        }

        x = new node();
        x->key = key;
        x->p = prev;
        x->childLeft = nil;
        x->childRight = nil;
        x->color = '1';

        if (prev != nil){
            if(key < prev->key){
                prev->childLeft = x;
            } else{
                prev->childRight = x;
            }
        } else{
            root = x;
        }
        RBInsertFixup(x);
        return (x);
    }
    void RBdelete(int key){
        node *z, *x, *y;
        z = findNode(key);

        /*****************************
         *  delete node z from tree  *
         *****************************/

        if (z == nil || z == 0) return;


        if (z->childLeft == nil || z->childRight == nil) {
            /* y has a NIL node as a child */
            y = z;
        } else {
            /* find tree successor with a NIL node as a child */
            y = z->childRight;
            while (y->childLeft != nil) y = y->childLeft;
        }

        /* x is y's only child */
        if (y->childLeft != nil)
            x = y->childLeft;
        else
            x = y->childRight;

        /* remove y from the parent chain */
        x->p = y->p;
        if(y->p == nil){
            root = x;
        }else{
            if (y == y->p->childLeft)
                y->p->childLeft = x;
            else
                y->p->childRight = x;
        }

        if (y != z) z->key = y->key;


        if (y->color == '0')
            deleteFixup (x);

        delete y;
    }



    void printRBTree(node* z, int h){

        if(z != nil)
        {
            printRBTree(z->childRight,h + 1);
            for(int i = 0;i< h;i++) std::cout<<"     ";
            std::cout << z->key << "(" << z->color << ")" << std::endl;
            std::cout << std::endl;
            printRBTree(z->childLeft,h + 1);
        }
    }
};
