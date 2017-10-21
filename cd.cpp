#include<iostream>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#include "headers.h"
using namespace std;

/*
Handled combination for cd
cd      direct to home
cd --  direct to home
cd ~   direct to home
cd #  direct to home
cd ~# give error
cd -  display path and & cd to previous path
*/

/*******************cd implementatio***********************/
void cdimpl(vector<string> vs){
	string s;
	if(vs.size() <= 2){	
		
		if(vs.size() > 1){	
		s=vs[1].c_str();
		}

		if(s.length()==1 && s[0] == '-'){
			string curpath;
			if(pwdimpl() != NULL){
				curpath=pwdimpl();
			}
			cout<<prevpath<<endl;
	    	if(chdir(prevpath.c_str()) < 0){
		    	perror("chdir");
		    	exit(EXIT_FAILURE);
	    	}
	    	prevpath=curpath;
	    }
	    
		else if(vs.size() == 1 || s[0] == '#' || (s.length()==1 && s[0] == '~') || 
														(s.length()==2 && s[0] == '-' && s[1]=='-') ){
			if(pwdimpl() != NULL){
				prevpath=pwdimpl();
			}	
			if(chdir(getenv("HOME")) < 0){
		    	perror("chdir");
		    	exit(EXIT_FAILURE);	
	    	}
	    }
	    else if(s.length()==2 && s[0] == '~' && s[1]=='#'){
	    	cout<<"chdir :";
	    	cout<<"No such option found"<<endl;
	    }
	    else{
	    	if(pwdimpl() != NULL){
				prevpath=pwdimpl();
			}
			if(chdir(s.c_str()) < 0){
	    	perror("chdir");
	    	exit(EXIT_FAILURE);	
	   	    }
	   	}
	}
	else{
		cout<<"No Such Command Found"<<endl;
	}

}