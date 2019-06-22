#include "canvasarea.hpp"

#include <cmath>

#include <QPainter>
#include <QPaintDevice>


CanvasArea::CanvasArea()
{
    m_margin_left   = 20.0;
    m_margin_bottom = 20.0;
    this->setBounds(0, 0, this->canvasWidth(), this->canvasHeight());
}


double CanvasArea::margin_left() const
{
    return m_margin_left;
}

void CanvasArea::setMargin_left(double margin_left)
{
    m_margin_left = margin_left;
    this->update();
}

double CanvasArea::margin_bottom() const
{
    return m_margin_bottom;
}

void CanvasArea::setMargin_bottom(double margin_bottom)
{
    m_margin_bottom = margin_bottom;
    this->update();
}

void CanvasArea::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    // painter->drawLine(QPointF{100.20, 20.50}, QPointF{80.2, 59.34});

    painter->scale(1, -1);
    painter->translate(m_margin_left, -(this->height() - m_margin_bottom));

    double w = this->canvasWidth();
    double h = this->canvasHeight();
    sx = w / (xmax - xmin);
    sy = h / (ymax - ymin);
    kx = - xmin * sx;
    ky = - ymin * sy;

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
    this->update();
}

void CanvasArea::drawEllipse(double x, double y, double a, double b)
{
    m_drawlist.push_back([=](QPainter* p){
        p->drawEllipse(QPointF(x, y), a, b);
    });
    this->update();
}

void CanvasArea::drawCircle(double x, double y, double radius)
{
    this->drawEllipse(x, y, radius, radius);
    this->update();
}

void CanvasArea::drawText(double x, double y, QString const& text)
{
    m_drawlist.push_back([=](QPainter* painter){
        painter->save();
        painter->translate(x, y);
        painter->scale(1, -1);
        painter->drawText(QPointF(0.0, 0.0), text);
        painter->restore();
    });
    this->update();
}

void CanvasArea::drawAxis()
{
    m_drawlist.push_back([=](QPainter* painter){
        // painter->setPen();
        painter->drawLine(QPointF(0, 0), QPointF(this->canvasWidth(), 0));
        painter->drawLine(QPointF(0, 0), QPointF(0, this->canvasHeight()));
    });
    this->update();
}



void CanvasArea::drawSine()
{
    constexpr int n = 200;
   //  this->setLimits(0.0, -1.0, 2 * M_PI, 1.0);

    double xmin = 0.0, xmax = 2 * M_PI, ymin = -1.0, ymax = 1.0;

    double step_x = (xmax - xmin) / n;

    m_drawlist.push_back([=](QPainter* p){
        double yd, xd;  // Device coordinates

        double w = this->canvasWidth();
        double h = this->canvasHeight();
        double sx = w / (xmax - xmin);
        double sy = h / (ymax - ymin) ;
        double kx = - xmin * sx;
        double ky = - ymin * sy;

        QPainterPath path;

        double x = xmin, y; // Chart coordinate
        y = sin(x);
        xd = x * sx + kx;
        yd = y * sy + ky;

        path.moveTo(xd, yd);
        for(int i = 0; i < n; i ++)
        {
            x += step_x;
            y = sin(x);
            xd = x * sx + kx;
            yd = y * sy + ky;
            path.lineTo(xd, yd);
        }
        p->drawPath(path);
    });
    this->update();
}

void CanvasArea::setPen(QColor color, int width)
{
    QPen pen(color, width);
    m_drawlist.push_back([=](QPainter* p){
        p->setPen(pen);
    });
    this->update();
}

void CanvasArea::setBounds(double xmin, double ymin, double xmax, double ymax)
{
    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
    double w = this->canvasWidth();
    double h = this->canvasHeight();
    sx = w / (xmax - xmin);
    sy = h / (ymax - ymin);
    kx = - xmin * sx;
    ky = - ymin * sy;
    this->update();
}

std::tuple<double, double>
CanvasArea::worldToDevice(double x, double y) const
{
    double xd = sx * x + kx;
    double yd = sy * y + ky;
    return {xd, yd};
}

double CanvasArea::canvasWidth() const
{
    return this->width() - 2 * m_margin_left;
}

double CanvasArea::canvasHeight() const
{
    return this->height() - 2 * m_margin_bottom;
}
