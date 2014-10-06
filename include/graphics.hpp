/*  VCS_ID
 *  $Filename:   graphics.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.7  $
 *  $Date:   31 Dec 1991 05:00:02  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __GRAPHICS_HPP
#define __GRAPHICS_HPP

#ifdef InclFixedMath
#include "fixed.hpp"
#endif

/**************** Devices and Presentation Spaces ******************/

struct wFontDef
{
	ushort  usRecordLength;
    ushort  fsSelection;
    long    lMatch;
    char    szFacename[FACESIZE];
    ushort  idRegistry;
    ushort  usCodePage;
    long    lMaxBaselineExt;
    long    lAveCharWidth;
    ushort  fsType;
    ushort  fsFontUse;
    ushort  usPointSize;
    ushort  usXDeviceRes;
    ushort  usYDeviceRes;
};

typedef tDList<wFontDef> wFontDefList;   // Define standard FontList class


class _EXPORT_ wDevice
{
	protected:
		bool fWindowDC;
        HDC hdc;
        wPresSpace *ps;
        wGraphicsDevice deviceType;

    public:
        wDevice(wGraphicsDevice type)   { deviceType = type; fWindowDC = FALSE; }
        wDevice(wGraphicsDevice type, long count, PDEVOPENDATA pDOD);
        ~wDevice();

        HDC& hDC()           { return hdc; }
        wPresSpace *& pPS()  { return ps;  }
        wGraphicsDevice GetDeviceType() { return deviceType; }
        void SetDeviceType(wGraphicsDevice type) { deviceType = type; }
        long Escape(long cmdCode, long cbInData, void *pInData, long *cbOutData, void * pOutData);
        long DeviceCaps(long param);

};

class _EXPORT_ wMemoryDevice : public wDevice
{
	public:
		wMemoryDevice(wDevice *devComp = NULL);
};


class _EXPORT_ wWindowDevice : public wDevice
{
	public:
		wWindowDevice(wWindow *);
		~wWindowDevice();
};

class _EXPORT_ wMetaFile : public wDevice
{
	private:
		HMF hmf;
		long alOpt[8];

	public:
        wMetaFile();
        wMetaFile(const char *filename, wPresSpace *ps = NULL);
        ~wMetaFile();

        HMF  hMetaFile()  { return hmf; }
        bool Close();
        bool Save(const char *filename, bool fReLoad = FALSE);
        void SetDrawOptions(ushort option, long value);
        bool Draw(wPresSpace *ps = NULL);
};


// Base classes for all graphics tools.  This structure allows all
// tools to be added to a container maintained by a wPresSpace object.
//

class _EXPORT_ wGraphicsTool
{
	protected:
		ulong toolType;
        wPresSpace *ps;
        HPS   hps;
        friend class wPresSpace;

	public:
        wGraphicsTool(wPresSpace *);
        ~wGraphicsTool();
        wPresSpace *pPS() { return ps;       }
        HPS hPS()         { return hps;      }
        ulong& ToolType() { return toolType; }
};


class _EXPORT_ wConnectedGraphicsTool : public wGraphicsTool
{
	protected:
		long  lcid;
        friend class wPresSpace;

	public:
        wConnectedGraphicsTool(wPresSpace *);
        virtual void ConnectTo(wPresSpace *);
        virtual void DisConnect();
        bool IsConnected(wPresSpace *testPS)   { return ps != NULL && testPS == ps; }
        bool IsConnected()                     { return ps != NULL;   }
};

typedef tDList<wGraphicsTool> wGraphicsToolList;

class _EXPORT_ wPicture : public wGraphicsTool
{
	protected:
		bool fOpen;
        long idSegment;
        long type;
        wPicture(void *);

	public:
        wPicture(wPresSpace *pPS, bool fView = FALSE, bool fDynamic = FALSE);
        ~wPicture();

        long hPicture() { return idSegment; }
        bool IsOpen()   { return fOpen;     }

