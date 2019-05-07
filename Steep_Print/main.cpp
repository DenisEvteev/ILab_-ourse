//
// Created by denis on 07.05.19.
//
//##########################----the small description of My_Print ;)-----#####################
//It is a very interesting function for print different types in console
//it is a patterned print function
//############################################################################################
#include "dump.h"

#define $(val) dump(val)
//-------------------------------------------------------------
template<typename T, typename ... others>
void my_print(const char* str, T arg, others ... args);
//------------------------------------------------------------

int main() {
    setlocale(LC_ALL, "RUS");


    const char* sub1 = "mathematical analysis";
    const char* sub3 = "linear algebra";
    const char* sub2 = "physics";

    const char* type1 = "writing exam";
    const char* type2 = "oral exam";
    my_print("# is one of the best university in the World and # is the best department in it", "Fiztex", "RT");

    my_print("This year we will have # exams in # different subjects. "
             "#   # on the # of May #  # on the # of June  "
             "#   # on the # of June, #   # on the # of June and #  # on the # of June",
             3, 3, sub1, type1, 27, sub1, type2, 1, sub2, type1, 7, sub2, type2, 14, sub3, type2, 21);


    return 0;
}
//---------------------------------------------------------------
void my_print(const char* str) {
    assert(std::count(str, str + strlen(str), '#') == 0);
    if(str != nullptr)
    {
        puts(str);
    }
}
//-----------------------------------------------------------------
template<typename T, typename ... others>
void my_print(const char* str, T arg, others... args) {
    assert(std::count(str, str + strlen(str), '#') == sizeof...(args) + 1);
    while (str != nullptr) {
        if (*str != '#') {
            putchar(*str);
            str++;
        }
        else {
            $(arg);
            my_print(str + 1, args...);
            break;
        }
    }
}


#undef $