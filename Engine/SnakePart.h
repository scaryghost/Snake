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

    SnakePart& addPivot(int x, int y, Direction dir);

    virtual void tick(double deltaTime);
    virtual void draw() const;

private:
    double speed;
    Direction currDir;
    vector<tuple<int, int, Direction> > pivotPoints;
};

}
}
}

#endif