        bool Open(bool fView = FALSE);
        bool Close();
        bool Draw();
        bool DrawThru(wPicture *lastPict = NULL);
        bool SetAttribute(long attr, bool state);
        bool GetAttribute(long attr);

        bool SetTransl(wPointl p, wTransformAddOpt xfType = TransformReplace);
        bool SetScale(wFixed xScale, wFixed yScale, wPointl orig, wTransformAddOpt xfType = TransformReplace);
        bool SetRotation(wFixed angle, wPointl c, wTransformAddOpt xfType = TransformReplace);
};

class _EXPORT_ wPictureList : public tDList<wPicture>
{
	private:
        wPicture *openPicture;

    public:
        wPictureList();
        wPicture *& OpenPicture()        { return openPicture; }
        bool Arrange (wPicture *dst, tIterator<wPicture> *it = NULL, short p = RelPosBefore);
        bool ArrangeToHead (tIterator<wPicture> * = NULL);
        bool ArrangeToTail (tIterator<wPicture> * = NULL);
        bool DrawPictures();
        bool DrawDynamicPictures();
        bool RemoveDynamicPictures();
};

class _EXPORT_ wDynamicPicture : public wPicture
{
	public:
		wDynamicPicture(wPresSpace *, bool fView = FALSE);
		bool RemoveThru(wDynamicPicture *pic = NULL);
};

class _EXPORT_ wSubPicture : public wPicture
{
        public:
		wSubPicture(wPresSpace *, bool fView = FALSE);
		bool Draw(wPointl pos, wFixed xScale, wFixed yScale, wFixed rotAngle, wPointl c, wTransformAddOpt xfComb = TransformAdd);
		bool Draw(wPointl pos, wTransformAddOpt xfComb = TransformAdd);
		bool Draw();
};


class _EXPORT_ wPresSpace
{
    private:
		friend class wFont;
		friend class wPen;
		friend class wTextPen;
		friend class wFillPattern;
		friend class wPicture;
		friend class wSubPicture;
		friend class wRegion;

		HPS hps;
		ulong flags;
        wDevice *pDev;
		long nextSegment;
		long nextLcid;
		wPointl baselineAngle;
		wPointl shearAngle;
		wDimension currCharBox;
		wGraphicsToolList *pGraphList;
		wPictureList *pPictList;
		wRegion *currClipRegion;

		wPen *currPen;
		wTextPen *currTextPen;
		wFillPattern *currPattern;

		long SetLCID(wConnectedGraphicsTool *);
		void LoadPresAttributes();

    public:
        wPresSpace(wDevice *dev, wPageUnits pu = PuPels, ushort caps = PcNormal, wDimension *pageSize = NULL);
        wPresSpace(wWindow *win, wPageUnits pu = PuPels, ushort caps = PcNormal);
        ~wPresSpace();

		HPS& hPS()                          { return hps;   }
        ulong& CreateFlags()                { return flags; }
		wDevice *PresDevice()              	{ return pDev;  }
		wGraphicsToolList *PresTools()    	{ return pGraphList; }
		wPictureList *PresPictures()      	{ return pPictList;  }
		wRegion *GetClipRegion()            { return currClipRegion; }

		bool  Erase();
		long  Erase(wRectl, wFillPattern *fp = 0);
        bool  Erase(wRectl, wColor clr);
		bool  InvertRectangle(const wRectl &);
		bool  AssociateDevice(wDevice *);
		bool  DisAssociateDevice();
        long  DeviceCaps(long param);
		bool  SetColorTable(wColor *clrs, long cColors);
		bool  SetColorTable(wColorTabCmd cmd = ColorTabReset);
		wColor GetColor(long index);
		bool  ConvertFromPels(wPointl *p, long count = 1);
		bool  ConvertToPels(wPointl *p, long count = 1);
		bStringList  *EnumFontFaces(ushort attrs = FfPublic);
		wFontDefList *EnumFonts(const char *faceName, ushort attrs = FfMatchDev);

