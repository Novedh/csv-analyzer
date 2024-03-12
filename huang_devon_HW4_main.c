/**************************************************************
* Class::  CSC-415-01 Spring 2024
* Name::Devon Huang
* Student ID::916940666
* GitHub-Name::Novedh
* Project:: Assignment 4 – Processing CSV Data with Threads
*
* File:: huang_devon_HW4_main.c
*
* Description::
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
#include "huang_devon_HW4_func.c"



int main (int argc, char *argv[])
    {
    //***TO DO***  Look at arguments, initialize application
    char ** header = csvopen (argv[1]);
    int colms = 0;
    while ((header[colms] != NULL) && (colms < 50)){
        ++colms;
    }
	//Law100K.csv 1 police_district(26) BAYVIEW MISSION TENDERLOIN
    //13 : call_type_final_desc
    //10 : call_type_original_desc

    //25 : analysis_neighborhood
    //26 : police_district

    //03 : received_datetime
    //05 : dispatch_datetime
    //06 : enroute_datetime
    //07 : onscene_datetime

    int threads = atoi(argv[2]);
    char *subfield = argv[3];
    char *subVal1 = argv[4];
    char *subVal2 = argv[5];
    char *subVal3 = argv[6];
    char **line = csvnext();
    int subfieldLoc = 0;
    char *lineCallType;
    EventData *head = NULL;

    // this is to find which subfield the user choose, police district or neighborhood
    for(int i =0; i<colms; i++){
         if (strcmp(header[i], subfield) == 0) {
            subfieldLoc = i;
            break; 
        }
    }

    //**************************************************************
    // DO NOT CHANGE THIS BLOCK
    //Time stamp start
    struct timespec startTime;
    struct timespec endTime;

    clock_gettime(CLOCK_REALTIME, &startTime);
    //**************************************************************
    
    // *** TO DO ***  start your thread processing
    //                wait for the threads to finish
    

    
    while((line = csvnext())!= NULL){

        
        int callFound = 0;
        // use line 13 for call type unless its empty then use 10
        if (!(strcmp(line[13], "") == 0)){
            lineCallType = line[13];
        }
        else{
            lineCallType = line[10];
        }
        if (head == NULL){
            EventData *newNode = createNode(lineCallType);
            insertNode(&head, newNode);
        }
         
        EventData *headptr = head;
        // make sure that the none of the times are empty, if they are ignore data
        if (!(strcmp(line[3], "") == 0) && !(strcmp(line[5], "") == 0) &&
            !(strcmp(line[6], "") == 0) && !(strcmp(line[7], "") == 0))
        {
            int timeDiffDis = timeDifference(line[3], line[5]);
            int timeDiffOn = timeDifference(line[6], line[7]);

            // iterates through every Node in the list and if the callType matches
            // it increments totalCalls if the call is found stop loop to save time
            while (headptr != NULL && callFound == 0 ){
                if (strcmp(headptr->callType, lineCallType) == 0){
                    callFound = 1;
                    
                    
                    
                        headptr->totalCalls++;

                        if(timeDiffDis< 120){
                            headptr->dispatchTimes[0]++;
                        }
                        else if (timeDiffDis>=120 && timeDiffDis <= 300){
                            headptr->dispatchTimes[1]++;
                        }
                        else if (timeDiffDis > 300 && timeDiffDis <= 600){
                            headptr->dispatchTimes[2]++;
                        }
                        else{
                            headptr->dispatchTimes[3]++;
                        }

                        if (timeDiffOn < 120){
                            headptr->onSceneTimes[0]++;
                        }
                        else if (timeDiffOn >= 120 && timeDiffDis <= 300){
                            headptr->onSceneTimes[1]++;
                        }
                        else if (timeDiffOn > 300 && timeDiffDis <= 600){
                            headptr->onSceneTimes[2]++;
                        }
                        else{
                            headptr->onSceneTimes[3]++;
                        }
                        // for each subfield value we are tracking we increment it 
                        // based off on the time in seconds
                        if (strcmp(line[subfieldLoc], subVal1) == 0){
                            if (timeDiffDis < 120){
                                headptr->subVal1DisTime[0]++;
                            }
                            else if (timeDiffDis >=120 && timeDiffDis <= 300){
                                headptr->subVal1DisTime[1]++;
                            }
                            else if (timeDiffDis > 300 && timeDiffDis <= 600){
                                headptr->subVal1DisTime[2]++;
                            }
                            else{
                                headptr->subVal1DisTime[3]++;
                            }

                            if (timeDiffOn < 120){
                                headptr->SubVal1OnTime[0]++;
                            }
                            else if (timeDiffOn >=120 && timeDiffDis <= 300){
                                headptr->SubVal1OnTime[1]++;
                            }
                            else if (timeDiffOn > 300 && timeDiffDis <= 600){
                                headptr->SubVal1OnTime[2]++;
                            }
                            else{
                                headptr->SubVal1OnTime[3]++;
                            }
                        }
                        if (strcmp(line[subfieldLoc], subVal2) == 0)
                        {
                            if (timeDiffDis < 120){
                                headptr->subVal2DisTime[0]++;
                            }
                            else if (timeDiffDis >=120 && timeDiffDis <= 300){
                                headptr->subVal2DisTime[1]++;
                            }
                            else if (timeDiffDis > 300 && timeDiffDis <= 600){
                                headptr->subVal2DisTime[2]++;
                            }
                            else{
                                headptr->subVal2DisTime[3]++;
                            }

                            if (timeDiffOn < 120){
                                headptr->SubVal2OnTime[0]++;
                            }
                            else if (timeDiffOn >=120 && timeDiffDis <= 300){
                                headptr->SubVal2OnTime[1]++;
                            }
                            else if (timeDiffOn > 300 && timeDiffDis <= 600){
                                headptr->SubVal2OnTime[2]++;
                            }
                            else{
                                headptr->SubVal2OnTime[3]++;
                            }
                        }
                        if (strcmp(line[subfieldLoc], subVal3) == 0)
                        {
                            if (timeDiffDis < 120){
                                headptr->subVal3DisTime[0]++;
                            }
                            else if (timeDiffDis >=120 && timeDiffDis <= 300){
                                headptr->subVal3DisTime[1]++;
                            }
                            else if (timeDiffDis > 300 && timeDiffDis <= 600){
                                headptr->subVal3DisTime[2]++;
                            }
                            else{
                                headptr->subVal3DisTime[3]++;
                            }

                            if (timeDiffOn < 120){
                                headptr->SubVal3OnTime[0]++;
                            }
                            else if (timeDiffOn >=120 && timeDiffDis <= 300){
                                headptr->SubVal3OnTime[1]++;
                            }
                            else if (timeDiffOn > 300 && timeDiffDis <= 600){
                                headptr->SubVal3OnTime[2]++;
                            }
                            else{
                                headptr->SubVal3OnTime[3]++;
                            }
                        }

                    
                }
                headptr = headptr->next;
            }
            if (callFound == 0){
                EventData *newNode = createNode(lineCallType);
                insertNode(&head, newNode);
                newNode->totalCalls++;
                // repeating the same time incrementations based on 
                // the difference of time for the first node that gets added in
                if (timeDiffDis < 120){
                    newNode->dispatchTimes[0]++;
                }
                else if (timeDiffDis >= 120 && timeDiffDis <= 300){
                    newNode->dispatchTimes[1]++;
                }
                else if (timeDiffDis > 300 && timeDiffDis <= 600){
                    newNode->dispatchTimes[2]++;
                }
                else{
                    newNode->dispatchTimes[3]++;
                }

                if (timeDiffOn < 120){
                    newNode->onSceneTimes[0]++;
                }
                else if (timeDiffOn >= 120 && timeDiffDis <= 300){
                    newNode->onSceneTimes[1]++;
                }
                else if (timeDiffOn > 300 && timeDiffDis <= 600){
                    newNode->onSceneTimes[2]++;
                }
                else{
                    newNode->onSceneTimes[3]++;
                }
                if (strcmp(line[subfieldLoc], subVal1) == 0){
                    if (timeDiffDis < 120){
                        newNode->subVal1DisTime[0]++;
                    }
                    else if (timeDiffDis >= 120 && timeDiffDis <= 300){
                        newNode->subVal1DisTime[1]++;
                    }
                    else if (timeDiffDis > 300 && timeDiffDis <= 600){
                        newNode->subVal1DisTime[2]++;
                    }
                    else{
                        newNode->subVal1DisTime[3]++;
                    }

                    if (timeDiffOn < 120){
                        newNode->SubVal1OnTime[0]++;
                    }
                    else if (timeDiffOn >= 120 && timeDiffDis <= 300){
                        newNode->SubVal1OnTime[1]++;
                    }
                    else if (timeDiffOn > 300 && timeDiffDis <= 600){
                        newNode->SubVal1OnTime[2]++;
                    }
                    else{
                        newNode->SubVal1OnTime[3]++;
                    }
                }
                if (strcmp(line[subfieldLoc], subVal2) == 0){
                    if (timeDiffDis < 120){
                        newNode->subVal2DisTime[0]++;
                    }
                    else if (timeDiffDis >= 120 && timeDiffDis <= 300){
                        newNode->subVal2DisTime[1]++;
                    }
                    else if (timeDiffDis > 300 && timeDiffDis <= 600){
                        newNode->subVal2DisTime[2]++;
                    }
                    else{
                        newNode->subVal2DisTime[3]++;
                    }

                    if (timeDiffOn < 120){
                        newNode->SubVal2OnTime[0]++;
                    }
                    else if (timeDiffOn >= 120 && timeDiffDis <= 300){
                        newNode->SubVal2OnTime[1]++;
                    }
                    else if (timeDiffOn > 300 && timeDiffDis <= 600){
                        newNode->SubVal2OnTime[2]++;
                    }
                    else{
                        newNode->SubVal2OnTime[3]++;
                    }
                }
                if (strcmp(line[subfieldLoc], subVal3) == 0)
                {
                    if (timeDiffDis < 120)
                    {
                        newNode->subVal3DisTime[0]++;
                    }
                    else if (timeDiffDis >= 120 && timeDiffDis <= 300)
                    {
                        newNode->subVal3DisTime[1]++;
                    }
                    else if (timeDiffDis > 300 && timeDiffDis <= 600)
                    {
                        newNode->subVal3DisTime[2]++;
                    }
                    else
                    {
                        newNode->subVal3DisTime[3]++;
                    }

                    if (timeDiffOn < 120)
                    {
                        newNode->SubVal3OnTime[0]++;
                    }
                    else if (timeDiffOn >= 120 && timeDiffDis <= 300)
                    {
                        newNode->SubVal3OnTime[1]++;
                    }
                    else if (timeDiffOn > 300 && timeDiffDis <= 600)
                    {
                        newNode->SubVal3OnTime[2]++;
                    }
                    else
                    {
                        newNode->SubVal3OnTime[3]++;
                    }
                }
            }
        }
    }
    
    // ***TO DO *** Display Data
    char * times =(" <2  | 3-5 | 6-10 | >10  ");
    printf("%32s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|\n"
    ," ","Total"," ","Total"," ",subVal1," ",subVal1," ",subVal2," ",subVal2," ",subVal3," ",
    subVal3," ");
    printf("%32s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|%20s%5s|\n",
    " ","Dispatch Time"," ","On Scene Time"," ","Dispatch Time"," ","On Scene Time"," ",
    "Dispatch Time"," ","On Scene Time"," ","Dispatch Time"," ","On Scene Time"," ");
    printf("%23s|%8s|%25s|%25s|%25s|%25s|%25s|%25s|%25s|%25s|\n",
    "Call type","Total",times,times,times,times,times,times,times,times);
    for (int i = 0; i < 241; i++) {
        printf("%c", '-');
    }
    printf("\n");

    EventData *headptr = head;
    // sorts using a linked list bubble sort 
    sortNodes(headptr);
    while (headptr != NULL)
    {
        printf("%23s|%8d|%5d|%5d|%6d|%6d|%5d|%5d|%6d|%6d|%5d|%5d|%6d|%6d|%5d|%5d|%6d|%6d|",
            headptr->callType, headptr->totalCalls, headptr->dispatchTimes[0],
            headptr->dispatchTimes[1], headptr->dispatchTimes[2], headptr->dispatchTimes[3],
            headptr->onSceneTimes[0], headptr->onSceneTimes[1], headptr->onSceneTimes[2],
            headptr->onSceneTimes[3],headptr->subVal1DisTime[0], headptr->subVal1DisTime[1],
            headptr->subVal1DisTime[2],headptr->subVal1DisTime[3], headptr->SubVal1OnTime[0], 
            headptr->SubVal1OnTime[1], headptr->SubVal1OnTime[2], headptr->SubVal1OnTime[3]);
        printf("%5d|%5d|%6d|%6d|%5d|%5d|%6d|%6d|%5d|%5d|%6d|%6d|%5d|%5d|%6d|%6d|\n",
            headptr->subVal2DisTime[0], headptr->subVal2DisTime[1],
            headptr->subVal2DisTime[2], headptr->subVal2DisTime[3], headptr->SubVal2OnTime[0],
            headptr->SubVal2OnTime[1], headptr->SubVal2OnTime[2], headptr->SubVal2OnTime[3],
            headptr->subVal3DisTime[0], headptr->subVal3DisTime[1],
            headptr->subVal3DisTime[2], headptr->subVal3DisTime[3], headptr->SubVal3OnTime[0],
            headptr->SubVal3OnTime[1], headptr->SubVal3OnTime[2], headptr->SubVal3OnTime[3]);

        headptr = headptr->next;
    }
    
    //**************************************************************
    // DO NOT CHANGE THIS BLOCK
    //Clock output
    clock_gettime(CLOCK_REALTIME, &endTime);
    time_t sec = endTime.tv_sec - startTime.tv_sec;
    long n_sec = endTime.tv_nsec - startTime.tv_nsec;
    if (endTime.tv_nsec < startTime.tv_nsec)
        {
        --sec;
        n_sec = n_sec + 1000000000L;
        }

    printf("Total Time was %ld.%09ld seconds\n", sec, n_sec);
    //**************************************************************

    // ***TO DO *** cleanup
    csvclose();
    
    }

