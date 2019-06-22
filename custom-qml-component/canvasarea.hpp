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

    Q_OBJECT
public:
    CanvasArea();

    void paint(QPainter* painter) override;

public slots:
    void drawLine(double x1, double y1, double x2, double y2);
    void setPen(QColor color, int width);

private:

signals:
    void updatePaint();
};

#endif // CANVASAREA_HPP
