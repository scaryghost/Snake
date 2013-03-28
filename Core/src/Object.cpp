#include "Core/Object.h"

namespace etsai {
namespace snake {
namespace core {

Object::Object(double x, double y) : x(x), y(y) {
}

double Object::getXPos() const {
    return x;
}

double Object::getYPos() const {
    return y;
}

}
}
}