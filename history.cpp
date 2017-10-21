#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<deque>
#include<algorithm>
#include<iterator>
#include<string.h>
#include<string>
#include<cmath>
#include "headers.h"
using namespace std;

/*******************History implementation***********************/
void historyimpl(vector<string> v){
	int count=1,flag=10;
	if(v.size() ==  2){
		flag=atoi(v[1].c_str());
	}
	for (deque<string>::iterator it = history.begin(); it!=history.end(); ++it){
		string s=to_string(count);
		s+=" ";
		s+=*it;
		s+="\n";
		if(history.size()-count <= flag-1)
		write(1,s.c_str(),s.length());
		count++;
	}
}


/*****************write history in file***************************/

void writehistoryfile(){
	int historyfd=open("history.txt",O_WRONLY | O_TRUNC | O_CREAT ,0777);
		for (deque<string>::iterator it = history.begin(); it!=history.end(); ++it){
			string s=*it;
			s+="\n";
    	 	write(historyfd,s.c_str(),s.length());
		}
		history.clear();
		close(historyfd);
}

/*****************load history in data structure***************************/

void loadhistory(){
	ssize_t ret;	
	char buffer[1];
	string temp="";
	
	int historyfd=open("history.txt",O_RDONLY | O_CREAT ,0777);	
	if(historyfd == -1){
		cout<<"history.txt file can not be opened.\n";
		exit(EXIT_FAILURE);
	}
	while(ret=read(historyfd,buffer,1) > 0){	
		if(buffer[0] == '\n'){
					history.push_back(temp);
					temp="";
			}
			else{
				temp+=buffer;
			}
		
	}
	close(historyfd);
}	

/**************history insert in data structure new cmd entered*************/
void writehistoryds(string input){
	if(!history.empty()){
			if(strcmp(history.back().c_str(),input.c_str())!=0 && input.at(0) !='!'){
				
				if(history.size() > 9){
					history.pop_front();
				}
				history.push_back(input);

			}
		}else{
				if(history.size() > 9){
					history.pop_front();
				}
				history.push_back(input);
		}
}


/***************iterate from start*****************/

void bangstartimpl(int n){
	int count=0;
	string temp;

	for (deque<string>::iterator it = history.begin(); count<n && it!=history.end() ; ++it,count++)
		temp=*it;
		if(count == n){
		vector<char> v(temp.length() + 1);
		strcpy(&v[0], temp.c_str());
		char* pc = &v[0];
		vvs.clear();
    	parse(pc);
    	execute();
    }
}


/***************iterate from last*******************/

void bangendimpl(int n){
	int count=0;
	string temp;

	for (deque<string>::reverse_iterator it = history.rbegin(); count<n && it!=history.rend() ; ++it,count++)
		temp=*it;
		if(count == n){
		vector<char> v(temp.length() + 1);
		strcpy(&v[0], temp.c_str());
		char* pc = &v[0];
		//cout<<pc<<endl;
		vvs.clear();
    	parse(pc);
    	execute();
    }
}

void bangfindimpl(string n){
	string temp;
	for (deque<string>::reverse_iterator it = history.rbegin(); it!=history.rend() ; ++it){
		temp=*it;
		if ( ! ( strncmp(temp.c_str(), n.c_str(), n.length()) )){
			vector<char> v(temp.length() + 1);
			strcpy(&v[0], temp.c_str());
			char* pc = &v[0];
			vvs.clear();
	    	parse(pc);
	    	execute();
	    }
	}

}

int isDigit(string s){
	int i,no;
	no=0;
	for(i=0;s[i]!='\0';i++){
		if(s[i]>='0' && s[i]<='9'){
			no=(no*((int)pow(10,i)))+(s[i]-'0');
		}
		else
			return -1;
	}
	return no;
}

/****************bang operator parsing****************/

void bangparser(string input){
	//cout<<"in parser"<<input<<endl;
	//system(input.c_str());
	if (input.at(1) == '-') {
    		string s=input.substr(2,input.length());
    		int n=isDigit(s);
    		//cout<<"in end :"<<n;
    		bangendimpl(n);
		}
		else if (input.at(1) =='!') {
			//cout<<"in double bang :"<<input<<endl;
    		bangendimpl(1);
		}
		else if(input.at(1) >= '0' && input.at(1) <= '9'){
			string s=input.substr(1,input.length());
    		int n=isDigit(s);
    		//cout<<"n= "<<n<<endl;
    		bangstartimpl(n);
		}
		else{
			
			string s=input.substr(1,input.length());
			//cout<<"Half way der"<<s<<endl;
			bangfindimpl(s);
		}
}

