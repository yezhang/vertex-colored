#include <gtest\gtest.h>

#include <set>
#include <iostream>


using namespace std;

bool testSetEqual()
{
	set<int> s1;
	int nodes[] = {0,2, 3};
	s1.insert(nodes, nodes+3);
	set<int> s2;
	int nodes2[] = { 2, 3, 0};
	s2.insert(nodes2, nodes2+3);

	return (s1 == s2);
}


TEST(STLTest, SetEqualTest)
{
	EXPECT_TRUE(testSetEqual());
	SUCCEED();
}

TEST(STLTest, SetEqualOperatorTest)
{
	set<int> s1;
	set<int> s2;
	set<int> s3;
	set<int> s4;

	set<set<int> > paths1;
	set<set<int> > paths2;

	int set1[] = { 0, 2, 3 };
	int set3[] = { 3, 2, 0 };
	int set2[] = { 3, 12, 6 };
	int set4[] = { 6, 3, 12 };

	s1.insert(set1, set1+3);
	s2.insert(set2, set2+3);

	paths1.insert(s1);
	paths1.insert(s2);

	s3.insert(set3, set3+3);
	s4.insert(set4, set4+3);

	paths2.insert(s3);
	paths2.insert(s4);

	EXPECT_EQ(paths1,paths2);

	SUCCEED();
}