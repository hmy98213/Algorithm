//
//  main.cpp
//  test_data_structure
//
//  Created by 黄鸣宇 on 2017/4/30.
//  Copyright © 2017年 黄鸣宇. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct PolyNode *Polynomial;
struct PolyNode{
    int coef;
    int expon;
    Polynomial link;
};

void Attach(int c,int e,Polynomial *pRear);
Polynomial ReadPoly();
int Compare(int a,int b);
Polynomial PolyAdd (Polynomial P1, Polynomial P2);
Polynomial Mult(Polynomial P1,Polynomial P2);
void PrintPoly( Polynomial P );    /* 输出多项式 */

int main(int argc, const char * argv[]) {
    Polynomial P1, P2, PP, PS;
    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Mult( P1, P2 );
    PrintPoly( PP );
    PS = PolyAdd( P1, P2 );
    PrintPoly( PS );
    return 0;
}
void Attach(int c,int e,Polynomial *pRear)
{
    Polynomial P;
    P=(Polynomial)malloc(sizeof(struct PolyNode));
    P->coef=c;
    P->expon=e;
    P->link=NULL;
    (*pRear)->link=P;
    *pRear=P;
}
Polynomial ReadPoly()
{
    int N;
    scanf("%d",&N);
    int c,e;
    Polynomial Rear;
    Polynomial P,t;
    P=(Polynomial)malloc(sizeof(PolyNode));
    P->link=NULL;
    Rear=P;
    while (N--) {
        scanf("%d%d",&c,&e);
        Attach(c,e,&Rear);
    }
    t=P;
    P=P->link;
    free(t);
    return P;
}
int Compare(int a,int b)
{
    if (a==b) {
        return 0;
    }
    else if(a>b){
        return 1;
    }
    else{
        return -1;
    }
}
Polynomial PolyAdd (Polynomial P1, Polynomial P2)
{
    Polynomial front, rear, temp;
    int sum;
    rear = (Polynomial) malloc(sizeof(struct PolyNode));
    front = rear; /* 由front 记录结果多项式链表头结点 */
    while ( P1 && P2 ) /* 当两个多项式都有非零项待处理时 */
        switch ( Compare(P1->expon, P2->expon) ){
            case 1:
            Attach( P1->coef, P1->expon, &rear);
            P1 = P1->link;
            break;
        case -1:
            Attach(P2->coef, P2->expon, &rear);
            P2 = P2->link;
            break;
        case 0:
            sum = P1->coef + P2->coef;
            if ( sum ) {Attach(sum, P1->expon, &rear);}
            P1 = P1->link;
            P2 = P2->link;
            break;
    }
    /* 将未处理完的另一个多项式的所有节点依次复制到结果多项式中去 */
    for ( ; P1; P1 = P1->link ) Attach(P1->coef, P1->expon, &rear);
    for ( ; P2; P2 = P2->link ) Attach(P2->coef, P2->expon, &rear);
    rear->link = NULL;
    temp = front;
    front = front->link; /*令front指向结果多项式第一个非零项 */
    free(temp); /* 释放临时空表头结点 */
    return front;
}
Polynomial Mult(Polynomial P1,Polynomial P2)
{
    Polynomial P,Rear,t1,t2,t;
    int c,e;
    if ((!P1) || (!P2)) {
        return NULL;
    }
    t1=P1;t2=P2;
    P=(Polynomial)malloc(sizeof(PolyNode));
    P->link=NULL;
    Rear=P;
    while (t2) {
        Attach(t1->coef*t2->coef, t1->expon+t2->expon, &Rear);
        t2=t2->link;
    }
    t1=t1->link;
    while (t1) {
        t2=P2;Rear=P;
        while (t2) {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while (Rear->link && Rear->link->expon>e) {
                Rear=Rear->link;
            }
            if (Rear->link && Rear->link->expon == e) {
                if (Rear->link->coef + c)
                    Rear->link->coef += c;
                else {
                    t = Rear->link;
                    Rear->link = t->link;
                    free(t);
                }
            }
            else{
                t = (Polynomial)malloc(sizeof(struct PolyNode));
                t->coef = c;
                t->expon = e;
                t->link = Rear->link;
                Rear->link = t;
                Rear = Rear->link;
            }
            t2 = t2->link;
        }
        t1=t1->link;
    }
    t2 = P; P = P->link; free(t2);
    return P;
}
void PrintPoly( Polynomial P )    /* 输出多项式 */
{
    /* 输出多项式 */
    int flag = 0;
    if (!P) {printf("0 0\n"); return;}
    while ( P ) {
        if (!flag)
            flag = 1;
        else
            printf(" ");
        /* 辅助调整输出格式用 */
        printf("%d %d", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}
