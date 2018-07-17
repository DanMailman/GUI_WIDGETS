/* Utilities.h */

#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>  // ostream
#include <vector>    // type
#include <set>       // type
#include <iomanip>   // For size_t
#include <iterator>  // ostream_iterator
#include <sstream>   // stringstream
#include <algorithm> // copy()

using namespace std;

typedef const char* StrP;
typedef StrP  (*StrFP)();
typedef void (*VoidFP)();

template<typename T> void SWAP(T & p1, T & p2){ T TMP(p1) ; p2 = p1 ; p2 = TMP ; }

#define CNT(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

long RandInt(long pnLower, long pnUpper);
bool PromptContinue(char *Prompt = NULL,char *sEndMsg = NULL);
template<typename T>
bool Between(const T &pMIN, const T &pTST, const T &pMAX){
   return ( (pMIN <= pTST) && (pTST <= pMAX) );
}
template<typename T>
bool Within(const T &pXMIN, const T &pXTST, const T &pXMAX,
			const T &pYMIN, const T &pYTST, const T &pYMAX){
   return Between (pXMIN,pXTST,pXMAX) && Between(pYMIN,pYTST,pYMAX) ;
}
template<typename T>
bool InBox(const T&pX, const T&pY, const T&pW, const T&pH, const T&px, const T&py){
#ifdef DEBUG
   printf("InBox(): Xmin(%d) X(%d) Xmax(%d) Ymin(%d) Y(%d) Ymax(%d) ==>> %s.\n",
	      pX,px,pX+pW,pY,py,pY+pH,boolstr(Within (pX,px,pX+pW,pY,py,pY+pH)));
#endif
   return Within (pX,px,pX+pW,pY,py,pY+pH);
}
ostream& operator<<(ostream& os, const vector<int>& v) ;
ostream& operator<<(ostream& os, const    set<double>& v) ;

const char * ToStr(const char * pStr);

template<typename T> 
const char *ToStr(const vector<T> &V) {
  stringstream SS;
  //SS.str(std::string());
  copy(V.begin(), V.end(), ostream_iterator<T>(SS, " "));
  cout << "*" << SS.str().c_str() << "*" << endl ;
  return SS.str().c_str();
}
template<typename ... Args>
string stringf( const string& pFmt, Args ... pArgs ){
   size_t size = snprintf( nullptr, 0, pFmt.c_str(), pArgs ... ) + 1; // Extra space for '\0'
   unique_ptr<char[]> buf( new char[ size ] );  // Deleted on Exit Scope
   snprintf( buf.get(), size, pFmt.c_str(), pArgs ... );
   return string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

#endif /* UTIL_H_ */

 
