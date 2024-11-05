
#include "entity.hpp"

class Physical : public Entity {
    public:
        Physical(float x, float y);
        Physical(float x, float y , float mass, float width, float height);

        float GetWidth();
        float GetHeight();
    
    protected:
        float mass_;
        float width_;
        float height_;
};