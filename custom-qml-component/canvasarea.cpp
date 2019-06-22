#include "canvasarea.hpp"

#include <QPainter>
#include <QPaintDevice>

CanvasArea::CanvasArea()
{

}

void CanvasArea::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    // painter->drawLine(QPointF{100.20, 20.50}, QPointF{80.2, 59.34});

    painter->scale(1, -1);
    painter->translate(m_margin_left, -(this->height() - m_margin_bottom));

    for(auto const& draw: m_drawlist)
        draw(painter);
}

void CanvasArea::drawLine(double x1, double y1, double x2, double y2)
{
    m_drawlist.push_back([=](QPainter* p){
        p->drawLine(QPointF(x1, y1), QPointF(x2, y2));
    });
}

void CanvasArea::setPen(QColor color, int width)
{
    QPen pen(color, width);
    m_drawlist.push_back([=](QPainter* p){
        p->setPen(pen);
    });
}
