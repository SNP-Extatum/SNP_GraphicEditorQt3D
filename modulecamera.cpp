#include "modulecamera.hpp"

ModuleCamera::ModuleCamera(Qt3DCore::QNode* parent, float aspect) : Qt3DCore::QEntity(parent) {
  p_camera = 0;
  p_aspect = aspect;

  p_lookXSpeed = 120.0f;
  p_lookYSpeed = 120.0f / aspect;
  p_linearSpeed = 0.2f;

  p_keyWPressed = false;
  p_keySPressed = false;
  p_keyAPressed = false;
  p_keyDPressed = false;
  p_keyShiftPressed = false;
  p_keyCtrlPressed = false;
  p_keyLeftButtonPressed = false;
  p_keyRightButtonPressed = false;

  p_axis_dx = 0.0f;
  p_axis_dy = 0.0f;

  p_mouseDevice = new Qt3DInput::QMouseDevice(this);
  p_keyboardDevice = new Qt3DInput::QKeyboardDevice(this);
  p_logicalDevice = new Qt3DInput::QLogicalDevice(this);

  p_keyWAction = new Qt3DInput::QAction(this);
  p_keySAction = new Qt3DInput::QAction(this);
  p_keyAAction = new Qt3DInput::QAction(this);
  p_keyDAction = new Qt3DInput::QAction(this);
  p_keyShiftAction = new Qt3DInput::QAction(this);
  p_keyCtrlAction = new Qt3DInput::QAction(this);
  p_keyLeftMouseAction = new Qt3DInput::QAction(this);
  p_keyRightMouseAction = new Qt3DInput::QAction(this);

  p_keyWInput = new Qt3DInput::QActionInput(this);
  p_keySInput = new Qt3DInput::QActionInput(this);
  p_keyAInput = new Qt3DInput::QActionInput(this);
  p_keyDInput = new Qt3DInput::QActionInput(this);
  p_keyShiftInput = new Qt3DInput::QActionInput(this);
  p_keyCtrlInput = new Qt3DInput::QActionInput(this);
  p_keyLeftMouseInput = new Qt3DInput::QActionInput(this);
  p_keyRightMouseInput = new Qt3DInput::QActionInput(this);

  p_XAxis = new Qt3DInput::QAxis(this);
  p_YAxis = new Qt3DInput::QAxis(this);

  p_mouseXInput = new Qt3DInput::QAnalogAxisInput(this);
  p_mouseYInput = new Qt3DInput::QAnalogAxisInput(this);

  p_frameAction = new Qt3DLogic::QFrameAction(this);

  p_keyWInput->setButtons(QVector<int>() << Qt::Key_W);
  p_keySInput->setButtons(QVector<int>() << Qt::Key_S);
  p_keyAInput->setButtons(QVector<int>() << Qt::Key_A);
  p_keyDInput->setButtons(QVector<int>() << Qt::Key_D);
  p_keyShiftInput->setButtons(QVector<int>() << Qt::Key_Shift);
  p_keyCtrlInput->setButtons(QVector<int>() << Qt::Key_Control);
  p_keyWInput->setSourceDevice(p_keyboardDevice);
  p_keySInput->setSourceDevice(p_keyboardDevice);
  p_keyAInput->setSourceDevice(p_keyboardDevice);
  p_keyDInput->setSourceDevice(p_keyboardDevice);
  p_keyShiftInput->setSourceDevice(p_keyboardDevice);
  p_keyCtrlInput->setSourceDevice(p_keyboardDevice);

  p_keyWAction->addInput(p_keyWInput);
  p_keySAction->addInput(p_keySInput);
  p_keyAAction->addInput(p_keyAInput);
  p_keyDAction->addInput(p_keyDInput);
  p_keyShiftAction->addInput(p_keyShiftInput);
  p_keyCtrlAction->addInput(p_keyCtrlInput);
  p_keyWAction->setObjectName("Key_W");
  p_keySAction->setObjectName("Key_S");
  p_keyAAction->setObjectName("Key_A");
  p_keyDAction->setObjectName("Key_D");
  p_keyShiftAction->setObjectName("Key_Shift");
  p_keyCtrlAction->setObjectName("Key_Control");

  p_keyLeftMouseInput->setButtons(QVector<int>() << Qt::LeftButton);
  p_keyRightMouseInput->setButtons(QVector<int>() << Qt::RightButton);
  p_keyLeftMouseInput->setSourceDevice(p_keyboardDevice);
  p_keyRightMouseInput->setSourceDevice(p_keyboardDevice);
  p_keyLeftMouseInput->setSourceDevice(p_mouseDevice);
  p_keyRightMouseInput->setSourceDevice(p_mouseDevice);
  p_keyLeftMouseAction->addInput(p_keyLeftMouseInput);
  p_keyRightMouseAction->addInput(p_keyRightMouseInput);
  p_keyLeftMouseAction->setObjectName("Button_Left");
  p_keyRightMouseAction->setObjectName("Button_Right");

  p_mouseXInput->setAxis(Qt3DInput::QMouseDevice::X);
  p_mouseXInput->setSourceDevice(p_mouseDevice);
  p_mouseYInput->setAxis(Qt3DInput::QMouseDevice::Y);
  p_mouseYInput->setSourceDevice(p_mouseDevice);
  p_XAxis->addInput(p_mouseXInput);
  p_YAxis->addInput(p_mouseYInput);
  p_XAxis->setObjectName("Axis_X");
  p_YAxis->setObjectName("Axis_Y");

  p_logicalDevice->addAction(p_keyWAction);
  p_logicalDevice->addAction(p_keySAction);
  p_logicalDevice->addAction(p_keyAAction);
  p_logicalDevice->addAction(p_keyDAction);
  p_logicalDevice->addAction(p_keyShiftAction);
  p_logicalDevice->addAction(p_keyCtrlAction);
  p_logicalDevice->addAction(p_keyLeftMouseAction);
  p_logicalDevice->addAction(p_keyRightMouseAction);
  p_logicalDevice->addAxis(p_XAxis);
  p_logicalDevice->addAxis(p_YAxis);

  connect(p_keyWAction, SIGNAL(activeChanged(bool)), this, SLOT(s_activeChanged(bool)));
  connect(p_keySAction, SIGNAL(activeChanged(bool)), this, SLOT(s_activeChanged(bool)));
  connect(p_keyAAction, SIGNAL(activeChanged(bool)), this, SLOT(s_activeChanged(bool)));
  connect(p_keyDAction, SIGNAL(activeChanged(bool)), this, SLOT(s_activeChanged(bool)));
  connect(p_keyShiftAction, SIGNAL(activeChanged(bool)), this, SLOT(s_activeChanged(bool)));
  connect(p_keyCtrlAction, SIGNAL(activeChanged(bool)), this, SLOT(s_activeChanged(bool)));
  connect(p_keyLeftMouseAction, SIGNAL(activeChanged(bool)), this, SLOT(s_activeChanged(bool)));
  connect(p_keyRightMouseAction, SIGNAL(activeChanged(bool)), this, SLOT(s_activeChanged(bool)));

  connect(p_XAxis, SIGNAL(valueChanged(float)), this, SLOT(s_valueAxisChange(float)));
  connect(p_YAxis, SIGNAL(valueChanged(float)), this, SLOT(s_valueAxisChange(float)));

  connect(p_frameAction, SIGNAL(triggered(float)), this, SLOT(s_frameActionTriggered(float)));
}

