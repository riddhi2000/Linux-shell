#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<vector>
#include<algorithm>
#include<iterator>
#include<string.h>
#include<string>
#include<cmath>
#include<stdio.h>
#include<sys/wait.h>  /* uses for wait*/

#include "headers.h"

using namespace std;

/*********************command calling implementation**********/
void cmdcallimpl(int ith){
	vector <char * > argv;
  //cout<<"in cmd exe"<<endl;
	for(vector<string>::iterator loop = vvs[ith].begin(); loop != vvs[ith].end(); ++loop){
        	argv.push_back(&(*loop)[0]);
  }
    argv.push_back(NULL);

    if (strcmp(vvs[ith].front().c_str(), "pwd") == 0) {
    	write(1,pwdimpl(),strlen(pwdimpl()));
      cout<<endl;
      exit(0);
	}
  else if (strcmp(vvs[ith].front().c_str(), "fg") == 0) {
    //cout<<"in cd"<<endl;
      fgimpl();
      exit(0);
  }
	else if (strcmp(vvs[ith].front().c_str(), "cd") == 0) {
		//cout<<"in cd"<<endl;
    	cdimpl(vvs[ith]);
      exit(0);
	}
	else if (strcmp(vvs[ith].front().c_str(), "history") == 0) {
		//cout<<"in history"<<endl;
    	historyimpl(vvs[ith]);
      exit(0);
	}
	else if (strcmp(vvs[ith].front().c_str(), "echo") == 0) {
		//cout<<"in echo"<<endl;
    	echoimpl(vvs[ith]);
      exit(0);
	}
  else if (strcmp(vvs[ith].front().c_str(), "export") == 0) {
      //cout<<"in export"<<endl;
      exportimpl(vvs[ith]);
      exit(0);
  }
	else if ((vvs[ith].front().at(0) == '!') && vvs[ith].front().length() >=2) {
			cout<<vvs[ith].front()<<endl;
		  //cout<<"in bang"<<endl;
			bangparser(vvs[ith].front().c_str());
      exit(0);
	}
  else if (vvs[ith].front().find("=") != string::npos) {
      localimpl(vvs[ith]); 
      exit(0);     
  }
	else{
	      execvp (vvs[ith].front().c_str(), &argv[0]);
	      perror("execvp");
	      exit(EXIT_FAILURE);	
  	}
}

/******************************* implementation*******************************/

int spawn_proc (int in, int out,int ith)
{
  pid_t pid1;
	
  if ((pid1 = fork ()) == 0)
    {	
      if (in != 0)
        {	
          dup2 (in, 0);
          close (in);
        }
      if (out != 1)
        {	
          dup2 (out, 1);
          close (out);          
        }    
  	cmdcallimpl(ith);
	  }
    return pid1;
}


int fork_pipes(){
  int i;
  pid_t pid;
  int in, out,fd [2];
  in = 0;

  if(inputflag ==1){
     in=inputfd;
  }  
  //close(inputfd);

  for (i = 0; i < vvs.size()-1; ++i)
    {
      pipe (fd);
      spawn_proc (in, fd [1],i);
      close (fd [1]);
      in = fd [0];
    }
  if (in != 0)
    dup2 (in, 0);

  if (outputflag == 1){ 
     dup2 (outputfd, 1);
     //close (outputfd);          
  }      
    cmdcallimpl(i);
}


void  execute()
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
               fork_pipes();
     }
     else {
          if(bcgroundflag == 0)                                  /* for the parent:      */
            while (wait(&status) != pid);       /* wait for completion  */
          //else  
            //setpgid(0, 0);     
     }
}
