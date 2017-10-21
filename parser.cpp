#include<iostream>
#include<vector>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>
#include "headers.h"
using namespace std;

/*************************************parser**************************************/
void parse(char input[]){

inputflag=outputflag=inputfd=bcgroundflag=0;

int i=0,count=0,j=0;
char temp[1000];
char ch;
vector<string> v;
	while(input[i] != '\0'){
		//cout<<"i at initial "<<i<<endl;
		while(input[i] ==' ' || input[i] == '\t' || input[i] == '\n')
			i++;

		if(input[i] == '&' && (strlen(input)-1) == i){
			bcgroundflag=1;
		 	if(j != 0){		 	
			 	temp[j]='\0';
			 	//cout<<temp<<endl;
				v.push_back(string(temp));			
			}
			vvs.push_back(v);
				v.clear();
				j=0;	
				i++;
		 }
		 else if(input[i] == '<' || input[i] == '>'){
		 	//cout<<"i at <"<<i<<endl;
		 	if(input[i] == '<'){
				inputflag=1;
			}
			else
				outputflag=1;

			i++;

		 	while(input[i] ==' ' || input[i] == '\t' || input[i] == '\n')
			i++;

			if(input[i]=='"' || input[i]=='\''){

			}
			else{
				while(input[i] !=' ' && input[i] != '\t' && input[i] != '\n' && input[i] != '\0')
					temp[j++]=input[i++];
			}
			temp[j]='\0';
			//cout<<temp<<endl;
			if(inputflag == 1){
				inputfd=open(temp,O_RDONLY | O_CREAT ,0777);;
			}
			else if(outputflag == 1){
				outputfd = open(temp, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				//outputfd=open(temp,O_WRONLY | O_CREAT ,0777);;
			}
			//cout<<"after >"<<i<<endl;
			j=0;
		 }
		else if(input[i] == '|' || input[i] == '<' || input[i] == '>'){
		 	if(j != 0){		 	
			 	temp[j]='\0';
			 	//cout<<temp<<endl;
				v.push_back(string(temp));			
			}
			vvs.push_back(v);
				v.clear();
				j=0;	
				i++;
		 }
		 else if(input[i] == '\'' || input[i] == '"'){
		 		count=0;
				ch=input[i];
				count++;
				//temp[j++]=input[i++];
				i++;
			while(input[i]!= ch || count%2==0){	
			
				if(input[i] == ch){
					count++;
					//cout<<"here"<<endl;
				}			
				else if(input[i] == '|'){
					if(count%2 == 0){
						continue;
					}
				}
				temp[j++]=input[i++];
			}
			
			i++;
			temp[j]='\0';
			v.push_back(string(temp));
			j=0;		
		}
		else if(input[i] != '\t' && input[i]!='\n' && input[i]!=' ' && input[i]!='\0'){	
			while(input[i] != '\t' && input[i]!='\n' && input[i]!=' ' && input[i]!='\0'){
				if(input[i] == '|' || input[i] == '<' || input[i] == '>'){
					break;
				}
				temp[j++]=input[i++];
			}	
			temp[j]='\0';
			v.push_back(string(temp));
			j=0;
		}
	}
	if(j != 0){
		temp[j]='\0';
		v.push_back(string(temp));
		j=0;
	}
	if(v.size() > 0)	
	vvs.push_back(v);
	v.clear();
}
