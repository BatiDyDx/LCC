#ifndef _GSTACK_H_
    #define _GSTACK_H_

    #include "../utils.h"
    #include "../practica2/glist.h"

    typedef GList GStack;

    /*
     ** Creates and initializes a new stack
    */
    GStack gstack_init(); 
    
    /*
     ** Frees the required memory for the stack
    */
    void gstack_free(GStack s, DestroyFunction destroy);
    
    /*
     ** Returns 1 if the stack is empty, 0 otherwise
    */
    int gstack_empty(GStack s); 

    /*
     ** Returns the element on the top of the stack, without removing it
    */
    void* gstack_top(GStack s, CopyFunction copy);

    /*
     ** Inserts an element on the top of the stack, if the stack is full,
     ** resizes the array to the double of its size
    */
    GStack gstack_push(GStack s, void* data, CopyFunction copy);
    
    /*
     ** Removes the element on the top of the stack
    */
    GStack gstack_pop(GStack s, DestroyFunction destroy);

    /*
     ** Prints in order the elements of the stack
    */
    void gstack_print(GStack s, VisitFunction visitor);

    /*
     ** Reverse a GList using a GStack
    */
    GList glist_reverse(GList list, CopyFunction copy);

#endif // _GSTACK_H_