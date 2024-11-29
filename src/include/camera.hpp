#include "pos.hpp"
#include <iostream>

class Camera {
    public: 
        Camera(float x, float y);
        Camera(Pos pos);

        Pos GetPos();
        float GetZoom();

        std::pair<int, int> Move(float x, float y);
        void MoveTo(float x, float y);

        float Zoom(float add);
        void ZoomTo(float zoom);

        float GetTimer();
        void AddTimer(float time);
        void ResetTimer();

        bool GetAnimation();

        void AnimationStep(float time);
        void NewAnimation(Pos goal, float zoom, float time);

    private:
        Pos pos_;
        float zoom_ = 10;

        bool animation_ = false;
        float timer_ = 0;
        float goalTime_ = 0;

        Pos start_;
        Pos goal_;
        
        float startZoom_ = 1;
        float goalZoom_ = 1;

};