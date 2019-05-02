#include "consts_and_prototips.h"
int main()
{
    int trueel = 0;
    int lines = 0;
    int elems = 0;
    int num = 0;
    FILE* file1;
    file1 = fopen("Onegin.txt", "r");
    if (file1 == NULL)
    {
        printf("Cannot open file1.txt");
        return ERROR_IN_OPENING_FILE;
    }
    num = calculate_elements(file1);
    char* buf = (char*) calloc(num + 1, sizeof(char));
    trueel = read_file(file1, &num, buf);
    lines = count_lines(buf, &trueel);
    change_elements(&trueel, buf);
    char** text = (char**)calloc(lines, sizeof(char*));
    if (text == NULL)
    {
        printf("Failed to allocate the memory for text");
        return ERROR_IN_MEMALLOC;
    }
    elems = divide_text(buf, &trueel, text);
    qsort(text, elems, sizeof(char*), compare_strings);
    result_text(text, &elems);
    fclose(file1);
    free(buf);
    free(text);
    return 0;
}
//------------------------------------------------------------------------
int calculate_elements(FILE* file1)
{
    int num = 0;
    fseek(file1, 0, SEEK_END);
    num = ftell(file1);
    if (num == -1)
    {
        printf("ERROR\n");
        return ERROR_IN_FTELL;
    }
    rewind(file1);
    return num;
}
//-----------------------------------------------------------------------
int read_file(FILE* file1, int* num, char* buf)
{
    int trueel = 0;
    trueel = fread(buf, sizeof(char), *num, file1);
    buf[*num] = '\n';
    trueel = trueel + 1;
    fclose(file1);
    return trueel;
}
//------------------------------------------------------------------------
int count_lines(char* buf, int* trueel)
{
    int lines = 0;
    for (int i = 0; i < *trueel; i++)
    {
        if (buf[i] == '\n')
        {
            lines = lines + 1;
        }
    }
    return lines;
}
//-----------------------------------------------------------------------
void change_elements(int* trueel, char* buf)
{
    for (int j = 0; j < *trueel; j++)
    {
        if (buf[j] == '\n')
        {
            buf[j] = '\0';
            while(buf[j + 1] == '\n')
            {
                if (buf[j + 2] != '\n')
                {
                    buf[j + 1] = '\0';
                }
                else
                {
                     j++;
                }
            }
        }
    }
}
//-----------------------------------------------------------------------------
int divide_text(char* buf, int* trueel, char** text)
{
    text[0] = &buf[0];
    int elem = 1;
    for (int i = 0; i < *trueel; i++)
    {
        if (buf[i] == '\0')
        {
             while(buf[i + 1] == '\n' && buf[i + 1] != '\0')
             {
                 i++;
             }
             text[elem] = &buf[i + 1];
             elem++;
        }
    }
    return elem;
}
//-----------------------------------------------------------------------------------------------
int cod_alph(char  c)
{
    char* alph = {"ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ"};
    for (int i = 0; i < N; i++)
    {
        if (c == alph[i])
        {
            return i + 1;
        }
    }
    return NOTLETTER;
}
//-----------------------------------------------------------------------------------------------
int compare_strings(const void* ptr1, const void* ptr2)
{
    int i = 0;
    int j = 0;
    char* str1 = *((char**)ptr1);
    char* str2 = *((char**)ptr2);
    while(*(str1 + i) != '\0' || *(str2 + j) != '\0')
    {
        while (cod_alph(*(str1 + i)) == NOTLETTER)
        {
            i++;
        }
        while (cod_alph(*(str2 + j)) == NOTLETTER)
        {
            j++;
        }

        if (cod_alph(*(str1 + i)) != cod_alph(*(str2 + j)))
        {
            return cod_alph(*(str1 + i)) - cod_alph(*(str2 + j));
        }
        i++;
        j++;
    }
}
//---------------------------------------------------------------------------------------------------------
int result_text(char** text, int* elems)
{
    FILE* file2;
    file2 = fopen("Result.txt", "w");
    if (file2 == NULL)
    {
        printf("Cannot open file2.txt");
        return ERROR_IN_OPENING_FILE;
    }
    for (int j = 0; j < *elems; j++)
    {
         fprintf(file2, "%s\n", text[j]);
    }
    fclose(file2);
}



