#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>
class RenderArea : public QWidget
{
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {
        Astroid,
        Cycloid,
        HuygensCycloid,
        HypoCycloid,
        Line,
        Circle,
        Ellipse,
        FancyCurve,
        Starfish

    };
    void setBackgroundColor(QColor color){mBackgroundColor = color;repaint();} //setter
    QColor backgroundColor() const {return mBackgroundColor;} //getter
    void setSetShapeColor(QColor color){mShapeColor = color;repaint(); }
    QColor shapeColor() const {return mShapeColor;}
    void setShape(ShapeType shape) {mShape = shape; on_shape_changed();}
    ShapeType shape () const {return mShape;}
    void setScale(float scale) {mScale = scale; repaint();}
    float scale() const {return mScale;}
    void setInterval(double intervalLen){mIntervalLength = intervalLen; repaint();}
    double intervalLen() const {return mIntervalLength;}
    void setStepCount(int count){mStepCount = count;repaint();}
    int stepCount()const {return mStepCount;}
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


signals:
private:
    void on_shape_changed();
    QPointF compute(float t);//dispatch function based on mShape Types
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens(float t);
    QPointF compute_hypo(float t);
    QPointF compute_line(float t);
    QPointF compute_circle(float t);
    QPointF compute_ellipse(float t);
    QPointF compute_fancyCurve(float t);
    QPointF compute_starfish(float t);
private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;
    float mIntervalLength;
    float mScale;
    int mStepCount;


};

#endif // RENDERAREA_H
