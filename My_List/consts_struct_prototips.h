#include <stdio.h>
#include <stdlib.h>
//--------------------------------------------------
#define ERROR_IN_NODE 230
#define ERROR_NO_SUCH_NODE -230
#define ERROR_ANOTHER_FUNCT 100
#define ERROR_IN_LIST 150
//--------------------------------------------------
struct Node{
    int data;
    Node* next;
    Node* prev;

};
struct List{
    int size_n;
    Node* head;
    Node* tail;
};
List* create_list();
Node* create_node(List* elem, int data);
void push_in_back(List* elem, Node* n1);
void push_in_front(List* elem, Node* n3);
void print_list(List* elem);
int insert_after(Node* after, int data, List* elem);
int delete_node(Node* cur, List* elem);
void delete_list(List* elem);
Node* search_by_data(int inf, List* elem);
#include "functions.cpp"
