#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
  Camera(int width, int height, int mapWidth, int mapHeight, int _xBuffer, int _yBuffer);
  ~Camera();
  int calculateOffset(int x, int y);
  void updatePosition(int x, int y);
  int getWidth(){return m_width;};
  int getHeight(){return m_height;};
  int getX(){return m_x;};
  int getY(){return m_y;};
  int getPos(){return m_x + m_y * m_mapWidth;};
	int getXBuffer(){ return m_xBuffer; };
	int getYBuffer(){ return m_yBuffer; };

private:
  int m_width;
  int m_height;
  int m_mapWidth;
  int m_mapHeight;
	int m_xBuffer;
	int m_yBuffer;
  int m_x;
  int m_y;
};

#endif
