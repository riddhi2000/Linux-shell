#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

using namespace std;



int main( void )
{	
    char* cwd;
    char buff[PATH_MAX + 1];

    cwd = getcwd( buff, PATH_MAX + 1 );
    if( cwd != NULL ) {
        cout<<cwd<<endl;
    }else{
    	perror("chdir");
    	exit(EXIT_FAILURE);	
    }
    
    string s;
    cin>>s;
    
    if(chdir(s.c_str()) < 0){
    	perror("chdir");
    	exit(EXIT_FAILURE);	
    }
    else{
    	cwd = getcwd( buff, PATH_MAX + 1 );
    if( cwd != NULL ) {
        cout<<cwd<<endl;
    }
    else{
    	perror("chdir");
    	exit(EXIT_FAILURE);	
    }
    }

    return EXIT_SUCCESS;
}
