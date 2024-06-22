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
  init_msgBox_save();

  view.setRootEntity(rootEntity);
  view.show();

  while (!setNewPath())
	;
  // connect(timer, SIGNAL(timeout()), this, SLOT(on_pbt_create_clicked()));

  connect(&lightTimer, SIGNAL(timeout()), this, SLOT(rotateLight()));
  lightTimer.start(1000 / 60);
}

MainWindow::~MainWindow() {
  delete cameraController;
  delete ui;
}

Qt3DCore::QEntity* MainWindow::createScene() {
  Qt3DCore::QEntity* resultEntity = new Qt3DCore::QEntity;
  Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(resultEntity);
  Qt3DRender::QPointLight* pointLight = new Qt3DRender::QPointLight(lightEntity);
  lightTransform = new Qt3DCore::QTransform(resultEntity);
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

void MainWindow::clearScene() {
  qDebug() << "clearscene";
  while (!p_cubics.isEmpty()) {
	// p_cubics.first().Cuboid::~Cuboid();
	p_cubics.first().deleteObject();
	p_cubics.removeFirst();
  }
  while (!p_spheres.isEmpty()) {
	// p_spheres.first().~Spheroid();
	p_spheres.first().deleteObject();
	p_spheres.removeFirst();
  }
  while (!p_toruses.isEmpty()) {
	// p_toruses.first().~Toroid();
	p_toruses.first().deleteObject();
	p_toruses.removeFirst();
  }
}

void MainWindow::init_msgBox_save() {
  msgBox_save.setWindowTitle("Фигурки");
  msgBox_save.setText("Хотите сохранить изменения в файле '" + fileName + "' ?");
  msgBox_save.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  msgBox_save.setIcon(QMessageBox::Question);
}

bool MainWindow::msgBox_save_call() {
  /*
   *Возвращает: true - при выполнении сохранения (или намеренный отказ от него)
   *            false - при невыполнении сохранения
   */
  switch (msgBox_save.exec()) {
	case QMessageBox::Save:
	  return saveBIN();
	case QMessageBox::Discard:
	  return true;
	case QMessageBox::Cancel:
	default:
	  return false;
  }
}

void MainWindow::on_pb_CreateCubic_clicked() {
  QVector3D pos = QVector3D(ui->sb_cubic_coordX->value(), ui->sb_cubic_coordY->value(), ui->sb_cubic_coordZ->value());
  QVector3D size = QVector3D(ui->sb_cubic_sizeX->value(), ui->sb_cubic_sizeY->value(), ui->sb_cubic_sizeZ->value());
  QVector3D rot = QVector3D(ui->sb_cubic_rotX->value(), ui->sb_cubic_rotY->value(), ui->sb_cubic_rotZ->value());
  QColor color = QColor(ui->sb_cubic_colorR->value(), ui->sb_cubic_colorG->value(), ui->sb_cubic_colorB->value());
  float scale = ui->sb_cubic_scale->value();
  p_cubics.append(Cuboid(pos, rot, size, color, scale, rootEntity));
  savingStatus(false);
}

void MainWindow::on_pb_CreateSphere_clicked() {
  QVector3D pos = QVector3D(ui->sb_sphere_coordX->value(), ui->sb_sphere_coordY->value(), ui->sb_sphere_coordZ->value());
  QVector3D size = QVector3D(ui->sb_sphere_radius->value(), ui->sb_sphere_slices->value(), ui->sb_sphere_rings->value());
  QColor color = QColor(ui->sb_sphere_colorR->value(), ui->sb_sphere_colorG->value(), ui->sb_sphere_colorB->value());
  float scale = ui->sb_sphere_scale->value();
  p_spheres.append(Spheroid(pos, size, color, scale, rootEntity));
  savingStatus(false);
}

void MainWindow::on_pb_CreateTorus_clicked() {
  QVector3D pos = QVector3D(ui->sb_torus_coordX->value(), ui->sb_torus_coordY->value(), ui->sb_torus_coordZ->value());
  QVector4D size =
	  QVector4D(ui->sb_torus_radius_big->value(), ui->sb_torus_radius_smol->value(), ui->sb_torus_slices->value(), ui->sb_torus_rings->value());
  QVector3D rot = QVector3D(ui->sb_torus_rotX->value(), ui->sb_torus_rotY->value(), ui->sb_torus_rotZ->value());
  QColor color = QColor(ui->sb_torus_colorR->value(), ui->sb_torus_colorG->value(), ui->sb_torus_colorB->value());
  float scale = ui->sb_torus_scale->value();
  p_toruses.append(Toroid(pos, rot, size, color, scale, rootEntity));
  savingStatus(false);
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
  savingStatus(false);

  // QString filePath = newFilePath;
  // file.setFileName(filePath);
  // QFileInfo fileInfo(filePath);
  // fileName = fileInfo.baseName();
}

void MainWindow::on_pb_createHouse_clicked() {
  // p_downloadObjects.append(DownloadObject(QUrl("qrc:/HOUSE.obj"), 0.0, 0.0, 20.0, rootEntity));
  p_downloadObjects.append(DownloadObject(QUrl("qrc:/home/HOUSE.obj"), QVector3D(0, 0, 0), QVector3D(0, 0, 0), 20, rootEntity));
  savingStatus(false);

  // m_createStars(ui->sb_countStars->value());
}

void MainWindow::on_action_create_triggered() {
  if (!isSaved) {
	if (!msgBox_save_call()) return;
  }
  if (!setNewPath()) return;
  clearScene();
}

void MainWindow::on_action_save_triggered() { saveBIN(); }

void MainWindow::on_action_saveAs_triggered() {
  QString path;
  getNewPath(path);
  qDebug() << path;
  // if (!setNewPath()) return;
  // saveBIN();
}

void MainWindow::rotateLight() {
  time += 0.02;
  lightTransform->setTranslation(QVector3D(sin(time) * 1000, 0.0f, cos(time) * 1000));
}

void MainWindow::on_action_load_triggered() {
  if (!isSaved) {
	if (!msgBox_save_call()) return;
  }
  if (setNewPath()) decodFromBIN();
}

void MainWindow::on_action_exit_triggered() { close(); }

bool MainWindow::getNewPath(QString& path) {
  /*
   * Возвращает false при некорректном выборе
   *            true когда все классно
   */
  path = QFileDialog::getSaveFileName(this, "Выбрать файл", "Example", "BIN (*.bin)");
  if (path.isEmpty()) {
	QMessageBox::information(this, "Упс", "Файл не выбран", QMessageBox::Ok);
	return false;
  } else {
	return true;
  }
}

bool MainWindow::setNewPath() /*установка нового пути к файлу*/ {
  /*
   * Возвращает false при некорректном выборе
   *            true когда все классно
   */
  QString newFilePath = QFileDialog::getSaveFileName(this, "Выбрать файл", "Example", "BIN (*.bin)");
  if (newFilePath.isEmpty()) {
	QMessageBox::information(this, "Упс", "Файл не выбран", QMessageBox::Ok);
	return false;
  } else {
	filePath = newFilePath;
	file.setFileName(filePath);
	QFileInfo fileInfo(filePath);
	fileName = fileInfo.baseName();
	savingStatus(true);
	return true;
  }
}

void MainWindow::savingStatus(bool status) /*функция изменения статуса сохранения*/ {
  isSaved = status;

  if (status) {
	// isSaved = true;
	view.setTitle(fileName);
	setWindowTitle(fileName);

  } else {
	// isSaved = false;
	view.setTitle("*" + fileName);
	setWindowTitle("*" + fileName);
  }
}

bool MainWindow::saveBIN() {
  prepairToSaveInBIN();
  if (!file.open(QIODevice::WriteOnly)) {
	QMessageBox::information(this, "Ой", "Файл не удалость открыть", QMessageBox::Ok);
	return false;
  }

  if (!file.write(saveBin)) {
	file.close();
	QMessageBox::information(this, "Ой", "Файл не удалость записать", QMessageBox::Ok);
	return false;
  }

  file.close();
  savingStatus(true);
  return true;
}

bool MainWindow::saveBIN(QString path) {
  prepairToSaveInBIN();
  QFile fileByPath;
  fileByPath.setFileName(path);
  if (!fileByPath.open(QIODevice::WriteOnly)) {
	QMessageBox::information(this, "Ой", "Файл не удалость открыть", QMessageBox::Ok);
	return false;
  }

  if (!fileByPath.write(saveBin)) {
	fileByPath.close();
	QMessageBox::information(this, "Ой", "Файл не удалость записать", QMessageBox::Ok);
	return false;
  }

  fileByPath.close();
  savingStatus(true);
  return true;
}

bool MainWindow::prepairToSaveInBIN() {
  saveBin.clear();
  int size = p_cubics.size();
  saveBin.append((char*)&size, sizeof(size));
  size = p_spheres.size();
  saveBin.append((char*)&size, sizeof(size));
  size = p_toruses.size();
  saveBin.append((char*)&size, sizeof(size));

  foreach (Cuboid figure, p_cubics) {
	saveBin.append((char*)&figure.get_coord(), sizeof(QVector3D));
	saveBin.append((char*)&figure.get_size(), sizeof(QVector3D));
	saveBin.append((char*)&figure.get_rotation(), sizeof(QVector3D));
	saveBin.append((char*)&figure.get_color(), sizeof(QColor));
	float scale = figure.get_scale();
	saveBin.append((char*)&scale, sizeof(float));
  }
  foreach (Spheroid figure, p_spheres) {
	saveBin.append((char*)&figure.get_coord(), sizeof(QVector3D));
	saveBin.append((char*)&figure.get_size(), sizeof(QVector3D));
	saveBin.append((char*)&figure.get_color(), sizeof(QColor));
	float scale = figure.get_scale();
	saveBin.append((char*)&scale, sizeof(float));
  }
  foreach (Toroid figure, p_toruses) {
	saveBin.append((char*)&figure.get_coord(), sizeof(QVector3D));
	QVector4D size = QVector4D(figure.get_size().x(), figure.innerRadius, figure.get_size().y(), figure.get_size().z());
	saveBin.append((char*)&size, sizeof(QVector4D));
	saveBin.append((char*)&figure.get_rotation(), sizeof(QVector3D));
	saveBin.append((char*)&figure.get_color(), sizeof(QColor));
	float scale = figure.get_scale();
	saveBin.append((char*)&scale, sizeof(float));
  }
  saveBin = (QCryptographicHash::hash(saveBin, QCryptographicHash::Md5)) + saveBin;
  return true;
}

Errors MainWindow::decodFromBIN() {
  if (saveBin.size() < 16) return WRONGFORMAT;

  if (saveBin.left(16) != QCryptographicHash::hash(saveBin.right(saveBin.size() - 16), QCryptographicHash::Md5)) return WRONGCONTROLHASH;

  int countCubics = 0;
  int countSpheres = 0;
  int countToroids = 0;
  char* byteShift = saveBin.data() + 16;

  memcpy((void*)&countCubics, byteShift, sizeof(int));
  byteShift = byteShift + sizeof(int);
  memcpy((void*)&countSpheres, byteShift, sizeof(int));
  byteShift = byteShift + sizeof(int);
  memcpy((void*)&countToroids, byteShift, sizeof(int));
  byteShift = byteShift + sizeof(int);

  for (int i = 0; i < countCubics; ++i) {
	QVector3D coord;
	QVector3D size;
	QVector3D rot;
	QColor color;
	float scale;
	memcpy((void*)&coord, byteShift, sizeof(QVector3D));
	byteShift = byteShift + sizeof(QVector3D);
	memcpy((void*)&size, byteShift, sizeof(QVector3D));
	byteShift = byteShift + sizeof(QVector3D);
	memcpy((void*)&rot, byteShift, sizeof(QVector3D));
	byteShift = byteShift + sizeof(QVector3D);
	memcpy((void*)&color, byteShift, sizeof(QColor));
	byteShift = byteShift + sizeof(QColor);
	memcpy((void*)&scale, byteShift, sizeof(float));
	byteShift = byteShift + sizeof(float);
	p_cubics.append(Cuboid(coord, rot, size, color, scale, rootEntity));
  }

  for (int i = 0; i < countSpheres; ++i) {
	QVector3D coord;
	QVector3D size;
	QColor color;
	float scale;
	memcpy((void*)&coord, byteShift, sizeof(QVector3D));
	byteShift = byteShift + sizeof(QVector3D);
	memcpy((void*)&size, byteShift, sizeof(QVector3D));
	byteShift = byteShift + sizeof(QVector3D);
	memcpy((void*)&color, byteShift, sizeof(QColor));
	byteShift = byteShift + sizeof(QColor);
	memcpy((void*)&scale, byteShift, sizeof(float));
	byteShift = byteShift + sizeof(float);
	p_spheres.append(Spheroid(coord, size, color, scale, rootEntity));
  }

  for (int i = 0; i < countToroids; ++i) {
	QVector3D coord;
	QVector4D size;
	QVector3D rot;
	QColor color;
	float scale;
	memcpy((void*)&coord, byteShift, sizeof(QVector3D));
	byteShift = byteShift + sizeof(QVector3D);
	memcpy((void*)&size, byteShift, sizeof(QVector4D));
	byteShift = byteShift + sizeof(QVector4D);
	memcpy((void*)&rot, byteShift, sizeof(QVector3D));
	byteShift = byteShift + sizeof(QVector3D);
	memcpy((void*)&color, byteShift, sizeof(QColor));
	byteShift = byteShift + sizeof(QColor);
	memcpy((void*)&scale, byteShift, sizeof(float));
	byteShift = byteShift + sizeof(float);
	p_toruses.append(Toroid(coord, rot, size, color, scale, rootEntity));
	qDebug() << coord;
	qDebug() << size;
	qDebug() << rot;
	qDebug() << color;
	qDebug() << scale;
  }
  return NOERRORS;
}

void MainWindow::closeEvent(QCloseEvent* e) {
  if (isSaved) {
	e->accept();
	view.close();
  } else {
	if (msgBox_save_call()) {
	  e->accept();
	  view.close();
	} else
	  e->ignore();
  }
}
