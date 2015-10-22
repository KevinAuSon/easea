/**
 * @file CGP2Node.h
 * @version 1.0
 *
 **/  

#ifndef __C_GP2Node__
#define __C_GP2Node__

#include <iostream>

using namespace std;

#define MAX_ARITY 2          // maximum arrity for GP node

/**
 *  \class   GP2Node 
 *  \brief   Genetic Programming 
 *  \details Used to modelised nodes of abstract syntax tree
 *  
 **/ 

class GP2Node {
  public:


    GP2Node(){  // Constructor
      for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
        children[EASEA_Ndx]=NULL;
    }


    GP2Node(int var_id, double erc_value, char opCode, GP2Node** childrenToAdd) : var_id(var_id), erc_value(erc_value), opCode(opCode)// other constructor
  {
    for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
      this->children[EASEA_Ndx]=childrenToAdd[EASEA_Ndx];
  }  


    GP2Node(const GP2Node &EASEA_Var) {  // Copy constructor
      var_id=EASEA_Var.var_id;
      erc_value=EASEA_Var.erc_value;
      //arity=EASEA_Var.arity;
      opCode=EASEA_Var.opCode;
      
      for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
        if( EASEA_Var.children[EASEA_Ndx] ) children[EASEA_Ndx] = new GP2Node(*(EASEA_Var.children[EASEA_Ndx]));
        else  children[EASEA_Ndx] = NULL;
    }


    virtual ~GP2Node() {  // Destructor
      for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
        if( children[EASEA_Ndx] ) delete children[EASEA_Ndx];
    }


    GP2Node& operator=(const GP2Node &EASEA_Var) {  // Operator=
      if (&EASEA_Var == this) return *this;
      var_id = EASEA_Var.var_id;
      erc_value = EASEA_Var.erc_value;
      //arity = EASEA_Var.arity;
      opCode = EASEA_Var.opCode;
      
      for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
        if(EASEA_Var.children[EASEA_Ndx]) children[EASEA_Ndx] = new GP2Node(*(EASEA_Var.children[EASEA_Ndx]));
      
      return *this;
    }


    bool operator==(GP2Node &EASEA_Var) const {  // Operator==
      if (var_id!=EASEA_Var.var_id) return false;
      if (erc_value!=EASEA_Var.erc_value) return false;
      //if (arity!=EASEA_Var.arity) return false;
      if (opCode!=EASEA_Var.opCode) return false;
      
      {for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
        if (children[EASEA_Ndx]!=EASEA_Var.children[EASEA_Ndx]) return false;}

      return true;
    }


    bool operator!=(GP2Node &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=


    friend ostream& operator<< (ostream& os, const GP2Node& EASEA_Var) { // Output stream insertion operator
      os <<  "var_id:" << EASEA_Var.var_id << "\n";
      os <<  "erc_value:" << EASEA_Var.erc_value << "\n";
      //os <<  "arity:" << EASEA_Var.arity << "\n";
      os <<  "opCode:" << EASEA_Var.opCode << "\n";
      
      {os << "Array children : ";
        for(int EASEA_Ndx=0; EASEA_Ndx<2; EASEA_Ndx++)
          if( EASEA_Var.children[EASEA_Ndx] ) os << "[" << EASEA_Ndx << "]:" << *(EASEA_Var.children[EASEA_Ndx]) << "\t";}
      
      os << "\n";

      return os;
    }


    // Class members 
    int var_id;
    double erc_value;
    // char opCode;
    int opCode;
    GP2Node* children[2];
};

/* Here are some utility functions for the template GP */

/*int depthOfTree(GP2Node* root);
int enumTreeNodes(GP2Node* root);
int depthOfNode(GP2Node* root, GP2Node* node);

//void flattenDatas( float** inputs, int length, int width, float** flat_inputs);
GP2Node* selectNode( GP2Node* root, int* childId, int* depth);
GP2Node* RAMPED_H_H(unsigned iINIT_TREE_DEPTH_MIN, unsigned iINIT_TREE_DEPTH_MAX, unsigned actualParentPopulationSize, unsigned parentPopulationSize, float iGROW_FULL_RATIO, unsigned iVAR_LEN, unsigned iOPCODE_SIZE, const unsigned* opArity, const int iOP_ERC);
void flattenDatas2D( float** inputs, int length, int width, float** flat_inputs);

GP2Node* construction_method( const int constLen, const int totalLen , const int currentDepth, const int maxDepth, const bool full, const unsigned* opArity, const int OP_ERC);

// display methods
void toDotFile(GP2Node* root, const char* baseFileName, int treeId, const unsigned* opArity , const char** opCodeName, int OP_ERC);
std::string toString(GP2Node* root, const unsigned* opArity , const char** opCodeName, int OP_ERC);*/

#endif // __C_GP2Node__
