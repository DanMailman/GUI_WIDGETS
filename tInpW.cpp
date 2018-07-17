/* tInpW.cpp - Implementation: Input Wdg (i.e. w/ (Optional) WdgD and HimW */

#include <FL/Fl.H>     // event_x(), event_y()

#include "tInpW.h"     // Interface
#include "tWdgD.h"     // tWdgD
#include "Utilities.h" // InBox()
#include "tPolyWD.h" 
#define nDEBUG

#ifdef xDEBUG
static StrP STATE_NAMES[]={ "EDT","EMO","SEL", "SMO", "HVR", "SHO" };
static StrP  STIM_NAMES[]={ "NUL","FOC","UNF","IMV","MBP","REL","OMV","RET","OTH" };
static StrP   ACT_NAMES[]={ "DO_NOTH","UPDATE" };
#endif

tInpW::eStim tInpW::GetStim(int pEvt){
   eStim Ret(NUL);
   switch (pEvt) {
	  case FL_ENTER  :{ Ret = IMV; } break;
	  case FL_PUSH   :{ Ret = MBP; } break;
	  case FL_RELEASE:{ Ret = REL; } break;
	  case FL_LEAVE  :{ Ret = OMV; } break; 
	  case FL_FOCUS  :{ Ret = FOC; } break;
	  case FL_UNFOCUS:{ Ret = UNF; } break;
	  case FL_DRAG   :
	  case FL_MOVE   :{ Ret =  (InBox(x(),y(),w(),h(),Fl::event_x(),Fl::event_y())) ? IMV : OMV; } break;
	  case FL_KEYDOWN:{ Ret =  (Fl::event_key() == FL_Enter)                        ? RET : OTH; } break;
	  default        :{ Ret = NUL; }
   }
#ifdef xDEBUG
   #include <FL/names.h>
   printf("INP: GetStim(): Evt: %s(%d) ==>> STIM: %s(%d).\n", fl_eventnames[pEvt], pEvt, STIM_NAMES[Ret], Ret);
#endif
   return Ret;
}
void tInpW::DoAct(eAct iAct){
  if (iAct == UPDATE){
    value(rWdgD->ChkStr(value()));
#ifdef xDEBUG
    printf("INP: DoAct(): UPDATE: ACT: %s(%d), WdgVal(%s).\n",   ACT_NAMES[iAct],iAct,value());
#endif
  } else {
#ifdef xDEBUG
	 printf("INP: DoAct(): NO ACT: %s(%d), WdgVal(%s).\n",   ACT_NAMES[iAct],iAct,value());
#endif
  }
}
void tInpW::draw() {
  if (input_type() == FL_HIDDEN_INPUT) return;
  //tHimWtype b = box();
  if (damage() & FL_DAMAGE_ALL) {
	 draw_box(box(), vAttr[State].BkgClr);
  }
  Fl_Input::drawtext(x(), y(),w(),h());
#ifdef xDEBUG
  printf("INP: Draw().\n");
#endif
}

void tInpW::UpdAttr(eState State){
   color (vAttr[State].BkgClr);
   textcolor(vAttr[State].TxtClr);
   redraw();
   if (rHimW){
	  if (vAttr[State].pHimStr) {
		 static StrP sLastHIM(NULL);
		 StrP sHIM((vAttr[State].pHimStr)());
		 if (sHIM){
			rHimW->label(sHIM);
			sLastHIM=sHIM;
		 } else if (sLastHIM) { // If Last One Was Something and This One is Nothing, Clear HIM
			rHimW->label(sHIM);			
		 } // else LEAVE HIM ALONE
	  }
   }
#ifdef xDEBUG
   printf("INP: UpdAttr(): State: %s(%d): H/I/M: %s.\n", STATE_NAMES[State], State,rHimW->label());
#endif
}

int tInpW::handle(int pEvt){
   static const eState NewState[NUM_STATES][NUM_STIMS]={
     /*****     STIM->    NUL      FOC      UNF      IMV      MBP      REL      OMV      RET      OTH */
     /* S * - EDT */{     EDT,     EDT,     HVR,     EDT,     EDT,     EDT,     EMO,     EDT,     EDT },
     /* T * - EMO */{     EMO,     EMO,     SHO,     EDT,     EMO,     SHO,     EMO,     EMO,     EMO },
     /* A * - SEL */{     SEL,     EDT,     SEL,     SEL,     SEL,     EDT,     EMO,     SEL,     SEL },
     /* T * - SMO */{     SMO,     EMO,     SMO,     SEL,     SMO,     SHO,     SMO,     SMO,     SMO },
     /* E * - HVR */{     HVR,     EDT,     HVR,     HVR,     SEL,     HVR,     SHO,     HVR,     HVR },
     /***** - SHO */{     SHO,     EMO,     SHO,     HVR,     SHO,     SHO,     SHO,     SHO,     SHO }};
   static const eAct Act[NUM_STATES][NUM_STIMS]={
     /*****    STIM->     NUL      FOC      UNF      IMV      MBP      REL      OMV      RET      OTH */
     /* S * - EDT */{ DO_NOTH, DO_NOTH,  UPDATE, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH,  UPDATE, DO_NOTH },
     /* T * - EMO */{ DO_NOTH, DO_NOTH,  UPDATE, DO_NOTH, DO_NOTH,  UPDATE, DO_NOTH,  UPDATE, DO_NOTH },
     /* S * - SEL */{ DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH },
     /* T * - SMO */{ DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH },
     /* A * - HVR */{ DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH },
     /* T * - SHO */{ DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH }
     /* S * */ };
   eStim Stim(GetStim(pEvt));
   eAct ACT_IDX = Act[State][Stim];
   DoAct(ACT_IDX);
   State=NewState[State][Stim];
   UpdAttr(State);
   
#ifdef xDEBUG
   if (Stim == NUL){ return(Fl_Input::handle(pEvt)); }
   printf("INP: handle():  STIM: %s(%d), ACT: %s(%d), STATE: %s(%d).\n",
		  STIM_NAMES[Stim], Stim, ACT_NAMES[ACT_IDX], ACT_IDX, STATE_NAMES[State], State);
#endif
   return(Fl_Input::handle(pEvt));
}

tInpW::tInpW(int x,int y,int w,int h,
			 StrP pLbl=NULL, StrP pTip=NULL,
			 tWdgD* rWdgD=NULL, tHimW* pHimW=NULL)
   : Fl_Input(x,y,w,h,pLbl), rWdgD(rWdgD), rHimW(pHimW),
	 vAttr{/*   Background     Text */
   /*    EDT */{ FL_WHITE      , FL_BLUE   , {rWdgD->HlpCB,rWdgD}  },
	  /* EMO */{ FL_CYAN       , FL_MAGENTA, vAttr[EDT].pHimStr },
	  /* SEL */{ FL_GREEN      , FL_BLACK  , "Release to Edit" },
	  /* SMO */{ FL_DARK_GREEN , FL_CYAN   , "Release To Cancel" },
	  /* HVR */{ FL_YELLOW     , FL_BLACK  , "Click To Edit" },
	  /* SHO */{ FL_WHITE      , FL_BLACK  , (StrP)NULL }}
{
#ifdef xDEBUG
   printf("***tInpW(): vAttr[EDT].pHimStr(): %s.\n",vAttr[EDT].pHimStr());
#endif
   tooltip(pTip);
   value(rWdgD->ChkStr(value()));
}
