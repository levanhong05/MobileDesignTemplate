#ifndef SETTINGSCREEN_H
#define SETTINGSCREEN_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class SettingScreen;
}

namespace VitragesDecision {

class SettingScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingScreen(QWidget *parent = 0);
    ~SettingScreen();

    void setParent(QWidget *parent);

protected slots:
    void onCoordinateClicked();
    void onAboutClicked();

    void onBackMouseHovered();
    void onBackMouseLeaved();

private slots:
    void on_btnQuit_clicked();

    void on_btnHome_clicked();

    void on_btnBack_clicked();

private:
    Ui::SettingScreen *ui;

    QWidget *_parent;
};

}

#endif // SETTINGSCREEN_H
