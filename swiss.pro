TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
        main.hpp

oracle_files.files = $$PWD/*.in $$PWD/*.oracle
oracle_files.path = $$OUT_PWD

COPIES += \
       oracle_files

DISTFILES += \
          2.in \
          README.md \
          1.in \
          1.oracle \
          2.in \
          2.oracle