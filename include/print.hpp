/*  VCS_ID
 *  $Filename:   print.hpp
 *  $Author  :   John Pompeii
 *  $Revision:   1.1  $
 *  $Date:   20 Dec 1991 12:40:44  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */

#ifndef __PRINT_HPP
#define __PRINT_HPP

#define PfmCurrent	  1
#define PfmSelectable 2
#define PfmSystemError  -1
#define PfmUnknownForm  -2
#define PfmUnSelectable -3 
#define PqDefault	  1
#define PqOnHold	  2		 
#define DEFJOBPRIORITY 50


class _EXPORT_ wPrinterForm
{
	private:
		bString formName;
		wDimension pageSize, usePgSize;
		wPointl blClip, trClip;
		ushort flags;

	public:
		wPrinterForm(HCINFO *_hci);
		
		bString	   GetFormName()				{ return formName;  }
		wDimension GetPageSize()				{ return pageSize;  }
		wDimension GetUsablePageSize()			{ return usePgSize; }
		wPointl    GetBottomLeftClipLimit()  	{ return blClip;	}
		wPointl	   GetTopRightClipLimit()		{ return trClip;	}
		bool 	   IsCurrent()					{ return (flags & PfmCurrent) != 0;    }
		bool 	   IsSelectable()				{ return (flags & PfmSelectable) != 0; }
};

class _EXPORT_ wPrinterFormList : public tDList<wPrinterForm>
{
	public:
		wPrinterFormList();
		~wPrinterFormList();
};

struct wPrintProperties
{
	long cb;
 	long version;
	char deviceName[32];
	char propData[1];
};

class _EXPORT_ wPrinterSetup
{
	private:
		bString physName, objName, printer, driver, port, form; 
		DRIVDATA *pdriv;
		ushort jobPriority, btime, etime;
		long LoadDriverData();
		friend class wPrinter;

	public:
		wPrinterSetup(PRQINFO6 *queInfo);
		wPrinterSetup(const char *physName);
		wPrinterSetup(const wPrinterSetup& setup);
		~wPrinterSetup();

		bString           GetPhysicalName()		    { return physName;   }
		bString 		  GetObjectName()			{ return objName;    }
		bString 		  GetQueueProcessor();
		bString			  GetPort() 				{ return port;		 }
		bString 		  GetDriver() 				{ return driver;	 }
		void   			  SetDriver(const char *drvdev) 	{ driver = drvdev;	  }
		ushort  		  GetJobPriority() 					{ return jobPriority; }
		void   			  SetJobPriority(ushort p);
		bString			  GetPrinter() { return printer; }
		ushort			  GetStartTime() { return btime; }
		ushort			  GetUntilTime()	{ return etime; }

		bool              PostJobProperties(bool fSaveable = FALSE, bool fOverrideForm = FALSE);
		wPrintProperties *GetJobProperties();
		void			  SetJobProperties(wPrintProperties *pprop);
		wPrinterFormList *GetFormList();
		wPrinterForm     *GetForm();
		bString			  GetFormName();
		short			  SetForm(wPrinterForm *form);
		short			  SetForm(const char *name);
		bool			  IsHeld();
		bool			  IsDefault();
};


class _EXPORT_ wPrinterList : public tDList<wPrinterSetup>
{
	public:
		wPrinterList();
		~wPrinterList();
};


class _EXPORT_ wPrinterInfo 
{
	public:
		wPrinterInfo() {}
		wPrinterList  *EnumPrintDestinations();
		wPrinterSetup *GetDefaultPrinter();
};


// Print Devices....

class _EXPORT_ wPrinter : public wDevice
{
	public:
		wPrinter(wPrinterSetup *setup, const char *comment = NULL, 
			bool fRaw = FALSE, bool fInfo = FALSE);

        void StartPrintJob(const char *docname);
        void EndPrintJob();
        void CancelPrintJob();
        void FormFeed();
		void SendRawBytes(ushort count, void *datap);
};

class _EXPORT_ wTextPrinter : public wPrinter
{
	private:
		wPresSpace *pPS;
            	
	public:
		wTextPrinter(wPrinterSetup *setup, const char *comment);
        ~wTextPrinter();

 		wPresSpace *TextPrinterPS()   { return pPS; }
        void PutChar(char c);
        char *PutString(char *s);
		void FormFeed();
        void CrLf(short n = 1);
};

#endif // __PRINT_HPP
