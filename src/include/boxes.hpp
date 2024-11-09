#include "box.hpp"

class Concrete : public Box {
    public: 
        Concrete(float x, float y)
            :  Box(x, y, "images/concrete.png", 100, 10, 10)  {}
};

class Wood : public Box {
    public: 
        Wood(float x, float y)
            : Box(x, y, "images/wood.png", 50, 5, 3) {}
};

class Glass : public Box {
    public: 
        Glass(float x, float y)
            : Box(x, y, "images/glass.png", 40, 3, 1) {}
};