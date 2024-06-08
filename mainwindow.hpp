#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>

#include "cuboid.hpp"
#include "downloadobject.hpp"
#include "modulecamera.hpp"
#include "spheroid.hpp"
#include "toroid.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pb_CreateCubic_clicked();

  void on_pb_CreateSphere_clicked();

  void on_pb_CreateTorus_clicked();

  void on_pb_CreateObject_clicked();

  void on_pb_createHouse_clicked();

 private:
  Ui::MainWindow* ui;

  Qt3DExtras::Qt3DWindow view;
  Qt3DCore::QEntity* createScene();
  Qt3DCore::QEntity* rootEntity;
  Qt3DRender::QCamera* camera;
  ModuleCamera* cameraController;
  Qt3DExtras::QSkyboxEntity* skybox;

  QList<Cuboid> p_cubics;
  QList<Spheroid> p_spheres;
  QList<Toroid> p_toruses;
  QList<DownloadObject> p_downloadObjects;

  void m_createStars(int);
};
#endif  // MAINWINDOW_HPP
