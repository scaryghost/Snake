#include "Engine/SnakePart.h"

#include "allegro5/allegro_primitives.h"

#include <exception>

namespace etsai {
namespace snake {
namespace engine {

using std::exception;
using std::get;
using std::make_tuple;

SnakePart::SnakePart(double x, double y) : SnakePart(x, y, false) {
}

SnakePart::SnakePart(double x, double y, bool head) : Object(x, y), head(head), speed(100), currDir(Direction::RIGHT) {
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
        switch(currDir) {
            case Direction::UP:
                if (int(y) <= get<1>(top)) {
                    y= get<1>(top);
                    currDir= get<2>(top);
                    pivotPoints.erase(pivotPoints.begin());
                }
                break;
            case Direction::RIGHT:
               if (int(x) >= get<0>(top)) {
                    x= get<0>(top);
                    currDir= get<2>(top);
                    pivotPoints.erase(pivotPoints.begin());
                }
               break;
            case Direction::DOWN:
                if (int(y) >= get<1>(top)) {
                    y= get<1>(top);
                    currDir= get<2>(top);
                    pivotPoints.erase(pivotPoints.begin());
                }
                break;
            case Direction::LEFT:
                if (int(x) <= get<0>(top)) {
                    x= get<0>(top);
                    currDir= get<2>(top);
                    pivotPoints.erase(pivotPoints.begin());
                }
                break;
        }
    } catch (exception &ex) {
    }
}

void SnakePart::draw() const {
    try {
        auto top= pivotPoints.at(0);
        switch(currDir) {
            case Direction::UP:
                al_draw_filled_rectangle(x - 10, y - (10 + (y - get<1>(top))), x + 10, y + 10, al_map_rgb(255, 0, 0));
                break;
            case Direction::RIGHT:
                al_draw_filled_rectangle(x - 10, y - 10, x + 10 + (get<0>(top) - x), y + 10, al_map_rgb(255, 0, 0));
                break;
            case Direction::DOWN:
                al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10 + (get<1>(top) - y), al_map_rgb(255, 0, 0));
                break;
            case Direction::LEFT:
                al_draw_filled_rectangle(x - (10 + (x - get<0>(top))), y - 10, x + 10, y + 10, al_map_rgb(255, 0, 0));
            break;
        }
    } catch (exception &ex) {
        al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(255, 0, 0));
    }
}

}
}
}