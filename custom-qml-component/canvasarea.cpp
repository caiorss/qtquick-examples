#include "canvasarea.hpp"

#include <cmath>

#include <QPainter>
#include <QPaintDevice>


CanvasArea::CanvasArea()
{
    m_margin_left   = 50.0;
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

void CanvasArea::drawTextw(double x, double y, const QString &text)
{
    m_drawlist.push_back([=](QPainter* painter){
        auto [xd, yd] = this->worldToDevice(x, y);
        painter->save();
        painter->translate(xd, yd);
        painter->scale(1, -1);
        painter->drawText(QPointF(0.0, 0.0), text);
        painter->restore();
    });
    this->update();
}


void CanvasArea::plotPoints(QVector<double> const& xs, QVector<double> const& ys)
{
    int n = std::min(xs.size(), ys.size());

    m_drawlist.push_back([=](QPainter* p){

        QPainterPath path;

        path.moveTo(this->worldToDeviceQPoint(xs[0], ys[0]));

        for(int i = 1; i < n; i ++)
        {
            path.lineTo(this->worldToDeviceQPoint(xs[i], ys[i]));
        }
        p->drawPath(path);
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
    double xmin = 0.0, xmax = 2 * M_PI, ymin = -1.0, ymax = 1.0;
    this->setBounds(xmin, xmax, ymin, ymax);

    this->drawTextw(M_PI / 2.0, 1.0, "(PI / 2, 1.0)");
    this->drawTextw(M_PI, 0.0, "(PI , 0.0)");

    // this->plotCurve(static_cast<double (*) (double)>(std::sin));
    this->plotCurvePoints(static_cast<double (*) (double)>(std::sin));
}

void CanvasArea::setPen(QColor color, int width)
{
    QPen pen(color, width);
    m_drawlist.push_back([=](QPainter* p){
        p->setPen(pen);
    });
    this->update();
}

void CanvasArea::setBounds(double xmin, double xmax, double ymin, double ymax)
{
    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
    this->update();
}

std::tuple<double, double>
CanvasArea::worldToDevice(double x, double y) const
{
    double xd = sx * x + kx;
    double yd = sy * y + ky;
    return {xd, yd};
}

QPointF
CanvasArea::worldToDeviceQPoint(double x, double y) const
{
    double xd = sx * x + kx;
    double yd = sy * y + ky;
    return {xd, yd};
}

std::tuple<double, double>
CanvasArea::deviceToWorld(double x, double y) const
{
    return { (x - kx) / sx, (y - ky) / sy };
}

void CanvasArea::plotCurve(std::function<double (double)> function)
{
    constexpr int n = 200;

    m_drawlist.push_back([=](QPainter* p){
        QPainterPath path;

        double step_x = (this->xmax - this->xmin) / n;

        double x = xmin, y; // Chart coordinate
        y = function(x);
        auto [xd, yd] = this->worldToDevice(x, y);
        path.moveTo(xd, yd);

        for(int i = 0; i < n; i ++)
        {
            x += step_x;
            y = function(x);
            auto [xd, yd] = this->worldToDevice(x, y);
            path.lineTo(xd, yd);
        }
        p->drawPath(path);
    });
   this->update();

}


void CanvasArea::plotCurvePoints(std::function<double (double)> function)
{
    // Number of points or interval [Xmin, Xmax] in the X axis
    int n = 200;

    m_drawlist.push_back([=](QPainter* p){
        QPainterPath path;

        // Save drawing context
        p->save();
        // Set pen to draw rounded points
        p->setPen(QPen(Qt::red,  3.0, Qt::SolidLine, Qt::RoundCap));

        double step_x = (this->xmax - this->xmin) / n;

        double x = xmin, y; // Chart coordinate
        y = function(x);
        auto [xd, yd] = this->worldToDevice(x, y);

        p->drawPoint(QPointF(xd, yd));

        for(int i = 0; i < n; i ++)
        {
            x += step_x;
            y = function(x);
            auto [xd, yd] = this->worldToDevice(x, y);
            p->drawPoint(QPointF(xd, yd));
        }
        // Restore drawing context
        p->restore();
    });
    this->update();
}



double CanvasArea::canvasWidth() const
{
    return this->width() - 2 * m_margin_left;
}

double CanvasArea::canvasHeight() const
{
    return this->height() - 2 * m_margin_bottom;
}
