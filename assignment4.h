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
#define SECONDS_MIN 60
#define SECONDS_DAY 86400
#define SECONDS_HOUR 3600
#define SECONDS_MONTH 2628000
#define SECONDS_YEAR 31536000

typedef struct EventData{
    char *callType;
    int totalCalls;
    int dispatchTimes[4];
    int onSceneTimes[4];
    int subVal1DisTime[4];
    int SubVal1OnTime[4];
    int subVal2DisTime[4];
    int SubVal2OnTime[4];
    int subVal3DisTime[4];
    int SubVal3OnTime[4];
    struct EventData *next;
}EventData;

EventData* createNode(char *callType);

void insertNode(EventData **head, EventData *newNode) ;


void swapNode(EventData *a, EventData *b) ;

void sortNodes(EventData *head) ;

void freeList(EventData *head) ;

int timeDifference(const char* time1, const char* time2);

char ** csvopen (char * filename);

char ** csvnext (void);

char ** csvheader (void);

int csvclose (void);