#ifndef EXPANDCOLORINGALGORITHM_H
#define EXPANDCOLORINGALGORITHM_H

#include "helper.h"
#include <vector>
#include <list>
#include <map>
#include <boost/property_map/vector_property_map.hpp>
using namespace std;

class ExpandColoringAlgorithm
{
private:
    int vertexNum;
    int colorNum;
    vector<bool> vertexAccessed;
    BoostGraph& g;
	vector<int> currentPath; // when search, record the vertex index int current path;

private:

    /// Process one subgraph, and step further, to get more larger subgraphs based on itself.
    /// \brief expandOneStep
    /// \param subgraph
    /// \param g
    /// \return
    ///
    list<vector<int> > expandOneStep(vector<int> subgraph,vector<int>& accessFlag);

    /// Process one vertex, get all coloring subgraphs consist of it
    /// \brief expandOneVertex
    /// \param vertexid
    /// \param g
    /// \return
    ///
    list<vector<int> > expandOneVertex(int vertexid);
	void searchOneVertex(int vertexId, int colorNumLeft);

    void printColorNeighbours(vector<vector<int> > coloredNeighbours);
    int numColorNeighbours(vector<vector<int> > coloredNeighbours);
    void printCurrentPaths(list<vector<int> > paths);
    bool checkNoVertexAccessable(vector<int> accessable);
    int numVertexAccessable(vector<int> accessable);
    bool checkVertexColorExist(vector<int> vertexpath, int vertexId);
    bool checkVectorInList(list<vector<int> > list, vector<int> v);
    bool checkVectorEqualsTarget(vector<int> v, vector<int> target);
    bool checkVectorHasSameValues(vector<int> v, vector<int> target);

public:
    ExpandColoringAlgorithm(int cNum, BoostGraph& g);

    /// Process all vertex in one color
    /// \brief expandOneColor
    /// \param colorId, zero-based
    /// \param g
    /// \return all the coloring subgraph
    ///
    list<vector<int> > expandOneColor(int colorId);
};


#endif // EXPANDCOLORINGALGORITHM_H
