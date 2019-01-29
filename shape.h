#ifndef SHAPE_H
#define SHAPE_H

class QPainter;

class Shape
{
public:
    Shape();
    virtual void draw(QPainter* painter) = 0;
//    virtual void transform() = 0;
};

#endif // SHAPE_H
