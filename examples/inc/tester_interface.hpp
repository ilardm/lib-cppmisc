#pragma once

#include    <string>

class TesterInterface
{
    public:
        TesterInterface( const char* _name );
        ~TesterInterface();

    public:
        virtual bool test() = 0;
        const std::string getName() { return name; };

    protected:
        const std::string       name;
};
