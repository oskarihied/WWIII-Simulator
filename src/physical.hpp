
#include "entity.hpp"

class Physical : public Entity {
    public:
        Physical(float x, float y);
        Physical(float x, float y , float mass);
    
    protected:
        float mass_;
};