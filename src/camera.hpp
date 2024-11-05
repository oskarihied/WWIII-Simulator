#include "pos.hpp"

class Camera {
    public: 
        Camera(float x, float y);
        Camera(Pos pos);

        Pos GetPos();
        float GetZoom();

    private:
        Pos pos_;
        float zoom_ = 10;
};