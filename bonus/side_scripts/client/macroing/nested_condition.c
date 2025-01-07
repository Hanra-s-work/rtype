/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** nested_condition.c
*/

/**
 *@brief This is a file that will contain a macro logic to check if, based on another macro what to put in the HelloWorld
 *
 */

#include <stdio.h>

 // Hello world 1, before the define definition
#ifndef _HELLOWORLD
#ifndef _GOODBYE
#define _HELLOWORLD "Hello World"
#endif
#ifdef _GOODBYE
#define _HELLOWORLD "Goodbye World"
#endif
#endif

// Defining _GOODBYE
#define _GOODBYE

// Setting HELLOWORLD2 after _GOODBYE has been defined
#ifndef _HELLOWORLD2
#ifndef _GOODBYE
#define _HELLOWORLD2 "Hello World"
#endif
#ifdef _GOODBYE
#define _HELLOWORLD2 "Goodbye World"
#endif
#endif

int main(void)
{
    printf("Content of _HELLOWORLD: %s\n", _HELLOWORLD);
    printf("Content of the _HELLOWORLD2 once _GOODBYE is defined: %s\n", _HELLOWORLD2);
    return 0;
}
