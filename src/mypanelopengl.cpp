#include "mypanelopengl.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent)
    : QOpenGLWidget(parent), m_angles(0., 0., 0.) {

  for (int i = 0; i < NUM_PROGS; i++) {
    m_shaderPrograms[i] = nullptr;
    m_vertexShaders[i] = nullptr;
    m_fragmentShaders[i] = nullptr;
  }

  m_sphere = nullptr;
  m_vis = nullptr;
  m_timer = nullptr;
  m_paused = false;
  m_drawSphere = false;
  m_polymode = 2;
  m_cull = true;
  m_curr_prog = 0;
  m_tex_map = 1;
  m_texture = nullptr;
}

MyPanelOpenGL::~MyPanelOpenGL() {
  m_shaderPrograms[m_curr_prog]->release();
  delete m_sphere;
  m_sphere = nullptr;
  delete m_square;
  m_square = nullptr;
  delete m_texture;
  m_texture = nullptr;
  delete m_timer;
  m_timer = nullptr;
  delete m_vis;
  m_vis = nullptr;
  destroyShaders(0);
}

void MyPanelOpenGL::setAnimation(DataVis* vis){
  m_vis = vis;
  textureReload();
}

void MyPanelOpenGL::initializeGL() {


  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  updatePolyMode(m_polymode);
  setCulling(m_cull);
  Q_INIT_RESOURCE(resources);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  createShaders(0, ":/shaders/vshader.glsl", ":/shaders/fshader.glsl");

  /* TODO: don't hard code this or make it part of distribution */
  m_texture = new QOpenGLTexture(QImage(":/background.jpg").mirrored());

  m_sphere = new Sphere(0.5, 30, 30);
  m_square = new Square(2.);

  m_shaderPrograms[m_curr_prog]->bind();

  m_projection.perspective(40, 1, 1, 8);
  m_camera.lookAt(vec3(0, 0, 3), vec3(0, 0, 0), vec3(0, 1., 0.));
  updateModel();

  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(step()));
  m_timer->start(10);
}

void MyPanelOpenGL::step(){
  if(!m_paused){
    textureReload();
    update();
  }
}

void MyPanelOpenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void MyPanelOpenGL::paintGL() {
  /* clear both color and depth buffer */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  setTexture();
  if (!m_shaderPrograms[m_curr_prog]) {
    return;
  }
  m_shaderPrograms[m_curr_prog]->bind();
  mat4 mview = m_camera * m_model;
  m_shaderPrograms[m_curr_prog]->setUniformValue("projection", m_projection);
  m_shaderPrograms[m_curr_prog]->setUniformValue("camera", m_camera);
  m_shaderPrograms[m_curr_prog]->setUniformValue("model", m_model);
  m_shaderPrograms[m_curr_prog]->setUniformValue("modelView", mview);
  m_shaderPrograms[m_curr_prog]->setUniformValue("normalMatrix",
                                                 mview.normalMatrix());
  m_shaderPrograms[m_curr_prog]->setUniformValue("Tex0", 0);
  m_shaderPrograms[m_curr_prog]->setUniformValue("Tex1", 1);
  m_shaderPrograms[m_curr_prog]->setUniformValue(
      "lightPos", QVector4D(1.5, 0, 2, 1.)); // in world coordinates

  if (m_drawSphere) {
    m_sphere->draw(m_shaderPrograms[m_curr_prog]);
    // m_square->draw(m_shaderProgram);
  } else {
    m_square->draw(m_shaderPrograms[m_curr_prog]);
  }
  glFlush();

  // swapBuffers(); /* not need in QT see QGLWidget::setAutoBufferSwap */
}

