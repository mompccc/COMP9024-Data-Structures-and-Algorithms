/**
     main.c

     Program supplied as a starting point for
     Assignment 1: Student record manager

     COMP9024 17s2
**/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "studentRecord.h"
#include "studentLL.h"

void printHelp();
void StudentLinkedListProcessing();


int main(int argc, char *argv[]) {
    if (argc == 2) {
        int n = atoi(argv[1]);
        float average = 0;
        float weight = 0;
        int score = 0;
        studentRecordT *array = NULL;
        array = (studentRecordT *)malloc(n * sizeof(studentRecordT));
        for(int i = 0; i<n; i=i+1){
            array[i].zID = readValidID();
            array[i].credits = readValidCredits();
            array[i].WAM = readValidWAM();
        }
        for(int i = 0; i<n; i=i+1) {
            printStudentData(array[i].zID, array[i].credits, array[i].WAM);
        }
        for(int i = 0; i<n; i=i+1) {
            average = average + array[i].WAM;
            score = score + array[i].credits;
            weight = weight + (array[i].credits * array[i].WAM);
        }
        printf("Average WAM: %.3f\nWeighted average WAM: %.3f\n", average/n, weight/score);
        free(array);
      /*** Insert your code for stage 1 here ***/
      
   } else {
       StudentLinkedListProcessing();
   }
   return 0;
}

/* Code for Stages 2 and 3 starts here */

void StudentLinkedListProcessing() {
   int op, ch, zID, credits;
   float WAM;
   int size;
   float wam;
   float a_wam;

   List list = newLL();   // create a new linked list
   while (1) {
      printf("Enter command (a,f,g,p,q, h for Help)> ");

      do {
	 ch = getchar();
      } while (!isalpha(ch) && ch != '\n');  // isalpha() defined in ctype.h
      op = ch;
      // skip the rest of the line until newline is encountered
      while (ch != '\n') {
	 ch = getchar();
      }

      switch (op) {

         case 'a':
         case 'A':
             zID = readValidID();
             credits = readValidCredits();
             WAM = readValidWAM();
             insertLL(list, zID, credits, WAM);
             printf("Student record added.\n");
            /*** Insert your code for adding a student record ***/

	    break;

         case 'f':
         case 'F':
             zID = readValidID();
             inLL(list, zID);
            /*** Insert your code for finding a student record ***/

	    break;

         case 'g':
         case 'G':
             getStatLL(list, &size, &wam, &a_wam);
             printf("Number of records: %d\n", size);
             printf("Average WAM: %.3f\nAverage weighted WAM: %.3f\n", wam, a_wam);
            /*** Insert your code for getting statistical information ***/

	    break;

         case 'h':
         case 'H':
            printHelp();
	    break;

         case 'p':
         case 'P':
             showLL(list);
            /*** Insert your code for printing all student records ***/

	    break;

	 case 'q':
         case 'Q':
            dropLL(list);       // destroy linked list before returning
	    printf("Bye.\n");
	    return;
      }
   }
}

void printHelp() {
   printf("\n");
   printf(" A - Add student record\n" );
   printf(" F - Find student record\n" );
   printf(" G - Get statistics\n" );
   printf(" H - Help\n");
   printf(" P - Print all records\n" );
   printf(" Q - Quit\n");
   printf("\n");
}