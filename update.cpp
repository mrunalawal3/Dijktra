#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include"write.h"

FILE *fp,*pp;

vertex *createVertex()
{
    fflush(stdin);
    char cnm[25];
    printf("\nEnter city name:\t");
    scanf("%[^\t\n]s",cnm);
   vertex *a=(vertex *)malloc(sizeof(vertex));
    strcpy(a->name,cnm);
    a->ne=NULL;
    a->nv=NULL;
    a->no=count;
    count++;
    return a;
}

edge *createEdge()
{
    fflush(stdin);
    char cnm[25];
    int d;
    edge *a=(edge *)malloc(sizeof(edge));
    printf("\nEnter adjacent city name:\t");
    scanf("%[^\t\n]s",cnm);
   strcpy(a->nm,cnm);
    printf("\nEnter distance till %s:\t",cnm);
    scanf("%d",&d);
    a->weight=d;
    a->eptr=NULL;
     a->vptr=NULL;
    vertex *p=head,*q;
    while(p!=NULL)
    {
        if(strcmp(p->name,cnm)==0)
           {
            a->vptr=p;
            a->no=p->no;
           }
        p=p->nv;
    }
    return a;
}

void insertVertex()
{
    vertex *b=head,*c;
    vertex *a=createVertex();
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

edge* insertEdge(edge *t)
{
      edge *c;
    edge *a=createEdge();
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

void updateEdges()
{
    int opt,flg;
    vertex* p=head;
    while(p!=NULL)
    {
        while(1)
        {
            flg=1;
            printf("\nEnter:\t1.add city adj to %s..?\t\t2.to stop\n",p->name);
            scanf("%d",&opt);
            switch(opt)
            {
            case 1:
               if(p->ne==NULL)
                {
                    p->ne=insertEdge(p->ne);
                }
              else
               insertEdge(p->ne);
               break;
            case 2:
                flg=0;break;
            }
             if(flg==0)
            break;
        }
       p=p->nv;
    }
}



void updatefile2()
{
   FILE *fp1=fopen("maplist.txt","w");
               FILE * pp1=fopen("citynames.txt","w");
   if(head==NULL)
    return;
    printf("\n------------MAP UPDATED--------------\n");
      vertex* p;
      p=head;
      edge* q;
      while(p!=NULL)
      {
          printf("in");
          q=p->ne;
            fprintf(fp1,"%s ",p->name);
            fprintf(pp1,"%s ",p->name);
            while(q!=NULL)
            {
                fprintf(fp1,"%s %d ",q->nm,q->weight);
                q=q->eptr;
            }
          p=p->nv;
          fprintf(fp1,"END\n");
      }
      fclose(fp1);
      fclose(pp1);
      getch();
}

void display()
{

   if(head==NULL)
    return;
    printf("\n\t\t\t\t------------MAP--------------\n\n");
      vertex* p;
      p=head;
      edge* q;
      while(p!=NULL)
      {
          q=p->ne;
            printf("\t%-13s |-> ",p->name);
            while(q!=NULL)
            {
                printf("%-13s %2d     ",q->nm,q->weight);
                q=q->eptr;
            }
          p=p->nv;
          printf("\n");
      }
      getch();
}

int main()
{
    	int a,dest;
    int i,sno,dno;
    char source[20];
    char desti[20];
    char adjnm[20];
    int weight;
    FILE* fp=fopen("maplist.txt","r");
    FILE* pp=fopen("citynames.txt","r");
    char nm1[20];
     while(1)
     {
         if(feof(pp))
            break;
         fscanf(pp,"%s ",nm1);
         insertVertex(nm1);
     }
     while(1)
      {
          if(feof(fp))
            break;
        fscanf(fp,"%s",nm1);
            while(1)
            {
                fscanf(fp,"%s",adjnm);
                if(strcmp(adjnm,"END")==0)
                    break;
                fscanf(fp,"%d",&weight);
                vertex*p=head;
                while(p!=NULL)
                {
                    if(strcmp(p->name,nm1)==0)
                    {
                        updateEdges(p,adjnm,weight);
                        break;
                    }
                    p=p->nv;
                }
            }
        }


    int opt;
    while(1)
    {
    printf("\nMENU\n\n1.Add city to map.\n2.Update distance of adjacent cities\n3.update file\n4.Update adjacent of city.\n5.display\n6.Stop\n");
    scanf("%d",&opt);
    if(opt>5)
        break;
        switch(opt)
        {
        case 1:
        insertVertex();
        break;

        case 2:
            if(head==NULL)
                {
                    printf("\nEmpty map..!\n");
                    getch();
                }
        updateEdges();
        break;

        case 3:
                if(head==NULL)
                {
                    printf("\nEmpty map..!\n");
                    getch();
                }
        updatefile2();
        break;

        case 4:
            {
            char nm[20],anm[20];
            int d;
            printf("\nEnter city name to be updated:\t");
            scanf("%s",nm);
            printf("\nEnter city adjacent to %s :\t",nm);
            scanf("%s",anm);
            printf("\nEnter distance from %s -> %s:\t",nm,anm);
            scanf("%d",&d);

                vertex* n=head;
                while(n!=NULL)
                {
                    if(strcmp(n->name,nm)==0)
                    {
                        updateEdges(n,anm,d);
                        break;
                    }
                    n=n->nv;
                }
        }
        case 5:
            {
              display();break;
            }
        }
    }
    fclose(fp);
    fclose(pp);
    return 0;
}
