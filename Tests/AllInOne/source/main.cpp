#include <AalTest.h>
#include "../../LexerTests/source/LexerTests.h"
#include "../../ParserTests/source/ParserTests.h"
#include "../../TypeCheckerTests/source/TypeCheckerTests.h"
#include "../../SourceLocationTests/source/SourceLocationTests.h"
#include "../../VirtualMachineTests/source/VirtualMachineTests.h"

int main()
{
    AalTest::TestRunner runner{};
    QList<AalTest::TestSuite> testSuites{};
    testSuites << LexerTestsSuite();
    testSuites << ParserTestsSuite();
    testSuites << TypeCheckerTestsSuite();
    testSuites << SourceLocationTests();
    testSuites << VirtualMachineTests();

    runner.run(testSuites);

    return 0;
}