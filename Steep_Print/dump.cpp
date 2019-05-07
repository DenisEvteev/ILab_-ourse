//
// Created by denis on 07.05.19.
//
#include "dump.h"

void dump(int val){
    printf("%d", val);
}

void dump(float val){
    printf("%f", val);
}

void dump(unsigned int val){
    printf("%u", val);
}

void dump(double val) {
    printf("%lf", val);
}

void dump(char val){
    printf("%c", val);
}

void dump(char* str){
    printf("%s", str);
}

void dump(short val){
    printf("%hd", val);
}

void dump(long int val) {
    printf("%ld", val);
}

void dump(unsigned long int val){
    printf("%lu", val);
}

void dump(const char* str){
    printf("%s", str);
}
