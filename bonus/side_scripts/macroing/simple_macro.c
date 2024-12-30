/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** simple_macro.c
*/

/**
 *@brief This is a file that will contain a simple ifndef define macro logic, why not start with the bases
 *
 */

#include <stdio.h>

#ifndef _HELLOWORLD
#define _HELLOWORLD "Hello World"
#endif

int main(void)
{
    printf("Content of _HELLOWORLD: %s\n", _HELLOWORLD);
    return 0;
}
