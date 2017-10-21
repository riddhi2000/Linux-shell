#include<iostream>
#include<deque>
#include<vector>
#include<map>
#include<string>

using namespace std;

extern deque<string> history;
extern vector<vector<string > > vvs;
extern map<string,string> exportmap;
extern map<string,string> localmap;
extern string prevpath;

extern int inputflag,outputflag,inputfd,outputfd,bcgroundflag;

/******#include<parser.cpp>****/
void parse(char []);

/******function from #include<cd.cpp>****/
void cdimpl(vector<string>);

/******function from #include<fg.cpp>****/
void fgimpl();


/******function from #include<export.cpp>****/
void exportimpl(vector<string>);
void localimpl(vector<string>);
void loadmap();

/******function from #include<echo.cpp>****/
void echoimpl(vector<string> );

/******function from #include<pwd.cpp>****/
char* pwdimpl();

/******function from #include<cmdexe.cpp>****/
void execute();

/******function from #include<history.cpp>****/

void loadhistory();
void historyimpl(vector<string>);
void writehistoryfile();
void writehistoryds(string);
void bangstartimpl(int n);
void bangendimpl(int n);
void bangparser(string);
void bangfindimpl(string);


/*compile syntax
g++ test.cpp parser.cpp  history.cpp cd.cpp pwd.cpp cmdexe.cpp export.cpp echo.cpp -std=c++11 -o a.out
*/
