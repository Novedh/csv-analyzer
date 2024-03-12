/**************************************************************
* Class::  CSC-415-01 Spring 2024
* Name::Devon Huang
* Student ID::916940666
* GitHub-Name::Novedh
* Project:: Assignment 4 – Processing CSV Data with Threads
*
* File:: huang_devon_HW4_func.c
*
* Description:: c file for functions i needed for linked list and getting the
* difference in time .
*
**************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "assignment4.h"

// for the times ill use an array of ints where each index will keep track of 
// the time it takes 
// 0's will keep track of 2 minutes or less
// 1's will keep track of 3 to 5 minutes
// 2's will keep track of 6 to 10 minute
// 3's will keep track of over 10 minutes

EventData* createNode(char *callType) {
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
    int tempSubVal1DisTime[4];
    int tempSubVal1OnTime[4];
    int tempSubVal2DisTime[4];
    int tempSubVal2OnTime[4];
    int tempSubVal3DisTime[4];
    int tempSubVal3OnTime[4];

    memcpy(tempDispatchTimes, a->dispatchTimes, sizeof(int) * 4);
    memcpy(tempOnSceneTimes, a->onSceneTimes, sizeof(int) * 4);
    memcpy(tempSubVal1DisTime, a->subVal1DisTime, sizeof(int) * 4);
    memcpy(tempSubVal1OnTime, a->SubVal1OnTime, sizeof(int) * 4);
    memcpy(tempSubVal2DisTime, a->subVal2DisTime, sizeof(int) * 4);
    memcpy(tempSubVal2OnTime, a->SubVal2OnTime, sizeof(int) * 4);
    memcpy(tempSubVal3DisTime, a->subVal3DisTime, sizeof(int) * 4);
    memcpy(tempSubVal3OnTime, a->SubVal3OnTime, sizeof(int) * 4);

    a->callType = b->callType;
    a->totalCalls = b->totalCalls;
    memcpy(a->dispatchTimes, b->dispatchTimes, sizeof(int) * 4);
    memcpy(a->onSceneTimes, b->onSceneTimes, sizeof(int) * 4);
    memcpy(a->subVal1DisTime, b->subVal1DisTime, sizeof(int) * 4);
    memcpy(a->SubVal1OnTime, b->SubVal1OnTime, sizeof(int) * 4);
    memcpy(a->subVal2DisTime, b->subVal2DisTime, sizeof(int) * 4);
    memcpy(a->SubVal2OnTime, b->SubVal2OnTime, sizeof(int) * 4);
    memcpy(a->subVal3DisTime, b->subVal3DisTime, sizeof(int) * 4);
    memcpy(a->SubVal3OnTime, b->SubVal3OnTime, sizeof(int) * 4);

    b->callType = tempCallType;
    b->totalCalls = tempTotalCalls;
    memcpy(b->dispatchTimes, tempDispatchTimes, sizeof(int) * 4);
    memcpy(b->onSceneTimes, tempOnSceneTimes, sizeof(int) * 4);
    memcpy(b->subVal1DisTime, tempSubVal1DisTime, sizeof(int) * 4);
    memcpy(b->SubVal1OnTime, tempSubVal1OnTime, sizeof(int) * 4);
    memcpy(b->subVal2DisTime, tempSubVal2DisTime, sizeof(int) * 4);
    memcpy(b->SubVal2OnTime, tempSubVal2OnTime, sizeof(int) * 4);
    memcpy(b->subVal3DisTime, tempSubVal3DisTime, sizeof(int) * 4);
    memcpy(b->SubVal3OnTime, tempSubVal3OnTime, sizeof(int) * 4);
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
//seperate the string and take the numbers into a array to calculate
//01/06/2016 08:46:50 PM


int timeDifference(const char *time1, const char *time2)
{
    // Initialize variables to store date and time components
    int day1, month1, year1, hour1, min1, sec1;
    int day2, month2, year2, hour2, min2, sec2;

    // had to make copies of the strings since strtok_r modifies the strings
    // causing segfaults
    char *time1Copy = malloc(strlen(time1) + 1);
    char *time2Copy = malloc(strlen(time2) + 1);
    strcpy(time1Copy, time1);
    strcpy(time2Copy, time2);

    char *token;
    char *saveptr1;
    char *saveptr2;

    // Tokenize the first time string
    token = strtok_r(time1Copy, "/ :", &saveptr1);
    month1 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr1);
    day1 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr1);
    year1 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr1);
    hour1 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr1);
    min1 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr1);
    sec1 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr1);
    if ((strcmp(token, "PM") == 0) && (hour1 != 12))
    {
        hour1 += 12;
    }
    else if ((strcmp(token, "AM") == 0) && (hour1 == 12))
    {
        hour1 = 0;
    }

    // Tokenize the second time string
    token = strtok_r(time2Copy, "/ :", &saveptr2);
    month2 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr2);
    day2 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr2);
    year2 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr2);
    hour2 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr2);
    min2 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr2);
    sec2 = atoi(token);
    token = strtok_r(NULL, "/ :", &saveptr2);
    if ((strcmp(token, "PM") == 0) && (hour2 != 12))
    {
        hour2 += 12;
    }
    else if ((strcmp(token, "AM") == 0) && (hour2 == 12))
    {
        hour2 = 0;
    }

    // Calculate the time difference
    int totalSec1 = sec1 + min1 * SECONDS_MIN + hour1 * SECONDS_HOUR + day1 * SECONDS_DAY + month1 * SECONDS_MONTH + year1 * SECONDS_YEAR;
    int totalSec2 = sec2 + min2 * SECONDS_MIN + hour2 * SECONDS_HOUR + day2 * SECONDS_DAY + month2 * SECONDS_MONTH + year2 * SECONDS_YEAR;

    // Free the allocated memory
    free(time1Copy);
    free(time2Copy);

    return totalSec2 - totalSec1;
}


