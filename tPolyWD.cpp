/* tPolyWD.h - Implementation for Coefficient Data */
#define DEBUG

#include "tPolyWD.h"          // Interface
#include "Utilities.h"        // RandInt(), stringf()
#include "gnuplot-iostream.h" // Gnuplot

#include <regex>              // regex collection type  

tPolyWD::tPolyWD(){ Randomize(); }
tPolyWD::tPolyWD(size_t pDeg,int pMin,int pMax)
   :Deg(pDeg),nMinCoeff(pMin),nMaxCoeff(pMax) {
   Randomize();
#ifdef xDEBUG
   printf("tPolyWD(%ld,%d,%d)\n", Deg,nMinCoeff,nMaxCoeff);
#endif
}
void tPolyWD::Randomize(){
   size_t nDeg(RandInt(0,Deg));
   Value.clear();
   for (size_t i(0) ;i <= nDeg ; i++){
	  Value.insert ( Value.begin() + i , RandInt(nMinCoeff,nMaxCoeff));
   }
#ifdef xDEBUG
   printf("Randomize().\n");
   STRING();
#endif
}
StrP tPolyWD::ChkStr(StrP pTst){
#ifdef xDEBUG
   printf("ChkStr(): ENTER: pTst(%s).\n", pTst);
#endif
   vector<int> vOld(Value);Value.clear();
   string S(pTst);
   const regex R("[-]?[0-9]+");
   for (sregex_iterator I(S.begin(), S.end(), R); I != sregex_iterator();++I) {
	  stringstream SS(*I->begin()); 
	  int N(0); SS >> N;
	  if (N > nMaxCoeff){N=nMaxCoeff;} if (N < nMinCoeff){N=nMinCoeff;}
	  if (Value.size() < Deg){ Value.push_back(N);}
   }
   if (!Value.size()){ Value=vOld; }
   if (!Value.size()){ Randomize(); }
   // NORMALIZE STRING
   static string STR;
   STR.clear();
   for (size_t i(0);i < Value.size();++i){
	  if (i > 0){ STR += " "; }
	  STR += to_string(Value[i]);
   }
   return STR.c_str();
}
StrP tPolyWD::HlpStr(){
   static string sRet(stringf("%d integers b/w %d and %d",Deg,nMinCoeff,nMaxCoeff));
#ifdef xDEBUG
   printf("tPolyWD::HlpStr(): %s\n", sRet.c_str());
#endif
   return sRet.c_str();
}
void tPolyWD::Plot(const tPolyWD &D){
#ifdef xDEBUG
   printf("Plot(): Enter.\n");
#endif
   Gnuplot gp;
   
   gp << "clear" << "\n";
   gp << "set xzeroaxis"  << "\n";
   gp << "set yzeroaxis"  << "\n";
   gp << "set autoscale"  << "\n";
   gp << "set xlabel 'x'" << "\n";
   gp << "set ylabel '" << D.STRING() << "'" << "\n";
   gp << "set style line 1"
   	 << "linetype 1"             << " "
   	 << "linecolor rgb 'orange'" << " "
   	 << "pointtype 1"            << " "
   	 << "linewidth 2"            << " "
   	 << "\n";
   gp << "set style line 2"       << " "
   	 << "linecolor rgb 'blue'"   << " "
   	 << "pointtype 1"            << " "
   	//<< "linewidth 10"          << " "
   	 << "pointsize 1"            << " "
  	 << "\n";
  
   gp << "plot" 
   	 << "'-' with lines linestyle 1"
   	 << "title '" << "" << "'"
   	 << ", "
	  << "'-' with points linestyle 2 title 'Real Roots " << D.Roots() << "'" << "\n"
   	 << "\n";
   for (long iX(D.nMinDomain-1); iX <= D.nMaxDomain  ; iX++){
	  gp   << iX << " " << D((double)iX) << "\n" ;
   }
   gp << "e\n";
   return;
}

string tPolyWD::STRING() const {
#ifdef xDEBUG
   printf("STRING(): Enter.\n");
#endif
  /* STRING(): String Representation of Polynomial  */
  string ret("F(x)=(");
  vector<int> vCoeff = Value ;
  reverse (vCoeff.begin(),vCoeff.end());
  size_t TermCnt(0);
  for (size_t iCoeff(0) ; iCoeff < vCoeff.size() ; iCoeff++){
	double Coeff(vCoeff[iCoeff]);
	if (Coeff != 0){
	  if (Coeff < 0) { ret+='-'; } else if (TermCnt > 0){ ret+='+'; }
	  float AbsCoeff(fabs(Coeff));
	  if (AbsCoeff != 1){ ret += to_string((size_t)AbsCoeff); }
	  size_t Degree(vCoeff.size()-iCoeff-1);
	  if (Degree == 0){
		if(AbsCoeff == 1) {
		  ret+= '1';
		}
	  } else {
		ret+='x';
		if ((Degree > 1) or (Degree < 0)){
		  ret+='^';
		  ret+=to_string(Degree);
		}
	  }
	  TermCnt++;
	}
  }
  if (TermCnt == 0){
	ret+="0";
  }
  ret+=")";
  return ret;
}


string tPolyWD::Roots() const {
  /* Roots(): String Representation of ROOTS  */
  string ret;
  if (bZero){ ret = "<" + STRING() + ">";
  } else {
	ret= "{";
	for (set<double>::iterator i = ROOTS.begin() ;i != ROOTS.end() ; ++i ){
	  if (i==ROOTS.begin()){
		ret += to_string(*i);
	  } else {
		ret += ", " + to_string(*i);
	  }
	}
	ret += "}"; 
  }
  return ret;
}

double tPolyWD::EVAL(const double X) const {
  /* EVAL(): Return Value of Polynomial.
	 Method: Iterate on Accumulation of Product of 
	         Coefficient With Degree Power of Argument.
  */
  double fRetSum(0.0);
  for (size_t Degree(0) ; Degree < Value.size() ; Degree++){
#ifdef xDEBUG
	cout <<   "EVAL F(" << X                                       << "): "
		 <<   "Degree(" << Degree                                  << "), "
		 <<    "Coeff(" << Value[Degree]                           << "), "
		 <<      "pow(" << pow(X,Degree)                           << "): Adding "
		 <<  "Product(" << Value[Degree] * pow(X,Degree)           << ") To"
		 <<      "ACC(" << fRetSum                                 << ")"
		 <<     "--> (" << fRetSum + Value[Degree] * pow(X,Degree) << ")" << endl;
#endif
	fRetSum += Value[Degree] * pow(X,Degree);
  }
#ifdef xDEBUG
  cout <<   "EVAL():" << "F(" << X << ") --> " <<  fRetSum << endl;
#endif
  return fRetSum;
}

double tPolyWD::operator()(const double X) const { return EVAL (X); }
