/*  VCS_ID
 *  $Filename:   dispatch.hpp
 *  $Author  :   Jeff Knaus
 *  $Revision:    $
 *  $Date:   05 Feb 1992 16:33:34  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */


//+*****************************************************************************
//
//	VERSION:  $Revision$
//	          $Date$
//
//	MODULE:   dispatch.hpp
//	AUTHOR:   Jeff Knaus
//	FACILITY: ObjectPM
//
//	Copyright (c)	1995 by Secant Technologies
//
//
//	DESCRIPTION:
//
//		Header file for wDispatchTable, DispatchVector, and MsgDesc classes.
//
//-*****************************************************************************

#ifndef __DISPATCH_HPP
#define __DISPATCH_HPP

/*
 *	MsgDesc class
 */

class MsgDesc 
{
		static int CompareMsgKeys(const MsgDesc *a, const MsgDesc *b);
        friend class wDispatchTable;

	public:
		MsgDesc();
		MsgDesc( ulong mId, ushort cId );

		ulong msgId;
		ushort ctrlId;
};

/*
 *	DispatchVector class
 */

typedef long (bEventListener::*wMessageMethod)(wMessage);

class DispatchVector
{
		wMessageMethod method;
		bEventListener *listener;
		MsgDesc key;
        friend class wDispatchTable;

	public:
		DispatchVector( bEventListener *messageListener,
						wMessageMethod messageListenerMethod, 
		                ulong messageId, ushort controlId=0 );
		~DispatchVector();
        long Dispatch(wMessage& m) { return (listener->*method)(m); }
};

/*
 *	wDispatchTable class
 */

class wDispatchTable : public tMap<MsgDesc, DispatchVector>
{
	public:
		wDispatchTable();
		bool Enable( bEventListener *messageListener,
					 wMessageMethod messageListenerMethod, 
		             ulong messageId, ushort controlId=0 );
		bool Disable( ulong messageId, ushort controlId=0 );
};

#endif // __DISPATCH_HPP
