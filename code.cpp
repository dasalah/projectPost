#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

typedef struct {

   int postcode;
   
   int postpaid;
   
   string sendername;
   
   string recivername;
   
   string sendercity;
   
   string recivercity;

} marsole;

void city(){

 marsole m, t;

 string date, date2, f1, f2;

 int counter;

 ifstream readfile("file1.txt");

 if(!readfile){

  cerr<<"somthing went wrong during opening thr file please make sure the file the you chose exists!"<<endl;

  exit(1);

 }
 while(!readfile.eof()){

  int count;

  bool citypair=false;

  readfile>>m.postcode>>m.sendername>>m.sendercity>>date>>m.recivername>>m.recivercity>>m.postpaid;

  ifstream readfile2("file1.txt");

     if(!readfile2){

  cerr<<"somthing went wrong during opening thr file please make sure the file the you chose exists!"<<endl;

  exit(1);

 }

  while(!readfile2.eof()){

   readfile2>>t.postcode>>t.sendername>>t.sendercity>>date2>>t.recivername>>t.recivercity>>t.postpaid;

   if(m.recivercity==t.recivercity&&m.sendercity==t.sendercity&&m.recivercity!=m.sendercity){

    count++;

    citypair=true;

   }

  }

  readfile2.close();

  if(citypair){

  cout<<m.sendercity<<setw(6)<<m.recivercity<<setw(6)<<count<<setw(4)<<endl;

 }

 readfile.close();

 }

int main() {
 city();
 return 0;
}