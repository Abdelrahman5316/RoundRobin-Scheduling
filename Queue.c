#include <stdio.h>
#include <stdlib.h>
#include<string.h>
/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
   Node *front,*rear;
} Queue;
/*
 *
 */
Queue* init()
{
    Queue *q=malloc(sizeof(Queue));
    q->front=NULL;
    q->rear=NULL;
    return q;
}
/*
 *
 */
int isEmpty(Queue *q)
{
   if(q->front==NULL)
    return 1;
   return 0;

}
/*
 *
 */
 Node *newNode(char *name,int startTime,int remainingTime){
   Node *n=malloc(sizeof(Node));
   n->data.name=malloc(50);
   strcpy(n->data.name,name);
   n->data.starting_time=startTime;
   n->data.remaining_time=remainingTime;
   n->next=NULL;
   return n;
 }
Process dequeue(Queue *q)
{
    Process p;
    p.name=malloc(50);
    p.name=q->front->data.name;
    p.starting_time=q->front->data.starting_time;
    p.remaining_time=q->front->data.remaining_time;
    if(q->front==NULL){
    q->rear=NULL;
    return;
     }
     else
    q->front=q->front->next;
    return p;

   }

/*
 *
 */
void enqueue(Queue *q, Process x)
{
    Node *node=newNode(x.name,x.starting_time,x.remaining_time);
    if(q->front==NULL)
        q->front=q->rear=node;
    else{
        q->rear->next=node;
        q->rear=node;
    }
}
/*
 *
 */
void destroy(Queue *q)
{
 Node *current= q->front;
 Node *next=NULL;
 while(current!=NULL){
    next=current->next;
    free(current);
    current=next;
 }
 q->front=q->rear=NULL;
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    FILE *f=fopen(filename,"r");
    Process p[100];
    char line[60];
    int count=0,i,x,j=0;
    int timeSlots;
    Queue *q=init();
    if(f!=NULL)
    {
        fgets(line,60,f);
        char *token=strtok(line," ");

        while(token!=NULL)
        {
            if(isdigit(token[0]))
            {

                timeSlots=atoi(token);

            }

            token=strtok(NULL," ");
        }

        while(!feof(f))
        {
            p[count].name=malloc(50);
            fscanf(f,"%s",p[count].name);
            fscanf(f,"%d",&p[count].starting_time);
            fscanf(f,"%d",&p[count].remaining_time);
            count++;
        }
        for(i=0; i<timeSlots; i++)
           {
            for(x=0; x<count;x++)
            {
                if(p[x].starting_time==i)
                {
                    enqueue(q,p[x]);
                }

            }
           if(isEmpty(q)){
            printf("idle\t(%d-->%d)\n",i,i+1);

           }
            else
            {
                Process dequeuedProcess=dequeue(q);
                dequeuedProcess.remaining_time=dequeuedProcess.remaining_time-1;
                printf("%s\t(%d-->%d)",dequeuedProcess.name,i,i+1);
                 for(x=0; x<count;x++)
           {
                if(p[x].starting_time==i+1)
                {
                    enqueue(q,p[x]);
                  p[x].starting_time=0;
                }
           }
                if(dequeuedProcess.remaining_time==0)
                {
                    printf("  %s aborts\n",dequeuedProcess.name);
                }
                else
                {
                    enqueue(q,dequeuedProcess);
                    printf("\n");
                }

           }

       }
        printf("stop\n");
        destroy(q);
        fclose(f);
    }
    else
    {
        printf("File not found");
    }
}
/*
 *
 */
int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
