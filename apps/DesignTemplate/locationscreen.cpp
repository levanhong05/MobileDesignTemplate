#include "locationscreen.h"
#include "ui_locationscreen.h"

#include <QFile>
#include <QMessageBox>

#include "homescreen.h"
#include "settingscreen.h"

using namespace VitragesDecision;

LocationScreen *LocationScreen::_instance = NULL;

LocationScreen *LocationScreen::Instance(QWidget *parent)
{
    if (_instance == NULL) {
        LocationScreen::_instance = new LocationScreen(parent);
    }

    return _instance;
}

LocationScreen::LocationScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LocationScreen)
{
    ui->setupUi(this);

    // Load an application style
    QFile styleFile(":/design/style/design.qss");
    styleFile.open(QFile::ReadOnly);

    // Apply the loaded stylesheet
    QString style = styleFile.readAll();
    this->setStyleSheet(style);

    ui->frameOutFrance->setVisible(false);

    connect(ui->btnProject, SIGNAL(onStateChanged(bool)), this, SLOT(onSwitchButtonClicked(bool)));
}

LocationScreen::~LocationScreen()
{
    delete ui;
}

void LocationScreen::on_btnHome_clicked()
{
    HomeScreen::Instance()->showMaximized();

    this->hide();
}

void LocationScreen::on_btnQuit_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, tr("Vitrages Décision"), tr("Do you want to quit application?"),
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void LocationScreen::on_btnSetting_clicked()
{
    SettingScreen *screen = new SettingScreen();

    screen->setParent(this);

    screen->showMaximized();

    this->hide();
}

void LocationScreen::onSwitchButtonClicked(bool state)
{
    if (state) {
        ui->frameFrance->setVisible(false);
        ui->frameOutFrance->setVisible(true);
    } else {
        ui->frameFrance->setVisible(true);
        ui->frameOutFrance->setVisible(false);
    }
}
