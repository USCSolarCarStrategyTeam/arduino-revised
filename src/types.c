#include <stdio.h>

// takes string of input type and converts it to enum pointer
enum InputType* str2enum(char* s) {
    for(int i = 0; i < N_IN_TYPES; i++) {
        if(strcmp(s, InputLabels[i]) == 0) {
            enum InputType* newIn = (enum InputType*) malloc(sizeof(enum InputType));
            (*newIn) = i;
            return newIn;
        }
    }

}
