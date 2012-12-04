#include    "version_tester.hpp"

#include    <iostream>
using namespace std;

#include    "examples_version.hpp"
#include    "libcppmisc_version.h"

VersionTester::VersionTester( const char* _name )
    : TesterInterface( _name )
{
}

VersionTester::~VersionTester()
{
}

bool VersionTester::test()
{
    cout << "=== running tests for " << name << " =============================" << endl;

    cout << "examples version bitmask: 0x"
        << std::hex
        << MACROVERSION_NAME_FOR(examples)
        << std::dec
        << endl;

    cout << "examples version (object): "
        << VERSIONO_NAME_FOR(examples).toString()
        << endl;

    cout << name << " ---------------------------------------------------------" << endl;

    cout << "libcppmisc version bitmask: 0x"
        << std::hex
        << MACROVERSION_NAME_FOR(libcppmisc)
        << std::dec
        << endl;

    cout << "examples version (object): "
        << VERSIONO_NAME_FOR(libcppmisc).toString()
        << endl;

    cout << name << " ---------------------------------------------------------" << endl;

    cout << "libcppmisc version required by examples bitmask: 0x"
        << std::hex
        << MACROVERSION_RNAME_OF_FOR(examples,libcppmisc)
        << std::dec
        << endl;

    cout << "libcppmisc version required by examples (object): "
        << VERSIONO_RNAME_OF_FOR(examples,libcppmisc).toString()
        << endl;

    cout << name << " ---------------------------------------------------------" << endl;

    bool ct_compat = MACROVERSION_COMPATIBLE_WITH(examples,libcppmisc);
    bool rt_compat = VERSIONO_RNAME_OF_FOR(examples,libcppmisc).isCompatibleWith( VERSIONO_NAME_FOR(libcppmisc) );

    cout << "compile-time compatibility check: "
        << ct_compat 
        << endl;

    cout << "run-time compatibility check: "
        << rt_compat 
        << endl;

    cout << name << " ---------------------------------------------------------" << endl;

    return (   ct_compat
             & rt_compat
           );
}
