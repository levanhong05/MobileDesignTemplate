#include "splashscreen.h"
#include "ui_splashscreen.h"

#include <QFile>
#include <QTimer>

#include "homescreen.h"

using namespace VitragesDecision;

SplashScreen::SplashScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);

    ui->lblSplashImage->setPixmap(QPixmap::fromImage(QImage(":/design/images/splash.jpg")));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdateProgressBar()));
    timer->start(50); // 1000ms -- 1 seconds

    // Load an application style
    QFile styleFile(":/design/style/design.qss");
    styleFile.open(QFile::ReadOnly);

    // Apply the loaded stylesheet
    QString style = styleFile.readAll();
    this->setStyleSheet(style);

    ui->progressBar->setAlignment(Qt::AlignCenter);

    showFullScreen();
}

SplashScreen::~SplashScreen()
{
    delete ui;
}

void SplashScreen::onUpdateProgressBar()
{
    int value = ui->progressBar->value() + 1;

    ui->progressBar->setValue(value);
}

void SplashScreen::on_progressBar_valueChanged(int value)
{
    if (value >= 100) {
        HomeScreen::Instance()->showMaximized();

        this->close();
    }
}
