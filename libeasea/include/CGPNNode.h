//
// Created by rinku on 10/15/15.
//

#ifndef EASEA_CGPNode_H
#define EASEA_CGPNode_H

#include "CGPNode.h"

using namespace std;

/**
 *  \class   GPNode
 *  \brief   Genetic Programming
 *  \details Used to modeling nodes with n children of abstract syntax tree.
 *  It's a subclass (and an interpretation) of the CGP2Node class limited to 2 children.
 *  The first children actually is his children, the second one is his brother. (A bit confusing ya)
 *
 **/

class GPNode : public GP2Node {
    public:

    void destruct() {
        GPNode* child = this->getFirstChild();
        if(child) {
            child->destructAux();
            delete child;
        }
    }

    void destructAux() {
        for (int i = 0; i < 2; ++i) {
            if(children[i]) {
                ((GPNode*)children[i])->destructAux();
                delete children[i];
            }
        }
    }
    /**
     *  Get the number of children of the node.
     *
     *  @return : the number of children
     */
    int getArity() {
        int result = 0;

        for(GPNode* curs = this->getFirstChild(); curs != NULL; curs = curs->getBrother())
            result++;

        return result;
    }

    /**
     * Get the child at the index 'index'
     *
     * @arg index : the child's index to get
     *
     * @return : return the node or NULL if it doesn't exist
     */
    GPNode* getChild(int index) {
        GPNode* result = this->getFirstChild();

        while(result && index > 0) {
            index--;
            result = result->getBrother();
        }

        return result;
    }

    /**
     * Get the first child
     *
     * @return : return the first child, or NULL if it doesn't exist
     */
    GPNode* getFirstChild() { return (GPNode*)this->children[0]; }

    /**
     * Get his brother
     *
     * @return : return the brother, or NULL if it doesn't exist
     */
    GPNode* getBrother() { return (GPNode*)this->children[1]; }

    /**
     * Set the first child
     *
     * @arg n : the new child
     */
    void setFirstChild(GPNode* n) { this->children[0] = n; }

    /**
     * Set his brother
     *
     * @arg n : the new brother
     */
    void setBrother(GPNode* n) { this->children[1] = n; }

    /**
     * Add a child to the end and give back the position.
     * It's equivalent to addChildren(child, getArity())
     *
     * @arg child : The child to add at the end
     *
     * @result : the position of the child
     *
     */
    int addChild(GPNode* child) {
        GPNode* curs = this->getFirstChild();
        int position = 0;

        if(!curs)
            this->setFirstChild(child);
        else {
            while(curs->getBrother()) {
                curs = curs->getBrother();
                position++;
            }

            curs->setBrother(child);
        }

        return position;
    }

    /**
     * Add a chil to the 'index' position or at the end if there is not enough children
     * and give back the position.
     *
     * @arg child : The child to add at the end
     * @arg index : The position where to put the new child
     *
     * @result : the position of the child
     *
     */
    int addChild(GPNode* child, int index) {
        GPNode* curs = this->getFirstChild();
        int position = 0;

        if(!curs || index == 0) {
            child->setBrother(curs);
            this->setFirstChild(child);
        }
        else {
            position = 1;

            while(curs->getBrother() && index > 1) {
                curs = curs->getBrother();
                position++;
                index--;
            }

            child->setBrother(curs->getBrother());
            curs->setBrother(child);
        }

        return position;
    }


};


/* Here are some utility functions for the template GP */
int depthOfTree(GPNode* root);
int enumTreeNodes(GPNode* root);
int depthOfNode(GPNode* root, GPNode* node);

GPNode* TreeConstructAux(const int constLen, const int totalLen,
                          const int currentDepth, const int maxDepth,
                          const bool full, const unsigned* opArity, const int OP_ERC);

GPNode* TreeConstruct(unsigned iINIT_TREE_DEPTH_MIN, unsigned iINIT_TREE_DEPTH_MAX,
                       unsigned actualParentPopulationSize, unsigned parentPopulationSize,
                       float iGROW_FULL_RATIO, unsigned iVAR_LEN, unsigned iOPCODE_SIZE,
                       const unsigned* opArity, const int iOP_ERC);

std::string toString(GPNode* root, const unsigned* opArity , const char** opCodeName, int OP_ERC);
void toString(std::ostringstream *oss, GPNode* root, const unsigned* opArity, const char** opCodeName, int OP_ERC);

#endif //EASEA_CGPNode_H
