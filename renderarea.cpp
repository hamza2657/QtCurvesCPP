#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>
#include <math.h>
#include <stdint.h>

RenderArea::RenderArea(QWidget *parent):
    QWidget{parent},mBackgroundColor (0,0,255), mShapeColor (255,255,255)
    ,mShape(Astroid)
{
    on_shape_changed();
}

QPointF RenderArea::compute(float t)
{
    switch (mShape) {
    case Astroid:
        return compute_astroid(t);
        break;
    case Cycloid:
        return compute_cycloid(t);
        break;
    case HuygensCycloid:
        return compute_huygens(t);
        break;
    case HypoCycloid:
        return compute_hypo(t);
    case lineCurve:
        return compute_curve(t);
        break;
    default:
        break;
    }
    return QPoint(0,0);
}
QSize RenderArea::minimumSizeHint() const
{
    return QSize(100,100);
}
void RenderArea::on_shape_changed()
{
    switch (mShape) {
    case Astroid:
        mScale = 40;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;
    case Cycloid:
        break;
    case HuygensCycloid:
        break;
    case HypoCycloid:
        break;
    case lineCurve:
        break;
    default:
        break;
    }
}
QPointF RenderArea::compute_astroid(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x  = 2 * cos_t * cos_t * cos_t; // pow(cos_t, 3)
    float y  = 2 * sin_t * sin_t * sin_t; // pow(sin_t, 3)
    return QPointF (x,y);
}
QPointF RenderArea::compute_curve(float t)
{

}
QPointF RenderArea::compute_cycloid(float t)
{

}
QPointF RenderArea::compute_huygens(float t)
{

}
QPointF RenderArea::compute_hypo(float t)
{

}
QSize RenderArea::sizeHint() const
{
    return QSize(400,200);
}
void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);

    //drawig area
    painter.drawRect(this->rect());
    QPoint center = this->rect().center();
    float step = mIntervalLength / mStepCount;
    for (float t = 0; t < mIntervalLength; t+=step) {
        QPointF point = compute (t);
        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());
        painter.drawPoint(pixel);

    }
}
