//
// Created by rinku on 10/16/15.
//

#ifndef EASEA_CGPNNODELIST_H
#define EASEA_CGPNNODELIST_H

#include "CGPNNode.h"

/**
 *  \class   GPNNodeList
 *  \brief   Genetic Programming
 *  \details Used to modeling a list of node (used to keep a slice of the tree).
 *
 **/

class GPNNodeList {
protected:
    GPNNode* elt;
    GPNNodeList* next;

public:
    GPNNodeList() : elt(NULL), next(NULL) {}
    GPNNodeList(GPNNode* node) : elt(node), next(NULL) {}

    ~GPNNodeList() { delete next; }

    /**
     * Some getters
     *
     * @return : the attribute to access
     */
    GPNNode* getElt() { return this->elt; }
    GPNNodeList* getNext() { return this->next; }

    /**
     * Add an element at the head of the list
     *
     * @arg node : The element to add
     *
     * @result : The new head of the list
     */
    GPNNodeList* add(GPNNode* node) {
        GPNNodeList* head = new GPNNodeList(node);
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
    GPNNodeList* concat(GPNNodeList* tail) {
        GPNNodeList* curs = this;

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

GPNNodeList* getSlice(GPNNode* root, int depth);
GPNNode* selectNode( GPNNode* root, int* childId, int* depth);

#endif //EASEA_CGPNNODELIST_H
