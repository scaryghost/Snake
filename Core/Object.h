#ifndef ETSAI_SNAKE_CORE_OBJECT
#define ETSAI_SNAKE_CORE_OBJECT

namespace etsai {
namespace snake {
namespace core {

class Object {
public:
    Object(double x, double y);

    virtual void tick(double deltaTime)= 0;
    virtual void draw() const= 0;

    double getXPos() const;
    double getYPos() const;

protected:
    double x;
    double y;
};

}
}
}

#endif