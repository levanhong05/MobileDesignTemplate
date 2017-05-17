#include "avatarscreen.h"
#include "ui_avatarscreen.h"

#include <QFile>
#include <QFileDialog>
#include <QDesktopWidget>

using namespace VitragesDecision;

AvatarScreen::AvatarScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvatarScreen)
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

    move(screen.center() - rect().center());

    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->btnBrowse->setVisible(true);
    ui->btnCapture->setVisible(true);

    ui->btnRetry->setVisible(false);
    ui->btnOK->setVisible(false);
}

AvatarScreen::~AvatarScreen()
{
    delete ui;
}

void AvatarScreen::on_btnBrowse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Logo Image"),
                                                    "",
                                                    tr("All Images (*.png *.jpg);;PNG Images (*.png);;JPEG Images (*.jpeg *.jpg)"));

    if (fileName != "") {
        ui->lblPictureSelected->setPixmap(QPixmap::fromImage(QImage(fileName)));
        ui->lblPictureSelected->setScaledContents(true);

        ui->btnBrowse->setVisible(false);
        ui->btnCapture->setVisible(false);

        ui->btnRetry->setVisible(true);
        ui->btnOK->setVisible(true);
    }
}

void AvatarScreen::on_btnCapture_clicked()
{
    ui->btnBrowse->setVisible(false);
    ui->btnCapture->setVisible(false);

    ui->btnRetry->setVisible(true);
    ui->btnOK->setVisible(true);
}

void AvatarScreen::on_btnRetry_clicked()
{
    ui->btnBrowse->setVisible(true);
    ui->btnCapture->setVisible(true);

    ui->btnRetry->setVisible(false);
    ui->btnOK->setVisible(false);
}

void AvatarScreen::on_btnOK_clicked()
{
    const QPixmap* pixmap = ui->lblPictureSelected->pixmap();

    if (pixmap) {
        emit avatarChanged(QPixmap::fromImage(pixmap->toImage()));
    }

    this->close();
}
