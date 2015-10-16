//
// Created by rinku on 10/15/15.
//

#include <global.h>
#include <sstream>
#include "include/CGPNNode.h"

/**
    Compute the maximum depth of a tree, rooted on root.
    The depth of a tree is the number of edge from the root node to
    the furthest leaf.
    If root is null, the result is -1 (just a convention),
    if it's a leaf the result is 0...

    @arg root : root of the tree

    @return : depth of current tree rooted on root
*/
int depthOfTree(GPNNode* root){
    int depth = -1;

    if(root) {
        depth = MAX(depthOfTree(root->children[0]) + 1,
                    depthOfTree(root->children[1]));
    }

    return depth;
}

/**
    Compute the depth of a node, i.e, the number of edge between the node
    and the root. If the node isn't in the tree, this function return -1.

    @arg root : root of the tree
    @arg node : a node of the tree

    @return : depth of the current node
*/
int depthOfNode(GPNNode* root, GPNNode* node){
    int depth = -1;

    if(root == node)
        depth = 0;
    else if(root){
        depth = MAX(depthOfNode(root->children[0], node) + 1,
                    depthOfNode(root->children[1], node));
    }

    return depth;
}

/**
    Count the node number in the tree.

    @arg root : root of the tree

    @return : the number of node in the tree.
*/
int enumTreeNodes(GPNode* root){
    int nbNode = 0;

    if(root) {
        nbNode = enumTreeNodes(root->children[0]) +
                 enumTreeNodes(root->children[1]) + 1;
    }

    return nbNode;
}


/**
   Recursive construction method for trees.
   Koza construction methods. Function set has to be ordered,
   with first every terminal nodes and then non-terminal.

   @arg constLen : length of terminal function set.
   @arg totalLen : length of the function set (non-terminal+terminal)
   @arg currentDepth : depth of the origin (should always be 0, when the function
   is directly call)
   @arg maxDepth : The maximum depth of the resulting tree.
   @arg full : whether the construction method used has to be full (from koza's book)
   Otherwise, it will use grow method (defined in the same book).

   @return : pointer to the root node of the resulting sub tree
*/
GPNNode* TreeConstructAux(const int constLen, const int totalLen, const int currentDepth,
                       const int maxDepth, const bool full,
                       const unsigned* opArity, const int OP_ERC){

    GPNNode* newNode = new GPNNode();

    // first select the opCode for the current Node.
    if( full ){
        if( currentDepth<maxDepth ) newNode->opCode = globalRandomGenerator->random(constLen,totalLen);
        else newNode->opCode = globalRandomGenerator->random(0, constLen);
    }
    else{
        if( currentDepth<maxDepth ) newNode->opCode = globalRandomGenerator->random(0, totalLen);
        else newNode->opCode = globalRandomGenerator->random(0, constLen);
    }

    int arity = opArity[newNode->opCode];
    //node->arity = arity;

    GPNNode* next = NULL;
    for(int i = 0; i < arity; i++) {
        GPNNode* temp = TreeConstructAux(constLen, totalLen, currentDepth+1,
                                         maxDepth, full, opArity, OP_ERC);
        temp->children[1] = next;
        next = temp;
    }

    newNode->children[0] = next;

    if( newNode->opCode==OP_ERC )
        newNode->erc_value = globalRandomGenerator->random(0.,1.);

    //else if( node->opCode==OP_VAR )
    //node->var_id = globalRandomGenerator->random(1,VAR_LEN);

    return newNode;
}


GPNNode * TreeConstruct(unsigned INIT_TREE_DEPTH_MIN, unsigned INIT_TREE_DEPTH_MAX,
                        unsigned actualParentPopulationSize, unsigned parentPopulationSize,
                        float GROW_FULL_RATIO, unsigned VAR_LEN, unsigned OPCODE_SIZE,
                        const unsigned* opArity, const int OP_ERC){

    int id = actualParentPopulationSize;
    int seg = parentPopulationSize/(INIT_TREE_DEPTH_MAX-INIT_TREE_DEPTH_MIN);
    int currentDepth = INIT_TREE_DEPTH_MIN+id/seg;

    bool full;
    if( GROW_FULL_RATIO==0 ) full=true;
    else full = (id%seg)/(int)(seg*GROW_FULL_RATIO);

    return TreeConstructAux( VAR_LEN+1, OPCODE_SIZE , 1, currentDepth ,full, opArity, OP_ERC);
}


void toString(std::ostringstream *oss, GPNNode* root, const unsigned* opArity, const char** opCodeName, int OP_ERC) {
    (*oss) << '('
           << opCodeName[root->opCode];

    if(root->children[0]) {
        (*oss) << ' ';
        toString(oss, (GPNNode*)root->children[0], opArity, opCodeName, OP_ERC);
    }

    (*oss) << ')';

    if(root->children[1]) {
        (*oss) << ' ';
        toString(oss, (GPNNode*)root->children[1], opArity, opCodeName, OP_ERC);
    }

    return;
}

std::string toString(GPNNode* root, const unsigned* opArity , const char** opCodeName, int OP_ERC) {
    std::ostringstream oss;

    toString(&oss, root, opArity, opCodeName, OP_ERC);

    return oss.str();
}