/* tWdgD.h - Interface for Wdg-Associated Data */

#ifndef WDGD_H
#define WDGD_H

//#include <cstddef>

#include "Utilities.h"

struct tWdgD { // tWdgD - Type for Wdg-Associated Data: NOTE: Wdg Value is String Representation of WdgD Value
   virtual StrP ChkStr(StrP)=0;      // ChkStr() - Set Data Value to Correspond to Valid Passed Str Representation
   virtual StrP HlpStr()=0;          // HlpStr() - Return Message Describing Valid String Representation of Data
   static  StrP HlpCB(tWdgD*);      // HlpCB() - Return Str Val for Wdg Msg Box.
};

typedef StrP (*WdgDataCB)(tWdgD*);
typedef void (*WdgDActCB)(tWdgD*);

struct tStrSrc { // Widget String Source - Str, Str Returned By Function, or Str Returned By Function on WdgDat
   enum eStrSrc {NUL,STR,STRFUN,CALLBACK,NUM_TYPES};
   eStrSrc Type = NUL;
   union uStrSrc { // Union/Type of Possible Instatiation Types
	  StrP SP; StrFP SF; WdgDataCB CB;
      uStrSrc();             // Constructor (default) for no args
      uStrSrc(StrP);         // Constructor for Str Instantiation
      uStrSrc(StrFP);        // Constructor for Function Returning Str
	  uStrSrc(WdgDataCB);      // Constructor for tWdgD member Function taking/returning StrP
   } U ;                     // Union of Possible Instantiatons
   tWdgD *D;                 // WdgDat for Function on WdgDat Returning Str
   StrP operator()() const;  // Return NULL, Str or Function Return Str 
   tStrSrc();                // Constructor (default) for no args 
   tStrSrc(StrP);            // Constructor for Function Returning Str
   tStrSrc(StrFP);           // Constructor for Function Returning Str
   tStrSrc(WdgDataCB,tWdgD*);         // Constructor for tWdgD member function taking/returning StrP  
   operator bool() const {return (Type==NUL)?false:true;}
};
//WIDGET ACTION CALLBACKS
struct tActSrc { // Wdg Act Src - Function or Function on WdgDat
   enum eActSrc { NUL,FUN,CALLBACK,NUM_TYPES };
   eActSrc Type = NUL;
   union uActSrc { // Union/Type Instantiation Possibilities
	  VoidFP VFP; WdgDActCB WDFP;
      uActSrc();                   // Constructor (default) for no args      
      uActSrc(VoidFP  f);          // Constructor for No Args Act Fun
      uActSrc(WdgDActCB f);          // Constructor for WD Args Act Fun
   } U ;                           // Function Instantiation
   tWdgD *D;                     // Data Instantiation
   void operator()() const;        // Execute Action Function
   tActSrc();                      // Constructor (Default) for No Args
   tActSrc(VoidFP f);              // Constructor for No Args Fun
   tActSrc(WdgDActCB f, tWdgD* d); // Constructor for WD Args Fun
   operator bool() const {return (Type==NUL)?false:true;}
};

#endif /* WDGD_H */

