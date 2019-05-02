#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//--------------------------------------------------------------------
#define ERROR_IN_FTELL -2
#define ERROR_IN_MEMALLOC -3
#define ERROR_IN_OPENING_FILE -230
#define NOTLETTER 230
//--------------------------------------------------------------------
const int N = 66;
//--------------------------------------------------------------------
int calculate_elements(FILE* file1);
int read_file(FILE* file1, int* num, char* buf);
int count_lines(char* buf, int* trueel);
void change_elements(int* trueel, char* buf);
int divide_text(char* buf, int* trueel, char** text);
int result_text(char** text, int* elems);
int compare_strings(const void* ptr1, const void* ptr2);
int cod_alph(char c);
//--------------------------------------------------------------------
