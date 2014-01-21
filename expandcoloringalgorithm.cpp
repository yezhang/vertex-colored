#include "expandcoloringalgorithm.h"
#include <QDebug>

ExpandColoringAlgorithm::ExpandColoringAlgorithm(int cNum, BoostGraph& graph)
    :colorNum(cNum),g(graph)
{
    vertexNum = num_vertices(graph);
	currentPath.reserve(cNum);
}

void ExpandColoringAlgorithm::printColorNeighbours(vector<vector<int> > coloredNeighbours)
{
    for(unsigned int i = 0; i < coloredNeighbours.size(); ++i)
    {
        vector<int> & vertexList = coloredNeighbours.at(i);

        std::cout << "color " << i << " ,";
        for(int j = 0; j < vertexList.size(); ++j)
        {
            std::cout << vertexList[j] << ",";
        }

        std::cout << std::endl;
    }
}

int ExpandColoringAlgorithm::numColorNeighbours(vector<vector<int> > coloredNeighbours)
{
    int sum = 0;
    for(int i = 0; i < coloredNeighbours.size(); ++i)
    {
        vector<int> & vertexList = coloredNeighbours.at(i);
        sum += vertexList.size();
    }

    return sum;
}

void ExpandColoringAlgorithm::printCurrentPaths(list<vector<int> > paths)
{
    list<vector<int> >::iterator itr = paths.begin();

    for(; itr != paths.end(); ++itr)
    {
        vector<int> & vertexList = *itr;

        for(int j = 0; j < vertexList.size(); ++j)
        {
            std::cout << vertexList[j] << ",";
        }

        std::cout << std::endl;
    }
}

bool ExpandColoringAlgorithm::checkNoVertexAccessable(vector<int> accessable)
{
    return numVertexAccessable(accessable) == 0;
}

int ExpandColoringAlgorithm::numVertexAccessable(vector<int> accessable)
{
    int num = 0;
    for(int i = 0; i < accessable.size(); ++i)
    {
        if(accessable[i]){
            num++;
        }
    }

    return num;
}

bool ExpandColoringAlgorithm::checkVertexColorExist(vector<int> vertexpath, int vertexId)
{
    bool isExisted = false;
    for(int i = 0; i < vertexpath.size(); i++)
    {
        isExisted = (g[vertexpath[i]].colorIndex == g[vertexId].colorIndex);
        if(isExisted)
        {
            break;
        }
    }
    return isExisted;
}

bool ExpandColoringAlgorithm::checkVectorInList( list<vector<int> > l, vector<int> v)
{
    bool in = false;
    list<vector<int> >::iterator itr = l.begin();
    for(; itr != l.end(); ++itr)
    {
        if(checkVectorHasSameValues(v,*itr)){
            in = true;
            break;
        }
    }

    return in;
}

bool ExpandColoringAlgorithm::checkVectorEqualsTarget(vector<int> v, vector<int> target)
{
    bool isEqual = false;

    isEqual = (v.size() == target.size());
    if(isEqual == false){
        return isEqual;
    }

    for(unsigned int i = 0; i < v.size(); ++i)
    {
        isEqual = isEqual && (v[i] == target[i]);
    }

    return isEqual;
}

bool ExpandColoringAlgorithm::checkVectorHasSameValues(vector<int> v, vector<int> target)
{
    bool isEqual = false;
    isEqual = (v.size() == target.size());
    if(isEqual == false){
        return isEqual;
    }

    for(unsigned int i = 0; isEqual && i < v.size(); ++i)
    {
        isEqual = isEqual && (find(target.begin(), target.end(), v[i]) != target.end());
    }

    return isEqual;
}


