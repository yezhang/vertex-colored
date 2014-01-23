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

#include "edge.h"
#include "node.h"
#include "graphwidget.h"


#include <qmath.h>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

//! [0]
//Node::Node(GraphWidget *graphWidget)
//    : graph(graphWidget)
//{
//    setFlag(ItemIsMovable);
//    setFlag(ItemSendsGeometryChanges);
//    setCacheMode(DeviceCoordinateCache);
//    setZValue(-1);
//}


Node::Node(GraphWidget *graphWidget, QColor color, int id, int colrId)
    : graph(graphWidget),nodeId(id),nodeColor(color),colorId(colrId),
      radius(30),isHighlighted(false),choosen(false)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

//! [0]

//! [1]
void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}
//! [1]

//! [2]
void Node::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }
//! [2]

//! [3]
    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
	//qreal delta = 0;

    foreach (QGraphicsItem *item, scene()->items()) {
        Node *node = qgraphicsitem_cast<Node *>(item);
        if (!node)
            continue;

        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();	

        double l = 2 * (dx * dx + dy * dy);

		//delta = qSqrt(dx*dx + dy*dy);

        if (l > 0) {
            xvel += (dx * 200.0) / l;
            yvel += (dy * 200.0) / l;
        }
    }
//! [3]

//! [4]
    // Now subtract all forces pulling items together
    double weight = (edgeList.size() + 1)*20;
    foreach (Edge *edge, edgeList) {
        QPointF vec;
        if (edge->sourceNode() == this)
            vec = mapToItem(edge->destNode(), 0, 0);
        else
            vec = mapToItem(edge->sourceNode(), 0, 0);
        xvel -= vec.x() / weight;
        yvel -= vec.y() / weight;
    }
//! [4]

//! [5]
    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;
//! [5]

//! [6]
    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + radius), sceneRect.right() - radius));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + radius), sceneRect.bottom() - radius));
}
//! [6]

//! [7]
bool Node::advance()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}
//! [7]

//! [8]
QRectF Node::boundingRect() const
{
    qreal adjust = 4;
    qreal width = 2*(radius + adjust);
    return QRectF( -radius - adjust, -radius - adjust, width, width);
}
//! [8]

//! [9]
QPainterPath Node::shape() const
{
    QPainterPath path;
    qreal diameter = 2*radius;
    path.addEllipse(-radius, -radius, diameter, diameter);
    return path;
}
//! [9]

//! [10]
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(Qt::darkGray);
//    painter->drawEllipse(-15, -15, 40, 40);


    QRadialGradient gradient(-3, -3, 40);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);

        gradient.setColorAt(1, nodeColor.light(120));
        gradient.setColorAt(0, QColor(Qt::white).light(120));
    } else {
        if(this->getChoosen()){
            gradient.setColorAt(0, QColor(255, 0, 255, 127));
        }else if(this->getIsHighlighted()){
            gradient.setColorAt(0, QColor(Qt::white).light(120));
        }else{
            gradient.setColorAt(0, nodeColor.light(120));
        }
        if(this->getChoosen()){
            gradient.setColorAt(1, QColor(255, 0, 255, 127));
        }else{
            gradient.setColorAt(1, Qt::white);
        }
    }
    painter->setBrush(gradient);

    if(this->getIsHighlighted()){
        painter->setPen(QPen(nodeColor, 4));
    }else{
        painter->setPen(QPen(Qt::black, 0));
    }

    qreal diameter = 2*radius;
    painter->drawEllipse(-radius, -radius, diameter, diameter);

    if(nodeId > -1)
    {
        if(this->getChoosen()){
            painter->setPen(QPen(Qt::white, 4));
        }else{
            painter->setPen(QPen(Qt::black, 0));
        }
        painter->setFont(QFont("song",24));
        painter->drawText(this->boundingRect(),Qt::AlignCenter ,QString::number(nodeId)); //show nodeId
    }

}
//! [10]

//! [11]
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
//! [11]

//! [12]
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{    
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{    
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    this->setIsHighlighted(!this->getIsHighlighted());

    QGraphicsItem::mouseDoubleClickEvent(event);
}

bool Node::getChoosen() const
{
    return choosen;
}

void Node::setChoosen(bool value)
{
    choosen = value;
    update();
}

QColor Node::getNodeColor() const
{
    return nodeColor;
}

void Node::setNodeColor(const QColor &value)
{
    nodeColor = value;
}


qreal Node::getRadius() const
{
    return radius;
}

void Node::setRadius(const qreal &value)
{
    radius = value;
}

bool Node::getIsHighlighted() const
{
    return isHighlighted;
}

void Node::setIsHighlighted(bool value)
{
    isHighlighted = value;
    update();
}

//! [12]
