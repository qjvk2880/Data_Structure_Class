#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-bst.h"
#include "memory.h"

void print_name(struct record *);
void print_number(struct record *);

// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.

/***********************
Address Book by binary search tree
**************************/

void init()
{
  init_pool();
}


void search(char name[3])  
{
  struct record *r; // Pointer to record being compared.
                    //data or left/right field of a node.
  int result;
  r=data;

  while (r!=NULL) {
    if ((result=compare(name,r))<0)
      r=r->left;
    else if (result==0) {
      print_name(r);
      printf(" : ");
      print_number(r);
      printf(" was found.\n");
      return;
    }
    else // case >0
      r=r->right;
  }
  printf("Couldn't find the name.\n");
}


void add(char *name, char *number)
{

    struct record *p = data;
    struct record *q,*r;
    while(p!=NULL){
        if(compare(name,p) <= 0){
            q = p;
            p = p->left;
          } else{
            q = p;
            p = p->right;
          }
    }
    r = new_node();
    if(r == NULL){
      printf("Can't add.  The pool is empty!\n");
      return;
    }
    strcpy(r->name, name);
    strcpy(r->number, number);
    r->left = NULL;
    r->right = NULL;
    if(data==NULL){
      data = r;
    } else if (compare(name,q)<=0) {
      q->left = r;
    } else {
      q->right = r;
    }
      printf("The name was successfully added!\n");
}


// The most complicated.
void delete(char name[3])
{
    struct record *p = data;
    struct record *q = NULL;
    while(p!=NULL){
        if(compare(name,p) < 0){
            q = p;
            p = p->left;
        } else if(compare(name,p) == 0){
            break;
        }
        else{
            q = p;
            p = p->right;
        }
    }
    if(p==NULL){
        printf("Couldn't find the name.\n");
        return;
    }
    if ((p->left == NULL) && (p->right == NULL)){
        if(p == data){
            data = NULL;
        } else {
            if (q->left == p){
                q->left = NULL;
            } else if (q-> right == p){
                q->right = NULL;
            }
        }
        free_node(p);
    }
    else if ((p->left != NULL) && (p->right != NULL))
    {
        struct record *r = p->right;
        struct record *s = p->right;
        while (r->left != NULL){
            s = r;
            r = r->left;
        }

        strcpy(p->name, r->name);
        strcpy(p->number, r->number);

        if (r == s){
            p->right = r->right;

        }
        else {
            s->left = r->right;
        }
        free_node(r);
    }
    else
    {
        struct record *r;
        if(p->left != NULL){
            r = p->left;
        } else {
            r = p->right;
        }

        if (p == data){
            data = r;
        } else {
            if (q->left == p){
                q->left = r;
            } else {
                q->right = r;
            }
        }
        free_node(p);
    }
        printf("The name was deleted.\n");
    //  printf("The name was deleted.\n");
    //  printf("Couldn't find the name.\n");
}


/* Just a wrapper of strncmp().
Regard strncmp(a,b) as a-b.
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    return strncmp(key, r->name, 3);
}


void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_name(struct record *r)
{
  print_data(r->name, 3);
}

void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_inorder(struct record *t)
{
    if(t!=NULL){
        print_inorder(t->left);
        print_name(t);
        printf(" : ");
        print_number(t);
        printf("\n");
        // print_name(t);
        // printf(" itself : %p\n",t);
        // print_name(t);
        // printf(" left : %p\n",t->left);
        // print_name(t);
        // printf(" right : %p\n",t->right);
        print_inorder(t->right);
    }
}

void print_list()  
{
  print_inorder(data);
}


// returns the height of the BST.
int height(struct record *t)
{
  if(t==NULL){
    return -1;
  } else {
    int l = height(t->left);
    int r = height(t->right);
    if(l<=r) {
      return r + 1;
    } else {
      return l + 1;
    }
  }
}

void print_height()  
{
  printf("The Address Book BST's height is %d.\n", height(data));
}
