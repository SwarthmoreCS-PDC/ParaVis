#pragma once

/* This is the primary QtOpenGL class that handles the primary
   event loop, updating the display, calling the user supplied
   animation function, and responding to keyboard events.
   Parts of it could be be simplified/expanded for a particular course
   by instructors familiar with OpenGL/Qt, but a typical user does not
   need to modify/understand this class
*/

#include "sphere.h"
#include "square.h"
#include "dataVis.h"
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QtOpenGL>
#include <QTimer>

typedef QVector4D point4;
typedef QVector4D color4;
typedef QVector3D vec3;
typedef QMatrix4x4 mat4;

#define NUM_PROGS 1
class MyPanelOpenGL : public QOpenGLWidget {
  Q_OBJECT

protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void keyPressEvent(QKeyEvent *event);

public:
  explicit MyPanelOpenGL(QWidget *parent = 0);
  virtual ~MyPanelOpenGL();
  void setAnimation(DataVis* vis);

private:

  /* simple test shapes */
  Sphere *m_sphere;
  Square *m_square;

  /* display geometry as  0 : points,  1 : lines, 2 : polygons */
  int m_polymode;
  /* cull back facing polygons (orientation CW by default) if true */
  bool m_cull;
  /* draw sphere if true, square otherwise */
  bool m_drawSphere;
  /* pause animation if true */
  bool m_paused;

  /* sample texture for shapes */
  QOpenGLTexture *m_texture;
  /* indicate current tex map ID 0: sample 1: animation texture */
  int m_tex_map;

  /* timer that periodically signals to control animation */
  QTimer* m_timer;

  /* User provided animation texture */
  DataVis* m_vis;

  vec3 m_angles; /* Euler angles for rotation */

  /* Matrix transormations for viewing scene */
  mat4 m_model;
  mat4 m_camera;
  mat4 m_projection;

  /* Shaders and programs */
  QOpenGLShader *m_vertexShaders[NUM_PROGS];
  QOpenGLShader *m_fragmentShaders[NUM_PROGS];
  QOpenGLShaderProgram *m_shaderPrograms[NUM_PROGS];
  int m_curr_prog; // current program ID

  // Make sure right texture is set based on m_tex_map
  void setTexture();

  void textureReload(); // run visualization update, reload texture

  /* update Euler angle at index idx by amt
   * idx=0,1,2 -> x,y,z */
  void updateAngles(int idx, qreal amt);

  /* update model matrix based on angle */
  void updateModel();

  /* wrap a angle value to the range 0..360*/
  qreal wrap(qreal amt);

  /* update Polygon draw mode based
   * 0 : point
   * 1 : line
   * 2 : polygon */
  void updatePolyMode(int val);

  /* Set openGL culling mode by provided cull parameter */
  void setCulling(bool cull);

  /* Create the ith shader given the file names
     for vertex and fragment shader */
  void createShaders(int i, QString vertName, QString fragName);

  /* Clean up memory for shader i */
  void destroyShaders(int i);

public slots:

  /* Called periodically by a timer signal to drive the
     animation loop */
  void step();

signals:


};
