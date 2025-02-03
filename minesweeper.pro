#-------------------------------------------------
# Qt Project Configuration File for Minesweeper
#-------------------------------------------------

# Specify required Qt modules
QT       += core gui widgets          # Core Qt, GUI, and Widgets modules
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  # Explicit widgets for Qt5+

# Application metadata
TARGET = minesweeper    # Output executable name
TEMPLATE = app          # Build as application (not library)

# Compiler configurations
DEFINES += QT_DEPRECATED_WARNINGS  # Show warnings for deprecated Qt features
CONFIG += sdk_no_version_check     # Disable SDK version checks

# Source files to compile
SOURCES += \
    main.cpp \          # Application entry point
    tile.cpp \          # Tile class implementation
    gameboard.cpp \     # Game board logic
    mainwindow.cpp      # Main window UI

# Header files
HEADERS += \
    tile.h \            # Tile class interface
    gameboard.h \       # Game board class interface
    mainwindow.h        # Main window class interface

# Note: This file uses Qt's qmake build system
# Run 'qmake' to generate Makefile, then 'make' to build