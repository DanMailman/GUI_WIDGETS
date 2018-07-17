/* tPolyWD.h - Interface for  Input Widget Polynomial Data */

#ifndef POLYWD_H
#define POLYWD_H

#include <vector>    // vector
#include <set>       // set
#include "tWdgD.h"   // Base Class

using namespace std; // vector, set

struct tPolyWD : tWdgD {
   StrP ChkStr(StrP); // Overload
   StrP HlpStr();     // Overload
   //static StrP HlpMsg(tPolyWD*);
   static void Plot(const tPolyWD&) ;
   
   size_t Deg = 5; vector<int> Value;
   int nMinCoeff=-10, nMaxCoeff=10, nMinDomain=-12, nMaxDomain=12;
  
   set<double> ROOTS;
   bool bZero;
   friend ostream& operator<<(ostream& OUT, const tPolyWD& POLY);  
   double EVAL(const double x) const ;
   string STRING() const ;
   void FindRoots();
   void MakeValues();
   string Roots() const;
   tPolyWD();
   tPolyWD(size_t pDeg,int pMin,int pMax);
   void Randomize();
   double operator()(const double) const;
};

#endif /* POLYWD_H */
