#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include <QWidget>

namespace Ui {
class RegisterScreen;
}

namespace VitragesDecision {

class RegisterScreen : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterScreen(QWidget *parent = 0);
    ~RegisterScreen();

public slots:
    void onLogoChanged(const QPixmap& image);
    void onLogoMouseHovered();
    void onLogoMouseLeaved();

    void onLogoClicked();

private slots:
    void on_btnCancel_clicked();

    void on_btnSave_clicked();

    void on_btnQuit_clicked();

private:
    Ui::RegisterScreen *ui;
};

}

#endif // REGISTERSCREEN_H
