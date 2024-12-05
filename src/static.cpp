#include "static.hpp"

// Static::Static(float x, float y) : 
//     Physical(x, y) {}

Static::Static(float x, float y, std::string image ) : 
    Physical(x, y, image, 100, 10, 10) {}

Static::Static(float x, float y, std::string image, float mass ) : 
    Physical(x, y, image, mass, 10, 10) {}