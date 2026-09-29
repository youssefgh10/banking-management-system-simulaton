#ifndef DOUBLYLINKEDLISTMETHODS_H
#define DOUBLYLINKEDLISTMETHODS_H
#include "doublylinkedlist.h"
Node* createNode(loan value);
void destroyNode(Node* node);
List createList();
void destroyList(List* L);
bool isEmpty(const List& L);
bool isFull(const List& L);
int listSize(const List& L);
int insert(List* L, loan e, int pos);
int removeAt(List* L, int pos);
loan getElement(const List& L, int pos);
void displayList(const List& L);
List CopyList(const List& L);
bool CompareLists(const List& L1, const List& L2);
#endif 
