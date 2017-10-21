#include<iostream>
#include<unistd.h>
#include<limits.h>
#include<stdlib.h>
#include<stdio.h>

#include "headers.h"

using namespace std;

/***************pwd implementation********************/
char* pwdimpl(){
    char* cwd;
    char buff[PATH_MAX + 1];
    cwd = getcwd( buff, PATH_MAX + 1 );
    if( cwd != NULL ) {
        return cwd;
    }
}
