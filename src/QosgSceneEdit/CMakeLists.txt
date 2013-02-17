SET(QT_USE_QTOPENGL TRUE)
SET(QT_USE_QTMAIN TRUE)

INCLUDE(${QT_USE_FILE})

#
# Header and source files
#
SET(SE_SOURCES
	BuildQtTreeView.h
	BuildQtTreeView.cpp
	main.cpp
	MainWindow.h
	MainWindow.cpp
	OsgWidget.h
	OsgWidget.cpp
	TreeViewItem.h
	TreeViewItem.cpp
	Undo/Commands.h
	Undo/Commands.cpp
	Styles/seStyle.h
	Styles/seStyle.cpp
	BackgroundGeode.h
	BackgroundGeode.cpp
	SelectionManager.h
	SelectionManager.cpp
	ComputeNodeInfoVisitor.h
	ComputeNodeInfoVisitor.cpp
)

#
# On Windows enable the .NET-Style
#

#
# Headers which have a Q_OBJECT
#
SET(MOC_HEADERS MainWindow.h )
qt4_wrap_cpp( SE_MOC_HEADERS ${MOC_HEADERS} )

#
# Generate C++ files from ui file
#
SET(SE_UIS UI/MainWindow.ui )

#
# Qt4 setup
#
QT4_WRAP_UI(SE_UIS_H ${SE_UIS})
QT4_ADD_RESOURCES(SE_RC_SOURCES resources.qrc)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${OPENSCENEGRAPH_INCLUDE_DIRS} )

SET(EXECUTABLE_OUTPUT_PATH ${SE_EXECUTABLE_DIR})

ADD_EXECUTABLE(QosgSceneEdit ${SE_SOURCES} ${SE_MOC_HEADERS} ${SE_UIS_H} ${SE_RC_SOURCES})
TARGET_LINK_LIBRARIES(QosgSceneEdit ${OPENSCENEGRAPH_LIBRARIES} ${QT_LIBRARIES} ${OPENGL_LIBRARIES} )

INSTALL( TARGETS QosgSceneEdit RUNTIME DESTINATION bin )