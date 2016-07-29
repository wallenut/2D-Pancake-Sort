//hash.h                                     Stan Eisenstat (2016/02/24)
//
// Define the abstract data type for a Queue.

#include <stdbool.h>
// A Queue is a pointer to a struct that is used to implement the queue
// operations declared below.  By defining its data type incompletely (i.e.,
// by not defining the fields of the struct node below), that pointer can be
// stored within the calling program without knowing what the exact type of
// the object is.

typedef struct node** hashtable;


// The following functions are the only means to access the Queue data
// structure.  They all require a pointer to a Queue variable since they may
// need to modify that variable in the course of accessing the data structure.
// Most return the status of the operation, either TRUE or FALSE (e.g., invalid
// arguments, an inconsistent Queue object, or a NULL return from malloc() /
// realloc()).

// Set table to be new object of type hashtable.
int createTable (hashtable* table);

void destroyTable(hashtable table);
// Hash the key in the node and insert it into the corresponding value of the hashtable
// accounting for collisions
int insertTable (hashtable table, char* conf, char* from, int l, int goal);


// Return TRUE if the Queue *Q is empty, FALSE otherwise.  *Q may change as a
// result.
struct node* searchTable (hashtable table, char* needle);

bool inTable (hashtable table, char* needle, int* l);

void printTable(hashtable table, char* initial);