ModuleCamera::~ModuleCamera() {
  delete p_mouseDevice;
  delete p_keyboardDevice;
  delete p_logicalDevice;

  delete p_keyWAction;
  delete p_keySAction;
  delete p_keyAAction;
  delete p_keyDAction;
  delete p_keyShiftAction;
  delete p_keyCtrlAction;
  delete p_keyLeftMouseAction;
  delete p_keyRightMouseAction;

  delete p_keyWInput;
  delete p_keySInput;
  delete p_keyAInput;
  delete p_keyDInput;
  delete p_keyShiftInput;
  delete p_keyCtrlInput;
  delete p_keyLeftMouseInput;
  delete p_keyRightMouseInput;

  delete p_XAxis;
  delete p_YAxis;

  delete p_mouseXInput;
  delete p_mouseYInput;

  delete p_frameAction;
}

void ModuleCamera::setCamera(Qt3DRender::QCamera* newCamera) { p_camera = newCamera; }

float ModuleCamera::linearSpeed() const { return p_linearSpeed; }

void ModuleCamera::setLinearSpeed(float newLinearSpeed) { p_linearSpeed = newLinearSpeed; }

void ModuleCamera::s_activeChanged(bool isActive) {
  if (sender()->objectName() == "Key_W") {
	p_keyWPressed = isActive;
  } else if (sender()->objectName() == "Key_S") {
	p_keySPressed = isActive;
  } else if (sender()->objectName() == "Key_A") {
	p_keyAPressed = isActive;
  } else if (sender()->objectName() == "Key_D") {
	p_keyDPressed = isActive;
  } else if (sender()->objectName() == "Key_Shift") {
	p_keyShiftPressed = isActive;
  } else if (sender()->objectName() == "Key_Control") {
	p_keyCtrlPressed = isActive;
  } else if (sender()->objectName() == "Button_Left") {
	p_keyLeftButtonPressed = isActive;
  } else if (sender()->objectName() == "Button_Right") {
	p_keyRightButtonPressed = isActive;
  }
}

