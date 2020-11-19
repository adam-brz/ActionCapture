#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class EditorWindow; }
QT_END_NAMESPACE

class EditorWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::EditorWindow *ui;
    QTimer *timer;

public:
    EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void printMousePos();


};
#endif // EDITORWINDOW_H
