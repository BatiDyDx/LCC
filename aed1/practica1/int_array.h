#ifndef _INT_ARRAY_H_
    #define _INT_ARRAY_H_
    #include <stdlib.h>

    typedef struct {
        int* dir;
        int size;
    } IntArray;

    /*
     ** Create a dynamic array with the given size
    */
    IntArray* create(size_t size);

    /*
     ** Destroy a dynamic array
    */
    void destroy(IntArray* arr);

    /*
     ** Returns the data from the array in the given position
    */
    int read(IntArray* arr, unsigned pos);

    /*
     ** Writes data to the given position in the array
    */
    void write(IntArray* arr, unsigned pos, int data);

    /*
     ** Prints the array
    */
    void print(IntArray* arr);

    /*
     ** Resizes the array to the given size
    */
    void resize(IntArray* arr, size_t nsize);

    /*
     ** Inserts a number in the given position moving all data to
     ** the right, resizing it if necessary
    */
    void insert(IntArray* arr, unsigned pos, int data);

    /*
     ** Deletes the position from the array, moving data to the left
    */
    void delete(IntArray* arr, unsigned pos);

#endif // _INT_ARRAY_H_