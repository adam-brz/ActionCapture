#include "editorwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditorWindow w;

    a.setStyle(QStyleFactory::create("Fusion"));
    w.show();

    return a.exec();
}
