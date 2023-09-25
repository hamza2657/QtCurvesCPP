#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>
#include <math.h>
#include <stdint.h>

RenderArea::RenderArea(QWidget *parent):
    QWidget{parent},mBackgroundColor (0,0,255), mPen(Qt::white)
    ,mShape(Astroid)
{
    mPen.setWidth(2);
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
    case Line:
        return compute_line(t);
        break;
    case Circle:
        return compute_circle(t);
        break;
    case Ellipse:
        return compute_ellipse(t);
        break;
    case FancyCurve:
        return compute_fancyCurve(t);
        break;
    case Starfish:
        return compute_starfish(t);
        break;
    default:
        break;
    }
    return QPoint(0,0);
}
QSize RenderArea::minimumSizeHint() const
{
    return QSize(400,400);
}
QSize RenderArea::sizeHint() const
{
    return QSize(400,400);
}
void RenderArea::on_shape_changed()
{
    switch (mShape) {
    case Astroid:
        mScale = 90;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;
    case Cycloid:
        mScale = 10;
        mIntervalLength = 4 * M_PI;
        mStepCount = 128;
        break;
    case HuygensCycloid:
        mScale = 12;
        mIntervalLength = 4 * M_PI;
        mStepCount = 256;
        break;
    case HypoCycloid:
        mScale = 40;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;
    case Line:
        mScale = 100;
        mIntervalLength = 2;  //Dont really matter in the case of line
        mStepCount = 128;
        break;
    case Circle:
        mScale = 100;
        mIntervalLength = 2 * M_PI;
        mStepCount = 128;
        break;
    case Ellipse:
        mScale = 75;
        mIntervalLength = 2 * M_PI;
        mStepCount = 256;
        break;
    case FancyCurve:
        mScale = 10;
        mIntervalLength = 12 * M_PI;
        mStepCount = 512;
        break;
    case Starfish:
        mScale = 25;
        mIntervalLength = 6 * M_PI;
        mStepCount = 256;
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
QPointF RenderArea::compute_circle(float t)
{
    return QPointF(
        cos(t), // X
        sin(t)// Y
    );
}
QPointF RenderArea::compute_ellipse(float t)
{
    float a = 2 ;
    float b = 1.1;
    return QPointF(
        a * cos(t), // X
        b * sin(t)// Y
    );
}
QPointF RenderArea::compute_starfish(float t)
{
    float R = 5 ;
    float r = 3;
    float d = 5;
    float x = ( (R-r) * cos(t) ) + (d * cos(t*((R-r)/r))) ;
    float y = ( (R-r) * sin(t) ) - (d * sin(t*((R-r)/r)));
    return QPointF(x,y);
}
QPointF RenderArea::compute_fancyCurve(float t)
{
    float v1 = 15;
    float v2 = 4;
    float x = (v1 * cos(t)) - (v2 * (cos((v1*t)/v2)));
    float y = (v1 * sin(t)) - (v2 * (sin((v1*t)/v2)));
    return QPointF(x,y);
}
QPointF RenderArea::compute_line(float t)
{
    /**
     * how to add parametric equation for desired shape
     * x = fx(t)
     * y = fy(t)
     * for simple line
     * x =  1 - t
     * y =  1 - t
     *
     */
    return QPointF(
        (1 - t), // X
        (1 - t)// Y
    );
}
QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF(
        1.5 * (1 - cos(t)), //X
        1.5 * (t - sin(t)) //Y
    );
}
QPointF RenderArea::compute_huygens(float t)
{
    return QPointF(
        4 * (3 * cos(t) - cos(3*t)), // X
        4 * (3 * sin(t) - sin(3*t)) // Y
    );
}
QPointF RenderArea::compute_hypo(float t)
{
    return QPointF(
        1.5 * (2 * cos(t) + cos(2*t)), // X
        1.5 * (2 * sin(t) - sin(2*t)) // Y
    );
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(mBackgroundColor);
    painter.setPen(mPen);

    //drawig area
    painter.drawRect(this->rect());
    QPoint center = this->rect().center();
    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX(prevPoint.x() * mScale + center.x());
    prevPixel.setY(prevPoint.y() * mScale + center.y());
    float step = mIntervalLength / mStepCount;
    for (float t = 0; t < mIntervalLength; t+=step) {
        QPointF point = compute (t);
        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());
        painter.drawLine(pixel,prevPixel);
        prevPixel = pixel;

    }
    QPointF point = compute (mIntervalLength);
    QPoint pixel;
    pixel.setX(point.x() * mScale + center.x());
    pixel.setY(point.y() * mScale + center.y());
    painter.drawLine(pixel,prevPixel);
}
