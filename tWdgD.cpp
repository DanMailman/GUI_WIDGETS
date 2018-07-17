/* tWdgD.cpp - Implementation: Wdg-Associated Data */
#include <assert.h>

#include "tWdgD.h" // Interface

#define nDEBUG

//StrP tWdgD::ChkStr(StrP pTstVal){return NULL;}
//StrP tWdgD::HlpStr(){return NULL;}
StrP tWdgD::HlpCB(tWdgD* d){return d->HlpStr();}

#ifdef xDEBUG
static StrP STRSRC_NAMES[tStrSrc::NUM_TYPES]{"NUL","STR","STRFUN","WdgDataCB"};
#endif
tStrSrc::uStrSrc::uStrSrc():SP(NULL){}
tStrSrc::uStrSrc::uStrSrc(StrP  s)    :SP(s){}
tStrSrc::uStrSrc::uStrSrc(StrFP f)    :SF(f){}
tStrSrc::uStrSrc::uStrSrc(WdgDataCB f):CB(f){}
StrP tStrSrc::operator()() const {
   switch(Type){
	  case      NUL: { return NULL   ; } break;
	  case      STR: { return U.SP   ; } break;
	  case   STRFUN: { return U.SF() ; } break;
	  case CALLBACK: {
#ifdef xDEBUG
		 printf("tStrSrc::OP(): %p, Return(%s).\n",D,U.CB(D));
#endif
		 return U.CB(D);
	  } break;
	  default      : { return NULL   ; } break;   
   }
   return NULL;
}
tStrSrc::tStrSrc()                   : Type(NUL),      U()       {} 
tStrSrc::tStrSrc(StrP s)             : Type(STR),      U(s)      {}
tStrSrc::tStrSrc(StrFP f)            : Type(STRFUN),   U(f)      {}
tStrSrc::tStrSrc(WdgDataCB f, tWdgD *d): Type(CALLBACK), U(f),D(d) {
#ifdef xDEBUG
   printf("tStrSrc(WdgDataCB, tWdgD*): f(%p) d(%p) U(%p) D(%p): %s.\n",f,d,U.CB,D,f(d));
#endif
}

tActSrc::uActSrc::uActSrc():VFP(NULL){}
tActSrc::uActSrc::uActSrc(VoidFP  f):VFP(f){}
tActSrc::uActSrc::uActSrc(WdgDActCB f):WDFP(f){}
#ifdef xDEBUG
static StrP ACTSRC_NAMES[tActSrc::NUM_TYPES]{"NUL","FUN","WDActFun"};
#endif
void tActSrc::operator()() const {
#ifdef xDEBUG
   printf("tActSrc::OP(): Enter: Type: %s(%d).\n",ACTSRC_NAMES[Type],Type);
#endif
   switch (Type) {
	  case NUL  : break;
	  case FUN  : { U.VFP()  ; } break;
	  case CALLBACK: { U.WDFP(D); } break;
	  default   : break;
   }
#ifdef xDEBUG
   printf("tActSrc::OP(): Return: Type: %s(%d).\n",ACTSRC_NAMES[Type],Type);
#endif
   return;
}
tActSrc::tActSrc():U(){
#ifdef xDEBUG
   printf("tActSrc(): Return: Type: %s(%d).\n",ACTSRC_NAMES[Type],Type);
#endif
}
tActSrc::tActSrc(VoidFP f):Type((f==NULL)?NUL:FUN),U(f) {
#ifdef xDEBUG
   printf("tActSrc(): Enter: f(%p).\n",f);
   printf("tActSrc(): Return: Type: %s(%d).\n",ACTSRC_NAMES[Type],Type);
#endif
}
tActSrc::tActSrc(WdgDActCB f, tWdgD* d):Type(CALLBACK),U(f), D(d){
   assert (f!=NULL);
#ifdef xDEBUG
   printf("tActSrc(): Enter: f(%p).\n",f);
   printf("tActSrc(): Return: Type: %s(%d).\n",ACTSRC_NAMES[Type],Type);
#endif
}
