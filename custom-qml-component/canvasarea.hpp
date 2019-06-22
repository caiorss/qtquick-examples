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

    Q_OBJECT
public:
    CanvasArea();

    void paint(QPainter* painter) override;

public slots:
    void drawLine(double x1, double y1, double x2, double y2);
    void setPen(QColor color, int width);

    double margin_left() const;
    void setMargin_left(double margin_left);

    double margin_bottom() const;
    void setMargin_bottom(double margin_bottom);

private:

signals:
    void updatePaint();
};

#endif // CANVASAREA_HPP
