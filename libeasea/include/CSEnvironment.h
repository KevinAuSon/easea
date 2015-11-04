//
// Created by rinku on 10/26/15.
//

#ifndef EASEA_CS_ENVIRONMENT_H
#define EASEA_CS_ENVIRONMENT_H

#include "CSEntity.h"
#include "List.h"

template <typename T>
class CSEnvironment {
protected:
    List<T> *CSAgentList;

    void doOneStep(float (*recEval)(GPNode*, T* self, T* other), GPNode *computationalTree) {
        for (List<T>* curs = this->CSAgentList; curs->hasNext(); curs = curs->getNext()) {
            T* elt = curs->getElt();
            List<T>* localAgents = getLocalCSAgents(elt);

            for (List<T>* cursLocalAgents = localAgents;
                 localAgents->hasNext();
                 localAgents = localAgents->getNext())
            {
                recEval(computationalTree, elt, cursLocalAgents->getElt());
            }

            delete localAgents;
            elt->action();
        }
    }


    /**
     * TODO : improve with graph or dichotomy
     */
    List<T>* getLocalCSAgents(T* agent) {
        List<T>* result = new List<T>();

        for (List<T>* curs = this->CSAgentList; curs->hasNext(); curs = curs->getNext()) {
            T* other = curs->getElt();

            if (agent != other && agent->sense(other))
                result = result->push_front(other);
        }

        return result;
    }

public:
    CSEnvironment() : CSAgentList(new List<T>()) {}

    CSEnvironment(int nbAgents) {
        CSAgentList = new List<T>();
        for (int i = 0; i < nbAgents; ++i)
            CSAgentList = CSAgentList->push_front(new T());
    }

    CSEnvironment(const CSEnvironment* other) {
        this->CSAgentList = new List<T>(other->CSAgentList);
    }

    ~CSEnvironment() {
        CSAgentList->destruct();
        delete CSAgentList;
    }

    std::string toString() {
        std::ostringstream oss;
        oss << CSAgentList->length() << " agents:\n[\n" << CSAgentList->toString() << "\n]\n";
        return oss.str();
    }

    void compute(int nbStep, float (*recEval)(GPNode*, T* self, T* other), GPNode *computationalTree) {
        for (int i = 0; i < nbStep; ++i)
            doOneStep(recEval, computationalTree);
    }

    float evaluate(float (*eval)(List<T>*)) { return eval(CSAgentList); }

};

template <typename T>
std::ostream & operator<<(std::ostream & ofs, CSEnvironment<T>& e) {
    ofs << e.toString();
    return ofs;
}

#endif //EASEA_CS_ENVIRONMENT_H
