#ifndef AVATARSCREEN_H
#define AVATARSCREEN_H

#include <QDialog>

namespace Ui {
class AvatarScreen;
}

namespace VitragesDecision {

class AvatarScreen : public QDialog
{
    Q_OBJECT
public:
    explicit AvatarScreen(QWidget *parent = 0);
    ~AvatarScreen();

private slots:
    void on_btnBrowse_clicked();

    void on_btnCapture_clicked();

    void on_btnRetry_clicked();

    void on_btnOK_clicked();

signals:
    void avatarChanged(const QPixmap& image);

private:
    Ui::AvatarScreen *ui;
};

}

#endif // AVATARSCREEN_H
