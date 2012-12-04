#include    "tester_interface.hpp"

#define ENABLE_DETRACE__        (1)
#include    "detrace.h"

#include    <string>
#include    <iostream>
using namespace std;

TesterInterface::TesterInterface( const char* _name )
    : name( _name )
{
#if ENABLE_DETRACE__
    OTRACE(clog) << "new tester interface for "
        << "'" << name << "'"
        << endl;
#endif
}

TesterInterface::~TesterInterface()
{
#if ENABLE_DETRACE__
    OTRACE(clog) << "destroy tester interface for "
        << "'" << name << "'"
        << endl;
#endif
}

#undef ENABLE_DETRACE__
