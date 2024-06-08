#ifndef TOROID_HPP
#define TOROID_HPP

#include "basicfigure.hpp"

class Toroid : public BasicFigure {
 public:
  Toroid(Qt3DCore::QNode* parent = Q_NULLPTR);
  Toroid(QVector3D coord, QVector3D rotation, QVector4D size, QColor color, float scale, Qt3DCore::QNode* parent = Q_NULLPTR);
  float innerRadius = 0.1f;
  Qt3DExtras::QTorusMesh* p_mesh;
  void m_updateParams() override;
};

#endif  // TOROID_HPP
