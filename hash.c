// An implementation of hash table

#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// functions are create hash table, 

typedef struct node{
    char* conf;
    char* from;
    int l;
    int goal;
    struct node* next;
} Node;

 long hash (char *s)
        {
            unsigned long sum;
            int shift;
            const unsigned long prime = 3141592653589793239L;

            for (sum = 0, shift = 0; *s; s++) {
                sum ^= *s<<shift;
                shift += 7;
                if (shift >= 57)
                    shift -= 57;
            }

            return ((prime * sum) % 100003);
        }

int Ltable (hashtable table, char* needle)
{
    Node* temp;
    temp = searchTable(table, needle);
    return temp->l;
}


// Set table to be new object of type hashtable.
int createTable (hashtable* table)
{
    *table = calloc(100003, sizeof(Node*));
    return 1;

}
void destroyTable(hashtable table)
{
    for (int i = 0; i < 100003; i++)
    {
        Node* temp = table[i];
        while (temp != NULL)
        {
            Node* die;
            die = temp;
            temp = temp->next;
            free(die);
        }
    }
    free(table);
}

// Hash the key in the node and insert it into the corresponding value of the hashtable
// accounting for collisions
int insertTable (hashtable table, char* conf, char* from, int l, int goal)
{
    Node* temp; // the pointer to a node
    temp = malloc(sizeof(Node));    

    temp->conf = conf;
    temp->from = from;
    temp->l = l;
    temp->goal = goal;
    int hashindex = hash(conf);
    if (table[hashindex] == NULL) // empty entry, add this node
    {
        table[hashindex] = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = table[hashindex];
        table[hashindex] = temp;
    }
    return 1;
}

// Return TRUE if the Queue *Q is empty, FALSE otherwise.  *Q may change as a
// result.
Node* searchTable (hashtable table, char* needle)
{
    Node* temp;
    if (!needle)
    {
        return NULL;
    }
    //printf("its bout to mess up\n");
    int hashindex = hash(needle);
    //printf("did it survive\n");
    //printf("temp->conf is %s\n", temp->conf );
    temp = table[hashindex];
    if (temp == NULL) 
    {
        return NULL;
    }
    else
    {
        while (temp != NULL)
        {
            if (strcmp(temp->conf, needle) == 0)
            {
                
                return  temp;
            }
            temp = temp->next;

        }
    }
    return 0;
}

bool inTable (hashtable table, char* needle, int* l)
{
    Node* temp;
    if (!needle)
    {
        return 0;
    }
    temp = searchTable(table, needle);
    if (temp == NULL) 
    {
        //printf("not in table\n");
        return 0;
    }
    else
    {
        while (temp != NULL)
        {
            if (strcmp(temp->conf, needle) == 0)
            {
                *l = temp->l;
                //printf("in table\n");
                return  1;
            }
            temp = temp->next;

        }
    }
    //printf("not in table\n");
    return 0;
}
void printTable(hashtable table, char* initial)
{
    char* from = initial;
    Node* temp;
    temp = searchTable(table, from);
    printf("%s\n", temp->conf);
    from = temp->from;
    while (from != NULL)
    { 
        temp = searchTable(table, from);
        printf("%s\n", temp->conf);
        from = temp->from;
    }
}


