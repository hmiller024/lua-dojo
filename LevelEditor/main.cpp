/// main.cpp
///
/// This file contains the main entry point for our SpriteEditor QApplication
///
/// Author: Auto Generated
/// Date: March 24, 2023

#include "editorwindow.h"
#include "editormodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    EditorModel x;
    EditorWindow w(x);
    w.show();
    return a.exec();

}

