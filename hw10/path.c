#include <stdio.h>
#include "backend.h"

/****************************************
Implement Breadth-First Search on the graph constructed in "backend.c" and
use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via
"backend.h"
*****************************************/

/****** implementation of queue *****/
int q[N];
int f = -1, r = 0;

void initQueue(){
    f = -1;
    r = 0;
}

void push(x){
    if (r >= N)
        printf("overflow\n");
    else {
        q[r] = x;
        r = r + 1;
    }
}

int pop(){
    if (r - f <= 1)
        printf("underflow\n");
    else {
        f = f + 1;
        return q[f];
    }
}
/***************************************/
char state[N];
int parent[N];

void initState() {
    int i;
    for (i = 0; i < N;i++){
        state[i] = 0;
    }
}

int bfs_shortest_path(int start, int goal) {
    initState();
    initQueue();

    push(start);
    parent[start] = -1;

    while (r - f - 1 > 0) // queue is not empty
    {
        int current = pop();
        struct node *current_list = adj_list[current];
        struct node *r = current_list;
        while (r != NULL)
        {
            if (state[r->index] == 0){
                state[r->index] = 1;
                push(r->index);
                parent[r->index] = current;
                
                if (r->index == goal) {
                    return 1;
                }
            }
            r = r->next;
        }
        state[current] = 1;
    }
    return 0;
}

void print_path(int start, int goal) {
    int p[N];

    int v = goal, i = 0;

    while (v != start){
        p[i++] = v;
        v = parent[v];
    }

    p[i] = start;
    int k = 0;
    while (i >= 0)
    {
        printf("          %d ", k++);
        print_word(p[i--]);
        printf("\n");
    }

}

void find_path(char start[5], char goal[5])
{
  int i,j,k,l;
  
  i=search_index(start);
  j=search_index(goal);

  if (i<0) {
    printf("Sorry. ");
    print_five_chars(start);
    printf(" is not in the dicitonary.");
  }
  else if (j<0) {
    printf("Sorry. ");
    print_five_chars(goal);
    printf(" is not in the dicitonary.");
  }
  else {
      int s = search_index(start);
      int t = search_index(goal);
      if(bfs_shortest_path(s, t)){
        print_path(s, t);
      } else {
        //   printf("Sorry. There is no path from %s to %s.\n", start, goal);
        printf("Sorry. There is no path from ");
        print_word(s);
        printf(" to ");
        print_word(t);
        printf(".\n");
      }
  }
}
  
