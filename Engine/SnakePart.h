#ifndef ETSAI_SNAKE_ENGINE_OBJECT
#define ETSAI_SNAKE_ENGINE_OBJECT

#include "Core/Object.h"

#include <tuple>
#include <vector>

namespace etsai {
namespace snake {
namespace engine {

using std::tuple;
using std::vector;

class SnakePart : public core::Object {
public:
    enum class Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    SnakePart(double x, double y);
    SnakePart(double x, double y, bool head);

    SnakePart& addPivot(int x, int y, Direction dir);
    SnakePart& changeDirection(Direction newDir);

    virtual void tick(double deltaTime);
    virtual void draw() const;

private:
    bool head;
    double speed;
    Direction currDir;
    vector<tuple<int, int, Direction> > pivotPoints;
};

}
}
}

#endif