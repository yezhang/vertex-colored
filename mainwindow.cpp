#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    //textPen = QPen(Qt::white);
    //textFont.setPixelSize(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Start()
{
    ui->graphicsView->startAlgorightm();
}

void MainWindow::Stop()
{
    ui->graphicsView->stopAlgorithm();
}

void MainWindow::Pause()
{
    ui->graphicsView->pauseAlgorightm();
}

void MainWindow::Resume()
{
    ui->graphicsView->resumeAlgorithm();
}

void MainWindow::PreviousStep()
{
    ui->graphicsView->previousStepAlgorithm();
}

void MainWindow::NextStep()
{
    ui->graphicsView->nextStepAlgorithm();
}

void MainWindow::StartMoveAnimation()
{
    ui->graphicsView->startAnimation();
}

void MainWindow::StopMoveAnimation()
{
    ui->graphicsView->stopAnimation();
}