		void  AddGraphicsTool(wGraphicsTool *);
		void  RemoveGraphicsTool(wGraphicsTool *);
		bool  SetModelTransl(wPointl p, wTransformAddOpt xfType = TransformReplace);
        bool  SetModelScale(wFixed xScale, wFixed yScale, wPointl orig, wTransformAddOpt xfType = TransformReplace);
        bool  SetModelRotation(wFixed angle, wPointl c, wTransformAddOpt xfType = TransformReplace);
		bool  SetPageOrigin(wPointl p, wTransformAddOpt xfType = TransformReplace);
		bool  SetPageScale(wFixed xScale, wFixed yScale, wTransformAddOpt xfType = TransformReplace);
		bool  SetPageRotation(wFixed angle, wTransformAddOpt xfType = TransformReplace);

		wRectl GetViewportRectangle();
		bool  SetViewportRectangle(wRectl v);
		bool  ChangePageUnits(wPageUnits pgUnits);
		wPageUnits GetPageUnits();
		bool  ChangePageSize(wDimension siz);
		wDimension GetPageSize();

		bool  SetColor(wColor clr);
		bool  SetBackColor(wColor clr);
		bool  SetMix(long lMixMode);
		bool  SetBackMix(long lMixMode);

		bool  RestoreState(long idPS);
		long  PushState();
		bool  Reset();
		void  ResetClipping(long type = ClpAll);
        bool  Convert(wPointl *p, long count, wCoordSpace from, wCoordSpace targ);
		wPointl GetCurrentPosition();

		wPen *CurrentPen() { return currPen; }
		wTextPen *CurrentTextPen() { return currTextPen; }
		wFillPattern *CurrentPattern() { return currPattern; }
};


class _EXPORT_ wRegion : public wGraphicsTool
{
    private:
		HRGN hrgn;

    public:
		wRegion(wPresSpace *pPS, wRectl *rectangles, long cRects);
		wRegion(const wRegion &r);
       ~wRegion(void);
		HRGN hRegion(void)                      { return hrgn; }

		wRegion& operator=(const wRegion &r);
		wRegion& operator=(const wRectl &rec);
		int operator==(wRegion&);
		int operator!=(wRegion&);
		wRegion& operator+=(const wPointl& p);
		wRegion& operator-=(const wPointl& p);
		wRegion& operator+=(const wRegion& r)   { AddRegion((wRegion *)(&r), RcOR);   return *this; }
		wRegion& operator-=(const wRegion& r)   { AddRegion((wRegion *)(&r), RcDiff); return *this; }
		wRegion& operator&=(const wRegion& r)   { AddRegion((wRegion *)(&r), RcAND);  return *this; }
		wRegion& operator^=(const wRegion& r)   { AddRegion((wRegion *)(&r), RcXOR);  return *this; }
		wRegion& operator+=(const wRectl& r)    { AddRectl(r, RcOR);   return *this; }
		wRegion& operator-=(const wRectl& r)    { AddRectl(r, RcDiff); return *this; }
		wRegion& operator&=(const wRectl& r)    { AddRectl(r, RcAND);  return *this; }
		wRegion& operator^=(const wRectl& r)    { AddRectl(r, RcXOR);  return *this; }
		wRegion  operator+(const wRegion&);
		wRegion  operator-(const wRegion&);
		wRegion  operator&(const wRegion&);
		wRegion  operator^(const wRegion&);
		wRegion  operator+(const wRectl&);
		wRegion  operator-(const wRectl&);
		wRegion  operator&(const wRectl&);
		wRegion  operator^(const wRectl&);
		operator wRectl()                       { return RegionBox(); }

		bool ReDefine(wRectl *rectangles, long cRects);
		bool PtInRegion(wPointl p);
		long RectlInRegion(wRectl r);
		long AddRegion(wRegion *r, wRegCombineMethod combMeth);
		long AddRectl(wRectl r, wRegCombineMethod combMeth);
		long Fill(wFillPattern *fp = NULL);
		wRectl RegionBox();

