#ifndef MODULECAMERA_HPP
#define MODULECAMERA_HPP

#include <QDebug>
#include <Qt3DCore>
#include <Qt3DInput>
#include <Qt3DLogic>
#include <Qt3DRender>

class ModuleCamera : Qt3DCore::QEntity {
  Q_OBJECT
 public:
  ModuleCamera(Qt3DCore::QNode* parent = Q_NULLPTR, float aspect = 1);

  void setCamera(Qt3DRender::QCamera* newCamera);

  float linearSpeed() const;
  void setLinearSpeed(float newLinearSpeed);

  float getAspect() const;
  void setAspect(float newAspect);

  float getP_lookXSpeed() const;
  void setP_lookXSpeed(float newP_lookXSpeed);

  float getP_lookYSpeed() const;
  void setP_lookYSpeed(float newP_lookYSpeed);

 protected slots:
  void s_activeChanged(bool isActive);
  void s_valueAxisChange(float value);
  void s_frameActionTriggered(float dt);

 private:
  Qt3DInput::QMouseDevice* p_mouseDevice;
  Qt3DInput::QKeyboardDevice* p_keyboardDevice;
  Qt3DInput::QLogicalDevice* p_logicalDevice;

  Qt3DInput::QAction* p_keyWAction;
  Qt3DInput::QAction* p_keySAction;
  Qt3DInput::QAction* p_keyAAction;
  Qt3DInput::QAction* p_keyDAction;
  Qt3DInput::QAction* p_keyShiftAction;
  Qt3DInput::QAction* p_keyCtrlAction;
  Qt3DInput::QAction* p_keyLeftMouseAction;
  Qt3DInput::QAction* p_keyRightMouseAction;
  Qt3DInput::QActionInput* p_keyWInput;
  Qt3DInput::QActionInput* p_keySInput;
  Qt3DInput::QActionInput* p_keyAInput;
  Qt3DInput::QActionInput* p_keyDInput;
  Qt3DInput::QActionInput* p_keyShiftInput;
  Qt3DInput::QActionInput* p_keyCtrlInput;
  Qt3DInput::QActionInput* p_keyLeftMouseInput;
  Qt3DInput::QActionInput* p_keyRightMouseInput;

  Qt3DInput::QAxis* p_XAxis;
  Qt3DInput::QAxis* p_YAxis;

  Qt3DInput::QAnalogAxisInput* p_mouseXInput;
  Qt3DInput::QAnalogAxisInput* p_mouseYInput;

  Qt3DLogic::QFrameAction* p_frameAction;

  Qt3DRender::QCamera* p_camera;
  float p_lookXSpeed;
  float p_lookYSpeed;
  float p_linearSpeed;

  bool p_keyWPressed;
  bool p_keySPressed;
  bool p_keyAPressed;
  bool p_keyDPressed;
  bool p_keyShiftPressed;
  bool p_keyCtrlPressed;
  bool p_keyLeftButtonPressed;
  bool p_keyRightButtonPressed;

  float p_axis_dx;
  float p_axis_dy;

  float p_aspect;
};

#endif  // MODULECAMERA_HPP
