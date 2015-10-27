//
// Created by rinku on 10/26/15.
//

#ifndef EASEA_CSAGENT_H
#define EASEA_CSAGENT_H

class CSAgent {
public:
    CSAgent(){}
    CSAgent(const CSAgent& other){}
    virtual ~CSAgent(){}
    virtual bool sense(CSAgent& other) = 0;
    virtual std::string toString() = 0;
};
bool operator!=(const CSAgent& a1, const CSAgent& a2) { return &a1 != &a2; }

#endif //EASEA_CSAGENT_H