list<vector<int> > ExpandColoringAlgorithm::expandOneStep(vector<int> vertexIndex,vector<int>& accessableFlag)
{
    vector<int>::iterator itr;
    BoostGraph::adjacency_iterator neighbourIt, neighbourEnd;
    vector<vector<int> > coloredNeighbours;

    //initialize coloredNeighbours
    for(unsigned int i = 0; i < colorNum; i++)
    {
        coloredNeighbours.push_back(vector<int>());
    }

    //make it that vertex in "vertexIndex" can't be accessable;
    for(unsigned int i = 0; i < vertexIndex.size(); ++i)
    {
        accessableFlag[vertexIndex[i]] = false;
    }

    //    qDebug() << "vertexIndex.size(): " << vertexIndex.size();
    for(itr = vertexIndex.begin();itr != vertexIndex.end(); ++itr)
    {
        boost::tuples::tie(neighbourIt, neighbourEnd) = adjacent_vertices(*itr, g);

        //int neighbourNum = 0;
        for (; neighbourIt != neighbourEnd; ++neighbourIt)
        {
			//if(accessableFlag[*neighbourIt]) //prevent it from accessing nodes in the current subgraph
			//check whether the neighbour node's color is in the path "vertexIndex".
			if(checkVertexColorExist(vertexIndex,*neighbourIt))
			{
				continue;
			}
			//record the neighbour node                
			int colorIndex = g[*neighbourIt].colorIndex;               

			coloredNeighbours[colorIndex].push_back(*neighbourIt); 

        }
    }

    if(numColorNeighbours(coloredNeighbours) == 0){
        list<vector<int> > returnValue;
        returnValue.push_back(vertexIndex);
        return returnValue;

    }else{
        //printColorNeighbours(coloredNeighbours);
    }


    vector<vector<int> > preResult,nextResult;
    preResult.push_back(vertexIndex);

    for(int i = 0; i < colorNum; i++)
    {
        vector<int>& nodesOfColor_i = coloredNeighbours[i]; //get all the vertex in color i;
        if(nodesOfColor_i.size() < 1)
        {
            continue;
        }

        if(nextResult.empty() == false){
            nextResult.clear();
        }

        for(unsigned int j = 0; j < preResult.size(); j++)
        {
			vector<int> curr(preResult[j]); 
            nextResult.push_back(curr);

            for(unsigned int cIndex = 0; cIndex < nodesOfColor_i.size(); ++cIndex)
            {
                curr = preResult[j];
				int vIndex = nodesOfColor_i.at(cIndex);
                curr.push_back(vIndex);

				//set the node's accessable property be false
				accessableFlag[vIndex] = false;

                nextResult.push_back(curr);
            }
        }

        preResult = nextResult;
    }


    list<vector<int> > returnValue;

    for(unsigned int i = 0; i < preResult.size(); ++i)
    {
        returnValue.push_back(preResult[i]);
    }

    return returnValue;
}


list<vector<int> > ExpandColoringAlgorithm::expandOneVertex(int vertexId)
{
    list<vector<int> > paths;
    vector<int> vertexIndex;
    vertexIndex.push_back(vertexId);
    paths.push_back(vertexIndex);

    vector<int> accessable(this->vertexNum,true); //one accessFlag for one Vertex

    while(checkNoVertexAccessable(accessable) == false){
        int accessableNum = numVertexAccessable(accessable);

        list<vector<int> > temppaths;
        list<vector<int> > ref;
        list<vector<int> >::iterator itr, refitr;

        for(itr = paths.begin(); itr != paths.end(); ++itr)
        {
            ref = expandOneStep(*itr,accessable);

            for(refitr = ref.begin(); refitr != ref.end(); ++refitr){
                temppaths.push_back(vector<int>(*refitr));
            }
        }

        paths.clear();

        list<vector<int> >::iterator tempItr;
        for(tempItr = temppaths.begin(); tempItr != temppaths.end(); ++tempItr)
        {
            if(checkVectorInList(paths,*tempItr) == false)
            {
                paths.push_back(vector<int>(*tempItr));
            }
        }
        temppaths.clear();

        if(numVertexAccessable(accessable) == accessableNum)
        {
            break;
        }
    }

    return paths;
}


//************************************
// Method:    expandOneColor
// FullName:  ExpandColoringAlgorithm::expandOneColor
// Access:    public 
// Returns:   list<vector<int> >
// Qualifier:
// Parameter: int colorId, zero-based
//************************************
list<vector<int> > ExpandColoringAlgorithm::expandOneColor(int colorId)
{
     list<vector<int> > allPaths;
     Vertex_Iterator vItr, vEnd;
     boost::tuples::tie(vItr,vEnd) = vertices(g);


    for(; vItr != vEnd; ++vItr)
    {
        if(g[*vItr].colorIndex == colorId){
            int vertexId = g[*vItr].id;
            list<vector<int> > paths = expandOneVertex(vertexId);

            list<vector<int> >::iterator pathItr = paths.begin();
            for(; pathItr != paths.end(); ++pathItr)
            {
                //only keep finished path, which node number is equal color number
                if((*pathItr).size() == this->colorNum){
                    allPaths.push_back(vector<int>(*pathItr));
                }

            }
        }
    }

    return allPaths;
}

void ExpandColoringAlgorithm::searchOneVertex( int vertexId, int colorNumLeft)
{
	BoostGraph::adjacency_iterator neighbourIt, neighbourEnd;
	int i = 0;
	int currentPathIndex = 0;

	if (colorNumLeft < 1)
	{
		return;
	}
	
	vertexAccessed[vertexId] = true;//visit it

	currentPathIndex = this->colorNum-colorNumLeft;
	

	boost::tuples::tie(neighbourIt, neighbourEnd) = adjacent_vertices(vertexId, g);
	for (; neighbourIt != neighbourEnd; ++neighbourIt)
	{
		if (!vertexAccessed[*neighbourIt] && !checkVertexColorExist(currentPath,*neighbourIt))
		{
			currentPath[currentPathIndex] = vertexId; //visit it

			if (colorNumLeft == 1)//the last colored path
			{
				//print currentPath;

			}else
			{
				searchOneVertex(*neighbourIt, colorNumLeft-1);
			}				
		}
		
		//clear the current path record history
		for ( i = currentPathIndex+1; i < this->colorNum; ++i)
		{
			currentPath[i] = -1;
		}
		
	}
	
}
