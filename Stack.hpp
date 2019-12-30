#pragma once
#define _STACK_HPP_

#include <stdio.h>
#include <stdlib.h>

enum State {
    ERROR, COMPLETE
};

#define MAX_SIZE 100

template<typename T>
struct Stack {
    T dataStorage[MAX_SIZE];
    int topPtr = -1;
};

template<typename T>
int GetTopPtr( Stack<T>* ptr ) {
    return ptr ->topPtr;
}

template<typename T>
bool isFull( Stack<T>* ptr ) {
    bool ret = false;
    if ( MAX_SIZE - 1 == ptr ->topPtr ) ret = true;
    return ret;
}

template<typename T>
bool isEmpty( Stack<T>* ptr ) {
    bool ret = false;
    if ( -1 == ptr ->topPtr ) ret = true;
    return ret;
}

template<typename T>
State PushIntoStack( Stack<T>* ptr, T item ) {
    if ( MAX_SIZE - 1 == ptr ->topPtr ) {
        return State::ERROR;
    }
    else {
        (ptr ->dataStorage)[++ptr ->topPtr] = item;
        return State::COMPLETE;
    }
}

template<typename T>
State PopFromStack( Stack<T>* ptr, T* item ) {
    if ( -1 == ptr ->topPtr ) {
        return State::ERROR;
    }
    else {
        ptr ->topPtr --;
        *item = (ptr ->dataStorage)[ptr ->topPtr + 1];
        return State::COMPLETE;
    }
}

template<typename T>
T DisplayTopItem( Stack<T>* ptr ) {
    return (ptr ->dataStorage)[ptr ->topPtr];
}