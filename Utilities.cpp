#include <iostream>    // cout,cin
#include <vector>      // vector
#include <cstddef>     // NULL
#include <string>      // string
#include <cstdlib>     // rand
#include <set>         // set
#include <complex>   // complex

using namespace std; // string

const char * ToStr(const char * pStr){
  if ( !pStr ) { return (char *)"" ;       }
  if ( pStr[0] == '\0' ) { return (char*)"<EMPTY>"; }
  return pStr ;
}

long RandInt(long pnLower, long pnUpper){
  return(pnLower + (rand() % static_cast<int>(pnUpper - pnLower + 1)));}

bool PromptContinue(char *Prompt = NULL, char *sEndMsg = NULL){
  string
	sOut((Prompt  != NULL) ? Prompt  : "(<ret>)Another? "),
	sEnd((sEndMsg != NULL) ? sEndMsg : "Moving On!");
  char c(getchar());
  if (c != '\n'){
	cout << sEndMsg << endl; 
  }
  return  (c == '\n');
}
ostream& operator<<(ostream& os, const vector<int>& v){
  os << "[";
  for (size_t i = 0; i < v.size(); ++i) {
	os << v[i];
	if (i != v.size() - 1)
	  os << ", ";
  }
  os << "]"; 
  return os;
}
ostream& operator<<(ostream& os, const set<double>& S){
  os << "{";
  for (set<double>::iterator i = S.begin() ;i != S.end() ; ++i ){
	if (i==S.begin()){
	  os << *i;
	} else {
	  os <<", " << *i;
	}
  }
  os << "}"; 
  return os;
}


/* getline(cin,sIn);
   if (sIn == string("")){
   return true;
   } else {
   cout << "Input" << "(" << sIn << ")" << sOut << endl;
   return false;
   }*/
