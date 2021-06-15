#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Plane.h"
#include "Airport.h"
#include  "PlaneLinkedList.h"
#include "AirportLinkedList.h"
#include "LinkedListIml.h"
#include <ctype.h>

int totalAirport=0;

void copyName(int length,char *newFile,char oldFile[])
{
    int i=0;
    for(i=0;i<length;i++)
    {
        newFile[i]=oldFile[i];
    }
    newFile[i]='\0';
}


int checkFile(FILE *fptr)
{
    if(fptr==NULL)
    {
        return 1;
    }

    return 0;
}

int generateRandomNumber()
{
    srand(time(0));
    int num=rand();
    return num%totalAirport==0?totalAirport:num%totalAirport;
}

void printPLaneToPaticularAirport(struct AirportLinkedList *head,struct PlaneLinkedList *planeHead)
{
    int randomNum = generateRandomNumber();
    struct AirportLinkedList *temp=head;
    int cnt=0;
    char charId[4];
    while(temp)
    {
        cnt++;
        if(cnt==randomNum)
        {
            printf("Airport which is selected is \n");
            printf("Airport id - %s\n",temp->data.airportId);
            printf("Airport Name - %s\n",temp->data.airportName);
            printf("Airport country - %s\n",temp->data.airportCountry);
            charId[0]=temp->data.airportId[0];
            charId[1]=temp->data.airportId[1];
            charId[2]=temp->data.airportId[2];
            charId[3]=temp->data.airportId[3];
            break;
        }
        temp=temp->next;
    }

    struct PlaneLinkedList *planeTemp=planeHead;

    while (planeTemp)
    {
        if( strcmp(planeTemp->data.planeLocation,charId)==0)
        {
            printf("plane id - %d\n",planeTemp->data.planeId);
            printf("plane model - %s\n",planeTemp->data.planeModel);
            printf("plane manfucaturer - %s\n",planeTemp->data.Manufacturer);
            printf("plane location - %s\n",planeTemp->data.planeLocation);
            printf("\n");
        }
        planeTemp=planeTemp->next;
    }
    


}


void landedPlandes(struct PlaneLinkedList *planehead)
{
    unsigned char arr[10];
    int pos=0;
    int cnt=0;
    memset(arr,'0',sizeof(arr));
    while(planehead)
    {cnt++;
        if(cnt>8)
        {
            printf("There are more then 8 list of planes");
            return ;
        }
        if(strcmp(planehead->data.planeLocation,"000")==0)
        {
            arr[pos]='1';
        }
        else{
            arr[pos]='0';
        }
        pos++;
        
        planehead=planehead->next;
    }
    
    FILE *fp = fopen("flight_status.txt","w");
    for(int i=0;i<8;i++)
    {
        if(i%4==0)
        {
            fprintf(fp,"%c",' ');
        }
        fprintf(fp,"%x",arr[i]-'0');
        
    }
}

int main(int argc,char *argv[])
{
    // char airportFilename[strlen(argv[1])]=argv[1];
    if(argc != 3)
    {
        printf("Please enter the file name\n");
        return 0;
    }
    int airportFileLength=strlen(argv[1]);
    int planeFileLength=strlen(argv[2]);
    char airportFileName[airportFileLength];
    char planeFileName[planeFileLength];

    copyName(airportFileLength,airportFileName,argv[1]);
    copyName(planeFileLength,planeFileName,argv[2]);

    FILE *fptr1 = fopen(airportFileName,"r");
    FILE *fptr2 = fopen(planeFileName,"r");

    if( checkFile(fptr1) || checkFile(fptr2) )
    {
        return 0;
    }

    char *c=NULL;
    size_t len=0;
    ssize_t read;

    char airportId[4];
    char airportName[127];
    char airportCountry[127];
    struct AirportLinkedList *head=NULL,*tail=NULL;
    while((read = getline(&c,&len,fptr1))!=-1)
    {
         struct Airport data;
        if(c[3]!='-')
        {
            for(int i=0;i<strlen(c)-1;i++)
            {
                airportCountry[i]=c[i];
            }
             for(int i=0;i<=strlen(airportCountry);i++)
            {
                data.airportCountry[i]=airportCountry[i];
            }
        }
        else{
            for(int i=0;i<3;i++)
            {
                airportId[i]=c[i];
            }
            airportId[4]='\0';
            for(int i=4;i<strlen(c);i++)
            {
                airportName[i-4]=c[i];
                airportName[i-3]='\0';
            }
            
            for(int i=0;i<strlen(airportId);i++)
            {
                data.airportId[i]=airportId[i];
                data.airportId[i+1]='\0';
            }

            for(int i=0;i<strlen(airportName)-1;i++)
            {
                data.airportName[i]=airportName[i];
                data.airportName[i+1]='\0';
            }

            totalAirport++;
            tail=createLinkedList(&head,tail,data);
            
        }
    }
    int leng=strlen(airportName);
    tail->data.airportName[leng-1]=airportName[leng-1];
    tail->data.airportName[leng]='\0';

    struct PlaneLinkedList *planeHead=NULL,*planeTail=NULL;

    while ((read=getline(&c,&len,fptr2))!=-1)
    {
        int id=atoi(c);
        char planeModel[64];
        char planeManufacturer[128];
        char planeLocation[15];
      

        getline(&c,&len,fptr2);
        
        for(int i=0;i<strlen(c)-1;i++)
        {
            planeModel[i]=c[i];
            planeModel[i+1]='\0';
        }
        getline(&c,&len,fptr2);
        for(int i=0;i<strlen(c)-1;i++)
        {
            planeManufacturer[i]=c[i];
            planeManufacturer[i+1]='\0';
        }
        getline(&c,&len,fptr2);
       
        int lolength=strlen(c);
        if(lolength==3)
        {
            lolength+=1;
        }
        else if(lolength==6)
        {
            lolength+=1;
        }
        int cnt=0;
        for(int i=0;i<lolength;i++)
        {
            cnt++;
            planeLocation[i]=c[i];
        }

        planeLocation[cnt-1]='\0';
        lolength=strlen(planeLocation);
        struct Plane data;
        data.planeId=id;

        for(int i=0;i<=strlen(planeModel);i++)
        {
            data.planeModel[i]=planeModel[i];
        }

        for(int i=0;i<=strlen(planeManufacturer);i++)
        {
            data.Manufacturer[i]=planeManufacturer[i];
        } 

        if(strcmp(planeLocation,"IN AIR")==0)
        {
            data.planeLocation[0]='0';
            data.planeLocation[1]='0';
            data.planeLocation[2]='0';
            data.planeLocation[3]='\0';
        }
        else{
            data.planeLocation[0]=planeLocation[0];
            data.planeLocation[1]=planeLocation[1];
            data.planeLocation[2]=planeLocation[2];
            data.planeLocation[3]='\0';
        }
        planeTail=createPlaneLinkedList(&planeHead,planeTail,data);
   
    }

    free(fptr1);
    free(fptr2);
    printf("Enter 1 to check flight which are landed in paticular country\n");
    printf("Enter 2 to check which are the landed and which are in air\n");
    int choice;
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:  printPLaneToPaticularAirport(head,planeHead); break;
        case 2: landedPlandes(planeHead);break;
        default: printf("Wrong Choice\n");
    }
    free(head);
    free(planeHead);
    return 0;
    
}