		bool SetAsClipRegion();
		bool IsClipRegion();
};

#ifndef FM_DEFN_WIN
class FONTMETRICS;
#endif

class _EXPORT_ wFont : public wConnectedGraphicsTool
{
    private:
		FONTMETRICS *fm;
		wDimension      boxSize;
		wDimension      origBoxSize;
		wPointl                 shearAngle;
		long            fontId;
		long            ptsize, ptch;
		bool SetPointSize();
		bool SetPitch();

    public:
		wFont(wFontDef *fd, wPresSpace *ps = NULL);
		wFont(wStdFont f, ushort fontAttr, wPresSpace *ps = NULL);
		FONTMETRICS *FontMetrics() { return fm; }
		~wFont();

		void  ConnectTo(wPresSpace *);
		void  SetAsCurrent();
		long  FontId()           { return fontId; }
		long  FontLCID()     	 { return lcid; }
		long  AveCharWidth();
		long  MaxCharHeight();
		long  EmWidth();
		long  MaxDescender();
		bool  IsOutline();
		bool  IsFixedWidth();
		short PointSize();
		bool  SetShearAngle(wPointl pt);
		bool  SetCharacterBoxSize(wDimension d);
		wDimension CharacterBoxSize();
		wDimension OriginalCharacterBox()    { return origBoxSize; }
		void  ChangePointSize(wFixed ptSize);
		void  ChangePitch(wFixed pitch);
};

#define ResBitmap (-1)

#ifndef PMBITMAP_INCLUDED
class BITMAPINFO2;
#endif

class _EXPORT_ wBitmap : public wConnectedGraphicsTool
{
    protected:
		long color;
		long backColor;
		long mixMode;
		long backMixMode;
		HBITMAP hbm;

	    bool ReadSection(bFile& file, BITMAPINFO2*&, char*&);
    	bool ReadFile(bFile& file, BITMAPINFO2*&, char*&, bool usemax);

	public:
		wBitmap() : wConnectedGraphicsTool (NULL) {};
		wBitmap(short idSysBmp, ushort resId = 0, wPresSpace *ps = NULL);
		wBitmap(wDimension sz, void *bmpdata, wColor *coldefs, short cBits, wPresSpace *ps = NULL);
	    wBitmap(const char* name, wPresSpace *ps = NULL, bool usemax=TRUE);
		wBitmap(const wBitmap &other);
		~wBitmap();

		wPresSpace *pPS()               	{ return ps;  }
		HBITMAP& hBitmap()                  { return hbm; }
		long  BitmapLCID()                  { return lcid; }
		void  ConnectTo(wPresSpace *ps);
		void  SetAsCurrent();

		bool  SetColor(wColor clr);
		bool  SetBackColor(wColor clr);
		bool  SetMix(long lMixMode);
		bool  SetBackMix(long lMixMode);
		wRectl BitmapRectangle();
		wDimension BitmapSize();
		bool  DrawMono(wPresSpace *dst, wPointl pos, ushort fOptions = DbmNormal);
		bool  DrawMono(wPresSpace *dst, wRectl posSiz, ushort fOptions = DbmNormal);
		bool  DrawMono(wPresSpace *dst, wRectl bmpRect, wRectl dstPosSiz, ushort fOptions = DbmNormal);
		long  BltBitsToWC(wPresSpace *, wRectl  src, wRectl dst, long mixOpts = RopSrcCopy, ulong fOptions = BboIgnore);
};



#ifndef BCE_RGB
class BITMAPINFOHEADER2;
#endif

class _EXPORT_ wMemoryBitmap : public wBitmap
{
    private:
		BITMAPINFOHEADER2 *bmp;
		wPresSpace *memPs;

    public:
		wMemoryBitmap(wDimension sz, wPageUnits pu = PuPels, bool fRetain = FALSE, wDevice *devType = NULL);
		wMemoryBitmap(wBitmap *bmp, wPageUnits pu = PuPels, bool fRetain = FALSE,wDevice *devType = NULL);
		~wMemoryBitmap();

