#ifndef BASICFIGURE_HPP
#define BASICFIGURE_HPP

#include <QList>
#include <QMainWindow>
#include <QVector>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>

class BasicFigure {
 public:
  BasicFigure();
  Qt3DCore::QEntity* p_entity;
  Qt3DExtras::QPhongMaterial* p_material;
  Qt3DCore::QTransform* p_transform;

  QVector3D p_coord = QVector3D(0.0f, 0.0f, 0.0f);
  QVector3D p_rotation = QVector3D(0.0f, 0.0f, 0.0f);
  QVector3D p_size = QVector3D(1.0f, 1.0f, 1.0f);
  QColor p_color = QColor(0, 0, 0);
  float p_scale = 1;

  virtual void m_updateParams();

  const QVector3D& get_coord() const;
  void set_coord(const QVector3D& new_coord);
  const QVector3D& get_rotation() const;
  void set_rotation(const QVector3D& new_rotation);
  const QVector3D& get_size() const;
  void set_size(const QVector3D& new_size);
  const QColor& get_color() const;
  void set_color(const QColor& new_color);
  float getScale() const;
  void setScale(float newScale);
};

#endif  // BASICFIGURE_HPP
