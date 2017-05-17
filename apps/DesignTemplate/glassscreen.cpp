#include "glassscreen.h"
#include "ui_glassscreen.h"

#include <QMessageBox>

#include "widgets/dragwidget.h"

#include "homescreen.h"
#include "settingscreen.h"

using namespace VitragesDecision;

GlassScreen *GlassScreen::_instance = NULL;

GlassScreen *GlassScreen::Instance(QWidget *parent)
{
    if (_instance == NULL) {
        GlassScreen::_instance = new GlassScreen(parent);
    }

    return _instance;
}

GlassScreen::GlassScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlassScreen)
{
    ui->setupUi(this);

    DragWidget *widget = new DragWidget();

    ui->frameGlass->layout()->addWidget(widget);
}

GlassScreen::~GlassScreen()
{
    delete ui;
}

void GlassScreen::on_btnHome_clicked()
{
    HomeScreen::Instance()->showMaximized();

    this->hide();
}

void GlassScreen::on_btnQuit_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, tr("Vitrages Décision"), tr("Do you want to quit application?"),
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void GlassScreen::on_btnSetting_clicked()
{
    SettingScreen *screen = new SettingScreen();

    screen->setParent(this);

    screen->showMaximized();

    this->hide();
}

void GlassScreen::on_btnRun_clicked()
{

}
