/**************************************************************
 * Class::  CSC-415-01 Spring 2024
 * Name::Devon Huang
 * Student ID::916940666
 * GitHub-Name::Novedh
 * Project:: Assignment 4 – Processing CSV Data with Threads
 *
 * File:: huang_devon_HW4_csv.c
 *
 * Description:: This program is for parsing the csv file into
 * arrays of strings. One for the header, the first line of the csv
 * then one that loaded in the next line in the csv.
 *
 **************************************************************/



#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <assignment4.h>
#include <pthread.h>

pthread_mutex_t prevmutex;
FILE *file;
int lineNum = 0;
char **header;
int colms;
char **prevRow = NULL;



char ** csvopen (char * filename){
    file = fopen(filename, "r");
    if (file == NULL) {
        return NULL; // return NULL on failure
    }

    // Read the header 
    char buffer[BUFFERSIZE]; 
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        return NULL;
    }

    // Replaces double quotes with @ as a place holder, I'll change it
    // to a single quote during parsing
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"' && buffer[i + 1] == '"') {
            buffer[i] = '@';
            // Remove the second quote
            memmove(&buffer[i + 1], &buffer[i + 2], strlen(&buffer[i + 2]) + 1); 
        }
    }

    colms = 1;
    // this counts the colms in header by counting commas and ignoring the commas that are 
    // imbedded in double quotes

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"' ) {
            i++;
            while(buffer[i]!='"'){
                i++;
            }
        }
        if (buffer[i] == ',') {
            colms++;
        }

    }

    // Allocate memory for header
    header = (char **)malloc(colms * sizeof(char *));
    if (header == NULL) {
        fclose(file);
        return NULL;
    }

    // Parse header line by using two pointers, the end pointer will imcrement until
    // it reaches one of the conditions then if it reaches the end of the read or
    // a comma it will add it to our header vector
    int header_index = 0;
    char *start = buffer;
    char *end = buffer;
    while (*end != '\0') {
        if (*end == '"') {
            start++;
            end++; // Skip the starting quote
            while (*end != '"' && *end != '\0') {
                // reverting double quotes to single
                if(*end == '@'){
                    *end = '"';
                }
                end++; // Skip until the ending quote
            }
            if (*end == '"') {
                end++; // Skip the ending quote
                end[-1]='\0';
            }
        }
        if (*end == ',' || *end == '\0') {
            *end = '\0'; // Null-terminate the current column
            header[header_index] = (char *)malloc((end - start + 1) * sizeof(char));
            if (header[header_index] == NULL) {
                for (int j = 0; j < header_index; j++) {
                    free(header[j]);
                }
                free(header);
                return NULL; // return NULL on failure
            }
            strcpy(header[header_index], start); // Assign the current column to the header array
            header_index++;
            start = end + 1; // Move start pointer to the next character after the comma or '\0'
        }

        end++;
    }
    // This is allocating and assigning the last column to the header array
    // because it was skipped
    header[header_index] = (char *)malloc((end - start + 1) * sizeof(char));
    if (header[header_index] == NULL) {
        for (int j = 0; j < header_index; j++) {
            free(header[j]);
        }
        free(header);
        return NULL; // return NULL on failure
    }
    strcpy(header[header_index], start); 
    header_index++;
    header[header_index] = '\0'; // Null-terminate the header array
    return header;
}

// Function to parse the next line from the CSV file
char ** csvnext (){
    if (file == NULL) {
        return NULL;
    }

    // Read the next line from the file
    char buffer[BUFFERSIZE]; 
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        return NULL; // return NULL if end of file is reached
    }
    
    // this counts how many double quotes are in the buffer, if it is a odd number
    // then that means a double quote hasnt been closed and it will read the next line
    // from the csv file in to tempBuffer and add it onto our buffer until every double quote 
    // has been close with another double quote
    int doubQuoteCount = 0;
    for(int i =0; i<strlen(buffer) ; i++){
        if(buffer[i] == '"'){
            doubQuoteCount++;
        }
    }
    while((doubQuoteCount%2) != 0){
        char tempBuffer[BUFFERSIZE];
        if (fgets(tempBuffer, sizeof(buffer), file) == NULL) {
            return NULL; // return NULL if end of file is reached
        }
        for(int i =0; i<strlen(tempBuffer) ; i++){
            if(tempBuffer[i] == '"'){
                doubQuoteCount++;
            }
        }
        int lenBuffer = strlen(buffer);
        int lenTempBuffer = strlen(tempBuffer);
        for(int i = 0; i < lenTempBuffer;i++){
            buffer[lenBuffer + i] = tempBuffer[i];
        }
        buffer[lenBuffer+lenTempBuffer] = '\0';
        
    }
    // DIDNT WORK
    // Locked so multiple threads wouldnt be accessing/ freeing pre_row
    // becasue it is global
    // i am trying to using prevRow to clear some memory 
    // pthread_mutex_lock(&prevmutex);
    
    // if (prevRow != NULL)
    // {
    //     for (int i = 0; i < colms; i++)
    //     {
    //         free(prevRow[i]);
    //     }
    //     free(prevRow);
        
    // }

    // Allocate memory for the row data
    char **row = (char **)malloc((colms) * sizeof(char *));
    if (row == NULL) {
        return NULL; // return NULL on failure
    }

    // same as in the header replaces two double quotes with @ as a temp place holder
    // to be replace with a single " in parsing
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"' && buffer[i + 1] == '"') {
            buffer[i] = '@';
            memmove(&buffer[i + 1], &buffer[i + 2], strlen(&buffer[i + 2]) + 1); 
        }
    }

    // Parse the row line
    int row_index = 0;
    char *start = buffer;
    char *end = buffer;
    while (*end != '\0') {
        if (*end == '"') {
            start++;
            end++; // Skip the starting quote
            while (*end != '"' && *end != '\0') {
                // replace @ place holder with single quote
                if(*end == '@'){
                    *end = '"';
                }
                end++; // Skip until the ending quote
            }
            if (*end == '"') {
                end++; // Skip the ending quote 
                end[-1]='\0';
            }
        }
        if (*end == ',' || *end == '\0') {
            *end = '\0'; // Null-terminate the current column
            row[row_index] = (char *)malloc((end - start + 1) * sizeof(char));
            if (row[row_index] == NULL) {
                for (int j = 0; j < row_index; j++) {
                    free(row[j]);
                }
                free(row);
                return NULL; // return NULL on failure
            }
            strcpy(row[row_index], start); // Assign the current column to the row array
            row_index++;
            
            start = end + 1; // Move start pointer to the next character after the comma or '\0'
        }
        
        end++;
    
    }

    // allocating the last column and assigning it to row
    row[row_index] = (char *)malloc((end - start + 1) * sizeof(char));
    if (row[row_index] == NULL) {
        for (int j = 0; j < row_index; j++) {
            free(row[j]);
        }
        free(row);
        return NULL; // return NULL on failure
    }

    strcpy(row[row_index], start); 
    row_index++;
    row[row_index] = '\0'; // Null-terminate the row array
    // keeping track of how many lines are read for our csvclose to return
    lineNum++;
    // DIDNT WORK
    // prevRow = row;
    // pthread_mutex_unlock(&prevmutex);
    return row;    
}

char ** csvheader (){
    return header;
}

int csvclose (){
    if (file != NULL) {
        if(fclose(file) != 0){
            return -1;
        }
    }
    
    for (int i = 0; i < colms; i++) {
            free(header[i]);
    }

    free(header);
    return lineNum;
}