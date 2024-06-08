#include "downloadobject.hpp"

DownloadObject::DownloadObject() {}

DownloadObject::DownloadObject(QUrl url, QVector3D coord, QVector3D rotation, float scale, Qt3DCore::QNode* parent) {
  p_url = url;
  p_coord = coord;
  p_rotation = rotation;
  p_scale = scale;

  p_entity = new Qt3DCore::QEntity(parent);
  p_sceneLoader = new Qt3DRender::QSceneLoader(p_entity);
  p_transform = new Qt3DCore::QTransform(p_entity);
  p_sceneLoader->setSource(p_url);
  p_entity->addComponent(p_sceneLoader);
  p_entity->addComponent(p_transform);
}

void DownloadObject::m_updateParams() {
  p_transform->setScale(p_scale);
  p_transform->setTranslation(p_coord);
  p_transform->setRotationX(p_rotation.x());
  p_transform->setRotationY(p_rotation.y());
  p_transform->setRotationZ(p_rotation.z());
}
