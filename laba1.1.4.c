#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//--------------------------------------------------------------------------------------------
#define error_in_file -1
#define error_in_memalloc -2
//--------------------------------------------------------------------------------------------
const int N = 199;
const int R = 99;
const int S1 = 10;
const int S2 = 40;
const double Tolerance = 3e-8;
const double MinValue = 0.0;
const double MaxValue = 80.0;
//-------------------------------------------------------------------------------------------
void read_data(double* Data, FILE* file, FILE* file2);
void write_data(double Res[], double Data[], FILE* file2);
void calculate_sred(double Data[], FILE* file2, const int size, const int seconds);
void rms_error(double Data[], FILE*file2, double n_0, const int size, const int seconds);
int consider_tolerance(double x);

//-------------------------------------------------------------------------------------------
int main ()
{
    int size1 = N;
    int size2 = R;
    int second1 = S1;
    int second2 = S2;
    int n_0 = 0.0;

    FILE* file = fopen ("input.txt", "r");
    if(file == NULL)
    {
        printf("Cannot open input.txt");
        return error_in_file;
    }
    FILE* file2 = fopen ("result.txt", "w");
    if(file2 == NULL)
    {
        printf("Cannot open result.txt");
        return error_in_file;
    }

    double* Data = (double*) calloc(N, sizeof(double));
    if (Data == NULL)
    {
        printf("Failed to allocate the memory for Data");
        return error_in_memalloc;
    }
    else
    {
        memset(Data, 0, N * sizeof(double));
    }

    double* Res = (double*) calloc(R, sizeof(double));
    if (Res == NULL)
    {
        printf("Failed to allocate the memory for Res");
        return error_in_memalloc;
    }
    else
    {
        memset(Res, 0, R * sizeof(double));
    }

    read_data(Data, file, file2);
    write_data(Res, Data, file2);
    calculate_sred(Data, file2, size1, second1);
    rms_error(Data, file2, n_0, size1, second1);
    calculate_sred(Res, file2, size2, second2);
    rms_error(Res, file2, n_0, size2, second2);

    free(Data);
    free(Res);

    fclose(file);
    fclose(file2);

    return 0;
}
int consider_tolerance(double x)
{
   if (x > MinValue - Tolerance && x < MaxValue - Tolerance)
   {
       return 0;
   }
   else
   {
       return -1;
   }
}
void read_data(double* Data, FILE* file, FILE* file2)
{
    int i = 0;
    fprintf(file2, "The number of counter hits in 10 seconds : \n");
    while(fscanf(file, "%lg", &Data[i]) != EOF)
    {
        if (i % 10 == 9)
        {
            fprintf(file2, "%5lg\n", Data[i]);
        }
        else
        {
            fprintf(file2, "%5lg", Data[i]);
        }
        i++;
    }
}
void write_data(double Res[], double Data[], FILE* file2)
{
    int j = 0;
    fprintf(file2, "The number of counter hits in 40 seconds : \n");
    for (int i = 0; i < N; i++)
    {
        Res[j] = Data[i] + Data[i + 1];
        if(j % 10 == 9)
        {
            fprintf(file2, "%5lg\n", Res[j]);
        }
        else
        {
            fprintf(file2, "%5lg", Res[j]);
        }
        i++;
        j++;
    }
}
void calculate_sred(double Data[], FILE* file2, const int size, const int second) /*изменить n на size*/
{
    double n_0 = 0.0;
    double s = 0.0;
    for (int i = 0; i < size; i++)
    {
        s = s + Data[i];
    }
    n_0 = s / (size + 1);
    consider_tolerance(n_0);
    fprintf(file2, "The average number of particles for %d seconds : \n", second);
    fprintf(file2, "%5lg\n", n_0);
}
void rms_error(double Data[], FILE* file2, double n_0, const int size, const int second)
{
    double a;
    double u = 0;
    int i;
    for (i = 0; i < size; i++);
    {
        u = u + (Data[i] - n_0)*(Data[i] - n_0);
    }
    a = sqrt(u / (size + 1));
    consider_tolerance(a);
    fprintf(file2, "The RMS error for  %d seconds : \n", second);
    fprintf(file2, "%5lg\n", a);
}
