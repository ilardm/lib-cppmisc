#pragma once

#include    "tester_interface.hpp"

class VersionTester : public TesterInterface
{
    public:
        VersionTester( const char* _name );
        ~VersionTester();

    public:
        virtual bool test();
};
