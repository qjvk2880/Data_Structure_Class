#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "memory.h"

void print_name(struct record *);
void print_number(struct record *);
void print_data(char *, int);

// data
struct record * data = NULL; // Initially NULL.


void init()
{
  init_pool();
}


void add(char *name, char *number)
{
    int numberOfNodes = 0;
    struct record *r = data;
    while (r != NULL)
    {
        r = r->next;
        numberOfNodes++;
    }

    if (numberOfNodes >= 10)
    {
        printf("Can't add.  The address book is full!\n");
    }
    else
    {
        struct record *newNode = new_node();
        strcpy(newNode->name, name);
        strcpy(newNode->number, number);
        if (data == NULL)
        {
            data = newNode;
            data->next = NULL;
        } else {
            newNode->next = data;
            data = newNode;
        }
    }
  // Error Message for overflow:
}


/* Just a wrapper of strncmp(), except for the case r is NULL.
Regard strncmp(a,b) as a-b, that is,
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
  if (r==NULL)
    return -1;
  else
    return strncmp(key, r->name, 3);
}


void search(char name[3])
{
  struct record *r=data;
  int result;

  while(r!=NULL && (result=compare(name,r))!=0)
    r=r->next;
  if(r==NULL)
    printf("Couldn't find the name.\n");
  else {
    print_name(r);
    printf(" : ");
    print_number(r);
    printf(" was found.\n");
  }
}


void delete(char name[3])
{
    struct record *r=data;
    int result;
    if(compare(name,data) == 0){
        data = data->next;
        free_node(r);
        printf("The name was deleted.\n");
    }
    else
    {
        while (r != NULL && (result = compare(name, r->next)) != 0)
            r = r->next;

        if (r == NULL)
            printf("Couldn't find the name.\n");
        else
        {
            struct record *t = r->next;
            r->next = t->next;
            free_node(t);
            printf("The name was deleted.\n");
        }
    }
  // Error Message:
  // printf("Couldn't find the name.\n");
}


// Prints ith name.
void print_name(struct record *r)
{
  print_data(r->name, 3);
}

// Prints ith number.
void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_list()
{
    struct record * r = data;
    while (r != NULL)
    {
        print_name(r);
        printf(" : ");
        print_number(r);
        printf("\n");
        r = r->next;
    }
//   printf("print_list() was not implemented.\n");
}
