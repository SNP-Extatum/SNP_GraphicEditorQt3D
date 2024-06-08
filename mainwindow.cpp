#include "mainwindow.hpp"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  rootEntity = createScene();
  camera = view.camera();
  camera->lens()->setPerspectiveProjection(60.0f, (float)view.width() / view.height(), 0.1f, 1000.0f);
  camera->setPosition(QVector3D(0.0f, 0.0f, 40.0f));
  camera->setViewCenter(QVector3D(0.0, 0.0, 0.0));
  cameraController = new ModuleCamera(rootEntity);
  cameraController->setCamera(camera);
  cameraController->setAspect((float)view.width() / view.height());

  // skybox = new Qt3DExtras::QSkyboxEntity(rootEntity);
  // skybox->setBaseName("skybox");
  // skybox->setExtension("png");

  view.setRootEntity(rootEntity);
  view.show();
}

MainWindow::~MainWindow() {
  delete cameraController;
  delete camera;
  delete ui;
}

Qt3DCore::QEntity* MainWindow::createScene() {
  Qt3DCore::QEntity* resultEntity = new Qt3DCore::QEntity;

  Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(resultEntity);
  Qt3DRender::QPointLight* pointLight = new Qt3DRender::QPointLight(lightEntity);
  Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform(resultEntity);
  lightTransform->setTranslation(QVector3D(0.0f, 20.0f, 20.0f));
  lightEntity->addComponent(pointLight);
  lightEntity->addComponent(lightTransform);

  return resultEntity;
}

void MainWindow::m_createStars(int) {
  // QImage image = QImage(":/SkyBox/skybox_negx.png");
  // for (int i = 0; i < 100; ++i) {
  // for (int j = 0; j < 100; ++j) {
  //   image.setPixelColor(i, j, QColor(150, 0, 150));
  // }
  //}
  // qDebug() << image.save(":/SkyBox/skybox_negx.png");
}

void MainWindow::on_pb_CreateCubic_clicked() {
  QVector3D pos = QVector3D(ui->sb_cubic_coordX->value(), ui->sb_cubic_coordY->value(), ui->sb_cubic_coordZ->value());
  QVector3D size = QVector3D(ui->sb_cubic_sizeX->value(), ui->sb_cubic_sizeY->value(), ui->sb_cubic_sizeZ->value());
  QVector3D rot = QVector3D(ui->sb_cubic_rotX->value(), ui->sb_cubic_rotY->value(), ui->sb_cubic_rotZ->value());
  QColor color = QColor(ui->sb_cubic_colorR->value(), ui->sb_cubic_colorG->value(), ui->sb_cubic_colorB->value());
  float scale = ui->sb_cubic_scale->value();
  p_cubics.append(Cuboid(pos, rot, size, color, scale, rootEntity));
}

void MainWindow::on_pb_CreateSphere_clicked() {
  QVector3D pos = QVector3D(ui->sb_sphere_coordX->value(), ui->sb_sphere_coordY->value(), ui->sb_sphere_coordZ->value());
  QVector3D size = QVector3D(ui->sb_sphere_radius->value(), ui->sb_sphere_slices->value(), ui->sb_sphere_rings->value());
  QColor color = QColor(ui->sb_sphere_colorR->value(), ui->sb_sphere_colorG->value(), ui->sb_sphere_colorB->value());
  float scale = ui->sb_sphere_scale->value();
  p_spheres.append(Spheroid(pos, size, color, scale, rootEntity));
}

void MainWindow::on_pb_CreateTorus_clicked() {
  QVector3D pos = QVector3D(ui->sb_torus_coordX->value(), ui->sb_torus_coordY->value(), ui->sb_torus_coordZ->value());
  QVector4D size =
	  QVector4D(ui->sb_torus_radius_big->value(), ui->sb_torus_radius_smol->value(), ui->sb_torus_slices->value(), ui->sb_torus_rings->value());
  QVector3D rot = QVector3D(ui->sb_torus_rotX->value(), ui->sb_torus_rotY->value(), ui->sb_torus_rotZ->value());
  QColor color = QColor(ui->sb_torus_colorR->value(), ui->sb_torus_colorG->value(), ui->sb_torus_colorB->value());
  float scale = ui->sb_torus_scale->value();
  p_toruses.append(Toroid(pos, rot, size, color, scale, rootEntity));
}

void MainWindow::on_pb_CreateObject_clicked() {
  QUrl filePath = QFileDialog::getOpenFileName(this, "Открыть файл", ".", "Object (*.obj)");
  if (filePath.isEmpty()) {
	QMessageBox::information(this, "Упс", "Файл не выбран", QMessageBox::Ok);
	return;
  }
  QVector3D pos = QVector3D(ui->sb_obj_coordX->value(), ui->sb_obj_coordY->value(), ui->sb_obj_coordZ->value());
  QVector3D rot = QVector3D(ui->sb_obj_rotX->value(), ui->sb_obj_rotY->value(), ui->sb_obj_rotZ->value());
  float scale = ui->sb_obj_scale->value();

  p_downloadObjects.append(DownloadObject(filePath, pos, rot, scale, rootEntity));

  // QString filePath = newFilePath;
  // file.setFileName(filePath);
  // QFileInfo fileInfo(filePath);
  // fileName = fileInfo.baseName();
}

void MainWindow::on_pb_createHouse_clicked() {
  // p_downloadObjects.append(DownloadObject(QUrl("qrc:/HOUSE.obj"), 0.0, 0.0, 20.0, rootEntity));
  p_downloadObjects.append(DownloadObject(QUrl("qrc:/home/HOUSE.obj"), QVector3D(0, 0, 0), QVector3D(0, 0, 0), 20, rootEntity));

  // m_createStars(ui->sb_countStars->value());
}
