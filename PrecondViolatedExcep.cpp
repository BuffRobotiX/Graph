#include "PrecondViolatedExcep.h"  

PrecondViolatedExcep::PrecondViolatedExcep(const string& message): logic_error("EXCEPTION! " + message)
{
}  // end constructor

// End of implementation file.