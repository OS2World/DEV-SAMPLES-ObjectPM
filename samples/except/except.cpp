#define NoWindows
#include <objectpm.hpp>

#include <iostream.h>
#include <stdlib.h>

class notify : public bEventListener
{
    ostream& out;
public:
    notify(ostream& stream) : out(stream) {}
    ulong error(bException* except);
};

ulong
notify :: error(bException* except) 
{
    out << endl << "Exception #" << hex << except->exception << " @"
        << except->Control->ctx_RegEip << endl;

    exit(except->exception);
    return 1;   // handled
}

short bMainThread::Start() 
{
    float d= 5.0, f= 4.8;
    memcpy(0, &d, sizeof(float));
    return d/(f-f);     // cause divide by zero except
}

int
main(int argc, char* argv[])
{
	bApp		thisApp;
	bMainThread priThread(argc, argv, ThreadRaw);

	cout << "\nExceptions Demonstration Program\n";
	cout << "Copyright (C), 1995 Secant Technologies, Inc. All rights reserved.\n\n";

    notify le(cerr);
    priThread.AddExceptionHandler(AccessViolation, Signal, &le, EXCEPTIONMETHOD(notify,error) );
 
    return  priThread.Start();     
}

