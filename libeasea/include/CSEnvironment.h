//
// Created by rinku on 10/26/15.
//

#ifndef EASEA_CSENVIRONMENT_H
#define EASEA_CSENVIRONMENT_H

#include "CSAgent.h"
#include "List.h"

template <typename T>
class CSEnvironment {
protected:
    List<T> *CSAgentList;
    GPNode *computationalTree;

public:
    CSEnvironment(int nbAgents) : computationalTree(NULL){
        CSAgentList = new List<T>();
        for (int i = 0; i < nbAgents; ++i)
            CSAgentList = CSAgentList->push_front(T());

        std::cout << nbAgents << " agents are in the system: "
                  << std::endl <<toString();
    }

    CSEnvironment(const CSEnvironment &other) : computationalTree(NULL){
        this->CSAgentList = new List<T>(other.CSAgentList);
    }

    ~CSEnvironment() {
        delete CSAgentList;
        delete computationalTree;
    }

    /**
     * TODO : improve with graph or dichotomy
     */
    List<T>* getLocalCSAgents(T agent) {
        List<T>* result = new List<T>();

        for (List<T>* curs = this->CSAgentList; curs->hasNext(); curs = curs->getNext()) {
            T other = curs->getElt();

            if (agent != other && agent.sense(other))
                result = result->push_front(other);
        }

        return result;
    }

    std::string toString() { return CSAgentList->toString(); }

    void doOneStep() {
        for (List<T>* curs = this->CSAgentList; curs->hasNext(); curs = curs->getNext()) {
            List<T>* localAgents = getLocalCSAgents(curs->getElt());

            for (List<T>* cursLocalAgents = localAgents;
                 localAgents->hasNext();
                 localAgents = localAgents->getNext())
            {
                compute(curs->getElt(), cursLocalAgents->getElt());
            }

            delete localAgents;
        }
    }

    void compute(T self, T other) {
        ;
    }
};

template <typename T>
std::ostream & operator<<(std::ostream & ofs, CSEnvironment<T>& e) {
    ofs << e.toString();
    return ofs;
}

#endif //EASEA_CSENVIRONMENT_H
