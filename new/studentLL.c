#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "studentLL.h"
#include "studentRecord.h"

// linked list node type
// DO NOT CHANGE
typedef struct node {
    studentRecordT data;
    struct node    *next;
} NodeT;

// linked list type
typedef struct ListRep {
    NodeT *head;
    int number;
    int total;
    float WAM;
    float W_WAM;
/* Add more fields if you wish */

} ListRep;

/*** Your code for stages 2 & 3 starts here ***/
NodeT *p1;

char *Level(NodeT *p) {
    char *level;
    if (p->data.WAM >= 50 && p->data.WAM <65)
        level = "PS";
    else if (p->data.WAM >= 65 && p->data.WAM <75)
        level = "CR";
    else if (p->data.WAM >= 75&& p->data.WAM < 85)
        level = "DN";
    else
        level = "HD";
    return level;
}

// Time complexity: O(1)
// Explanation: 
List newLL() {
    ListRep *new = (ListRep *)malloc(sizeof(ListRep));
    assert(new != NULL);
    new->head = NULL;
    new->number = 0;
    new->WAM = 0;
    new->W_WAM = 0;
    new->total = 0;
   return new;  /* needs to be replaced */
}

// Time complexity: O(n)
// Explanation: 
void dropLL(List listp) {
    NodeT *p;
    p = listp->head;
    while (p != NULL){
        NodeT *temp = p->next;
        free(p);
        p = temp;
    }/* needs to be replaced */
}

// Time complexity: O(n)
// Explanation: 
void inLL(List listp, int zid) {
    int n = 0;
    NodeT *p;
    p = listp->head;
    char *level;
    while(p != NULL){
        level = Level(p);
        if (p->data.zID == zid){
            printf("------------------------\n");
            printf("Student zID: z%d\n", p->data.zID);
            printf("Credits: %d\n", p->data.credits);
            printf("Level of performance: %s\n",  level);
            printf("------------------------\n");
            n = 1;
            break;}
         p = p->next;}
    if (n != 1)
        printf("No record found.\n");
}

// Time complexity: O(1)
// Explanation: 
void insertLL(List listp, int zid, int cr, float wam) {
    listp->number += 1;
    if (listp->head == NULL){
        listp->head = (NodeT *)malloc(sizeof(NodeT));
        listp->head->data.zID = zid;
        listp->head->data.credits = cr;
        listp->head->data.WAM = wam;
        listp->WAM += wam;
        listp->W_WAM += (cr * wam);
        listp->total += cr;
        listp->head->next = NULL;
    }
    else{
        NodeT *p = listp->head;
        while(p != NULL){
            if (p->data.zID == zid){
                p->data.credits = cr;
                p->data.WAM = wam;
                printf("Student record updated.\n");
                return;
            }
            p = p->next;
        }








        NodeT *new = (NodeT *)malloc(sizeof(NodeT));
        new->data.zID = zid;
        new->data.credits = cr;
        new->data.WAM = wam;
        listp->WAM += wam;
        listp->W_WAM += (cr * wam);
        listp->total += cr;
        new->next = listp->head;
        listp->head = new;}

        /*NodeT *p;
        p = listp->head;
        while (p->next != NULL){
            p = p->next;
        }
        p->next = (NodeT *)malloc(sizeof(NodeT));
        p = p->next;
        p->data.zID = zid;
        p->data.credits = cr;
        p->data.WAM = wam;
        p->next = NULL;}*/
}

// Time complexity: O(n)
// Explanation: 
void getStatLL(List listp, int *n, float *wam, float *w_wam) {
    *n = listp->number;
    *wam = listp->WAM/listp->number;
    *w_wam = listp->W_WAM/listp->total;
}


// Time complexity:O(n)
// Explanation: 
void showLL(List listp) {
    NodeT *p;
    p = listp->head;
    char *level;
    while (p != NULL){
        level = Level(p);
        printf("------------------------\n");
        printf("Student zID: z%d\n", p->data.zID);
        printf("Credits: %d\n", p->data.credits);
        printf("Level of performance: %s\n",  level);
        printf("------------------------\n");
        p = p->next;}
}