		wPresSpace *pPS()                               { return memPs; }
		BITMAPINFOHEADER2 *BitMapInfo() { return bmp; }

		void SetAsCurrent(wPresSpace *ps);
		void DeSelect(wPresSpace *ps);
		bool BltBitsTo(wPresSpace *ps, wRectl  src, wRectl dst, long mixOpts = RopSrcCopy, ulong fOptions = BboIgnore);
		bool BltBitsTo(wPresSpace *ps, wPointl src, wRectl dst, long mixOpts = RopSrcCopy);
		bool BltBitsFrom(wPresSpace *ps, wRectl  src, wRectl dst, long mixOpts = RopSrcCopy, ulong fOptions = BboIgnore);
		bool BltBitsFrom(wPresSpace *ps, wPointl src, wRectl dst, long mixOpts = RopSrcCopy);
		bool FreeMemoryPS();
};


class _EXPORT_ wFillPattern : public wConnectedGraphicsTool
{
    private:
		long  color;
		long  backColor;
		wForgroundMix  mixMode;
		wBackgroundMix  backMixMode;
		long  set;
		long  symbol;
		wPointl  reference;
		wFont *  currFont;
		wBitmap *currBmp;

    public:
		wFillPattern(wPresSpace *ps = NULL);
		void  ConnectTo(wPresSpace *ps);
		void  SetAsCurrent();
		bool  SetColor(wColor clr);
		bool  SetBackColor(wColor clr);
		bool  SetMix(wForgroundMix mixMode);
		bool  SetBackMix(wBackgroundMix bmixMode);

		bool  SetPattern(wFont *, short codepoint);
        bool  SetPattern(wBitmap *);
		bool  SetPattern(wShadePattern pat);
		bool  SetPatternRefPoint(wPointl ref);

		wColor GetColor()           { return wColor(color); }
		wColor GetBackColor()	    { return wColor(backColor); }
		wForgroundMix  GetMix()     { return mixMode; }
		wBackgroundMix  GetBackMix() { return backMixMode; }
};


class _EXPORT_ wTextPen : public wConnectedGraphicsTool
{
    private:
		char *pBuf;
		long color;
		long backColor;
		wForgroundMix  mixMode;
		wBackgroundMix  backMixMode;
		wTextDirection charDirection;
        long cxChar;
        long cxCaps;
        long cyChar;
        long cyDesc;
		wFont *f;
		wPointl baselineAngle;

    public:
		wTextPen(wPresSpace *ps = NULL);
		~wTextPen();

		wTextPen& operator =(wTextPen &t);
		void  ConnectTo(wPresSpace *ps);
		void  PenDown(wFont *f = NULL);
		long  AveCharWidth()    { return cxChar; }
		long  EmWidth()                 { return cxCaps; }
		long  MaxCharHeight()   { return cyChar; }
		long  MaxDescender()    { return cyDesc; }
		bool  SetColor(wColor clr);
		bool  SetBackColor(wColor clr);
		bool  SetMix(wForgroundMix mixMode);
		bool  SetBackMix(wBackgroundMix bmixMode);
		bool  SetDirection(wTextDirection dir);
		bool  SetBaselineAngle(wPointl angle);
		void  SetBufferSize(short size);
		bool  MoveTo(wPointl p);
		bool  MoveTo(long x, long y);
		long  Display(const char *pText);
		long  Display(wPointl p, const char *pText);
		long  Display(long x, long y, const char *pText);
		short Display(wRectl r, ushort cmd, const char *pText);
		short Printf(const char *fmt, ...);
		short Printf(wPointl p, const char *fmt, ...);
		short Printf(long x, long y, const char *fmt, ...);
		short Printf(wRectl r, ushort cmd, const char *fmt, ...);
		wDimension TextSize(const char *pText, bool fInclConcatPt = FALSE);
		wPointl GetCurrentPosition();
};

