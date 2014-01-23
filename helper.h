#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <iostream> // for std::cout
#include <utility> // for std::pair
#include <algorithm> // for std::for_each
#include <functional>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <QColor>
#include <QGraphicsScene>

#include "graphwidget.h"
#include "node.h"

using namespace boost;
using namespace std;

struct Vertex_Info{
    int id;
    string name;
    int colorIndex;
    QColor color;
};

typedef adjacency_list<vecS, vecS, undirectedS, Vertex_Info> BoostGraph; //define structure of a graph
typedef graph_traits<BoostGraph>::vertex_descriptor Vertex;
typedef graph_traits<BoostGraph>::vertex_iterator Vertex_Iterator;

//define a edge type
typedef std::pair<int, int> BoostEdge;

struct ColorPrinter
{
    void print(QColor const & c)
    {
        cout << "(" << c.red() << "," << c.green() << "," << c.blue() << ")" << endl;
    }

    void operator()( QColor& c )
    {
        print(c);
    }
};

// Make convenient labels for the vertices
enum { N1, N2, N3, N4, N5, N6, N7, N8,
       N9, N10, N11, N12, N13, N14, N15, N}; //代表 1，2，3，4, 5, 6, 7, 8 顶点

class Helper
{
private:
//    string names[15] = { "N1", "N2", "N3", "N4", "N5", "N6", "N7", "N8",
//                                "N9", "N10", "N11", "N12", "N13", "N14", "N15"};

    std::vector<QColor> allcolors;
    std::vector<QColor> excluded;

    BoostGraph graph;
    vector<Node*> nodes;
    int colorNum; //the number of used colors
    int vertexNum; //the number of vertexes in "graph"

public:
    Helper();
    ~Helper();

    void printQColor(QColor const & c);
    void printAllPaths(list<vector<int> > re);
    void printAllPaths(vector<vector<int> > re);
	QColor colorToGray(QColor color);

    /**
     * 产生一个或多个唯一的颜色
     * @param count 要产生的颜色的个数
     * @param colors 用于保存生成颜色的向量
     * @param excludeColors 要排除的颜色
     * @return 产生的颜色的个数
     */
    unsigned int getUniqueColors(unsigned int count, std::vector<QColor>& colors,
                                        const std::vector<QColor>& excludeColors);
    Node* showGraphInScene(GraphWidget* view, QGraphicsScene* scene, BoostGraph const & g);

    BoostGraph generateGraph();
	BoostGraph generateGraphFromNumber(int colorNum, int vertexNumPerColor);

    Node* generateGraphInView(GraphWidget* view, QGraphicsScene* scene);
    void highlightTheseNodeOnly(vector<int>& vertexIndex);
    void chooseTheseNodeOnly(vector<int>& vertexIndex);
    void unchooseTheseNodeOnly(vector<int>& vertexIndex);
    void unchooseAllNode();

    list<vector<int> > getAllPaths();
};


#endif // HELPER_H
