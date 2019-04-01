
#include"dijkstra.h"

int main()
{
	int i,sno,dno;
    char source[20],ans[6],desti[20],adjnm[20];
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
        fclose(fp);
        fclose(pp);
        init();

while(1)
{
    int sno=-1,dno=-1;
      x:
            printf("\n\n\t\tEnter source:\t\t");
        scanf("%s",source);
    vertex* p=head;
    while(p!=NULL)
   {
        if(strcmp(p->name,source)==0)
        {
            sno=p->no;
            break;
        }
        p=p->nv;
    }
    if(sno==-1)
    {
        printf("\t\tINVALID INPUT..!");
        getch();
        goto x;
    }
y:
    fflush(stdin);
      printf("\n\n\t\tEnter destination:\t");
      scanf("%s",desti);
      p=head;
    while(p!=NULL)
   {
        if(strcmp(p->name,desti)==0)
        {
            dno=p->no;
            break;
        }
          p=p->nv;
    }
    if(dno==-1)
    {
        printf("\t\tINVALID INPUT..!");
       getch();
       goto y;
    }
    dijkstra(sno,dno);
    printf("\n\n\n\n\n\n\t\t\t\tWant to search again..?");
    scanf("%s",ans);
     if((strcmp(ans,"yes")==0)||(strcmp(ans,"yeah")==0)||(strcmp(ans,"sure")==0)||(strcmp(ans,"y")==0))
        continue;
     break;
    system("cls");
}
    return 0;
}
