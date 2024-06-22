#ifndef CUBOID_HPP
#define CUBOID_HPP

#include "basicfigure.hpp"

class Cuboid : public BasicFigure {
 public:
  Cuboid(Qt3DCore::QNode* parent = Q_NULLPTR);
  Cuboid(QVector3D coord, QVector3D rotation, QVector3D size, QColor color, float scale, Qt3DCore::QNode* parent = Q_NULLPTR);
  ~Cuboid();
  Qt3DExtras::QCuboidMesh* p_mesh;

  void m_updateParams() override;
};

#endif  // CUBOID_HPP
