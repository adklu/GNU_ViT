#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void openvideo();
    void openfile();
    void startpoint();
    void endpoint();
    void stop();
    void play();
    void reset();
    void slider();
    void slow();
    void cut();
    void dir();
     void conc();
     void startgoto();
     void endgoto();
      void openhelp();
       void openpng();
        void openwav();
         void to24fps();
         void to30fps();
         void to60fps();
         void towav();
          void tofullhd();
          void ffprobe();
          void tomp4aac();
          void replaceaudio();
          void titles();
          void crop();
           void cropbottomleft();
            void croptopright();
             void croptopleft();
             void slowmotion();
             void to4K();
             void crop4Kbottomright();
             void crop4Kbottomleft();
             void crop4Ktopright();
             void crop4Ktopleft();

};

#endif // MAINWINDOW_H
