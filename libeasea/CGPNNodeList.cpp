//
// Created by rinku on 10/16/15.
//

#include "include/CRandomGenerator.h"
#include "include/global.h"
#include "include/CGPNNodeList.h"

extern CRandomGenerator* globalRandomGenerator;

/**
 * Return the list of all the node of depth 'depth'.
 *
 * @arg root : the root of the tree
 * @arg depth : the depth of the slice to get
 *
 * @result : a list of GPNode
 */
GPNodeList* getSlice(GPNode* root, int depth) {
    GPNodeList* result = NULL;

    if(depth == 0)
        result = new GPNodeList(root);
    else
        result = getSlice((GPNode*)root->getFirstChild(), depth-1)->concat(getSlice((GPNode*)root->getBrother(), depth));

    return result;
}

/**
 * Give a node picked randomly with a certain depth (first the depth is chose, then the node in this slice).
 *
 * @arg root : the root of the tree
 * @arg childId : return the id of the child
 * @arg depth : return the depth of the node
 *
 * @return : the node selected
 */
GPNode* selectNode( GPNode* root, int* childId, int* depth) {
    GPNode* result = NULL;

    *depth = globalRandomGenerator->random(0, depthOfTree(root));
    if(*depth > 0) {
        GPNodeList* slice = getSlice(root, *depth);
        GPNodeList* curs = slice;
        int index = globalRandomGenerator->random(0, slice->countChildren());

        int currentIndex = slice->getElt()->getArity();
        while(index > currentIndex) {
            index -= currentIndex;
            curs = curs->getNext();
            currentIndex = curs->getElt()->getArity();
        }

        *childId = index;
        result = curs->getElt()->getChild(index);
        delete slice;
    }

    return result;
}