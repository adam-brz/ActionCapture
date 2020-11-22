#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <input/GlobalMouse.h>
#include <input/GlobalKeyboard.h>

QT_BEGIN_NAMESPACE
namespace Ui { class EditorWindow; }
QT_END_NAMESPACE

class EditorWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::EditorWindow *ui;
    QTimer *timer;

    GlobalMouse *mouse;
    GlobalKeyboard *keyboard;

public:
    EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

private:
    void printKey(int key, int status, int time);
    void printMousePos(const KeyInfo &info);

};
#endif // EDITORWINDOW_H
