/* tBtnW.h - Interface: Btn Wdg w/ (Optional) tHimW */

#ifndef BTNW_H
#define BTNW_H

#include <FL/Fl_Button.H> // Fl_Button

#include "tWdgD.h" // tWdgD, tActSrc, WdInfFP
#include "tHimW.h" // tHimW

struct tBtnW : Fl_Button {
   // Widget Attributes
   // FSA States, Stims, Acts, Initial State/* TODO: SEE NOTES EOF */
   enum eState { SEL,SMO,HVR,SHO,NUM_STATES };
   enum eStim  { NUL,IMV,MBP,REL,OMV,NUM_STIMS };
   enum eAct   { DO_NOTH,BTN_ACT,NUM_ACTS };
   eState State = SHO;

   eStim GetStim(int pEvt);     // Return Stim Associated with Underlying GUI System Events
   int    handle(int pEvt);     // Implement FSA in Event Loop of Underlying GUI System
   void   draw();               // GUI System Draw Method Overload
   void DoAct(eAct iAct);       // Perform Actions Specifed in Action Table
   void UpdAttr(eState iState); // Update Wdg Attributes to reflect new/current state
   const tActSrc* vAct[NUM_ACTS];      // Actions: Values in Action Table
   tHimW* rHimW = NULL;     // Optional MsgBox   // TODO: const?
   tBtnW(int, int, int, int,            // Constructor Parms: Rectangle
		 StrP, StrP, tActSrc*, tHimW*); // Constructor Parms: Label, Wdg Data, Msg Box
};

#endif // BTNW_H
/* 
   eState:
      SEL: Widget Selected via Unreleased Mouse Button Press
      SMO: (Selected, Mouse Outside) Mouse Outside Widget Bounds While Widget Still Selected
	  HVR: Mouse Within Widget Bounds, No Pending Mouse Button Release
	  SHO: Mouse Outside Widget Bounds, No Pending Mouse Button Release
   eStim:
      NUL: Non-Relevant Event
	  IMV: (Inside MoVe) Mouse Enters or Moves Within Widget Space
	  MBP: Mouse Button Pressed While Mouse in Widget Space
	  REL: Mouse Button RELeased
	  OMV: (Outside MoVe) Mouse Leaves Widget Space
   eAct: All NON-DO_NOTH Acts ReDraw Widget to indicate State 
      DO_NOTH: Do Nothing
	  ACT_HVR: Perform Btn Ext Act & ReDraw Widg to Indicate In-Widg Btn Press & Release
	  BEG_SMO: ReDraw Widg to Indicate Unreleased In-Widg Press, Out-Widg Mouse 
	  BEG_SEL: ReDraw Widg to Indicate Unreleased In-Widg Press, In-Widg Mouse
	  BEG_HVR: ReDraw Widg to Indicate Unreleased, Un-Prior-Pressed In-Widg Mouse
	  BEG_SHO: ReDraw Widg to Indicate Unreleased, Un-Prior-Pressed In-Widg Mouse
*/
