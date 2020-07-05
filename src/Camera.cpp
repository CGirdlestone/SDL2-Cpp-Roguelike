
#include <algorithm>
#include "Camera.h"

Camera::Camera(int width, int height, int mapWidth, int mapHeight):
m_width(width), m_height(height), m_mapWidth(mapWidth), m_mapHeight(mapHeight)
{

}

Camera::~Camera()
{

}

int Camera::calculateOffset(int x, int y)
{
  int i, j;

  i = x - m_x;
  j = y - m_y;

  return i + j * m_width;
}

void Camera::updatePosition(int x, int y)
{
  m_x = x - m_width / 2;
  m_y = y - m_height / 2;

  m_x = std::min(m_x, m_mapWidth - m_width);
  m_x = std::max(m_x, 0);

  m_y = std::min(m_y, m_mapHeight - m_height);
  m_y = std::max(m_y, 0);
}
