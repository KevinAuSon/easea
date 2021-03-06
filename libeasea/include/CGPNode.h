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
  public:
    int opCode;


    virtual bool isTerminal() = 0;
    virtual float getValue(float input[]) = 0;
    virtual GPNode* clone() = 0;
    virtual float reduce(float (*reduceFunction)(GPNode*, float), float result) = 0;
    virtual GPNode* getChild(int i) { return NULL; }
    virtual GPNode* setChild(int i, GPNode* node) { return this; }

    virtual ~GPNode() {;}
};

class GPNodeTerminal : public GPNode {
    public:
        bool isTerminal() { return true; }
        float reduce(float (*reduceFunction)(GPNode*, float), float result) {
            return reduceFunction(this, result);
        }
};

class GPNodeVal : public GPNodeTerminal {
  public:
  float value;

    float getValue(float input[]){ return value; };

    GPNode* clone() {
        GPNodeVal* result = new GPNodeVal();
        result->value = value;
        result->opCode = opCode;

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

        return result;
    }
};

class GPNodeNonTerminal : public GPNode {
    protected:
        GPNode* children[MAX_ARITY];
        int size;

    public:

        GPNodeNonTerminal() : size(0) {  // Constructor
          for(int EASEA_Ndx=0; EASEA_Ndx<MAX_ARITY; EASEA_Ndx++)
            children[EASEA_Ndx]=NULL;
        }

        virtual ~GPNodeNonTerminal() {  // Destructor
          for(int EASEA_Ndx=0; EASEA_Ndx<MAX_ARITY; EASEA_Ndx++)
            if( children[EASEA_Ndx] ) delete children[EASEA_Ndx];
        }

        bool isTerminal() { return false; }

        GPNode* getChild(int i) { return children[i]; }

        GPNode* setChild(int i, GPNode* node) {
            if(i >= size) size = i+1;
            children[i] = node;
            return this;
        }

        float reduce(float (*reduceFunction)(GPNode*, float), float result) {
            result = reduceFunction(this, result);

            for(int i = 0; i < size; i++)
                result = ((GPNodeNonTerminal*)children[i])->reduce(reduceFunction, result);

            return result;
        }

        void cloneHelp(GPNodeNonTerminal* result) {
            result->opCode = opCode;
            result->size = size;

            for(int i = 0; i < size; i++)
                result->children[i] = children[i]->clone();
        }
};

class GPNodeOR : public GPNodeNonTerminal {
  public:

    float getValue(float input[]){
        return children[0]->getValue(input) || children[1]->getValue(input);
    };

    GPNode* clone() {
        GPNodeOR* result = new GPNodeOR();
        cloneHelp(result);
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
        cloneHelp(result);
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
        cloneHelp(result);
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
