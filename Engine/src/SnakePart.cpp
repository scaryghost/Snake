#include "Engine/SnakePart.h"

#include "allegro5/allegro_primitives.h"

#include <exception>

namespace etsai {
namespace snake {
namespace engine {

using std::exception;
using std::get;
using std::make_tuple;

SnakePart::SnakePart(double x, double y) : Object(x, y), speed(100), currDir(Direction::RIGHT) {
}

SnakePart& SnakePart::addPivot(int x, int y, Direction dir) {
    pivotPoints.push_back(make_tuple(x, y, dir));
    return *this;
}

SnakePart& SnakePart::changeDirection(Direction newDir) {
    currDir= newDir;
    return *this;
}

void SnakePart::tick(double deltaTime) {
    double offset(speed * deltaTime);

    switch(currDir) {
        case Direction::UP:
            y-= offset;
            break;
        case Direction::RIGHT:
            x+= offset;
            break;
        case Direction::DOWN:
            y+= offset;
            break;
        case Direction::LEFT:
            x-= offset;
            break;
    }
    
    try {
        auto top= pivotPoints.at(0);
        if (get<0>(top) == int(x) && get<1>(top) == int(y)) {
            currDir= get<2>(top);
            pivotPoints.erase(pivotPoints.begin());
        }
    } catch (exception &ex) {
    }
}

void SnakePart::draw() const {
    al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(255, 0, 0));
}

}
}
}