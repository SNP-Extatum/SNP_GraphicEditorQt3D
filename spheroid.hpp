#ifndef SPHEROID_HPP
#define SPHEROID_HPP

#include "basicfigure.hpp"

class Spheroid : public BasicFigure {
 public:
  Spheroid(Qt3DCore::QNode* parent = Q_NULLPTR);
  Spheroid(QVector3D coord, QVector3D size, QColor color, float scale, Qt3DCore::QNode* parent = Q_NULLPTR);
  Qt3DExtras::QSphereMesh* p_mesh;

  void m_updateParams() override;
};

#endif  // SPHEROID_HPP
