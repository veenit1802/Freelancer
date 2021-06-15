#include<stdio.h>
#include<stdlib.h>

#define Size 100000
#define MOD 12000
int newarr[3][3];
struct ArrCollection
{
    int arr[3][3];
    struct ArrCollection *next;
};


struct ArrCollection *array[Size];
int totelementInHashTable=0;
int totalMovement=0;

struct ArrCollection * createObject(int arr[][3])
{
    struct ArrCollection *newnode = (struct ArrCollection* ) malloc(sizeof(struct ArrCollection));
    newnode->next=NULL;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            newnode->arr[i][j]=arr[i][j];
        }
    }

    return newnode;
}




//how initailize the hash table with null
void init_array()
{
    for(int i=0;i<Size;i++)
    {
        array[i]=NULL;
    }
}



//to find the hash number of the matrix
long long hash(int arr[3][3])
{
    long long int value=0,powmul=1;
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            int num=i+j+1;
            value+=((num*num) + (num*arr[i][j]*arr[i][j]))*powmul;
            powmul*=2;
        }
    }

    return value;
}


// compare the value which is in the headarr and arr which is to be inserted
int cmp(int headarr[3][3],int lolarr[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(headarr[i][j]!=lolarr[i][j])
            {
                return 0;
            }
        }
    }
  

    return 1;
}







//to insert the value of the matrix in the hash table
int enterInhashTable(long long int hashnum,int arr[3][3])
{
    hashnum=hashnum%MOD;
    // printf("%lld",hashnum);
    if(array[hashnum]==NULL)
    {
        array[hashnum] = createObject(arr);
        totelementInHashTable++;
        return 1;
    }
    else{
        struct ArrCollection *head=array[hashnum];

        while (head)
        {
            if(cmp(head->arr,arr))
            {
                return 0;
            }
            head=head->next;
        }
        totelementInHashTable++;
        head=array[hashnum];
        struct ArrCollection *temp = createObject(arr);
        temp->next=head;
        array[hashnum]=temp;

        return 1;
    }

}



struct ArrCollection *front=NULL,*rear=NULL;

void insertInQueue(int arr[3][3])
{
    if(rear==NULL)
    {
        struct ArrCollection *temp = createObject(arr);
        rear=temp;
        front=rear;

    }
    else{
        struct ArrCollection *temp = createObject(arr);
        rear->next=temp;
        rear=rear->next;
    }
}

void popFromQueue()
{
    if(front==NULL)
    {
        return;
    }
    // printf("%p",front->arr);
    // for(int i=0;i<3;i++)
    // {
    //     for(int j=0;j<3;j++)
    //     {
    //         printf("%d ",front->arr[i][j]);
    //     }
    //     printf("\n");
    // }
        struct ArrCollection *temp=front;
        
        front=front->next;
        temp->next=NULL;
        // rear=NULL;
        free(temp);

        if(front==NULL)
        {
            rear=NULL;
        }
}

struct ArrCollection *top=NULL;

void insertInStack(int arr[3][3])
{
    if(top==NULL)
    {
        top=createObject(arr);
        return;
    }
    else{
        struct ArrCollection *temp = createObject(arr);
        struct ArrCollection *newhead=top;
        temp->next=newhead;
        top=temp;
        return;
    }
}


void popFromStack()
{
    if(top==NULL)
    {
        return ;
    }

    struct ArrCollection *temp = top;
    top=top->next;
    free(temp);
}


void moveUp(int posi,int posj,int insertIn)
{
    if(posi==0)
    {
        return;
    }
    int arr[3][3];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            arr[i][j]=newarr[i][j];
        }
    }
    int temp=arr[posi][posj];
    arr[posi][posj]=arr[posi-1][posj];
    arr[posi-1][posj]=temp;
    totalMovement++;
    if(insertIn==1 &&  enterInhashTable(hash(arr),arr)==1)
    {
        insertInQueue(arr);
    }
    else if(insertIn==0 &&  enterInhashTable(hash(arr),arr)==1)
    {
        insertInStack(arr);
    }
}

void moveDown(int posi,int posj,int insertIn)
{
    if(posi==2)
    {
        return;
    }
    int arr[3][3];
     for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            arr[i][j]=newarr[i][j];
        }
    }
    totalMovement++;
    int temp=arr[posi][posj];
    arr[posi][posj]=arr[posi+1][posj];
    arr[posi+1][posj]=temp;
      if(insertIn==1 &&  enterInhashTable(hash(arr),arr)==1)
    {
        insertInQueue(arr);
    }
    else if(insertIn==0 &&  enterInhashTable(hash(arr),arr)==1)
    {
        insertInStack(arr);
    }
}