class _EXPORT_ wPen : public wConnectedGraphicsTool
{
	private:
		long color;
		wForgroundMix  mixMode;
		long  geomWidth;
        FIXED lineWidth;
        long  lineType;
        wLineEndStyle endStyle;
        wLineJoinStyle joinStyle;
		bool  fPathOpen;

    public:
		wPen(wPresSpace *ps = NULL);
		void ConnectTo(wPresSpace *ps);
		void PenDown();
		bool SetColor(wColor clr);
		wColor  GetColor() { return color; }
		bool SetMix(wForgroundMix mixMode);
		wForgroundMix	GetMix() { return mixMode; }
        bool SetLineStyle(long lLineStyle);
		long GetLineStyle() { return lineType; }
        bool SetGeomLineWidth(long lLineWidth);
		long GetGeomLineWidth() { return geomWidth; }
        bool SetEndLineStyle(wLineEndStyle lEndStyle);
        bool SetLineJoinStyle(wLineJoinStyle lJoinStyle);
		bool MoveTo(wPointl p);
		bool MoveTo(long x, long y);
		long Line(wPointl p1, wPointl p2) { MoveTo(p1); return LineTo(p2); }
		long LineTo(wPointl p);
		long LineTo(long x, long y);
		long PolyLine(wPointl *pts, long count);
		long PolyLineDisjoint(wPointl *pts, long count);
		long PolySpline(wPointl *pts, long count);
		wPointl GetCurrentPosition();

		long Circle(long radius, wPenDrawOption = DoOutline, wFillPattern *fp = 0);
		long Ellipse(wPointl p1, wPointl p2, wPenDrawOption = DoOutline, wFillPattern *fp = 0);
		long Ellipse(long rad1, long rad2, wFixed ang, wPenDrawOption = DoOutline, wFillPattern *fp = 0);
		long Box(wPointl pOppCorner, wPenDrawOption = DoOutline, wFillPattern *fp = 0);
		long Box(wRectl rect, wPenDrawOption = DoOutline, wFillPattern *fp = 0);
		long Arc(wPointl p1, wPointl endpoint);
		long Arc(wPointl center, wPointl p1, wPointl p2, wFixed start, wFixed sweep);
		long ArcFillet(wPointl center, wPointl endpoint);
		long ArcSpline(wPointl c1, wPointl c2, wPointl endpoint);
        bool BeginPath();
		bool EndPath(bool fSetClipPath = FALSE, wPathClipMode mode = PcAlternate);
		long PaintPath();
		long PaintPath(wFillPattern *, wPenDrawOption = DoOutline, wPathDrawOption = PdAlternate);
		bool BeginArea(bool drawOutline, wPathDrawOption = PdAlternate);
        long PaintArea();
};

class _EXPORT_ wMarker : public wConnectedGraphicsTool
{
	private:
		long color, backcolor;
		wMarkerSymbol sym;
		wForgroundMix  mixMode;
		wBackgroundMix	backMixMode;
		wDimension	boxSize;
		wFont	*fnt;

		bool SetAttr(ulong attr, void *bundle);

    public:
		wMarker(wPresSpace *ps = NULL);
		void ConnectTo(wPresSpace *ps);
		void MarkerDown();

		long Display(wPointl p);
		long PolyDisplay(wPointl *p, long n);

		bool SetSymbol(wMarkerSymbol s);
		wMarkerSymbol GetSymbol();
		bool SetSymbolSet(wFont *f);
		wFont *GetSymbolSet();
		bool SetMarkerBoxSize(wDimension d);
		wDimension MarkerBoxSize();

		wColor GetColor() { return color; }
		bool SetColor(wColor clr);
		wColor GetBackColor() { return backcolor; }
		bool SetBackColor(wColor clr);
		bool SetMix(wForgroundMix mixMode);
		bool SetBackMix(wBackgroundMix lMixMode);
};

#endif // __GRAPHICS_HPP


