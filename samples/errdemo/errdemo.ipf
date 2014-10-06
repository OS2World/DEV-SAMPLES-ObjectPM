:userdoc.
.* Extended help for Error Demo
:h1 res=1000.Help for Error Demo
:i1 id=general.Help for Error Demo
:p.
This application demonstrates the use of the bCondition, bFacilty,
bConditionHandler, and wStdErrorDialg classes.  Together, these
classes form an error/condition management system that allows these
events to be recorded, reported and logged, and event handlers to be
defined in order to report or handle the conditons. 
:p.
:h2 res=1001.Generate Fatal Error
This menu choice causes a fatal error condition to be recoreded
and dispatched to the default condition handler.  The handler will
dislplay an appropriate message and then terminate the application
:h2 res=1002.Generate Error
This menu choice causes two error condtions to be recorded on thread
1's condition stack and the event dispatcher to be invoked.
:h1 res=2000.Help for Errors
:i1 id=errors.Help for Errors
:p.
This dialog displays error information
:h2 res=2001.0001 Corrupted Application Component
This error occurs when the application discovers that a critical
system component has been damaged.  Please contact the supplier of
the application.
:h2 res=2002.0002 Cannot init IO Sub-system
This error is generated when the ObjectIO subsystem cannot open or
understand the configuration file.
:h2 res=2003.0003 Cannot open ...
The given resource cannot be opened.  Maybe it doesn't exist!
:h2 res=2004.0004 Resource "n" is not available
The given resource cannot be opened because it's in use.  Either an
application on your workstation or on the network is currently making
use of it.
:h2 res=2005.0005 A general error has occurred.
The message box contians the error details and possible courses of
action.
:h2 res=2006.0006 Application Warning
The application is informing you of a situation that it thinks is
important.  This is not an error.
:euserdoc.  



