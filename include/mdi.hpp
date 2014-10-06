/*  VCS_ID
 *  $Filename:   mdi.hpp
 *  $Author  :   
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __MDI_HPP
#define __MDI_HPP

#define MDI_MAXTITLE		0x0000
#define MDI_MAXTITLEAUTO	0x0001


class _EXPORT_ wMdiDocument : public wFrameWindow
{
	private:
		long		mstyle;
		wAccelTable *	accel;
		wBitmap		*sysbmp;
		ushort		menuid;
		HWND		deskSysMenu;

	public:
		wMdiDocument(long maxstyle = MDI_MAXTITLE);
		~wMdiDocument();

		bool CreateWindow(wWindow *parent, ulong fCreateFlags = OpmStdFrame);
		bool CreateWindow(ulong fCreateFlags = OpmStdFrame);
		long &MaxStyle() { return mstyle; }
		ushort &MenuID() { return menuid; }
};

typedef tDList<wMdiDocument> MdiDocumentList;

class _EXPORT_ wMdiDesktop : public wFrameWindow
{
	protected:
		MdiDocumentList	*docList;		

	private:
		ushort			menuid, tileid, cascadeid, firstwinid, 
						currentwinid, olddocid;

		short CeilSqRt(register ushort us);

	public:
		wMdiDesktop(ushort Menuid=0, ushort Tileid=0, ushort Cascadeid=0, ushort FirstWinid=0);
		~wMdiDesktop();

		ushort& MenuID() { return menuid; }
		ushort& TileID()	{ return tileid; }
		ushort& CascadeID() { return cascadeid; }
		ushort& FirstWinID()	{ return firstwinid; }
		MdiDocumentList	*DocList() { return docList; }

		virtual bool CascadeDocuments();
		virtual bool TileDocuments();
		wMdiDocument *FindDoc(ushort id);
		wMdiDocument *TopMdiDocument();
		bool AddDocument(wMdiDocument *doc);
		bool RemoveDocument(wMdiDocument *doc);
};


// STANDARD DIALOG OF MDI DOCUMENT WINDOWS 

class MdiWinList : public wDialogWindow
{
	private:
		wListBox		*lb;
		wPushButton	*view, *cancel, *help;
	public:
		MdiWinList(wWindow *parent, MdiDocumentList *l);
		~MdiWinList();

		long InitDlg(wInitDlgMsg m);
		long PushButtonCommand(wCommandMsg m);
		long Control(wControlMsg m);
};

#endif // __MDI_HPP
