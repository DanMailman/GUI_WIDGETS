/* tInpW - Interface for Inp Wdg (i.e. (Optional) tWdgD and tHimW) */

#ifndef INPW_H
#define INPW_H

#include <FL/Fl_Input.H>

#include "tWdgD.h"
#include "tHimW.h"

struct tInpW :  Fl_Input {
   // Widget Attributes
   struct tAttr { Fl_Color BkgClr,TxtClr; tStrSrc pHimStr; }; //Wdg Attributes
   // FSA States, Stims, Acts, Initial State
   enum eState { EDT,EMO,SEL,SMO,HVR,SHO,NUM_STATES } ;
   enum eStim  { NUL,FOC,UNF,IMV,MBP,REL,OMV,RET,OTH,NUM_STIMS };
   enum eAct   { DO_NOTH,UPDATE,NUM_ACTS };
   eState State = SHO;

   eStim GetStim(int pEvt);            // Return Stim for Underlying GUI System Event
   int    handle(int pEvt);            // FSA in Event Loop of Underlying GUI System
   void draw();                        // GUI System Draw Method Overload, If Needed.
   void DoAct(eAct iAct);              // Perform Actions Specifed in Action Table
   void UpdAttr(eState iState);        // Update Wdg Attributes for new/current state
   tWdgD* rWdgD = NULL;                // Optional tWdgD // TODO: const?
   tHimW* rHimW = NULL;                // Optional MsgBox  // TODO: const?
   tAttr vAttr[NUM_STATES];            // Attribute Values for Each Wdg State
   tInpW(int, int, int, int,           // Constructor Parms: Rect
		 StrP, StrP,tWdgD*, tHimW*);  // Constructor Parms: Label, Tooltip, Wdg Data, Msg Box
};
#endif /* INPW_H */

/* eStates: Input Widget States wrt FOCUS & HOVER
      EDT: Editing, Mouse In Widg Space 
	  EMO: Editing, Mouse Outside Widg Space
	  SEL: Widget Selected via Unreleased Mouse Button Press
	  SMO: (Selected, Mouse Outside) Mouse Outside Widget Bounds While Widget Still Selected
	  HVR: Mouse Within Widget Bounds, No Pending Mouse Button Release
	  SHO: Mouse Outside Widget Bounds, No Pending Mouse Button Release
   eStims: Events that May Cause Change of State
      NUL: Non-Relevant Event
	  IMV: (Inside MoVe) Mouse Enters or Moves Within Widget Space
	  MBP: Mouse Button Pressed While Mouse in Widget Space
	  REL: Mouse Button RELeased
	  OMV: (Outside MoVe) Mouse Leaves Widget Space
	  RET - Kbd <Enter> Key While Widg Has Focus
	  OTH - Kbd *Other* Key While Widg Has Focus
   eAct: Actions To Take on State to New State
*/
 
