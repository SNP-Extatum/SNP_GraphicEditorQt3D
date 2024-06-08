#include "basicfigure.hpp"

BasicFigure::BasicFigure() {}

float BasicFigure::getScale() const { return p_scale; }

void BasicFigure::setScale(float newScale) {
  p_scale = newScale;
  m_updateParams();
}

const QColor& BasicFigure::get_color() const { return p_color; }

void BasicFigure::set_color(const QColor& new_color) {
  p_color = new_color;
  m_updateParams();
}

const QVector3D& BasicFigure::get_size() const { return p_size; }

void BasicFigure::set_size(const QVector3D& new_size) {
  p_size = new_size;
  m_updateParams();
}

const QVector3D& BasicFigure::get_rotation() const { return p_rotation; }

void BasicFigure::set_rotation(const QVector3D& new_rotation) {
  p_rotation = new_rotation;
  m_updateParams();
}

const QVector3D& BasicFigure::get_coord() const { return p_coord; }

void BasicFigure::set_coord(const QVector3D& new_coord) {
  p_coord = new_coord;
  m_updateParams();
}

void BasicFigure::m_updateParams() {}
