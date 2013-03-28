#include "Engine/SnakePart.h"

#include "allegro5/allegro_primitives.h"

namespace etsai {
namespace snake {
namespace engine {

using std::make_tuple;

SnakePart::SnakePart(double x, double y) : Object(x, y), speed(100), currDir(Direction::RIGHT) {
}

SnakePart& SnakePart::addPivot(int x, int y, Direction dir) {
    pivotPoints.push_back(make_tuple(x, y, dir));
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
}

void SnakePart::draw() const {
    al_draw_filled_rectangle(x - 50, y - 50, x + 50, y + 50, al_map_rgb(255, 0, 0));
}

}
}
}