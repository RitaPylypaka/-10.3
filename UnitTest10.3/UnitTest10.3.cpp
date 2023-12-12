#include "pch.h"
#include "CppUnitTest.h"
#include "../пр10.3/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest103
{
	TEST_CLASS(UnitTest103)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            string testFileName = "test_addBill.txt";
            Bill testBill = { "TestPlatnik", "TestOderz", 150.5 };

            addBill(testFileName, testBill);

            ifstream file(testFileName);
            string line;
            bool found = false;
            while (getline(file, line)) {
                if (line.find("TestPlatnik") != string::npos) {
                    found = true;
                    break;
                }
            }
            Assert::IsTrue(found);
            file.close();
		}
	};
}
