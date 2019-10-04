//
//  main.c
//  graph
//
//  Created by REAL CYH on 9/30/19.
//  Copyright © 2019 REAL CYH. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node{
    int index;
    double weight;
    struct Node *next;
} Node;

double rand_double( double a, double b) {
    double randNum;
    srand((unsigned)time(NULL));
    if (a !=b ) {
        randNum = rand()/(double)(RAND_MAX)/(b-a)+a;
    } else {
        randNum = a;
    }
        
    return randNum;
}

Node *list_creat() {
    Node *first;
    first = malloc(sizeof(Node));
    first->next = NULL;
    
    return first;
}

int list_insert(Node * list, int index, double weight) {
    Node *newNode;
    Node *p;
    newNode = malloc(sizeof(Node));
    newNode->index = index;
    newNode->weight = weight;
    newNode->next = NULL;
    for (p=list; p->next != NULL; p=p->next){
        ;
    }
    p->next = newNode;
    return 1;
}


void list_print(Node *list) {
    Node *p;
    for (p=list; p->next != NULL; p=p->next) {
        printf("node index = %d, weight = %lf\n", p->next->index, p->next->weight);
    }
}

int list_count(Node *list) {
    Node *p;
    int cnt = 0;
    for (p=list; p->next != NULL; p=p->next) {
        cnt++;
    }
    return cnt;
}

Node *list_free(Node *list) {
    if (list == NULL) {
    } else if (list->next == NULL) {
        free(list);
    } else {
        while (list->next) {
            Node *p = list->next;
            list->next = list->next->next;
            free(p);
        }
        free(list);
        //free(list->next);
    }
    list = NULL;
    return list;
}



int main(int argc, const char * argv[]) {
    
    FILE *fpWriteHis;
    FILE *fpWriteTop;
    
    fpWriteHis = fopen("histo.txt", "w");
    fpWriteTop = fopen("topology.txt", "w");
    
    
    int N = 100;
    double w1 = 1;
    double w2 = 1;
    double randNum;
        
    Node *A[N];
    int d[N];
    double p[N];
    int dSum = 0;
    int i, j;
    for (i=0; i<N; i++) {
        A[i] = list_creat();
    }
    for (i=0; i<N; i++) {
        d[i] = 0;
        p[i] = 0;
        dSum += d[i];
    }
    //n0=3, initialize
    double weight0_1, weight0_2, weight1_2;
    weight0_1 = rand_double(w1, w2);
    weight0_2 = rand_double(w1, w2);
    weight1_2 = rand_double(w1, w2);
    
    list_insert( A[0], 1, weight0_1);
    list_insert( A[0], 2, weight0_2);
    d[0] = list_count(A[0]);
    list_insert( A[1], 0, weight0_1);
    list_insert( A[1], 2, weight1_2);
    d[1] = list_count(A[1]);
    list_insert( A[2], 0, weight0_2);
    list_insert( A[2], 1, weight1_2);

    d[2] = list_count(A[2]);
    for (i=0; i<3; i++) {
        dSum += d[i];
    }
    //printf("dSum=%d\n", dSum);
//    for (i=0; i<3; i++) {
//        p[i] = d[i]*1.0/dSum;
//    }

    int index = 0;
    for (i=3; i<N; i++) {
        p[0] = d[0];
        for (j=1; j<i; j++) {
            p[j] = p[j-1] + d[j];
            //printf("%lf", p[j]);
        }
        for (j=0; j<i; j++) {
            p[j] /= dSum;
            //printf("%lf", p[j]);
        }
        srand((unsigned)time(NULL));
        randNum = rand()/(double)(RAND_MAX);
        printf("%lf\n", randNum);
        for (j=0; j<i; j++) {
            if (p[j]<randNum) {
                index = j+1;
                //printf("%d\n", index);
            }
        }
        double weight = rand_double(w1, w2);
        list_insert(A[index], i, weight);
        list_insert(A[i], index, weight);
        d[i]++;
        d[index]++;
        dSum += 2;
    }

    
    
    list_print(A[0]);
//    list_print(A[1]);
//    list_print(A[2]);
//    printf("\n");
//    list_print(A[4]);
    
    Node *fp;
    for (i=0; i<N; i++) {
        fprintf(fpWriteTop, "%d  ", i);
        for (fp=A[i]; fp->next != NULL; fp=fp->next) {
            fprintf(fpWriteTop,"%d %lf  ", fp->next->index, fp->next->weight);
        }
        fprintf(fpWriteTop, "\n");
    }
    
    int his[N];
    int cnt = 0;
    int cntAll = 0;
    for (i=0; i<N; i++) {
        his[i] = list_count(A[i]);
        // printf("%d ", his[i]);
    }
    for (i=1; i<N; i++) {
        cnt = 0;
        for (j=0; j<N; j++) {
            if (his[j] == i) {
                cnt++;
                cntAll++;
            }
        }
        fprintf(fpWriteHis, "%d %d ", i, cnt);
        for (j=0; j<N; j++) {
            if (his[j] == i) {
                fprintf(fpWriteHis, "%d ", j);
            }
        }
        fprintf(fpWriteHis, "\n");
        if (cntAll == N) break;
    }
    
    for (i=0; i<N; i++) {
        A[i] = list_free(A[i]);
    }
//    for (i=0; i<N; i++) {
//        printf("%p ", A[i]);
//    }
//
    printf("git first try!\n");
    
    return 0;
}

