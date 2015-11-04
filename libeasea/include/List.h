//
// Created by rinku on 10/26/15.
//

#ifndef EASEA_LIST_H
#define EASEA_LIST_H
#include "ListElt.h"

template <typename T>
class List {
protected:
    ListElt<T> *first;
    int size;

public:
    List() : first(NULL), size(0) {}
    List(ListElt<T>* newElt) : first(newElt), size(1) {}

    List(const List<T>* l) : first(NULL), size(0) {
        if(l) {
            size = l->length();

            if(!isEmpty())
                first = new ListElt<T>(l->first);
        }
    }

    ~List() { if(!isEmpty()) delete first; }

    int length()   const { return size; }
    bool isEmpty() const { return length() == 0; }

    T getElt(int index) {
        ListElt<T> *curs = first;

        if(length() < index)
            throw std::string("Try to get the next element of an empty list");

        for(int i = 0; i < index ; i++)
            curs = curs->getNext();

        return curs->getElt();
    }

    T getFirst() { return getElt(0); }

    void push_front(T elt) {
        ListElt<T> *head = new ListElt<T>(elt, first);
        first = head;
    }

    std::string toString() const { if(!isEmpty()) return first->toString(); }
};

/**
 * TODO improve make it recursive
 */
template <typename T>
bool operator!=(List<T>& l1, List<T>& l2) {
    bool result = false;

    if(l1.isEmpty() != l2.isEmpty())
        result = true;
    else if(!l1.isEmpty() && !l2.isEmpty() &&
            l1.getFirst() != l2.getFirst())
        result = true;

    return result;
}

#endif //EASEA_LIST_H
