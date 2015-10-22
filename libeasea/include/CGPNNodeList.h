//
// Created by rinku on 10/16/15.
//

#ifndef EASEA_CGPNodeLIST_H
#define EASEA_CGPNodeLIST_H

#include "CGPNNode.h"

/**
 *  \class   GPNodeList
 *  \brief   Genetic Programming
 *  \details Used to modeling a list of node (used to keep a slice of the tree).
 *
 **/

class GPNodeList {
protected:
    GPNode* elt;
    GPNodeList* next;

public:
    GPNodeList() : elt(NULL), next(NULL) {}
    GPNodeList(GPNode* node) : elt(node), next(NULL) {}

    ~GPNodeList() { delete next; }

    /**
     * Some getters
     *
     * @return : the attribute to access
     */
    GPNode* getElt() { return this->elt; }
    GPNodeList* getNext() { return this->next; }

    /**
     * Add an element at the head of the list
     *
     * @arg node : The element to add
     *
     * @result : The new head of the list
     */
    GPNodeList* add(GPNode* node) {
        GPNodeList* head = new GPNodeList(node);
        head->next = this;

        return head;
    }

    /**
     * Concatenate two list
     *
     * @arg tail : the second list
     *
     * @result : the concatenation of the lists
     */
    GPNodeList* concat(GPNodeList* tail) {
        GPNodeList* curs = this;

        while(curs->next) curs = curs->next;
        curs->next = tail;

        return this;
    }

    /*
     * Count the number of children of all the elements of the list
     *
     * @result : the number of children
     */
    int countChildren() {
        return elt->getArity() + next->countChildren();
    }
};

GPNodeList* getSlice(GPNode* root, int depth);
GPNode* selectNode( GPNode* root, int* childId, int* depth);

#endif //EASEA_CGPNodeLIST_H
