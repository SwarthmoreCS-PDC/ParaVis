#include "qtSafeViewer.h"
QTSafeViewer::QTSafeViewer(int w, int h, QString title) : m_argc(1) {
  m_argv[0] = new char[5];
  m_argv[0][0] = 'h';
  m_argv[0][1] = 'i';
  m_argv[0][2] = '\0';
  m_viewer = new QTViewer(m_argc, m_argv, w, h, title);
}

QTSafeViewer::~QTSafeViewer() {
  delete m_viewer;
  m_viewer = nullptr;
  delete m_argv[0];
  m_argv[0] = nullptr;
}
