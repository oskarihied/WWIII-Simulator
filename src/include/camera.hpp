#include "pos.hpp"

class Camera {
    public: 
        Camera(float x, float y);
        Camera(Pos pos);

        Pos GetPos();
        float GetZoom();

        std::pair<int, int> Move(float x, float y);

        float Zoom(float add);

    private:
        Pos pos_;
        float zoom_ = 10;
};