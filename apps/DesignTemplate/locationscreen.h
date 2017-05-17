#ifndef LOCATIONSCREEN_H
#define LOCATIONSCREEN_H

#include <QMainWindow>

namespace Ui {
class LocationScreen;
}

namespace VitragesDecision {

class LocationScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit LocationScreen(QWidget *parent = 0);
    ~LocationScreen();

    static LocationScreen *Instance(QWidget *parent = 0);

protected slots:
    void onSwitchButtonClicked(bool state);

private slots:
    void on_btnHome_clicked();

    void on_btnQuit_clicked();

    void on_btnSetting_clicked();

protected:
    static LocationScreen *_instance;

private:
    Ui::LocationScreen *ui;
};

}

#endif // LOCATIONSCREEN_H