void MyPanelOpenGL::keyPressEvent(QKeyEvent *event) {
  qreal step = 1;
  /*Enable strong Focus on GL Widget to process key events*/
  switch (event->key()) {
  case Qt::Key_Space:
     m_paused=!m_paused;
     break;
  case Qt::Key_X:
    if (event->text() == "x") {
      updateAngles(0, step);
    } else {
      updateAngles(0, -step);
    }
    break;
  case Qt::Key_Y:
    if (event->text() == "y") {
      updateAngles(1, step);
    } else {
      updateAngles(1, -step);
    }
    break;
  case Qt::Key_Z:
    if (event->text() == "z") {
      updateAngles(2, step);
    } else {
      updateAngles(2, -step);
    }
    break;
  case Qt::Key_C:
    m_cull=!m_cull;
    setCulling(m_cull);
    break;
  case Qt::Key_P:
    m_polymode = (m_polymode + 1) % 3;
    updatePolyMode(m_polymode);
    break;
  case Qt::Key_S:
    m_drawSphere = !m_drawSphere;
    break;
  case Qt::Key_T:
    m_tex_map = (m_tex_map + 1) % 2;
    setTexture();
    break;
  case Qt::Key_V:
    m_curr_prog = (m_curr_prog + 1) % NUM_PROGS;
    break;
  default:
    QWidget::keyPressEvent(event); /* pass to base class */
  }
  update();
}

void MyPanelOpenGL::setTexture() {
  if (m_tex_map == 0) {
    m_texture->bind();
  } else if (m_tex_map == 1 && m_vis) {
    m_vis->bind();
  }
}

void MyPanelOpenGL::updateAngles(int idx, qreal amt) {
  if (idx == 0) {
    m_angles.setX(wrap(m_angles.x() + amt));
  } else if (idx == 1) {
    m_angles.setY(wrap(m_angles.y() + amt));
  } else if (idx == 2) {
    m_angles.setZ(wrap(m_angles.z() + amt));
  }
  updateModel();
}

void MyPanelOpenGL::updateModel() {
  m_model.setToIdentity();
  m_model.rotate(m_angles.z(), vec3(0, 0, 1.));
  m_model.rotate(m_angles.y(), vec3(0, 1, 0.));
  m_model.rotate(m_angles.x(), vec3(1, 0, 0.));
}

qreal MyPanelOpenGL::wrap(qreal amt) {
  if (amt > 360.) {
    return amt - 360.;
  } else if (amt < 0.) {
    return amt + 360.;
  }
  return amt;
}

void MyPanelOpenGL::updatePolyMode(int val) {
  GLenum mode = GL_NONE;
  if (val == 0) {
    mode = GL_POINT;
  } else if (val == 1) {
    mode = GL_LINE;
  } else if (val == 2) {
    mode = GL_FILL;
  }

  if (mode != GL_NONE) {
    makeCurrent();
    glPolygonMode(GL_FRONT_AND_BACK, mode);
  }
  // glPolygonMode(GL_BACK,GL_POINT);
}

void MyPanelOpenGL::setCulling(bool cull){
  makeCurrent();
  if (cull){
    glEnable(GL_CULL_FACE);
  }
  else{
    glDisable(GL_CULL_FACE);
  }
}

void MyPanelOpenGL::createShaders(int i, QString vertName, QString fragName) {

  //cout << "building shader " << i << endl;
  destroyShaders(i); // get rid of any old shaders
  m_vertexShaders[i] = new QOpenGLShader(QOpenGLShader::Vertex);
  if (!m_vertexShaders[i]->compileSourceFile(vertName)) {
    qWarning() << m_vertexShaders[i]->log();
  }

  m_fragmentShaders[i] = new QOpenGLShader(QOpenGLShader::Fragment);
  if (!m_fragmentShaders[i]->compileSourceFile(fragName)) {
    qWarning() << m_fragmentShaders[i]->log();
  }

  m_shaderPrograms[i] = new QOpenGLShaderProgram();
  m_shaderPrograms[i]->addShader(m_vertexShaders[i]);
  m_shaderPrograms[i]->addShader(m_fragmentShaders[i]);

  if (!m_shaderPrograms[i]->link()) {
    qWarning() << m_shaderPrograms[i]->log() << endl;
  }
}

void MyPanelOpenGL::destroyShaders(int i) {
  delete m_vertexShaders[i];
  m_vertexShaders[i] = nullptr;
  delete m_fragmentShaders[i];
  m_fragmentShaders[i] = nullptr;

  if (m_shaderPrograms[i]) {
    m_shaderPrograms[i]->release();
    delete m_shaderPrograms[i];
    m_shaderPrograms[i] = nullptr;
  }
}

void MyPanelOpenGL::textureReload() {
  if(m_vis){
    m_vis->textureReload();
  }
}
