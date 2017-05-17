#include "registerscreen.h"
#include "ui_registerscreen.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopWidget>

#include "widgets/vlabel.h"
#include "avatarscreen.h"

using namespace VitragesDecision;

RegisterScreen::RegisterScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterScreen)
{
    ui->setupUi(this);

    // Load an application style
    QFile styleFile(":/design/style/design.qss");
    styleFile.open(QFile::ReadOnly);

    // Apply the loaded stylesheet
    QString style = styleFile.readAll();
    this->setStyleSheet(style);

    //Move the dialog away from the center
    setGeometry(0, 0, this->width(), this->height());

    int i = 0;

    if (qApp->desktop()->screenCount() > 1) {
        i = qApp->desktop()->screenNumber(this) ;
    }

    //Put the dialog in the screen center
    const QRect screen = qApp->desktop()->screenGeometry(i);

    move(screen.center().x() - rect().center().x(), 0);

    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->txtEmail->setInputMethodHints(Qt::ImhEmailCharactersOnly);

    connect(ui->lblIconLogo, SIGNAL(mouseHovered()), this, SLOT(onLogoMouseHovered()));
    connect(ui->lblIconLogo, SIGNAL(mouseLeaved()), this, SLOT(onLogoMouseLeaved()));
    connect(ui->lblIconLogo, SIGNAL(mouseReleased()), this, SLOT(onLogoClicked()));
}

RegisterScreen::~RegisterScreen()
{
    delete ui;
}

void RegisterScreen::onLogoChanged(const QPixmap &image)
{
    ui->lblIconLogo->setPixmap(image);
    ui->lblIconLogo->setScaledContents(true);
}

void RegisterScreen::onLogoMouseHovered()
{
    setCursor(Qt::PointingHandCursor);
}

void RegisterScreen::onLogoMouseLeaved()
{
    setCursor(Qt::ArrowCursor);
}

void RegisterScreen::onLogoClicked()
{
    AvatarScreen *screen = new AvatarScreen();
    connect(screen, SIGNAL(avatarChanged(const QPixmap&)), this, SLOT(onLogoChanged(const QPixmap&)));

    screen->show();
}

void RegisterScreen::on_btnCancel_clicked()
{
    this->close();
}

void RegisterScreen::on_btnSave_clicked()
{
    this->close();
}

void RegisterScreen::on_btnQuit_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, tr("Vitrages Décision"), tr("Do you want to quit application?"),
                                QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}
