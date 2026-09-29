#ifndef SINGLYLINKEDLISTMETH_H
#define SINGLYLINKEDLISTMETH_H

#include "singlylinkedlist.h"



Node1* createNode3(transaction value);
void destroyNode3(Node1* node);
List1 createList3();
void destroyList3(List1* L);
bool isEmpty3(const List1& L);
bool isFull3(const List1& L);
int listSize3(const List1& L);
int insert3(List1* L, transaction e, int pos);
int removeAt3(List1* L, int pos);
transaction getElement3(const List1& L, int pos);
void displayList3(const List1& L);
List1 CopyList3(const List1& L);
bool CompareLists3(const List1& L1, const List1& L2);
int insertAtEnd3(List1* L, const transaction& e);
#endif 
