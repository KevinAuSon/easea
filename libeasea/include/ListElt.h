//
// Created by rinku on 11/4/15.
//

#ifndef EASEA_LISTELT_H
#define EASEA_LISTELT_H

#include <stdlib.h>
#include <iostream>
#include <string>

template <typename T>
class ListElt {
private:
    T elt;
    ListElt *next;

public:
    ListElt(T _elt) : elt(_elt), next(NULL) {}
    ListElt(T _elt, ListElt *_next) : elt(_elt), next(_next) {}
    ListElt(ListElt *toCopy) : next(NULL) {
        elt = T(toCopy->getElt());

        if(toCopy->hasNext())
            next = new ListElt(toCopy->getNext());
    }

    ~ListElt() { if(hasNext()) delete next; }

    T getElt() { return elt; }
    void setElt(T _elt) { elt = _elt; }

    ListElt* getNext() { return next; }
    void setNext(ListElt *_next) { next = _next; }

    bool hasNext() const { return next != NULL; }

    std::string toString() const {
        std::string result("");

        result.append(this->elt->toString());

        if(hasNext())
            result.append(next->toString());

        return result;
    }
};
#endif //EASEA_LISTELT_H
