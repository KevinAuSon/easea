//
// Created by rinku on 10/26/15.
//

#ifndef EASEA_LIST_H
#define EASEA_LIST_H
#include <stdlib.h>
#include <iostream>
#include <string>

template <typename T>
class List {
protected:
    bool _isEmpty;
    T elt;
    List* next;

public:
    List() : _isEmpty(true), next(NULL) {}
    List(T& newElt) : _isEmpty(false), elt(newElt), next(NULL) {}

    List(const List<T>* l) : _isEmpty(true), next(NULL) {
        if(l->hasNext()) {
            List* newElt = new List(l->next);
            this->next = newElt;
        }

        if(!l->isEmpty()) {
            T newElt = T(l->elt);
            this->elt = newElt;
        }
    }

    ~List() { delete next; }

    bool hasNext() const { return next != NULL && next != this; }
    bool isEmpty() const { return _isEmpty; }

    List* getNext() const {
        if(this->hasNext())
            return this->next;
        else
            throw std::string("Try to get the next element of an empty list");
    }

    T getElt() const {
        if(!this->isEmpty())
            return this->elt;
        else
            throw std::string("Try to get an element in an empty list");
    }

    List* push_front(T elt) {
        List<T>* head = new List<T>(elt);
        head->next = this;

        return head;
    }

    int length() {
        int result = isEmpty() ? 0 : 1;

        if(hasNext()) result += next->length();

        return result;
    }

    std::string toString() {
        std::string result("");

        if(!isEmpty())
            result.append(this->elt.toString());

        if(hasNext()) {
            if(!isEmpty()) result.append("\n");
            result.append(next->toString());
        }

        return result;
    }
};

template <typename T>
bool operator!=(List<T>& l1, List<T>& l2) {
    bool result = false;

    if(l1.isEmpty() != l2.isEmpty())
        result = true;
    else if(!l1.isEmpty() && !l2.isEmpty() &&
            l1.getElt() != l2.getElt())
        result = true;

    return result;
}

#endif //EASEA_LIST_H