void ModuleCamera::s_valueAxisChange(float value) {
  if (sender()->objectName() == "Axis_X") {
	p_axis_dx = value;
  } else if (sender()->objectName() == "Axis_Y") {
	p_axis_dy = value;
  }
}

void ModuleCamera::s_frameActionTriggered(float dt) {
  if (p_camera == 0) return;
  // qDebug() << dt;
  if (p_keyRightButtonPressed) {
	p_camera->tilt(-p_axis_dy * p_lookYSpeed * dt);
	p_camera->pan(-p_axis_dx * p_lookXSpeed * dt, QVector3D(0, 1, 0));
  }

  if (p_keyWPressed) {
	p_camera->translate(QVector3D(0.0, 0.0, 1.0) * p_linearSpeed);
  }
  if (p_keySPressed) {
	p_camera->translate(QVector3D(0.0, 0.0, -1.0) * p_linearSpeed);
  }
  if (p_keyAPressed) {
	p_camera->translate(QVector3D(-1.0, 0.0, 0.0) * p_linearSpeed);
  }
  if (p_keyDPressed) {
	p_camera->translate(QVector3D(1.0, 0.0, 0.0) * p_linearSpeed);
  }
  if (p_keyShiftPressed) {
	p_camera->translateWorld(QVector3D(0.0, 1.0, 0.0) * p_linearSpeed);
  }
  if (p_keyCtrlPressed) {
	p_camera->translateWorld(QVector3D(0.0, -1.0, 0.0) * p_linearSpeed);
  }
}

float ModuleCamera::getP_lookYSpeed() const { return p_lookYSpeed; }

void ModuleCamera::setP_lookYSpeed(float newP_lookYSpeed) { p_lookYSpeed = newP_lookYSpeed; }

float ModuleCamera::getP_lookXSpeed() const { return p_lookXSpeed; }

void ModuleCamera::setP_lookXSpeed(float newP_lookXSpeed) { p_lookXSpeed = newP_lookXSpeed; }

float ModuleCamera::getAspect() const { return p_aspect; }

void ModuleCamera::setAspect(float newAspect) { p_aspect = newAspect; }
