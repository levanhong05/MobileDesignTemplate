#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QMainWindow>

namespace Ui {
class HomeScreen;
}

namespace VitragesDecision {

class HomeScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit HomeScreen(QWidget *parent = 0);
    ~HomeScreen();

    static HomeScreen *Instance(QWidget *parent = 0);

private slots:
    void on_btnSetting_clicked();

    void on_btnAbout_clicked();

    void on_btnDefinition_clicked();

    void on_btnLocation_clicked();

protected:
    static HomeScreen *_instance;

private:
    Ui::HomeScreen *ui;
};

}

#endif // HOMESCREEN_H
