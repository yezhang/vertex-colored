#include "helper.h"
#include "edge.h"
#include <QDebug>
#include "expandcoloringalgorithm.h"
#include <sstream>
#include <fstream>

Helper::Helper()
{
    excluded.push_back(QColor(0,0,0));// exclude white color
    excluded.push_back(QColor(255,255,255)); //exclude black color
    getUniqueColors(colorNum,allcolors,excluded);

	//print all colors
    //std::for_each(allcolors.begin(), allcolors.end(), ColorPrinter());

    // Here we use std::vector as exterior property storage.
    //this->colors.resize(vertexNum);

    //this->graph = NULL;//initialized
}

Helper::~Helper()
{
    
}

void Helper::printQColor(const QColor &c)
{
    qDebug() << "(" << c.red() << "," << c.green() << "," << c.blue() << ")";
}

void Helper::printAllPaths(list<vector<int> > re)
{
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

}

void Helper::printAllPaths(vector<vector<int> > re)
{
    vector<vector<int> >::iterator itr;
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
}

unsigned int Helper::getUniqueColors(unsigned int count, std::vector<QColor> &colors, const std::vector<QColor> &excludeColors)
{
    unsigned int i, j, k, l;
    unsigned int numUnique = 0;
    double slValues[] = {0.0, 1.0, 0.5, 0.8, 0.3, 0.6, 0.9, 0.2, 0.7, 0.4, 0.1};
    QColor baseColors[] =
    {
        QColor(0,0,255),
        QColor(0,255,0),
        QColor(255,0,0),
        QColor(0,255,255),
        QColor(255,255,0),
        QColor(255,0,255),
        QColor(255,255,255)
    };

    for (i = 0; i < sizeof(slValues) / sizeof(slValues[0]); i++)
    {
        for (j = 0; j < sizeof(slValues) / sizeof(slValues[0]); j++)
        {
            for (k = 0; k < sizeof(baseColors) / sizeof(baseColors[0]); k++)
            {
                int newColor[3];
                int maxValue;

                newColor[0] = (int) (baseColors[k].red() * slValues[j] + 0.5);
                newColor[1] = (int) (baseColors[k].green() * slValues[j] + 0.5);
                newColor[2] = (int) (baseColors[k].blue() * slValues[j] + 0.5);

                maxValue = 0;
                for (l = 0; l < 3; l++)
                {
                    if (newColor[l] > maxValue)
                    {
                        maxValue = newColor[l];
                    }
                }

                maxValue = (int) (maxValue * slValues[i] + 0.5);
                for (l = 0; l < 3; l++)
                {
                    if (newColor[l] < maxValue)
                    {
                        newColor[l] = maxValue;
                    }
                }

                QColor colorToInsert;
                colorToInsert.setRed(newColor[0]);
                colorToInsert.setGreen(newColor[1]);
                colorToInsert.setBlue(newColor[2]);

                for (l=0; l<excludeColors.size(); l++)
                {
                    if (excludeColors[l].red() == colorToInsert.red() &&
                            excludeColors[l].green() == colorToInsert.green() &&
                            excludeColors[l].blue() == colorToInsert.blue())
                    {
                        break;
                    }
                }
                if (l == excludeColors.size())
                {
                    for (l = 0; l < colors.size(); l++)
                    {
                        if (colors[l].red() == colorToInsert.red() &&
                                colors[l].green() == colorToInsert.green() &&
                                colors[l].blue() == colorToInsert.blue())
                        {
                            break;
                        }
                    }
                    if (l == colors.size())
                    {
                        colors.push_back (colorToInsert);
                        ++numUnique;
                        if (colors.size() == count)
                        {
                            return numUnique;
                        }
                    }
                }
            }
        }
    }
    return numUnique;
}

