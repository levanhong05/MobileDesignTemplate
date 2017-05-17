#ifndef GLASSSCREEN_H
#define GLASSSCREEN_H

#include <QMainWindow>

namespace Ui {
class GlassScreen;
}

namespace VitragesDecision {

class GlassScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit GlassScreen(QWidget *parent = 0);
    ~GlassScreen();

    static GlassScreen *Instance(QWidget *parent = 0);

private slots:
    void on_btnHome_clicked();

    void on_btnQuit_clicked();

    void on_btnSetting_clicked();

    void on_btnRun_clicked();

protected:
    static GlassScreen *_instance;

private:
    Ui::GlassScreen *ui;
};

}

#endif // GLASSSCREEN_H
