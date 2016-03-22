#include "Error.h"

/* Implementation of class Error */
void Error::Report() const
{
	cerr <<  message << " @ char " << ((index == -1) ? "N/A" : to_string(index)) << endl << endl;
	cerr << "Program exited.\n\n";

	system("pause");
	exit(-1);
}

//End of implementation of class Error