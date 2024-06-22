#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>

#include "cuboid.hpp"
#include "downloadobject.hpp"
#include "modulecamera.hpp"
#include "spheroid.hpp"
#include "toroid.hpp"

enum Errors { NOERRORS, EMPTYFILE, WRONGCONTROLHASH, WRONGFORMAT };
// enum SaveFormat { NON, TXT, BIN };

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
  void rotateLight();
  void on_pb_CreateCubic_clicked();
  void on_pb_CreateSphere_clicked();
  void on_pb_CreateTorus_clicked();
  void on_pb_CreateObject_clicked();
  void on_pb_createHouse_clicked();
  void on_action_create_triggered();
  void on_action_save_triggered();
  void on_action_load_triggered();
  void on_action_exit_triggered();

  void on_action_saveAs_triggered();

 private:
  Ui::MainWindow* ui;

  QTimer lightTimer;  //= new QTimer;
  float time = 0;
  Qt3DCore::QTransform* lightTransform;

  Qt3DExtras::Qt3DWindow view;
  Qt3DCore::QEntity* createScene();
  Qt3DCore::QEntity* rootEntity;
  Qt3DRender::QCamera* camera;
  ModuleCamera* cameraController;
  // Qt3DExtras::QSkyboxEntity* skybox;

  QList<Cuboid> p_cubics;
  QList<Spheroid> p_spheres;
  QList<Toroid> p_toruses;
  QList<DownloadObject> p_downloadObjects;

  void m_createStars(int);
  void clearScene();

  //// Сохранение:
  QMessageBox msgBox_save;
  QString saveString = "";
  QByteArray saveBin;
  QString fileName = "";
  QString filePath = "";
  QFile file;
  bool isSaved = true;
  ///
  bool prepairToSave();
  Errors decodFrom();
  bool save();
  bool saveBIN();
  bool saveBIN(QString path);
  bool getNewPath(QString& path);
  bool setNewPath();
  bool open();
  void savingStatus(bool status);
  void init_msgBox_save();
  bool msgBox_save_call();
  Errors decodFromBIN();
  bool prepairToSaveInBIN();

 protected:
  void closeEvent(QCloseEvent* e) override;
};
#endif  // MAINWINDOW_HPP
