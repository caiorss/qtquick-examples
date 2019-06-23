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

    double canvasWidth() const;
    double canvasHeight() const;

    /** @brief Converts world coordinates to screen/device coordinates */
    std::tuple<double, double>
    worldToDevice(double x, double y) const;

    QPointF worldToDeviceQPoint(double x, double y) const;

    /** @brief Converts screen coordinates to device coordinates */
    std::tuple<double, double>
    deviceToWorld(double x, double y) const;

    void plotCurve(std::function<double (double)> function);

    void plotCurvePoints(std::function<double (double)> function);

    void drawLine(double x1, double y1, double x2, double y2);

    void drawEllipse(double x, double y, double a, double b);

    void drawCircle(double x, double y, double radius);

    void drawText(double x, double y, QString const& text);

    // Draw text in world's coordinate
    void drawTextw(double x, double y, QString const& text);

    /** @brief Draw points in World's coordinates */
    void plotPoints(QVector<double> const& xs, QVector<double> const& ys);

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
