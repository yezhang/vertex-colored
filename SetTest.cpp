#include <gtest\gtest.h>

//#include <set>

#include "helper.h"
#include <iostream>
#include "expandcoloringalgorithm.h"

using namespace std;

bool testAltorithm()
{
	Helper hper;
	BoostGraph  g = hper.generateGraph();
	unsigned int colorNum = 5;
	unsigned int vNum = num_vertices(g);

	map<int,int> vertexColorMap;//first, vertexIndex; second, colorIndex; (vertexIndex, colorIndex)
	for(int i = 0; i < vNum; ++i)
	{
		if(0 <= i && i <= 9){
			vertexColorMap.insert(pair<int,int>(i,i%5));
		}else if(10 <= i && i <= 13){
			vertexColorMap.insert(pair<int,int>(i,i%5+1));
		}else{
			vertexColorMap.insert(pair<int,int>(i,i%6));
		}
	}

	ExpandColoringAlgorithm eca(colorNum,g);

	list<vector<int> > re = eca.expandOneColor(4);
	list<vector<int> >::iterator itr;
	cout << "output " << endl;
	for(itr = re.begin(); itr != re.end(); ++itr)
	{
		vector<int> v = *itr;
		if(v.size() == colorNum){
			for(int i = 0; i < v.size(); ++i)
			{
				cout << v[i] << ",";
			}
			cout << endl;
		}
	}

	return true;
}

//bool testSetEqual()
//{
//	set<int> s1;
//	int nodes[] = {0,2, 3};
//	s1.insert(nodes, nodes+3);
//		set<int> s2;
//	int nodes2[] = { 2, 3, 0};
//	s2.insert(nodes2, nodes2+3);
//
//	return (s1 == s2);
//}

TEST(ExpandAlgorithmTest, ExpandOneColorTest)
{
	EXPECT_TRUE(testAltorithm());
	//EXPECT_TRUE(testSetEqual());
	SUCCEED();
}

//TEST(STLTest, SetEqualTest)
//{
//	EXPECT_TRUE(testSetEqual());
//	SUCCEED();
//}
//
//TEST(STLTest, SetEqualOperatorTest)
//{
//	set<int> s1;
//	set<int> s2;
//	set<int> s3;
//	set<int> s4;
//
//	set<set<int> > paths1;
//	set<set<int> > paths2;
//
//	int set1[] = { 0, 2, 3 };
//	int set3[] = { 3, 2, 0 };
//	int set2[] = { 3, 12, 6 };
//	int set4[] = { 6, 3, 12 };
//
//	s1.insert(set1, set1+3);
//	s2.insert(set2, set2+3);
//
//	paths1.insert(s1);
//	paths1.insert(s2);
//
//	s3.insert(set3, set3+3);
//	s4.insert(set4, set4+3);
//
//	paths2.insert(s3);
//	paths2.insert(s4);
//
//	EXPECT_EQ(paths1,paths2);
//
//	SUCCEED();
//}