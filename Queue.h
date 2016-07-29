//Queue.h                                     Stan Eisenstat (2016/02/24)
//
// Define the abstract data type for a Queue.

#include <stdbool.h>

// A Queue is a pointer to a struct that is used to implement the queue
// operations declared below.  By defining its data type incompletely (i.e.,
// by not defining the fields of the struct node below), that pointer can be
// stored within the calling program without knowing what the exact type of
// the object is.

typedef struct node *Queue;

// The following functions are the only means to access the Queue data
// structure.  They all require a pointer to a Queue variable since they may
// need to modify that variable in the course of accessing the data structure.
// Most return the status of the operation, either TRUE or FALSE (e.g., invalid
// arguments, an inconsistent Queue object, or a NULL return from malloc() /
// realloc()).

// Set *Q to a new object of type Queue.  Return status.
int createQ (Queue *q);

// Add the string pointer S to the tail of Queue *Q; the string itself is not
// copied.  *Q may change as a result.  Return status.
int addQ (Queue *q, char *s);

// Return TRUE if the Queue *Q is empty, FALSE otherwise.  *Q may change as a
// result.
int isEmptyQ (Queue *q);

// Copy the string pointer at the head of Queue *Q to *S, but do not remove it
// from *Q.  *Q may change as a result.  Return status.  (If *Q is empty, then
// returns FALSE and leaves *S unchanged.)
int headQ (Queue *q, char **s);

// Remove the string pointer at the head of the Queue *Q and store that value
// in *S.  *Q may change as a result.  Return status.  (If *Q is empty, then
// returns FALSE and leaves *S unchanged.)
int removeQ (Queue *q, char **s);

// Destroy the Queue *Q by freeing any storage it uses (but not that to which
// the string pointers point).  Set *Q to NULL.  Return status.
int destroyQ (Queue *q);


