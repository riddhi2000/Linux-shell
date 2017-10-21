#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include "headers.h"

using namespace std;

void echoimpl(vector<string> input){
	
	for(vector<string>::iterator itr=input.begin()+1;itr!=input.end();++itr){
		string s=*itr;
		string sub;

		if(s.length() >= 2)
			sub=s.substr(1,s.length());
		if (!(*itr).empty() && s[0] == '$' && exportmap.count(sub)){
			write(1,exportmap[sub].c_str(),exportmap[sub].length());
			cout<<"  "<<endl;
		}
		else if (!(*itr).empty() && s[0] == '$' && localmap.count(sub)){
			write(1,localmap[sub].c_str(),localmap[sub].length());
			cout<<"  "<<endl;
		}
		else if(!(*itr).empty() && s[0] == '$'){
			if( (strcmp( getenv(sub.c_str()),"(null)" ) ) != 0){
				write(1,getenv(sub.c_str()),strlen(getenv(sub.c_str())));
				cout<<"  "<<endl;
			}
			else
				cout<<endl;
		}
		else{
				s=s+"  ";
				write(1,s.c_str(),s.length());
			}
	}
		
	cout<<endl;
}