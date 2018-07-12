#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Graph.h"

typedef struct{
    unsigned int size;
    char **list;
    int *num;
}strlist;

int add_str(strlist *array, char *str)
{
    int len = strlen(str);
    array->size++;
    array->list = (char**)realloc(array->list, sizeof(char*) * array->size);
    array->list[array->size-1]=(char*)malloc(len+1);
    memcpy(array->list[array->size-1], str, len);
    (array->list[array->size-1])[len]=0;
    return array->size;
}

int compute(strlist *array, char *str, int n)  //try to compute ASCII for each character, didn't use
{
    int ACS;
    int len;
    int total = 0;
    len = strlen(str);
    for(int i = 0; i < len; i = i + 1){
        ACS = str[i];
        total = total + ACS;
    }
    array->num[n] = total;
    return array->num[n];
}

void show(strlist *array, Graph g) {
    int i, j;
    for (i = 0; i < g->nV; i++){
        printf("%s:", array->list[i]);
        for (j = i+1; j < g->nV; j++){
            if (g->edges[i][j]){
                printf(" %s", array->list[j]);}
        }
    printf("\n");
    }
}

//Time Complexity: O(m)
int compare_1(strlist *array, int i, int j) {  //compare two words with same length
    int len_A = strlen(array->list[i]);
    int count;
    int sum = 0;
    for (int a = 0; a < len_A; a++) {  // O(m)
        if (array->list[i][a] == array->list[j][a]) {
            count = 0;  // O(m)
        } else {
            count = 1;
        }
           sum += count;  //if the characters in same position is different, sum + 1, O(m)
    }
    return sum; // O(1)
}

//Time Complexity: O(60m) or O(m^2)
int compare_2(strlist *array, int i, int j, int *compare){  //compare two words with different length
    int len_A = strlen(array->list[i]);
    int len_B = strlen(array->list[j]);
    int sum = 0;
    int temp;
    for (int x = 0; x < 20; x++){  // O(20)
        compare[x] = 0;  // O(20)
    }
    for (int a = 0; a < len_A; a++){  // O(m)
        compare[a] = array->list[i][a];  // O(m)
    }
    for (int b = 0; b < len_B; b++){  // O(m)
        int count = 0;
        temp = array->list[j][b];  // O(m)
        for (int c = 0; c < 20; c++) {  // O(20m)
            if (compare[c] == temp) {
                compare[c] = 0;
                count = 1;
                break;
            }
        }
        if (count == 0) {
            for (int c = 0; c < 20; c++) {  // O(20m)
                if (compare[c] == 0) {
                    compare[c] = array->list[j][b];  // O(20m)
                    break;
                }
            }
        }
    }
    for (int x = 0; x < 20; x++){  // O(20)
        if (compare[x] != 0){
            sum += 1;  // O(20)
        }
    }
    return sum;
}

//Time Complexity: O(n)
int search(int *visited, Graph G, int v, int number){
    for(int w = 0; w < number; w = w + 1) {  // O(n)
        if (G->edges[v][w] ==1) {
            if (visited[w] == -1) {
                visited[w] = v;  // O(n)
                if (w == number - 1) {
                    return 1;  // O(n)
                }
                if (search(visited, G, w, number) == 1) {  // O(n^2)
                    return 1;  // O(n)
                }
            }
        } else{
            continue;
        }
    }
    return 0;  // O(1)
}

//Time Complexity: O(n)
int findPath(int *visited, Graph G, int src, int number, int *path){
    int max = 0;
    int n = number-1;
    for(int i = 0; i < number; i = i + 1) {  // O(n)
        visited[i] = -1;  // O(n)
        path[i] = 0;  // O(n)
    }
    visited[src] = src;  // O(1)
    if (search(visited, G, src, number) == 1){
        int v = number-1;
        while (v != src){  // O(n)
            path[n] = v;
            v = visited[v];
            max += 1;
            n -= 1;
        }
        path[n] = -1;
        max += 1;
    }
    else{
        number -= 1;
        max = findPath(visited, G, src, number, path);
    }
    return max;
}

int main() {
    int number;
    int n = 0;
    char word[30];
    int temp;
    strlist *array = NULL;
    printf("Enter a number: ");
    scanf("%d", &number);
    int compare[20];
    int visited[number];
    int path[number];
    array = (strlist *)malloc(sizeof(strlist));
    memset(array, 0, sizeof(strlist));
    array->num = (int*)malloc(number * sizeof(int));
    while (n < number) {
        printf("Enter word: ");
        scanf("%s", word);
        add_str(array, word);
        n ++;
    }
    printf("\n");
    Graph G = newGraph(number);

//Finding following words for each word: same length: O(m * n^2); different length: O(m^2 * n^2)
    for(int i = 0; i < number; i = i + 1) {  // O(n)
        for(int j = i + 1; j < number; j = j + 1) {  // O(n^2)
            if (strlen(array->list[i]) == strlen(array->list[j])){
                temp = (compare_1(array,i,j));  // O(m * n^2)
            }
            else{
                temp = (compare_2(array,i,j,compare));  // O(m^2 * n^2)
            }
            if (temp == 1){
                Edge e;
                e.v = i;
                e.w = j;
                insertEdge(G, e);
            }
        }
    }
    show(array, G);
//Time complexity for task 1:  O(m * n^2)
//Time complexity for task 2:  O(n^3)
    int max = findPath(visited, G, 0, number, path);
    printf("\nMaximum chain length: %d\nMaximal chains:\n", max);
    for(int i = 0; i < number; i = i + 1) {
        if (path[i] == 0) {
            continue;
        }
        if (path[i] == -1) {
            printf("%s", array->list[0]);
        }
        else{
            printf(" -> %s", array->list[path[i]]);
        }
    }
    printf("\n");

    freeGraph(G);
    free(array);
}


