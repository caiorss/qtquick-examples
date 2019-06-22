#ifndef CANVASAREA_HPP
#define CANVASAREA_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <functional>

#include <QQuickPaintedItem>
#include <QColor>


using draw = std::function<void (QPainter*)>;

class CanvasArea : public QQuickPaintedItem
{
    std::vector<draw> m_drawlist;
    double m_margin_left;
    double m_margin_bottom;

    double xmin, xmax, ymin, ymax;
    double sx, sy, kx, ky;

    Q_OBJECT
public:
    CanvasArea();

    void paint(QPainter* painter) override;

// Note: All methods in Slots can be called by the QML engine
// slots: is just a macro that tells the MOC meta object compiler
// the methods that it will generate metadata and reflection data.
public slots:

    void clear();
    void setPen(QColor color, int width);

    void setBounds(double xmin, double xmax, double ymin, double ymax);

    std::tuple<double, double>
    WorldToDevice(double x, double y) const;


    double canvasWidth() const;
    double canvasHeight() const;

    void drawLine(double x1, double y1, double x2, double y2);

    void drawEllipse(double x, double y, double a, double b);

    void drawCircle(double x, double y, double radius);

    void drawText(double x, double y, QString const& text);

    void drawAxis();

    void drawSine();

    double margin_left() const;
    void setMargin_left(double margin_left);

    double margin_bottom() const;
    void setMargin_bottom(double margin_bottom);

private:

signals:
    void updatePaint();
};

#endif // CANVASAREA_HPP
