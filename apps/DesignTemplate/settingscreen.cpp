#include "settingscreen.h"
#include "ui_settingscreen.h"

#include <QMessageBox>

#include "homescreen.h"
#include "aboutscreen.h"
#include "registerscreen.h"

using namespace VitragesDecision;

SettingScreen::SettingScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingScreen)
{
    ui->setupUi(this);

    // Load an application style
    QFile styleFile(":/design/style/design.qss");
    styleFile.open(QFile::ReadOnly);

    // Apply the loaded stylesheet
    QString style = styleFile.readAll();
    this->setStyleSheet(style);

    connect(ui->lblCoordinate, SIGNAL(mouseReleased()), this, SLOT(onCoordinateClicked()));
    connect(ui->lblAbout, SIGNAL(mouseReleased()), this, SLOT(onAboutClicked()));

    connect(ui->btnBack, SIGNAL(mouseHovered()), this, SLOT(onBackMouseHovered()));
    connect(ui->btnBack, SIGNAL(mouseLeaved()), this, SLOT(onBackMouseLeaved()));
}

SettingScreen::~SettingScreen()
{
    delete ui;
}

void SettingScreen::onCoordinateClicked()
{
    RegisterScreen *screen = new RegisterScreen();
    screen->show();
}

void SettingScreen::onAboutClicked()
{
    AboutScreen *screen = new AboutScreen();

    screen->show();
}

void SettingScreen::onBackMouseHovered()
{
    ui->btnBack->setStyleSheet("color:#00aaff;" \
                               "border-image: url(:/design/images/back.png) 0 0 0 0 stretch stretch;" \
                               "height:35px;" \
                               "padding-left:5px;" \
                               "padding-bottom:3px;");
}

void SettingScreen::onBackMouseLeaved()
{
    ui->btnBack->setStyleSheet("color:#ffffff;" \
                               "border-image: url(:/design/images/back.png) 0 0 0 0 stretch stretch;" \
                               "height:35px;" \
                               "padding-left:5px;" \
                               "padding-bottom:3px;");
}

void SettingScreen::on_btnQuit_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, tr("Vitrages Décision"), tr("Do you want to quit application?"),
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void SettingScreen::on_btnHome_clicked()
{
    HomeScreen::Instance()->showMaximized();

    this->close();
}

void SettingScreen::setParent(QWidget *parent)
{
    _parent = parent;
}

void SettingScreen::on_btnBack_clicked()
{
    _parent->showMaximized();

    this->hide();
}
