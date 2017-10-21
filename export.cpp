#include<iostream>
#include<map>
#include<string>
#include<cstring>

#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#include "headers.h"
using namespace std;

void loadmap(){
	ssize_t ret;	
	char buffer[1];
	string temp="";
	
	int exportfd=open("export.txt",O_RDONLY | O_CREAT ,0777);	
	if(exportfd == -1){
		cout<<"history.txt file can not be opened.\n";
		exit(EXIT_FAILURE);
	}
	while(ret=read(exportfd,buffer,1) > 0){	
		if(buffer[0] == '\n'){

					string variable,value;
					int i=0;
					const char *s=temp.c_str();

					while(s[i] != '='){
						variable+=s[i++];
					}
					variable[i++]='\0';
					while(s[i] != '\0'){
						value+=s[i++];
					}
					value[i]='\0';

					exportmap.insert(make_pair(variable,value));
					temp="";
			}
			else{
				temp+=buffer;
			}
		
	}
}

void exportimpl(vector<string> input){

	string variable,value;
	int i=0;
	const char *s=input[1].c_str();

	int exportfd=open("export.txt",O_RDWR | O_APPEND | O_CREAT ,0777);
	write(exportfd,s,strlen(s));

	while(s[i] != '='){
		variable+=s[i++];
	}
	variable[i++]='\0';
	while(s[i] != '\0'){
		value+=s[i++];
	}
	value[i]='\0';
	exportmap[variable]=value;
}

void localimpl(vector<string> input){
	string s,variable,value;
	int i=0;
	s=input[0].c_str();

	while(s[i] != '='){
		variable+=s[i++];
	}
	variable[i++]='\0';
	while(s[i] != '\0'){
		value+=s[i++];
	}
	value[i]='\0';
	localmap[variable]=value;
}