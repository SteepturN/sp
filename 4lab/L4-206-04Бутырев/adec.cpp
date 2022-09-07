
//               adec.cpp
#include <iostream>
#include <fstream>
#include <iomanip>
#include "fsm.h"
using namespace std;

int main()
{
  tFSM Adec;
///////////////////////
  addstr( Adec, 0, "+-", 1 );
  addrange( Adec, 1, '0', '9', 1 );
  Adec.add( 1, '.', 2 );
  addrange( Adec, 2, '0', '9', 3 );
  addrange( Adec, 3, '0', '9', 3 );
  addstr( Adec, 3, "eE", 4 );
  addstr( Adec, 4, "+-", 5 );
  addrange( Adec, 5, '0', '9', 6 );
  addrange( Adec, 4, '0', '9', 6 );
  addrange( Adec, 6, '0', '9', 6 );
  Adec.final( 6 );
///////////////////////
  cout << "Number of states = " << Adec.size()
       << "\n";

  char buf[1000];
  do{
   char* name="dec.ss";
    ifstream file(name);
    if(!file){
 cout<<"Can't open file "<< name << " !\n";
 continue;
            }
    while(file){
     *buf=0;
     file.getline(buf,1000);
     cout<< ">"<<buf<<endl;
  int res = Adec.apply(buf);
  cout << setw(res?res+1:0) << "^"
       << endl;
     }//whil
 } while(false);
 return 0;
}

