#include "spheroid.hpp"

Spheroid::Spheroid(Qt3DCore::QNode* parent) {
  p_entity = new Qt3DCore::QEntity(parent);
  p_mesh = new Qt3DExtras::QSphereMesh(p_entity);
  p_material = new Qt3DExtras::QPhongMaterial(p_entity);
  p_transform = new Qt3DCore::QTransform(p_entity);
  p_entity->addComponent(p_mesh);
  p_entity->addComponent(p_material);
  p_entity->addComponent(p_transform);
  qDebug() << "create";
  m_updateParams();
}

Spheroid::Spheroid(QVector3D coord, QVector3D size, QColor color, float scale, Qt3DCore::QNode* parent) {
  p_coord = coord;
  p_size = size;
  p_color = color;
  p_scale = scale;

  p_entity = new Qt3DCore::QEntity(parent);
  p_mesh = new Qt3DExtras::QSphereMesh(p_entity);
  p_material = new Qt3DExtras::QPhongMaterial(p_entity);
  p_transform = new Qt3DCore::QTransform(p_entity);
  p_entity->addComponent(p_mesh);
  p_entity->addComponent(p_material);
  p_entity->addComponent(p_transform);

  m_updateParams();
}

void Spheroid::m_updateParams() {
  p_mesh->setRadius(p_size.x() * p_scale);
  p_mesh->setSlices(p_size.y());
  p_mesh->setRings(p_size.z());
  // p_mesh->setXExtent(p_size.x() * p_scale);
  // p_mesh->setYExtent(p_size.y() * p_scale);
  // p_mesh->setZExtent(p_size.z() * p_scale);

  p_material->setDiffuse(p_color);

  p_transform->setTranslation(p_coord);
}
