#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;

public slots:
        void Start();
        void Stop();
        void Pause();
        void Resume();
        void PreviousStep();
        void NextStep();
        void StartMoveAnimation();
        void StopMoveAnimation();
};

#endif // MAINWINDOW_H
