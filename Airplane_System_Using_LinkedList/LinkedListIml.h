

struct AirportLinkedList* createLinkedList(struct AirportLinkedList **head,struct AirportLinkedList *tail,struct Airport data)
{
    
    if(*head==NULL)
    {
        (*head) = malloc(sizeof(struct AirportLinkedList));
        (*head)->data=data;
        (*head)->next=NULL;
        return *head;
    }
    else{
        tail->next  = malloc(sizeof(struct AirportLinkedList));
        tail->next->data = data;
        tail=tail->next;
        tail->next=NULL;
        return tail;
    }
} 


struct PlaneLinkedList* createPlaneLinkedList(struct PlaneLinkedList **head,struct PlaneLinkedList *tail,struct Plane data)
{
    
    if(*head==NULL)
    {
        (*head) = malloc(sizeof(struct PlaneLinkedList));
        (*head)->data=data;
        (*head)->next=NULL;
        return *head;
    }
    else{
        tail->next  = malloc(sizeof(struct PlaneLinkedList));
        tail->next->data = data;
        tail=tail->next;
        tail->next=NULL;
        return tail;
    }
} 