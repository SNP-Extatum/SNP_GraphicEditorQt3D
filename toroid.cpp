#include "toroid.hpp"

Toroid::Toroid(Qt3DCore::QNode* parent) {
  p_entity = new Qt3DCore::QEntity(parent);
  p_mesh = new Qt3DExtras::QTorusMesh(p_entity);
  p_material = new Qt3DExtras::QPhongMaterial(p_entity);
  p_transform = new Qt3DCore::QTransform(p_entity);
  p_entity->addComponent(p_mesh);
  p_entity->addComponent(p_material);
  p_entity->addComponent(p_transform);
  qDebug() << "create";
  m_updateParams();
}

Toroid::Toroid(QVector3D coord, QVector3D rotation, QVector4D size, QColor color, float scale, Qt3DCore::QNode* parent) {
  p_coord = coord;
  p_size.setX(size.x());
  innerRadius = size.y();
  p_size.setY(size.z());
  p_size.setZ(size.w());
  p_color = color;
  p_scale = scale;
  p_rotation = rotation;

  p_entity = new Qt3DCore::QEntity(parent);
  p_mesh = new Qt3DExtras::QTorusMesh(p_entity);
  p_material = new Qt3DExtras::QPhongMaterial(p_entity);
  p_transform = new Qt3DCore::QTransform(p_entity);
  p_entity->addComponent(p_mesh);
  p_entity->addComponent(p_material);
  p_entity->addComponent(p_transform);

  m_updateParams();
}

void Toroid::m_updateParams() {
  p_mesh->setRadius(p_size.x() * p_scale);
  p_mesh->setMinorRadius(innerRadius * p_scale);
  p_mesh->setSlices(p_size.y());
  p_mesh->setRings(p_size.z());
  p_material->setDiffuse(p_color);

  p_transform->setTranslation(p_coord);
  p_transform->setRotationX(p_rotation.x());
  p_transform->setRotationY(p_rotation.y());
  p_transform->setRotationZ(p_rotation.z());
}
