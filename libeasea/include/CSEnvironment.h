//
// Created by rinku on 10/26/15.
//

#ifndef EASEA_CS_ENVIRONMENT_H
#define EASEA_CS_ENVIRONMENT_H

#include "CSEntity.h"
#include "List.h"
#include <sstream>

template <typename T>
class CSEnvironment {
protected:
    List<T> CSAgentList;

    void doOneStep(float (*recEval)(GPNode*, T& self, T& other), GPNode *computationalTree) {
        for (List<T> curs(this->CSAgentList); !curs.isEmpty(); curs = curs.getNext()) {
            T elt = curs.getFirstElt();

            for (List<T> localAgents = getLocalCSAgents(elt);
                 !localAgents.isEmpty();
                 localAgents = localAgents.getNext())
            {
                T other = localAgents.getFirstElt();
                recEval(computationalTree, elt, other);
            }

            elt.action();
        }
    }


    /**
     * TODO : improve with graph or dichotomy
     */
    List<T> getLocalCSAgents(T& agent) {
        List<T> result;

        for (List<T> curs(this->CSAgentList); !curs.isEmpty(); curs = curs.getNext()) {
            T other = curs.getFirstElt();

            if (&agent != &other && agent.sense(&other))
                result.push_front(other);
        }

        return result;
    }

public:
    CSEnvironment() : CSAgentList(new List<T>()) {}

    CSEnvironment(int nbAgents) {
        for (int i = 0; i < nbAgents; ++i)
            CSAgentList.push_front(T());
    }

    CSEnvironment(const CSEnvironment* other) {
        CSAgentList = List<T>(other->CSAgentList.copy());
    }

    std::string toString() {
        std::ostringstream oss;
        oss << "" << CSAgentList.length() << " agents:\n[\n" << CSAgentList.toString() << "\n]\n";
        return oss.str();
    }

    void compute(int nbStep, float (*recEval)(GPNode*, T& self, T& other), GPNode *computationalTree) {
        for (int i = 0; i < nbStep; ++i)
            doOneStep(recEval, computationalTree);
    }

    float evaluate(float (*eval)(List<T>&)) { return eval(CSAgentList); }

};

template <typename T>
std::ostream & operator<<(std::ostream & ofs, CSEnvironment<T>& e) {
    ofs << e.toString();
    return ofs;
}

#endif //EASEA_CS_ENVIRONMENT_H
