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
#include "assignment4.h"



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

    // this is to find which subfield the user choose, police district or neighborhood
    for(int i =0; i<colms; i++){
         if (strcmp(header[i], subfield) == 0) {
            subfieldLoc = i;
            break; 
        }
    }
    // printf("\n\n%s",header[subfieldLoc]);
    // for(int i =0; i<colms;i++){
    //     printf("\n%02d : %s",i,header[i]);
    // }
    for(int i =0; i<colms;i++){
        printf("\n%02d : %s",i,line[i]);
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
    EventData *head = NULL;
    char **currLine;
    
    while((currLine = csvnext() )!= NULL){
        //if police district is argv[4], argv[5] or argv[6];
        if(strcmp(currLine[subfieldLoc], subVal1) == 0 ){
            

        }
        if(strcmp(currLine[subfieldLoc], subVal2) == 0 ){
            
        }
        if(strcmp(currLine[subfieldLoc], subVal3) == 0 ){
            
        }
        
    }
    printf("%d\n%d\n%d\n",count1,count2,count3);
    // if((currLine[13] || currLine[10]) != ""){
    //         printf("%s",currLine[13]);

    //     }



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

    printf("%23s|%8s|%5s|%5s|%6s|%6s|%5s|%5s|%6s|%6s|%5s|%5s|%6s|%6s|%5s|%5s|%6s|%6s|",
    " "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ");
    printf("%5s|%5s|%6s|%6s|%5s|%5s|%6s|%6s|%5s|%5s|%6s|%6s|%5s|%5s|%6s|%6s|\n"
    ," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ");
    

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

