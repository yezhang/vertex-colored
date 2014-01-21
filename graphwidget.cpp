/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include "helper.h"

#include <math.h>
#include <QKeyEvent>

#include <QColor>
#include <QMessageBox>

#include <iostream> // for std::cout
#include <utility> // for std::pair
#include <algorithm> // for std::for_each
#include <functional>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

//! [0]
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0), nodesIsMovable(true),graphIsGray(false), showPathTimerId(0)
{
    QGraphicsScene *scene;
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200,-200,400,400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.9), qreal(0.9));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Elastic Nodes"));
//! [0]

//! [1]
    this->helper = new Helper();
    centerNode = helper->generateGraphInView(this,scene);

    this->pathIndex = -1;
    this->vertexIndexOfPath = -1;
}

GraphWidget::~GraphWidget()
{
    if(this->helper != NULL){
        delete this->helper;
    }
}
//! [1]

//! [2]
void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 50);
}

void GraphWidget::stopAnimation()
{
    this->nodesIsMovable = false;
}

void GraphWidget::startAnimation()
{
    this->nodesIsMovable = true;
}

void GraphWidget::startAlgorightm()
{
    list<vector<int> > paths = this->helper->getAllPaths();
    list<vector<int> >::iterator itr = paths.begin();

    for(; itr != paths.end(); ++itr)
    {
        allColoringPaths.push_back(vector<int>(*itr));
    }

    //this->helper->printAllPaths(paths);
    this->helper->printAllPaths(allColoringPaths);

    this->pathIndex = 0;
    this->vertexIndexOfPath = 0;

    if (!showPathTimerId)
        showPathTimerId = startTimer(1000/2);
}

void GraphWidget::pauseAlgorightm()
{
    killTimer(showPathTimerId);
    showPathTimerId = 0;
}

void GraphWidget::resumeAlgorithm()
{
    if (!showPathTimerId)
        showPathTimerId = startTimer(1000/2);
}

void GraphWidget::stopAlgorithm()
{
    killTimer(showPathTimerId);
    showPathTimerId = 0;

    this->pathIndex = 0;
    this->vertexIndexOfPath = 0;
}

void GraphWidget::nextStepAlgorithm()
{
    if(this->pathIndex >= allColoringPaths.size())
    {
        this->pathIndex = 0;

        stopAlgorithm();

        return;
    }

    //record stop history
    pair<pair<int,int>,vector<int> > step;
    step.first = pair<int,int>(this->pathIndex,this->vertexIndexOfPath);

    vector<int>& path = allColoringPaths[this->pathIndex];
    int vertexId = path[this->vertexIndexOfPath];

    this->helper->unchooseAllNode();

    this->itemsHighlied.push_back(vertexId);

    step.second = vector<int>(this->itemsHighlied);
    stepHistory.push(step);

    this->helper->highlightTheseNodeOnly(this->itemsHighlied);

    for(int i = 0; i < itemsHighlied.size(); ++i)
    {
        cout << this->itemsHighlied[i] << ",";
    }
    cout << endl;

    this->vertexIndexOfPath++;
    if(this->vertexIndexOfPath >= path.size())
    {
        this->pathIndex++;
        this->vertexIndexOfPath = 0;

        this->itemsHighlied.clear();
    }
}

void GraphWidget::previousStepAlgorithm()
{
    if(stepHistory.empty()){
        QMessageBox msgBox;
        msgBox.setText("No Previous Step.");
        msgBox.exec();

        return;
    }

    stepHistory.pop();

    if(stepHistory.empty()){

        this->itemsHighlied.clear();//make sure no items is highlighed when got to the first step.

        QMessageBox msgBox;
        msgBox.setText("No Previous Step.");
        msgBox.exec();

        return;
    }

    pair<pair<int,int>,vector<int> > preStep = stepHistory.top();
    pair<int,int> index = preStep.first;
    this->itemsHighlied = preStep.second;

    this->pathIndex = index.first;
    this->vertexIndexOfPath = index.second;

    this->helper->unchooseAllNode();
    this->helper->highlightTheseNodeOnly(this->itemsHighlied);
}
//! [2]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void GraphWidget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() != timerId && event->timerId() == showPathTimerId)
    {

        nextStepAlgorithm();
        return;
    }

    if(this->nodesIsMovable == false){
        return;
    }

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();
	
    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
//! [4]

#ifndef QT_NO_WHEELEVENT
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

//! [6]
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);


    // Shadow
    QRectF sceneRect = this->sceneRect();
    //QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    //QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    //if (rightShadow.intersects(rect) || rightShadow.contains(rect))
    //painter->fillRect(rightShadow, Qt::darkGray);
    //if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
    //painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
	 QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
	 if (this->GraphIsGray())
	 {
		 gradient.setColorAt(0, Qt::white);
		 gradient.setColorAt(1, Qt::white);
	 }else{
		 gradient.setColorAt(0, Qt::white);
		 gradient.setColorAt(1, Qt::lightGray);
	 }


	//painter->fillRect(rect.intersected(sceneRect), gradient);
	painter->setBrush(Qt::NoBrush);
	painter->drawRect(sceneRect);



//    // Text
//    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
//                    sceneRect.width() - 4, sceneRect.height() - 4);
//    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
//                       "wheel or the '+' and '-' keys"));

//    QFont font = painter->font();
//    font.setBold(true);
//    font.setPointSize(14);
//    painter->setFont(font);
//    painter->setPen(Qt::lightGray);
//    painter->drawText(textRect.translated(2, 2), message);
//    painter->setPen(Qt::black);
//    painter->drawText(textRect, message);
}
//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::resizeEvent(QResizeEvent *event)
{
    this->scene()->setSceneRect(-200,-200,event->size().width(),event->size().height());
    update();
}

//! [7]

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
