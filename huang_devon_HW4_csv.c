/**************************************************************
* Class::  CSC-415-0# Spring 2024
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

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "assignment4.h"


FILE *file;
int lineNum = 0;
char **header;
int colms;

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

    colms = 1;

    //replaces double quotes with @, ill change it to a single quote after
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"' && buffer[i + 1] == '"') {
            buffer[i] = '@';
            memmove(&buffer[i + 1], &buffer[i + 2], strlen(&buffer[i + 2]) + 1); // Remove the second quote
        }
    }
    
    for (int i = 0; buffer[i] != '\0'; i++) {
        // treat string inside of "'s as one, so ignores ,'s
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

    // Parse header line
    int header_index = 0;
    char *start = buffer;
    char *end = buffer;
    while (*end != '\0') {
        if (*end == '"') {
            start++;
            end++; // Skip the starting quote
            while (*end != '"' && *end != '\0') {
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
            *end = '\0'; // Null-terminate the current field
            header[header_index] = start; // Assign the current field to the header array
            header_index++;
            start = end + 1; // Move start pointer to the next character after the comma or '\0'
        }

        end++;
    }

    header[header_index++] = start;
    header[header_index] = NULL; // Null-terminate the header array
    return header;
}

// Function to parse the next line from the CSV file
char ** csvnext (){
    if (file == NULL) {
        return NULL;
    }

    // Read the next line from the file
    char buffer[BUFFERSIZE]; // assuming a maximum line size of BUFFERSIZE characters
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        return NULL; // return NULL if end of file is reached
    }

    // Allocate memory for the row data
    char **row = (char **)malloc(colms * sizeof(char *));
    if (row == NULL) {
        return NULL; // return NULL on failure
    }

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"' && buffer[i + 1] == '"') {
            buffer[i] = '@';
            memmove(&buffer[i + 1], &buffer[i + 2], strlen(&buffer[i + 2]) + 1); // Remove the second quote
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
            *end = '\0'; // Null-terminate the current field

            row[row_index] = start; // Assign the current field to the row array
            row_index++;
            start = end + 1; // Move start pointer to the next character after the comma or '\0'
        }

        end++;
    
    }
        
    row[row_index] = start;
    row_index++;
    row[row_index] = NULL; // Null-terminate the row array

    return row;    
}

char ** csvheader (){
    return header;

}

int csvclose (){
    for (int i = 0; i < colms; i++) {
        free(header[i]);
    }
    free(header);
    fclose(file);


    return lineNum;
}