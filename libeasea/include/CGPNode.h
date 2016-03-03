/**
 * @file CGPNode.h
 * @version 1.0
 *
 **/

#ifndef __C_GPNODE__
#define __C_GPNODE__

#include <iostream>
#include <cstdlib>

using namespace std;

#define MAX_ARITY 2          // maximum arrity for GP node

/**
 *  \class   GPNode
 *  \brief   Genetic Programming
 *  \details Used to modelised nodes of abstract syntax tree
 *
 **/

class GPNode {
    protected:
        GPNode* children[2];
  public:
    int opCode;


    virtual bool isTerminal() = 0;
    virtual float getValue(float input[]) = 0;
    virtual GPNode* clone() = 0;
    virtual GPNode* getChild(int i) { return children[i]; }
    virtual GPNode* setChild(int i, GPNode* node) {
        children[i] = node;
        return this;
    }

    GPNode(){  // Constructor
      for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
        children[EASEA_Ndx]=NULL;
    }

    virtual ~GPNode() {  // Destructor
      for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
        if( children[EASEA_Ndx] ) delete children[EASEA_Ndx];
    }
};

class GPNodeTerminal : public GPNode {
    bool isTerminal() { return true; }
};

class GPNodeVal : public GPNodeTerminal {
  public:
  float value;

    float getValue(float input[]){ return value; };

    GPNode* clone() {
        GPNodeVal* result = new GPNodeVal();
        result->value = value;
        result->opCode = opCode;

        for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
        if( children[EASEA_Ndx] ) result->children[EASEA_Ndx] = children[EASEA_Ndx]->clone();
        else  result->children[EASEA_Ndx] = NULL;

        return result;
    }
};

class GPNodeVar : public GPNodeTerminal {
  public:
    int index;

    float getValue(float input[]){ return input[index]; };

   GPNode* clone() {
        GPNodeVar* result = new GPNodeVar();
        result->index = index;
        result->opCode = opCode;

        for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
        if( children[EASEA_Ndx] ) result->children[EASEA_Ndx] = children[EASEA_Ndx]->clone();
        else  result->children[EASEA_Ndx] = NULL;

        return result;
    }
};

class GPNodeNonTerminal : public GPNode {
    bool isTerminal() { return false; }
};

class GPNodeOR : public GPNodeNonTerminal {
  public:

    float getValue(float input[]){
        return children[0]->getValue(input) || children[1]->getValue(input);
    };

    GPNode* clone() {
        GPNodeOR* result = new GPNodeOR();
        result->opCode = opCode;

        for(int i = 0; i < 2; i++)
            result->children[i] = children[i]->clone();

        return result;
    }
};

class GPNodeAND : public GPNodeNonTerminal {
  public:

    float getValue(float input[]){
        return children[0]->getValue(input) && children[1]->getValue(input);
    };

    GPNode* clone() {
        GPNodeAND* result = new GPNodeAND();
        result->opCode = opCode;

        for(int i = 0; i < 2; i++)
            result->children[i] = children[i]->clone();

        return result;
    }
};

class GPNodeNOT : public GPNodeNonTerminal {
  public:

    float getValue(float input[]){
        return !(children[0]->getValue(input));
    };

    GPNode* clone() {
        GPNodeNOT* result = new GPNodeNOT();
        result->opCode = opCode;

        result->children[0] = children[0]->clone();

        return result;
    }
};



/* Here are some utility functions for the template GP */
int depthOfTree(GPNode* root);
int enumTreeNodes(GPNode* root);
int depthOfNode(GPNode* root, GPNode* node);

//void flattenDatas( float** inputs, int length, int width, float** flat_inputs);
GPNode* selectNode( GPNode* root, int* childId, int* depth);
GPNode* RAMPED_H_H(unsigned iINIT_TREE_DEPTH_MIN, unsigned iINIT_TREE_DEPTH_MAX, unsigned actualParentPopulationSize, unsigned parentPopulationSize, float iGROW_FULL_RATIO, unsigned iVAR_LEN, unsigned iOPCODE_SIZE, const unsigned* opArity, const int iOP_ERC);
void flattenDatas2D( float** inputs, int length, int width, float** flat_inputs);

GPNode* construction_method( const int constLen, const int totalLen , const int currentDepth, const int maxDepth, const bool full, const unsigned* opArity, const int OP_ERC);

// display methods
void toDotFile(GPNode* root, const char* baseFileName, int treeId, const unsigned* opArity , const char** opCodeName, int OP_ERC);
std::string toString(GPNode* root, const unsigned* opArity , const char** opCodeName, int OP_ERC);

GPNode* init_node(int i);

#endif // __C_GPNODE__
