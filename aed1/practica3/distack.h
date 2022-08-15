#ifndef _DISTACK_H_

    #define _DISTACK_H_
    #include "../practica1/int_array.h"

    struct _DIStack {
        IntArray *arr;
        int last;
    };

    // Dynamic Integer Stack
    typedef _DIStack *DIStack;

    /*
     ** Creates and initializes a new stack with the size given
    */
    DIStack distack_init(size_t size); 
    
    /*
     ** Frees the required memory for the stack
    */
    void distack_free(DIStack s);
    
    /*
     ** Returns 1 if the stack is empty, 0 otherwise
    */
    int distack_empty(DIStack s); 

    /*
     ** Returns the element on the top of the stack, without removing it
    */
    int distack_top(DIStack s);

    /*
     ** Inserts an element on the top of the stack, if the stack is full,
     ** resizes the array to the double of its size
    */
    void distack_push(DIStack s, int data);
    
    /*
     ** Removes the element on the top of the stack
    */
    void distack_pop(DIStack s);

    /*
     ** Prints in order the elements of the stack
    */
    void distack_print(DIStack s);

#endif // _DISTACK_H_