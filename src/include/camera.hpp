#include <iostream>

#include "vector.hpp"

//Depicts the Camera in the GameView
//Has methods for animation and moving and others
class Camera {
 public:
  //params: x and y coordinates of the camera
  Camera(float x, float y);
  Camera(Vector pos);

  Vector GetPos();
  float GetZoom();

  //moves the camera instantly to a position
  //params: coordinates of the goal position
  void MoveTo(float x, float y);

  //moves the camera by an amount
  //params: wanted x and y movement
  void ShiftBy(float x, float y);

  //zooms the camera by an amount
  //params: an amount by which the camera is zoomed. The current zoom is multiplied by this amount
  //returns: new zoom
  float Zoom(float add);

  //Sets zoom to a number
  //params: wanted zoom
  void ZoomTo(float zoom);

  //returns: current timer value
  float GetTimer();

  //adds a value to the timer
  //params: addition
  void AddTimer(float time);

  //sets timer to 0
  void ResetTimer();

  //returns: boolean on whether the camera has an animation going on
  bool GetAnimation();

  //progresses the camera animation.
  //params: time since the last step
  void AnimationStep(float time);

  //creates new animation
  //params: goal position, goal zoom, duration
  void NewAnimation(Vector goal, float zoom, float time);

 private:
  //current position and zoom
  Vector pos_;
  float zoom_ = 10;

  //is animation on or off currently
  bool animation_ = false;

  //current and goal time
  float timer_ = 0;
  float goalTime_ = 0;

  //start and goal positions
  Vector start_;
  Vector goal_;

  //start and goal zooms
  float startZoom_ = 1;
  float goalZoom_ = 1;
};