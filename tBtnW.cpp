/* tBtnW.cpp - Implementation:  Btn Wdg (i.e. (Optional) tWdgD, tHimW) */

#include <FL/Fl.H> // event_x(), event_y(), focus()

#include "tBtnW.h" // Interface

#define nDEBUG

#ifdef xDEBUG
static StrP STATE_NAMES[] = { "SEL","SMO","HVR","SHO" };
static StrP  STIM_NAMES[] = { "NUL","IMV","MBP","REL","OMV" };
static StrP   ACT_NAMES[] = { "DO_NOTH","BTN_ACT" };
#endif

tBtnW::eStim tBtnW::GetStim(int pEvt){
   eStim Ret(NUL);
   switch (pEvt) {
	  case FL_ENTER  :{ Ret = IMV; } break;
	  case FL_PUSH   :{ Ret = MBP; } break;
	  case FL_RELEASE:{ Ret = REL; } break;
	  case FL_LEAVE  :{ Ret = OMV; } break; 
	  case FL_DRAG   :
	  case FL_MOVE   :{ Ret = (InBox(x(),y(),w(),h(),Fl::event_x(),Fl::event_y())) ? IMV : OMV; } break;
	  default        :{ Ret = NUL; }
   }
#ifdef xDEBUG
   #include <FL/names.h>
   printf("BTN: GetStim(): Evt: %s(%d) ==>> STIM: %s(%d).\n", fl_eventnames[pEvt], pEvt, STIM_NAMES[Ret], Ret);
#endif
   return Ret;
}
void tBtnW::DoAct(eAct iAct){
   if (vAct[iAct]){
#ifdef xDEBUG
	  printf("BTN: DoAct(): Exec: ACT: %s(%ld).\n",   ACT_NAMES[iAct],iAct);
#endif
	  (*vAct[iAct])();
   } else {
#ifdef xDEBUG
   printf("BTN: DoAct(): NO ACT: %s(%ld).\n",   ACT_NAMES[iAct],iAct);
#endif
   }
}
void tBtnW::UpdAttr(eState State){
   struct tAttr { Fl_Color BkgClr,TxtClr; tStrSrc BtnTxtF,MsgTxtF; }; //Wdg Attributes
   const tAttr vAttr[NUM_STATES]{/*   Background     Text */ // Attribute Values for Each Wdg State
	  /*    SEL */{ FL_CYAN      , FL_MAGENTA, "Plot"            , "Release to Plot"    },
		 /* SMO */{ FL_BLUE      , FL_RED    , vAttr[SEL].BtnTxtF, "Release to Cancel"  },
		 /* HVR */{ FL_GREEN     , FL_YELLOW , vAttr[SEL].BtnTxtF, "Plot: Press/Release"},
		 /* SHO */{ FL_DARK_GREEN, FL_BLACK  , vAttr[SEL].BtnTxtF, (StrP)NULL            }};
   color (vAttr[State].BkgClr);
   labelcolor(vAttr[State].TxtClr);
   label(vAttr[State].BtnTxtF());
   redraw();
   if (rHimW){
	  if (vAttr[State].MsgTxtF) {
		 StrP sHIM(vAttr[State].MsgTxtF());
		 if (sHIM){
			rHimW->label(sHIM);
		 }
	  }
   }
#ifdef xDEBUG
   printf("BTN: UpdAttr(): State: %s(%d): H/I/M: %s.\n", STATE_NAMES[State], State,rHimW->label());
#endif
}
int tBtnW::handle(int pEvt){
   //NOTE: Self-Loops <<==>> DO_NOTH
   static const eState NewState[NUM_STATES][NUM_STIMS]={
	  /**S**         STIM->NUL      IMV      MBP      REL      OMV */
	  /* T * - SEL */{     SEL,     SEL,     SEL,     HVR,     SMO },
	  /* A * - SMO */{     SMO,     SEL,     SMO,     SHO,     SMO },
	  /* T * - HVR */{     HVR,     HVR,     SEL,     HVR,     SHO },
	  /* E * - SHO */{     SHO,     HVR,     SEL,     SHO,     SHO }};
   static const eAct Act[NUM_STATES][NUM_STIMS]={
	  /**S**         STIM->NUL      IMV      MBP      REL      OMV */
	  /* T * - SEL */{ DO_NOTH, DO_NOTH, DO_NOTH, BTN_ACT, DO_NOTH },
	  /* A * - SMO */{ DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH },
	  /* T * - HVR */{ DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH },
	  /* E * - SHO */{ DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH, DO_NOTH }};
   eStim Stim(GetStim(pEvt));
   eAct ACT_IDX = Act[State][Stim];
   DoAct(ACT_IDX);
   State=NewState[State][Stim];
   UpdAttr(State);
   
#ifdef xDEBUG
   if (Stim == NUL){ return(Fl_Button::handle(pEvt)); }
   printf("BTN: handle():  STIM: %s(%d), ACT: %s(%d), STATE: %s(%d).\n",
		  STIM_NAMES[Stim], Stim, ACT_NAMES[ACT_IDX], ACT_IDX, STATE_NAMES[State], State);
#endif
   return (Fl_Button::handle(pEvt));
}

tBtnW::tBtnW(int x,int y,int w,int h,
			 StrP pLbl=NULL, StrP pTip=NULL,
			 tActSrc* pActSrc=NULL, tHimW *pMsgBox=NULL)
   : Fl_Button(x,y,w,h,pLbl),vAct{NULL,pActSrc}, rHimW(pMsgBox)
   {
#ifdef xDEBUG
		printf("tBtnW(): Enter.\n");
#endif
		tooltip(pTip);
		labelfont(FL_BOLD);
#ifdef xDEBUG
		printf("tBtnW(): Return.\n");
#endif
	 }

void tBtnW::draw() {
   draw_box(box(),color());
   draw_backdrop();
   draw_label();
   if (Fl::focus() == this) draw_focus();
#ifdef xDEBUG
   printf("BTN: Draw().\n");
#endif
}
