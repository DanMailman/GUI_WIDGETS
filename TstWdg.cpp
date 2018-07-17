/* TstWdg.cpp - Driver For Testing Wdg Classes */

#include "tWndW.h"   // App Wnd Wdg
#include "tBtnW.h"   // Plot Cmd Btn Wdg
#include "tInpW.h"   // Coeffs Inp Wdg
#include "tHimW.h"   // Help/Info/Msg Wdg
#include "tPolyWD.h" // Coeffs Wdg Data

#define DEBUG
// Polynomial tWdg-Amenable Data
tPolyWD oCoeffs (5, -10, 10), *rCoeffs(&oCoeffs);
//Action Callback for Button Wdg
tActSrc oActSrc_Plot((WdgDActCB)tPolyWD::Plot,rCoeffs),*rPlotAct(&oActSrc_Plot);
// Wdg for Window, Help/Info/Msg Display, Input, Button
tWndW oWndW(100, 100, 240, 128, "Coefficients"), *rWdnW(&oWndW); 
tHimW oHimW(  5, 100, 230,  24), *rHimW(&oHimW);
tInpW oInpW(  5,  10, 230,  24, "Coefficients", "Enter Polynomial Coefficients", rCoeffs , rHimW) , *rInpW(&oInpW);
tBtnW oBtnW( 20,  80,  80,  20, "PLOT"        , "Call GnuPlot"                 , rPlotAct, rHimW) , *rBtnW (&oBtnW);
int main(int argc, char **argv) {
   try {                      // Call Exception-Throwing (Might Fail Un-Recover-Ably) Code.
	 rWdnW->show();
   int Ret(Fl::run());
   return Ret ;
   } catch(StrP Msg) {        // Call Destructors & Return Err Indicating Termination Problem.
	  printf("%s(main): Exception %s.\n",argv[0],Msg);
	  return -1;
   }
   return 0;                  // Normal Termination
  
}
#ifdef xDEBUG
   printf("main(): Return.\n"); 
#endif
#ifdef xDEBUG
   printf("main(): Run.\n");
#endif
#ifdef xDEBUG
	  printf("main(): rCoeffs(%p) HlpMsg:%s.\n",rCoeffs,rCoeffs->HlpMsg(rCoeffs));
	  printf("main(): rInpW->vAttr[EDT].MsgTxtF(): %s.\n",rInpW->vAttr[tInpW::EDT].MsgTxtF());
	  tStrSrc oStrSrc { (WDInfFP)rCoeffs->HlpMsg, rCoeffs };
	  printf("main(): oStrSrc(): %s.\n",oStrSrc());
	  throw "Abby Someone";
#endif
