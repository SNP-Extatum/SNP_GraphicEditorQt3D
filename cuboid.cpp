#include "cuboid.hpp"

Cuboid::Cuboid(Qt3DCore::QNode* parent) {
  p_entity = new Qt3DCore::QEntity(parent);
  p_mesh = new Qt3DExtras::QCuboidMesh(p_entity);
  p_material = new Qt3DExtras::QPhongMaterial(p_entity);
  p_transform = new Qt3DCore::QTransform(p_entity);
  p_entity->addComponent(p_mesh);
  p_entity->addComponent(p_material);
  p_entity->addComponent(p_transform);
  m_updateParams();
}

Cuboid::Cuboid(QVector3D coord, QVector3D rotation, QVector3D size, QColor color, float scale, Qt3DCore::QNode* parent) {
  p_coord = coord;
  p_rotation = rotation;
  p_size = size;
  p_color = color;
  p_scale = scale;

  p_entity = new Qt3DCore::QEntity(parent);
  p_mesh = new Qt3DExtras::QCuboidMesh(p_entity);
  p_material = new Qt3DExtras::QPhongMaterial(p_entity);
  p_transform = new Qt3DCore::QTransform(p_entity);
  p_entity->addComponent(p_mesh);
  p_entity->addComponent(p_material);
  p_entity->addComponent(p_transform);
  qDebug() << "create";

  m_updateParams();
}

Cuboid::~Cuboid() {
  // p_entity->removeComponent(p_mesh);
  // p_entity->removeComponent(p_material);
  // p_entity->removeComponent(p_transform);
  // delete p_entity;
  // delete p_mesh;
  // delete p_material;
  // delete p_transform;
}

void Cuboid::m_updateParams() {
  p_mesh->setXExtent(p_size.x() * p_scale);
  p_mesh->setYExtent(p_size.y() * p_scale);
  p_mesh->setZExtent(p_size.z() * p_scale);

  p_material->setDiffuse(p_color);

  p_transform->setTranslation(p_coord);
  p_transform->setRotationX(p_rotation.x());
  p_transform->setRotationY(p_rotation.y());
  p_transform->setRotationZ(p_rotation.z());
}
