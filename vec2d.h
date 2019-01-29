#ifndef VEC2D_H
#define VEC2D_H

class Vec2d
{
public:
    Vec2d();
    Vec2d(int x, int y);

    int x() {return xi;}
    int y() {return yi;}         //ints?

private:           //this seems like something I should do, but is it? different names perhaps?
    int xi;
    int yi;
};

#endif // VEC2D_H
