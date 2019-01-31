#ifndef VEC2D_H
#define VEC2D_H

class Vec2d
{
public:
    Vec2d();
    Vec2d(double x, double y);

    double x() {return xi;}
    double y() {return yi;}         //ints?

private:           //this seems like something I should do, but is it? different names perhaps?
    double xi;
    double yi;
};

#endif // VEC2D_H
