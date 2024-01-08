#include <AalTest.h>
#include "../../AalTestTests/source/AalTestTests.h"
#include "../../LexerTests/source/LexerTests.h"
#include "../../ParserTests/source/ParserTests.h"
#include "../../SourceLocationTests/source/SourceLocationTests.h"
#include "../../VirtualMachineTests/source/VirtualMachineTests.h"

int main()
{
    TestRunner runner{};
    QList<TestSuite> testSuites{};
    testSuites << AalTestTestsSuiteSimple();
    testSuites << AalTestTestsSuiteParameterized();
    testSuites << LexerTestsSuite();
    testSuites << ParserTestsSuite();
    testSuites << SourceLocationTests();
    testSuites << VirtualMachineTests();

    runner.run(testSuites);

    return 0;
}