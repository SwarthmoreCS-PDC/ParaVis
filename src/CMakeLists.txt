#General vis libraries but not too Qt heavy
target_sources(qtvis
   PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/timerCPU.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dataVis.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dataVisCPU.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dataVisCFunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gridVisiWrapper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cgridvisi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sphere.cpp
    ${CMAKE_CURRENT_LIST_DIR}/square.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cylinder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/matrixstack.cpp
    ${CMAKE_CURRENT_LIST_DIR}/qtSafeViewer.cpp
)

#Core Qt window stuff, some requring AutoMOC AutoUI
target_sources(qtvis
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mypanelopengl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/qtViewer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui
    ${CMAKE_CURRENT_LIST_DIR}/resources.qrc
)

set_target_properties(qtvis PROPERTIES
  AUTOMOC ON
  AUTOUIC ON
  AUTORCC ON
)
