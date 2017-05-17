#include "homescreen.h"
#include "ui_homescreen.h"

#include <QFile>

#include "aboutscreen.h"
#include "glassscreen.h"
#include "settingscreen.h"
#include "locationscreen.h"

using namespace VitragesDecision;

HomeScreen *HomeScreen::_instance = NULL;

HomeScreen *HomeScreen::Instance(QWidget *parent)
{
    if (_instance == NULL) {
        HomeScreen::_instance = new HomeScreen(parent);
    }

    return _instance;
}

HomeScreen::HomeScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);

    // Load an application style
    QFile styleFile(":/design/style/design.qss");
    styleFile.open(QFile::ReadOnly);

    // Apply the loaded stylesheet
    QString style = styleFile.readAll();
    this->setStyleSheet(style);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::on_btnSetting_clicked()
{
    SettingScreen *screen = new SettingScreen();

    screen->setParent(this);

    screen->showMaximized();

    this->hide();
}

void HomeScreen::on_btnAbout_clicked()
{
    AboutScreen *screen = new AboutScreen();

    screen->show();
}

void HomeScreen::on_btnDefinition_clicked()
{
    GlassScreen::Instance()->showMaximized();

    this->hide();
}

void HomeScreen::on_btnLocation_clicked()
{
    LocationScreen::Instance()->showMaximized();

    this->hide();
}
