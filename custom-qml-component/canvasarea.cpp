#include "canvasarea.hpp"

#include <QPainter>
#include <QPaintDevice>

double CanvasArea::margin_left() const
{
    return m_margin_left;
}

void CanvasArea::setMargin_left(double margin_left)
{
    m_margin_left = margin_left;
}

double CanvasArea::margin_bottom() const
{
    return m_margin_bottom;
}

void CanvasArea::setMargin_bottom(double margin_bottom)
{
    m_margin_bottom = margin_bottom;
}

CanvasArea::CanvasArea()
{
    m_margin_left   = 20.0;
    m_margin_bottom = 20.0;
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

void CanvasArea::clear()
{
    m_drawlist.clear();
    // Readraw canvas
    this->update();
}

void CanvasArea::drawLine(double x1, double y1, double x2, double y2)
{
    m_drawlist.push_back([=](QPainter* p){
        p->drawLine(QPointF(x1, y1), QPointF(x2, y2));
    });
}

void CanvasArea::drawEllipse(double x, double y, double a, double b)
{
    m_drawlist.push_back([=](QPainter* p){
        p->drawEllipse(QPointF(x, y), a, b);
    });
}

void CanvasArea::setPen(QColor color, int width)
{
    QPen pen(color, width);
    m_drawlist.push_back([=](QPainter* p){
        p->setPen(pen);
    });
}
