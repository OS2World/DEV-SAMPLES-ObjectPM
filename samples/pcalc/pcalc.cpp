/*  VCS_ID
 *  $Filename:   pcalc.cpp
 *  $Author  :   Mike Flis
 *  $Revision:   1.2  $
 *  $Date:   28 Dec 1991 14:36:04  $
 *
 *	Copyright (c)	1995 by Secant Technologies
 *
 */
 
// PROGRAMMERS CALCULATOR

extern "C" {
	#include <ctype.h>
	#include <stdlib.h>
	#include <string.h>
}

#include "pcalc.hpp"

Define_tStack(stknode)  // instantiate Stack methods

static short   
	NumID[]={IDF,IDE,IDD,IDC,IDB,IDA,ID9,ID8,ID7,ID6,ID5,ID4,ID3,ID2,ID1,ID0},
	FuncID[]={IDCLRALL,IDBACK,IDANS,IDEQ,IDCLEAR,IDSIGN,IDSHR,IDSHL,IDNOT,IDXOR,      
				IDOR,IDAND,IDMOD,IDDIV,IDMULT,IDMINUS,IDPLUS},
	ModeID[]={MDEC,MHEX,MOCT,MBIN};


short MainThread :: Start()
{
	CalcWin	cw;
	Exec();

	return 0;
}


// CONSTRUCT THE CALCULATOR FRAME WINDOW INTO WHICH THE CALCULATOR WILL GO
CalcWin :: CalcWin()
{
	CreateWindow(FaMinButton | FaSysMenu | FaDlgBorder |
		FaTaskList | FaTitleBar);

	SetCaption("Programmer's Calculator");		// SET TITLE BAR
	SetSwitchTitle("Programmer's Calculator");	// SET SWITCH LIST TITLE
	SetIcon(new wIcon(ResIcon, ID_ICON));		// ATTACH ICON

	// THE DIALOG BOX
	pc=new PCalc(this, PCALC); 

	// PUT FRAME AROUND DIALOG BOX
	ChangeFrameSize(pc);		   	
	ChangePosition(PosCenter);

	// CHANGE SYSTEM MENU -- ADD AN ABOUT BOX
	psys=new wSysMenu(this);
	psys->AppendSeparator();
	psys->AppendItem(ID_ABOUT,"About Calculator...");

	// SHOW THE CALCULATOR
	Show();	   	
	ToTop();
}


// PROCESS ABOUT BOX SYSTEM MENU COMMAND 
long CalcWin :: MenuCommand(wCommandMsg m)
{
	if (m.usCmd() == ID_ABOUT)
	{
		AboutDialog	about(this);
		return TRUE;
	}
	else
		return Default((wMessage&)m);
}


// PROCESS INITDLG MESSAGE -- SET UP BUTTONS, FLAGS, ETC
long PCalc :: InitDlg(wInitDlgMsg)
{
	short	lp;

	for (lp = 0 ; lp < 16 ;lp++)
		BNum[lp]=new wPushButton(this, NumID[lp]);

	for (lp = 0 ; lp < 4 ; lp++)
		BMode[lp]=new wRadioButton(this,ModeID[lp]);

	answer = new wStaticControl(this,IDANS);	// ANSWER WINDOW

	BMode[0]->Click();
	SetMode(0);
	answer->SetText("0");
	ChangePosition(wPointl(0,0));		// POSITION THE DLG WINDOW
	inNum = FALSE;
	lastop=0;
	total = 0;
	return TRUE;
}

// SET THE CALCULATOR MODE (DECIMAL, HEX, OCTAL, OR BINARY)
void PCalc :: SetMode(short n)
{	
	static short 
		ModePos[]={6,0,8,14},		// INDEX INTO NUMID FOR DEC,HEX,OCT,BIN
		ModeBase[]={10,16,8,2};		// BASES

	short	lp;

	// DISABLE & ENABLE BUTTONS FOR CURRENT MODE (EG A-F FOR DECIMAL)
	for (lp=0 ; lp < ModePos[n] ; lp++)
		BNum[lp]->Disable();

	for ( ; lp<16 ; lp++)
		BNum[lp]->Enable();

	Mode = n;
	Base = ModeBase[Mode];
}

// IS THIS BUTTON ID A NUMBER -- RETURNS VALUE
short IsNum(short n)
{
	int lp;
	for (lp = 0 ; lp < 16 ; lp++)
	{
		if (n == NumID[lp])
			return 15-lp;
	}
	return -1;
}

long PCalc :: PopStk()
{
	stknode	*p;
	long	num;

	p=stk.Pop();
	num=p->value;
	delete p;
	return num;
}

// DO THE CALCULATION OFF THE STACK
long PCalc :: DoCalc()
{
	long	num1,num2,op;

	num2=PopStk();	// SECOND VALUE
	op=PopStk();	// OPERATION
	num1=PopStk();	// FIRST VALUE
	switch(op)
	{
		case IDPLUS:
			return num1 + num2; 
		case IDMINUS:
			return num1 - num2; 
		case IDMULT:
			return num1 * num2; 
		case IDDIV:
			if (!num2)	// DIVIDE BY 0
			{
				wMessageBox mb(this,"Attempt to divide by 0","Error",MbIconAsterisk|MbOk);
				return 0;
			}
			return num1 / num2; 
		case IDMOD:
			return num1 % num2; 
		case IDAND:
			return num1 & num2; 
		case IDOR:
			return num1 | num2; 
		case IDXOR:
			return num1 ^ num2;
		default:
			return 0;
	}
}

