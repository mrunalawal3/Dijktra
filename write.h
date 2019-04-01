
#include <stdio.h>
#include <limits.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

int count=0;

# define V count
typedef struct vertex
{
    int no;
    char name[25];
    struct vertex *nv;
    struct edge *ne;
}vertex;

struct vertex *head=NULL;

typedef struct edge
{
	struct vertex *vptr;
	int weight;
	char nm[25];
	int no;
	struct edge *eptr;
}edge;

vertex *createVertex(char *city)
{
    vertex *a=(vertex *)malloc(sizeof(vertex));
    strcpy(a->name,city);
    a->ne=NULL;
    a->nv=NULL;
    a->no=count;
    count++;
    return a;
}

edge *createEdge(char *adjnm,int wt)
{
    int d;
    edge *a=(edge *)malloc(sizeof(edge));
     strcpy(a->nm,adjnm);
      a->weight=wt;
    a->eptr=NULL;
     a->vptr=NULL;
    vertex *p=head,*q;
    while(p!=NULL)
    {
        if(strcmp(p->name,adjnm)==0)
           {
            a->vptr=p;
            a->no=p->no;
           }
        p=p->nv;
    }
    return a;
}

void insertVertex(char *city)
{
    vertex *b=head,*c;
    vertex *a=createVertex(city);
    if(head==NULL)
       {
           head=a;
           return;
       }
    while(b!=NULL)
    {
        c=b;
        b=b->nv;
    }
   c->nv=a;
}

edge* insertEdge(edge *t,char *adjnm,int wt)
{
      edge *c;
    edge *a=createEdge(adjnm,wt);
    if(t==NULL)
      {
         return a;
      }
    else
        {
            while(t!=NULL)
            {
                c=t;
                t=t->eptr;
            }
            c->eptr=a;
        }
}

void updateEdges(vertex *q,char *adjnm,int wt)
{
   if(q->ne==NULL)
            {
                q->ne=insertEdge(q->ne,adjnm,wt);
               return;
            }
    else
          insertEdge(q->ne,adjnm,wt);
}
