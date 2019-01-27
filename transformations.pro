QT += widgets
requires(qtConfig(combobox))

HEADERS     = renderarea.h \
              window.h \
    vec2d.h
SOURCES     = main.cpp \
              renderarea.cpp \
	      window.cpp \
    vec2d.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/transformations
INSTALLS += target
