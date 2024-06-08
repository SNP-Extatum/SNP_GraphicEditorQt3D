#ifndef DOWNLOADOBJECT_HPP
#define DOWNLOADOBJECT_HPP

#include <QList>
#include <QMainWindow>
#include <QVector>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>

class DownloadObject {
 public:
  DownloadObject();
  DownloadObject(QUrl url, QVector3D coord, QVector3D rotation, float scale, Qt3DCore::QNode* parent = Q_NULLPTR);
  Qt3DCore::QEntity* p_entity;
  Qt3DRender::QSceneLoader* p_sceneLoader;
  Qt3DCore::QTransform* p_transform;
  void m_updateParams();
  QUrl p_url;
  QVector3D p_coord;
  QVector3D p_rotation;
  float p_scale;
};

#endif  // DOWNLOADOBJECT_HPP
