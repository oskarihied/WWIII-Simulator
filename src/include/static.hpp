#ifndef STATIC_HPP
#define STATIC_HPP

#include "physical.hpp"

class Static : public Physical {
    public:
        // Static(float x, float y);
        Static(float x, float y, std::string image);
        Static(float x, float y, std::string image, float mass);
};

#endif