#include "shape.h"

Shape::Shape()
{

}

Shape::~Shape() {

}

void Shape::mouseReleaseEvent(QMouseEvent *) {
    if(currentState == State::Creating || currentState == State::Moving) {
        currentState = State::Finished;
    }
}
