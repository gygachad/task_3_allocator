#include <string>
#include <gtest/gtest.h>
#include "allocator.h"

#include "version.h"

using namespace std;

class TestSerialization : public ::testing::Test {
public:
    TestSerialization() { /* init protected members here */ }
    ~TestSerialization() { /* free protected members here */ }
    void SetUp() { /* called before every test */ }
    void TearDown() { /* called after every test */ }

protected:
    /* none yet */
};

TEST_F(TestSerialization, MainTest)
{
    EXPECT_TRUE(version() > 0);

    map<int, string, less<int>, linear_allocator<pair<const int, string>>> m;

    for (int i = 0; i < 0x20000; i++)
        m[i] = to_string(i);

    for (int i = 0; i < 0x20000; i++)
        m[i] = "_" + m[i] + "_";

    for (int i = 0; i < 0x20000; i++)
        EXPECT_TRUE(m[i] == "_" + to_string(i) + "_");
}

int main(int argc, char** argv) 
{    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}