Node* Helper::showGraphInScene(GraphWidget* view, QGraphicsScene* scene, const BoostGraph &g)
{

    Node *centerNode;

    BoostGraph::vertex_iterator vertexIt, vertexEnd;
    BoostGraph::adjacency_iterator neighbourIt, neighbourEnd;

    boost::tuples::tie(vertexIt, vertexEnd) = vertices(g);

    Node* nodePtr = NULL;

    for (; vertexIt != vertexEnd; ++vertexIt)
    {
        //qDebug() << g[*vertexIt].name.c_str() << "(" << *vertexIt << ")" << "is connected with ";

        nodePtr = new Node(view,g[*vertexIt].color,*vertexIt + 1);
        nodes.push_back(nodePtr); //save node ptr

        boost::tuples::tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, g);

       /* for (; neighbourIt != neighbourEnd; ++neighbourIt)
        {
            qDebug() << g[*neighbourIt].name.c_str() << "(" << *neighbourIt << ")";
        }*/

        scene->addItem(nodePtr);

        if(*vertexIt == N7){
            centerNode = nodePtr;
        }
    }

    BoostGraph::edge_iterator edgeIt, edgeEnd;
    boost::tuples::tie(edgeIt, edgeEnd) = edges(g);//Get all edges of Graph g

    Vertex src,des;
    for (; edgeIt!= edgeEnd; ++edgeIt)
    {
        src = source(*edgeIt, g);
        des = target(*edgeIt, g);
        scene->addItem(new Edge(nodes[src], nodes[des]));
    }


    nodes[0]->setPos(-50, -50); //N1
    nodes[1]->setPos(0, -50); //N2
    nodes[2]->setPos(150, -50); //N3
    nodes[3]->setPos(-50, 0); //N4
    centerNode->setPos(0, 0);//N5
    nodes[5]->setPos(150, 0);//N6
    nodes[6]->setPos(150, -50); //N7
    nodes[7]->setPos(150, 150); //N8
    nodes[N9]->setPos(200,100); //N9


    return centerNode;
}

BoostGraph Helper::generateGraph()
{
	int i = 0;
	BoostGraph g(N);
    this->vertexNum = 15;
    this->colorNum = 5;

	g = BoostGraph(this->vertexNum);
	
	//BoostEdge edge_array[] = {BoostEdge(N1,N2), BoostEdge(N1,N7),
	//	BoostEdge(N2,N8),
	//	BoostEdge(N3,N4), BoostEdge(N3,N5),
	//	BoostEdge(N6,N11),
	//	BoostEdge(N7,N3),BoostEdge(N7,N12),BoostEdge(N7,N14),
	//	BoostEdge(N11,N15),
	//	BoostEdge(N12,N9),BoostEdge(N12,N10),
	//	BoostEdge(N13,N14),
	//	BoostEdge(N15,N13)};

    BoostEdge edge_array[] = {BoostEdge(N1,N2), BoostEdge(N1,N7),
                              BoostEdge(N2,N8), BoostEdge(N2,N13),
                              BoostEdge(N3,N4), BoostEdge(N3,N5),
                              BoostEdge(N6,N11), BoostEdge(N6,N12),
                              BoostEdge(N7,N3),BoostEdge(N7,N12),BoostEdge(N7,N14),
							  BoostEdge(N8,N6),
							  BoostEdge(N10,N4),
                              BoostEdge(N11,N15),
                              BoostEdge(N12,N9),BoostEdge(N12,N10),
                              BoostEdge(N13,N14),
                              BoostEdge(N15,N13)};
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);

//    colors[0] = colors[5] = allcolors[0];
//    colors[1] = colors[6] = colors[10] = allcolors[1];
//    colors[2] = colors[7] = colors[11] = colors[14] = allcolors[2];
//    colors[3] = colors[8] = colors[12] = allcolors[3];
//    colors[4] = colors[9] = colors[13] = allcolors[4];

   

    //initialize each vertex by id, name, colorIndex, color;
    for(i = 0; i < vertexNum; ++i)
    {
        (g)[i].id = i;
        std::stringstream ss;
        ss << i+1;
        (g)[i].name = ss.str();

        if(0 <= i && i <= 9){
            (g)[i].colorIndex = i%5;
            (g)[i].color = allcolors[i%5];
        }else if(10 <= i && i <= 13){
            (g)[i].colorIndex = i%5+1;
            (g)[i].color = allcolors[i%5+1];
        }else{
            (g)[i].colorIndex = i%6;
            (g)[i].color = allcolors[i%6];
        }
    }
	   
    for (i = 0; i < num_edges; ++i)
	{
		add_edge(edge_array[i].first, edge_array[i].second, g);
	}        

    return g;
}

