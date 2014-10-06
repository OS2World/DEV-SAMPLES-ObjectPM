/*  VCS_ID
 *  $Filename:   imgbtnwn.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */



#ifndef __IMGBTWN_HPP
#define __IMGBTWN_HPP

#define WC_IMGBTN "IMAGEBUTTON"

class wImgBtnImp : public wWindow
{
	private:
		ulong   	id;			    	// ID Value				
		ulong		style;		    	// Style				
		bool		fFocus;		    	// Focus Flag			
		wRectl		rcl;				// Button Rectangle
		wRectl   	rclText;			// Text Limits Rectangle		
		wRectl   	rclHitTest;			// Hit Test Rectangle		
		wRectl   	rclSrc[3];		   	// Source Rectangle	- Up, down and disabled
		wPointl  	ptlDest[3];			// Destination Point - Up, down and disabled
		LHANDLE		handle[3];			// up,down,disabled image handles
		wPointl  	aptlFocus[5];	   	// Focus Emphasis Polyline Array	
		wPointl  	aptlDFocus[5];	   	// Focus Emphasis Polyline Array-Down
		wPointl  	aptlOutline[12];	// Outline Polyline Array		
		wPointl  	aptlShadow[12];		// Shadow Polyline Array		
		wRectl		finv[2][4];			// parent focus invalidation rectls
		ulong   	flState;		   	// Button State			
		ulong   	saveState;		   	// Saved State -- for sticky buttons			
		wDimension	size[3];			// image sizes
		HPOINTER 	hptrArrow;			// Arrow wPointer			
		bString	 	szText;				// Button Text			
		ulong   	aClr[7];		   	// Presentation Colours Array	
		ulong   	lButtonShadow;	   	// Button Shadow Colour		
		ulong   	lButtonFace;	   	// Button Face Colour		
		ulong   	lButtonReflect;		// Button Reflection	Edge Colour	
		wFont		*fnt;				// font for drawing text

		void CalcImagePos(wRectl &rcl, wPointl &ptl, wDimension d, wDimension shift);
	    void SizeButton(wPointl p, wDimension d);
		void ProcessCtlData(void *);
	    long lGetPresParam(ulong ulID1, ulong ulID2, long lDefault);
	    void SetDefaultColours();
		void CalcTextRectl(char *s, wRectl &r, wRectl &hit);
		void DrawFocus(wPresSpace *ps=NULL);
		void AutoSize();
		void CalcImageSizes();

	public:
		wImgBtnImp(HWND _hwnd);
		~wImgBtnImp();
		long Dispatch(wMessage);
		long Create(wCreateMsg);
		long KeyStroke(wKeyStrokeMsg);
		long Size(wSizeMsg);
		long Active(wActivateMsg);
		long FocusChange(wFocusChangeMsg);
		long ButtonClick(wButtonClickMsg);
		long MouseMove(wMouseMoveMsg);
		void Paint();
};


class wImgBtnClass : public wWindowClass
{
	public:
		wImgBtnClass();
		wWindow *Create(HWND _hwnd);
		void Destroy(wWindow *p);
};

#endif // __IMGBTWN_HPP

