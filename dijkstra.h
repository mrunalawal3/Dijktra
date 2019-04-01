
#include <stdio.h>
#include <limits.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

int count;

# define INT_MAX 999 //INT_MAX is estimated as infinity

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
    vertex* p=head;
    while(p!=NULL)
    {
        if(p==q)
        {
               if(p->ne==NULL)
                {
                    p->ne=insertEdge(p->ne,adjnm,wt);
                    break;
                }
              else
               insertEdge(p->ne,adjnm,wt);
        }
       p=p->nv;
    }
}

// function to find the vertex with minimum distance from the set of vertices not yet included in shortest path
int minDistance(int dist[], bool sptSet[])
{
    int v;
    int min = INT_MAX, min_index;
    for ( v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra( int src,int dest)
{
    int dist[V];    //dist[i] will hold the shortest distance from src to i

    bool sptSet[V];     //sptSet[i] will true if vertex i is included in shortest path tree

    int parent[V];      //to hold order of intermediate cities to be visited

    int wt,v,i,cnt;

    // Initialize all distances as INFINITE and stpSet[] as false
    for ( i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    parent[src] = -1;
    dist[src] = 0;

    // Find shortest path for all vertices
    for ( cnt = 0; cnt < V-1; cnt++)
    {
            int u = minDistance(dist, sptSet); //Pick the minimum distance vertex from the set of vertices not yet processed
            sptSet[u] = true;
        for ( v = 0; v < V; v++)
        {
            vertex* p=head;
            edge* q;
            while(p!=NULL)
            {
                if(p->no==u)
                {
                    q=p->ne;
                    while(q!=NULL)
                    {
                        if(q->no==v)
                        {
                            wt=q->weight;
                            break;
                        }
                        else
                            wt=0;
                     q=q->eptr;
                    }
                }
                p=p->nv;
             }

            if (!sptSet[v] && wt && dist[u] + wt < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + wt;
            }
        }
    }
    int num=V;
    char s[num][20];
        FILE* pp=fopen("citynames.txt","r");
        int nm1=0;
     while(1)
     {
         if(feof(pp))
            break;
         fscanf(pp,"%s ",s[nm1++]);
     }
     fclose(pp);
    printSolution(num,s,dist, parent,src,dest);
}



void printPath(int num,char s[][20],int parent[], int dest)
{
    if (parent[dest]==-1)
        return;
    printPath(num,s,parent, parent[dest]);
    printf("-> %s ", s[dest]);
}

int printSolution(int num,char s[][20],int dist[], int parent[],int source,int dest)
{
    printf("\n\t\tDistance and path from\t------- \"%s\" -> \"%s\" ------- \n",(s[source]),(s[dest]));
    printf("\n\t\tTotal distance:\t%d kms.\n\n\t\t\t\t\t******** PATH ********\n\n\t\t%s ",dist[dest],s[source]);
    printPath(num,s,parent, dest);
    getch();
    system("cls");
    printf("\n\n\n\n\n\n\n\n -----------------------------------------------------  %c  THANK YOU !  %c  --------------------------------------------------",1,1);
    getch();
    return 0;
}

void display()
{

   if(head==NULL)
    return;
    printf("\n------------------------------------------------------------------------------------------------------------------------------\n\n\t\t\t\t\t\t\t*** MAP ***\n\n------------------------------------------------------------------------------------------------------------------------------\n\n");
      vertex* p;
      p=head;
      edge* q;
      while(p!=NULL)
      {
          q=p->ne;
            printf("\t%-13s |-> ",p->name);
            while(q!=NULL)
            {
                printf("%-13s %2d    ",q->nm,q->weight);
                q=q->eptr;
            }
          p=p->nv;
          printf("\n");
      }
      printf("\n\n------------------------------------------------------------------------------------------------------------------------------\n\n");
      getch();
}

void init()
{
    char in[100];
    printf("\n\n------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t\t\t\t\t\"SILICON VALLEY\" WELCOMES YOU  !!!");
    printf("\n\n------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("\t\tMay I know your name.....?\n\t\t->");
    scanf("%[^\t\n]s",in);
    printf("\n\n\n\t\tHello, %s ....\n\t\tHope you are having a Good Day..! %c",in,1);
    getch();
    printf("\n\n\n\t\t%s, do you want any assistance from me regarding Silicon Valley..?\n\t\t->",in);
    scanf("%s",in);
    tolower(in);
    if((strcmp(in,"yes")==0)||(strcmp(in,"yeah")==0)||(strcmp(in,"sure")==0)||(strcmp(in,"y")==0)||(strcmp(in,"corrac")==0))
    {
    system("cls");
    printf("\n\n\t\tHere's the map of SILICON VALLEY ..... \n\n");
    display();
    }
   else
    {
       return;
    }
}
