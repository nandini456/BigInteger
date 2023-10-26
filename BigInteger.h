#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1001

struct node {
    int data;
    struct node* next;
};

struct BigInteger {
    struct node* l;
    int length;
    int sign;
};

struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
struct BigInteger mod(struct BigInteger a, struct BigInteger b);
struct BigInteger truncate(struct BigInteger n);
void addAtEnd(struct node** head, int data);
void addatfront(struct node** n1, int data);
struct node* addition(struct node* p1, struct node* p2);
struct BigInteger initialize(char* s);
struct node* rev(struct node* head);
void display(struct BigInteger n1);
int length(struct node* head);
int compare(struct node* a, struct node* b);
struct node* newnode(int data);

#endif
