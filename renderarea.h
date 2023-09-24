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
        HypoCycloid

    };
    void setBackgroundColor(QColor color){mBackgroundColor = color;} //setter
    QColor backgroundColor() const {return mBackgroundColor;} //getter
    void setShape(ShapeType shape) {mShape = shape;}
    ShapeType shape () const {return mShape;}
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


signals:
private:
    QPointF compute_astroid(float t);
private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;


};

#endif // RENDERAREA_H
