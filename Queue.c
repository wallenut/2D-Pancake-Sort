// An implementation of the Queue ADT.

#include "Queue.h"
#include <stdlib.h>

// The internal representation of a Queue is a headless, singly-linked,
// circular list.  The Queue data type is a pointer to the LAST node in
// the list (or NULL if the queue is empty).

typedef struct node {
	char* data;
	struct node* next;
} Node;


int createQ (Queue *q){
		Node *temp = NULL;
		*q = temp;
		return true;
}

int isEmptyQ (Queue *q)
{
	if (*q == NULL)
	{
		return true;
	}
	else return false;
}


int addQ (Queue *q, char *s){
	struct node *newnode;
    newnode = malloc(sizeof(struct node));
    if (newnode == NULL) return false;

    if (isEmptyQ(q)) 
    {
    	newnode->next = newnode;
    	newnode->data = s;
    	*q = newnode;
    }
    else
    {
    	newnode->next = (*q)->next;
    	(*q)->next = newnode;
    	newnode->data = s;
    	(*q) = newnode;

    }
    return true;
}
									    

int headQ (Queue *q, char **s)
{
    if (isEmptyQ(q)){
    	return false;
    }
    else
    {
    	*s = (*q)->next->data;
    }
    return true;
}


int removeQ (Queue *q, char **s)
{
    if (isEmptyQ(q)){
    	return false;
    }
    else
    {
    	*s = (*q)->next->data;
    	Node *copy = (*q)->next;
    	if ((*q)->next != ((*q)->next)->next)
    	{
    		(*q)->next = ((*q)->next)->next;
    		free (copy);
    		return true;
    	}
    	else
    	{
    		free (copy);
    		*q = NULL;
    		return true;
    	}
    }
}


									    
									    
int destroyQ (Queue *q)
{
	Node *temp;
	while (*q != NULL)
	{
		temp = (*q)->next;
	    if ((*q)->next != ((*q)->next)->next)
	    {
	    	(*q)->next = ((*q)->next)->next;
	    	free (temp);
	    }
    	else
    	{
    		free (temp);
    		*q = NULL;
    	}
    }
    return true;
}
