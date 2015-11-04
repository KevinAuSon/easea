//
// Created by rinku on 10/26/15.
//

#ifndef EASEA_CS_ENTITY_H
#define EASEA_CS_ENTITY_H

class CSEntity {
public:
    CSEntity(){}
    CSEntity(const CSEntity& other){}
    virtual ~CSEntity(){}
    virtual bool sense(CSEntity* other) = 0;
    virtual void action() = 0;
    virtual std::string toString() = 0;
};
bool operator!=(const CSEntity& a1, const CSEntity& a2) { return &a1 != &a2; }

#endif //EASEA_CS_ENTITY_H
