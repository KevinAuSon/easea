//
// Created by rinku on 10/15/15.
//

#ifndef EASEA_CGPNNODE_H
#define EASEA_CGPNNODE_H

#include "CGPNode.h"

using namespace std;

/**
 *  \class   GPNNode
 *  \brief   Genetic Programming
 *  \details Used to modeling nodes with n children of abstract syntax tree.
 *  It's a subclass (and an interpretation) of the CGPNode class limited to 2 children.
 *  The first children actually is his children, the second one is his brother. (A bit confusing ya)
 *
 **/

class GPNNode : public GPNode {
    public:

    /**
     *  Get the number of children of the node.
     *
     *  @return : the number of children
     */
    int getArity() {
        int result = 0;

        for(GPNode* curs = this->children[0]; curs != NULL; curs = curs->children[1])
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
    GPNNode* getChild(int index) {
        GPNode* result = this->children[0];

        while(result && index > 0) {
            index--;
            result = result->children[1];
        }

        return (GPNNode*)result;
    }

    /**
     * Add a child to the end and give back the position.
     * It's equivalent to addChildren(child, getArity())
     *
     * @arg child : The child to add at the end
     *
     * @result : the position of the child
     *
     */
    int addChild(GPNNode* child) {
        GPNode* curs = this->children[0];
        int position = 0;

        if(!curs)
            this->children[0] = child;
        else {
            while(curs->children[1]) {
                curs = curs->children[1];
                position++;
            }

            curs->children[1] = child;
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
    int addChild(GPNNode* child, int index) {
        GPNode* curs = this->children[0];
        int position = 0;

        if(!curs || index == 0) {
            child->children[1] = curs;
            this->children[0] = child;
        }
        else {
            position = 1;

            while(curs->children[1] && index > 1) {
                curs = curs->children[1];
                position++;
                index--;
            }

            child->children[1] = curs->children[1];
            curs->children[1] = child;
        }

        return position;
    }


};


/* Here are some utility functions for the template GP */
int depthOfTree(GPNNode* root);
int enumTreeNodes(GPNNode* root);
int depthOfNode(GPNNode* root, GPNNode* node);

GPNNode* TreeConstructAux(const int constLen, const int totalLen,
                          const int currentDepth, const int maxDepth,
                          const bool full, const unsigned* opArity, const int OP_ERC);

GPNNode* TreeConstruct(unsigned iINIT_TREE_DEPTH_MIN, unsigned iINIT_TREE_DEPTH_MAX,
                       unsigned actualParentPopulationSize, unsigned parentPopulationSize,
                       float iGROW_FULL_RATIO, unsigned iVAR_LEN, unsigned iOPCODE_SIZE,
                       const unsigned* opArity, const int iOP_ERC);

std::string toString(GPNNode* root, const unsigned* opArity , const char** opCodeName, int OP_ERC);
void toString(std::ostringstream *oss, GPNNode* root, const unsigned* opArity, const char** opCodeName, int OP_ERC);

#endif //EASEA_CGPNNODE_H