void moveLeft(int posi,int posj,int insertIn)
{
    if(posj==0)
    {
        return;
    }
    int arr[3][3];
     for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            arr[i][j]=newarr[i][j];
        }
    }
    totalMovement++;
    int temp=arr[posi][posj];
    arr[posi][posj]=arr[posi][posj-1];
    arr[posi][posj-1]=temp;
    if(insertIn==1 &&  enterInhashTable(hash(arr),arr)==1)
    {
        insertInQueue(arr);
    }
    else if(insertIn==0 &&  enterInhashTable(hash(arr),arr)==1)
    {
        insertInStack(arr);
    }
}


void moveRight(int posi,int posj,int insertIn)
{
    
    if(posj==2)
    {
        return;
    }
    int arr[3][3];
     for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            arr[i][j]=newarr[i][j];
        }
    }
    totalMovement++;
    int temp=arr[posi][posj];
    arr[posi][posj]=arr[posi][posj+1];
    arr[posi][posj+1]=temp;
    if(insertIn==1 &&  enterInhashTable(hash(arr),arr)==1)
    {
        insertInQueue(arr);
    }
    else if(insertIn==0 &&  enterInhashTable(hash(arr),arr)==1)
    {
        insertInStack(arr);
    }
}


int main()
{
    
    printf("Kindly enter initial state of the box\n");
    int arr[3][3];
    int finalarr[3][3]={{1,2,3},{4,5,6},{7,8,0}};

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            scanf("%d",&arr[i][j]);
        }
    }
           
    
    printf("Enter 1 for code to run with queue\nEnter 2 for code to run with stack\n");
    printf("Enter you choice\n");
    int choice;
    scanf("%d",&choice);

    switch (choice)
    {
    case 1:{
                init_array();
            insertInQueue(arr);
            enterInhashTable(hash(arr),arr);
                    
            
                while (1)
                {
                    if(front==NULL)
                        break;
                    struct ArrCollection *temp = front;
                    int positioni,positionj;
                    int cnt=0;
                    for(int i=0;i<3;i++)
                    {
                        for(int j=0;j<3;j++)
                        {
                            newarr[i][j]=temp->arr[i][j];
                            if(newarr[i][j]==0)
                            {
                                positioni=i;
                                positionj=j;
                            }
                            if(newarr[i][j]==finalarr[i][j])
                            {
                                cnt++;
                            }
                            // printf("%d ",newarr[i][j]);
                        }
                        // printf("%d\n",cnt);
                    }
                    if(cnt==9)
                    {
                        printf("Total states visited = %d\n",totelementInHashTable);
                        printf("Total number of movements to arrive at the solution = %d\n",totalMovement);
                        for(int i=0;i<3;i++)
                        {
                            for(int j=0;j<3;j++)
                            {
                                printf("%d ",newarr[i][j]);
                            }
                            printf("\n");
                        }
                        break;
                    }
                    // printf("%lld ",hash(newarr)%MOD);

                    popFromQueue();
                    moveUp(positioni,positionj,1);
                    moveDown(positioni,positionj,1);
                    moveRight(positioni,positionj,1);
                    moveLeft(positioni,positionj,1);
                    
                }
                
        break;}
    case 2: { init_array();
            insertInStack(arr);
            enterInhashTable(hash(arr),arr);
                    
            
                while (1)
                {
                    if(top==NULL)
                    {
                        printf("not able to solve with within time limit\n");
                        return 0;
                    }
                    struct ArrCollection *temp = top;
                    int positioni,positionj;
                    int cnt=0;
                    for(int i=0;i<3;i++)
                    {
                        for(int j=0;j<3;j++)
                        {
                            newarr[i][j]=temp->arr[i][j];
                            if(newarr[i][j]==0)
                            {
                                positioni=i;
                                positionj=j;
                            }
                            if(newarr[i][j]==finalarr[i][j])
                            {
                                cnt++;
                            }
                            // printf("%d ",newarr[i][j]);
                        }
                        // printf("%d\n",cnt);
                    }
                    if(cnt==9)
                    {
                        printf("Total states visited = %d\n",totelementInHashTable);
                        printf("Total number of movements to arrive at the solution = %d\n",totalMovement);
                        for(int i=0;i<3;i++)
                        {
                            for(int j=0;j<3;j++)
                            {
                                printf("%d ",newarr[i][j]);
                            }
                            printf("\n");
                        }
                        break;
                    }
                    // printf("%lld ",hash(newarr)%MOD);

                    popFromStack();
                    moveUp(positioni,positionj,0);
                    moveDown(positioni,positionj,0);
                    moveRight(positioni,positionj,0);
                    moveLeft(positioni,positionj,0);
                    
                }
     
            break;
            }
    default: printf("Wrong Choice");
        break;
    }
    
    return 0;
}