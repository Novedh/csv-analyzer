/**************************************************************
* Class::  CSC-415-01 Spring 2024
* Name::Devon Huang
* Student ID::916940666
* GitHub-Name::Novedh
* Project:: Assignment 4 – Processing CSV Data with Threads
*
* File:: assignment4.h
*
* Description:: A header file for the csvthreads project
*
**************************************************************/
#define BUFFERSIZE 1024

// for the times ill use an array of ints where each index will keep track of 
// the time it takes 
// 0's will keep track of 2 minutes or less
// 1's will keep track of 3 to 5 minutes
// 2's will keep track of 6 to 10 minute
// 3's will keep track of over 10 minutes
typedef struct EventData{
    char *callType;
    int totalCalls;
    int dispatchTimes[4];
    int onSceneTimes[4];
    struct EventData *next;
}EventData;

EventData* createNode(char *callType, int totalCalls, int dispatchTimes[], int onSceneTimes[]) {
    EventData* newNode = (EventData*)malloc(sizeof(EventData));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->callType = (char*)malloc(strlen(callType) + 1);
    if (newNode->callType == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newNode->callType, callType);
    newNode->totalCalls = totalCalls;
    memcpy(newNode->dispatchTimes, dispatchTimes, sizeof(int) * 4);
    memcpy(newNode->onSceneTimes, onSceneTimes, sizeof(int) * 4);
    newNode->next = NULL;
    return newNode;
}

void insertNode(EventData **head, EventData *newNode) {
    if (*head == NULL) {
        *head = newNode;
    } else {
        EventData *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
int nodeCount(EventData *head){
    int count =1;
    while(head->next != NULL){
        count++;
        head = head->next;
    }
    return count;
}

void swapNode(EventData *a, EventData *b) {
    char *tempCallType = a->callType;
    int tempTotalCalls = a->totalCalls;
    int tempDispatchTimes[4];
    int tempOnSceneTimes[4];
    memcpy(tempDispatchTimes, a->dispatchTimes, sizeof(int) * 4);
    memcpy(tempOnSceneTimes, a->onSceneTimes, sizeof(int) * 4);

    a->callType = b->callType;
    a->totalCalls = b->totalCalls;
    memcpy(a->dispatchTimes, b->dispatchTimes, sizeof(int) * 4);
    memcpy(a->onSceneTimes, b->onSceneTimes, sizeof(int) * 4);

    b->callType = tempCallType;
    b->totalCalls = tempTotalCalls;
    memcpy(b->dispatchTimes, tempDispatchTimes, sizeof(int) * 4);
    memcpy(b->onSceneTimes, tempOnSceneTimes, sizeof(int) * 4);
}

void sortNodes(EventData *head) {
    if (head == NULL || head->next == NULL)
        return;

    int swapped;
    EventData *ptr1;
    EventData *lastptr = NULL;

    while (1) {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lastptr) {
            if (strcmp(ptr1->callType, ptr1->next->callType) > 0) {
                swapNode(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        
        if (!swapped){
            break;
        }

        lastptr = ptr1;
    }
}

void freeList(EventData *head) {
    EventData *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->callType);
        free(temp);
    }
}

char ** csvopen (char * filename);

char ** csvnext (void);

char ** csvheader (void);

int csvclose (void);