#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QMainWindow>

namespace Ui {
class SplashScreen;
}

namespace VitragesDecision {

class SplashScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit SplashScreen(QWidget *parent = 0);
    ~SplashScreen();

private slots:
    void onUpdateProgressBar();

    void on_progressBar_valueChanged(int value);

private:
    Ui::SplashScreen *ui;
};

}

#endif // SPLASHSCREEN_H