// PUT THE TOTAL INTO THE ANSWER WINDOW, CONVERTING TO CURRENT BASE
void PCalc :: SetAnswer(long n)
{
	char	buf[100];
	int		lp;

	ltoa(n,buf,Base);
	// ADJUST ANY HEX CHARACTERS TO UPPER CASE (ltoa USES LOWERCASE)
	if (Base==16)
		for(lp=0 ; buf[lp] ; lp++) buf[lp] = toupper(buf[lp]);

	answer->SetText(buf);
}

// PROCESS CLICK MESSAGES FROM CALCULATOR MODE RADIO BUTTONS
long PCalc :: Control(wControlMsg m)
{
	int	lp;
	if (m.usNotifyCode() == BnClicked)
	{
		for (lp = 0 ; lp < 4 ; lp++)
		{
			if (m.id() == ModeID[lp])
			{
				SetMode(lp);
				SetAnswer(total);
				break;
			}
		}
	}
	return FALSE;
}

// RETURNS ORDER OF OPERAND (1=HIGH ORDER--MULT, DIV; 0=LOW ORDER--ADD,SUBTRACT; 
//							 -1=EQUAL, -2==ANY OTHER);
OrderOp(short op)
{
	switch(op)
	{
		case IDMULT:
		case IDDIV:
		case IDMOD:
		case IDAND:
			return 1;
		case IDPLUS:
		case IDMINUS:
		case IDOR:
		case IDXOR:
			return 0;
		case IDEQ:
		case IDCLEAR:
			return -1;
		default:
			return -2;
	}
}

// PROCESS PUSH BUTTON COMMANDS -- MAIN PROCESSING
long PCalc :: PushButtonCommand(wCommandMsg m)
{
	short		num, ctlid;
	long		oldtot;

	oldtot=total;

	if ((num=IsNum(ctlid=m.usCmd())) >= 0)
	{
		if (!inNum) 
			total = 0;
		total = total * Base + num;
		inNum = TRUE;		
	}
	else 
		switch(ctlid)
		{
			case IDBACK:	// REMOVE LAST NUMBER
				if (inNum) 
					total /= Base;
				break;
			case IDCLEAR:	// CLEAR TOP OF STACK
				if (lastop == IDCLEAR) 
					break;
				if (!stk.Top()) 
				{
					total = 0;
					inNum = FALSE;
					break;
				}
				if (!inNum)	// CLEAR THE OP
					delete stk.Pop();
				else
				{
					inNum = FALSE;
					total = 0;
				}
				lastop=ctlid;
				break;
			case IDCLRALL:	// CLEAR ALL
				stk.Clear();
				inNum = FALSE;
				total = 0;
				break;
			case IDSIGN:	// SWITCH SIGN
				total *= -1;
				break;
			case IDSHL:		// SHIFT LEFT 1
				inNum = FALSE; 
				total <<= 1;
				break;
			case IDSHR:		// SHIFT RIGHT 1
				inNum = FALSE; 
				total >>= 1;
				break;
			case IDNOT:
				inNum = FALSE;
				total ^= 0xFFFFFFFF;
				break;
			case IDEQ:
				if (stk.Top() &&			// CHECK IF USER PRESSED =
					stk.Top()->type == OP	// RIGHT AFTER SOME OTHER
					&& !inNum) 				// OP (!inNum) -> GET RID OF OP
					PopStk();								 
				while (stk.Entries() > 1)
				{
					stk.Push(new stknode(NUM, total));
					total = DoCalc();
				}
				inNum = FALSE;
				lastop = ctlid;
				break;
			case IDMULT:
			case IDDIV:
			case IDMOD:
			case IDAND:
				// IGNORE IF 2 OPERATIONS IN A ROW
				if (!(inNum || OrderOp(lastop) == -1)) 
					break;

				// CHECK IF PREVIOUS OP WAS NOT LOW ORDER THEN CALC				
				stk.Push(new stknode(OP, total));	// PUSH CURRENT VALUE
				if (OrderOp(lastop)!=0 && stk.Entries() > 2)	
					stk.Push(new stknode(NUM, total=DoCalc()));

				stk.Push(new stknode(OP, (long)ctlid));	// PUSH OPERATION
				inNum = FALSE;
				lastop = ctlid;
				break;
			case IDPLUS:
			case IDMINUS:
			case IDOR:
			case IDXOR:
				// IGNORE IF 2 OPERATIONS IN A ROW
				if (!(inNum || OrderOp(lastop) == -1)) 
					break;

				stk.Push(new stknode(NUM, total));	// PUSH CURRENT VALUE
				if (stk.Entries() > 2)
					stk.Push(new stknode(NUM, total = DoCalc()));	// CALCULATE

				stk.Push(new stknode(OP, (long)ctlid));	// PUSH OPERATION
				inNum = FALSE;
				lastop = ctlid;
				break;
		}

	if (oldtot != total)
		SetAnswer(total);

	return FALSE;
}


