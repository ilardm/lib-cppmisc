#include    "main.hpp"

#include    <memory>
#include    <iostream>
using namespace std;

#define MKSTR(s)         # s

#define TEST(c) {\
    auto_ptr<c> p( new c( MKSTR(c) ) );\
    bool r = p->test();\
    std::cout << "test of " << p->getName() << ": " << (r?"succeed":"FAILED") << endl;\
    }

#include    "version_tester.hpp"

int main(int argc, char** argv)
{
    TEST(VersionTester);

    return 0;
}
