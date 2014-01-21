#include <gtest\gtest.h>

#include "..\helper.h"
#include <iostream>
#include "..\expandcoloringalgorithm.h"

using namespace std;

class NumberPair
{
	
public:
	NumberPair(int _k, int _b)
	{
		k = _k;
		p = _b;
	}
	int k;
	int p;

	friend ostream& operator << (ostream& os, const NumberPair& np)
	{
		os << "(" << np.k << "," << np.p << ")";  
		return os; 
	}
};

class EfficientTest: public ::testing::TestWithParam<NumberPair>
{

};

bool testAlgorithm(int k, int p)
{
	Helper hper;
	BoostGraph  g = hper.generateGraphFromNumber(k,p);
	unsigned int colorNum = k;
	unsigned int vNum = num_vertices(g);

	ExpandColoringAlgorithm eca(colorNum,g);

	list<vector<int> > re = eca.expandOneColor(0);
	//list<vector<int> >::iterator itr;
	/*cout << "output " << endl;
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
	}*/

	return true;
}



TEST_P(EfficientTest, ExpandOneColorCaseTest)
{
	struct NumberPair para = GetParam();

	EXPECT_TRUE(testAlgorithm(para.k, para.p));
	//EXPECT_TRUE(testSetEqual());
	SUCCEED();
}

INSTANTIATE_TEST_CASE_P(KPN,EfficientTest,testing::Values(	
	NumberPair(6, 1),
	NumberPair(3, 2),
	NumberPair(4, 2),
	NumberPair(5, 2),
	NumberPair(6, 2),
	NumberPair(7, 2),
	NumberPair(8, 2)
	));