Node* Helper::generateGraphInView(GraphWidget *view, QGraphicsScene* scene)
{
    this->graph = generateGraph();
    Node* centerNode = showGraphInScene(view,scene, this->graph);

    //centerNode->setIsHighlighted(true);

    return centerNode;
}

void Helper::highlightTheseNodeOnly(vector<int> & vertexIndex)
{
    for(unsigned int i = 0; i < vertexNum; ++i){
        nodes[i]->setIsHighlighted(false);
    }

    cout << "Highlighting: ";
    for(unsigned int i = 0; i < vertexIndex.size(); ++i)
    {
        cout << vertexIndex[i] << ",";
        nodes[vertexIndex[i]]->setIsHighlighted(true);

    }

    cout << endl;

    if(vertexIndex.size() == colorNum){
        chooseTheseNodeOnly(vertexIndex);
    }
}

void Helper::chooseTheseNodeOnly(vector<int> &vertexIndex)
{
    for(unsigned int i = 0; i < vertexNum; ++i){
        nodes[i]->setChoosen(false);
    }

    for(unsigned int i = 0; i < vertexIndex.size(); ++i)
    {
        nodes[vertexIndex[i]]->setChoosen(true);
    }
}

void Helper::unchooseTheseNodeOnly(vector<int> &vertexIndex)
{
    for(unsigned int i = 0; i < vertexIndex.size(); ++i)
    {
        nodes[vertexIndex[i]]->setChoosen(false);
    }
}

void Helper::unchooseAllNode()
{
    for(unsigned int i = 0; i < vertexNum; ++i){
        nodes[i]->setChoosen(false);
    }
}

list<vector<int> > Helper::getAllPaths()
{
    ExpandColoringAlgorithm eca(colorNum, this->graph);

    list<vector<int> > re = eca.expandOneColor(0);
	vector<set<set<int> > > pathsByAllColors(this->colorNum);

	for (int i = 0; i < this->colorNum; i++)
	{
		printQColor(this->allcolors[i]);
		re = eca.expandOneColor(i);
		set<set<int> > iColorPaths;

		
		list<vector<int> >::iterator itr = re.begin();

		vector<int> onePath;
		
		for (itr = re.begin(); itr != re.end(); ++itr)
		{
			onePath = *itr;
			set<int> onePathSet;
			for (int j = 0; j < onePath.size(); ++j)
			{
				onePathSet.insert(onePath[j]);
			}
			iColorPaths.insert(onePathSet);
		}
		
		pathsByAllColors[i] = iColorPaths;

		cout << "ByColor " << i << ", there are " << pathsByAllColors[i].size() << " paths" << endl;

	}

	ofstream fout;

	for (int i = 0; i < pathsByAllColors.size(); ++i)
	{
		
		ostringstream outStr;
		outStr << i;
		
		outStr.flush();

		string fileName = "Color_" + outStr.str() + ".txt";

		
		fout.open(fileName, ios::out | ios::app);

		fout << "(" << allcolors[i].red() << "," << allcolors[i].green() << "," << allcolors[i].blue() << ")" << endl;

		set<set<int> > icolorPaths = pathsByAllColors[i];
		for (set<set<int> >::iterator pitr = icolorPaths.begin(); pitr != icolorPaths.end(); ++pitr)
		{
			set<int> path = *pitr;
			for (set<int>::iterator nodeItr = path.begin(); nodeItr != path.end(); ++nodeItr )
			{
				fout << (*nodeItr) + 1 << ",";
			}
			fout << endl;
		}
		
		fout.close();
	}
	
	//get the differences 
	set<set<int> > color0Path = pathsByAllColors[0];
	set<set<int> > color1Path = pathsByAllColors[1];
	set<set<int> > diff;
	set_difference(color1Path.begin(), color1Path.end(), color0Path.begin(), color0Path.end(), inserter(diff, diff.begin()));
	set<set<int> >::iterator diffItr = diff.begin();

	for (diffItr = diff.begin(); diffItr != diff.end(); ++diffItr)
	{

	}
	
    return re;
}

QColor Helper::colorToGray( QColor color )
{
	int Y = qGray(color.red(), color.green(), color.blue());
	
	return QColor(Y,Y,Y,color.alpha());
}
