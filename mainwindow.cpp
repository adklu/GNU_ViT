//needed:
//sudo apt-get install qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5
//ffmpeg 3.3.6

//todo
//-
//-

#include "mainwindow.h"
#include "ui_mainwindow.h"

QString version= "v0110";
QString license = "GNU_ViT - Video Editor Tool\
        \n\
\n\
Copyright (c) 2021-2024 A.D.Klumpp\
\n\
\n\
This program is free software; you can redistribute it and/or modify \
it under the terms of the GNU General Public License as published by \
the Free Software Foundation; either version 2 of the License, or \
(at your option) any later version.\
\n\
\n\
This program is distributed in the hope that it will be useful, \
but WITHOUT ANY WARRANTY; without even the implied warranty of \
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the \
GNU General Public License for more details.\
\n\
\n\
You should have received a copy of the GNU General Public License \
along with this program; if not, write to the Free Software \
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA";

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
//#include <QThread>
#include <unistd.h>

#include <QMediaPlayer>
#include <QFileInfo>
#include <QDirIterator>
#include <QStringList>
#include <QProcess>

#include <QInputDialog>

#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlayer>

#include <sstream>
#include <iomanip>
//#include <QTimer>
//#include <QMediaMetaData>





QMediaPlayer *player;

qint64 globdur=0;
int i=0;
int j=0;

float iposstart=0;
float iposend=0;

QString vfilePath;
QString wavfilePath;
QString pngfilePath;
QString oppath;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer();




}

void MainWindow::openfile()
{

   QString hpath = QDir::homePath();

   if(oppath=="")
   {

  vfilePath= QFileDialog::getOpenFileName(this, "Select a video file to open...", hpath);

  oppath = QFileInfo(vfilePath).path();

   }

   else
   {
       vfilePath= QFileDialog::getOpenFileName(this, "Select a video file to open...", oppath);
       oppath = QFileInfo(vfilePath).path();

   }

   qDebug() << "vfilePath = " << vfilePath;

   qDebug() << "directoryPath = " << oppath;

   //ui->statusBar->showMessage(filePath);
   ui->plainTextEdit_3->setPlainText(vfilePath);

   openvideo();
}

void MainWindow::openvideo()
{

      QString vvfilePath = ui->plainTextEdit_3->toPlainText();

    QVideoWidget *video = new QVideoWidget();

    video->resize(960, 540);

    //QMediaPlayer *player = new QMediaPlayer();



    connect(player, &QMediaPlayer::durationChanged, this, [&](qint64 dur)
    {
        //qDebug() << "total duration = " << dur;


        float idur = dur;

        //QString spos = QString::number(pos);


        //ui->label_3->setText(QString::number(pos));

       float mindur= (idur/1000)/60;




        ui->label_4->setText(QString::number(mindur));

        globdur=dur;

        // qDebug() << "............... globduration = " << globdur;




    });

    connect(player, &QMediaPlayer::positionChanged, this, [&](qint64 pos)
    {
        //qDebug() << "position connect = " << pos;
        float ipos = pos;
        float iglobdur = globdur;

        //QString spos = QString::number(pos);


        //ui->label_3->setText(QString::number(pos));

       float posmin= (ipos/1000)/60;

        qDebug() << "---------------position min = " << posmin;

       float dialv=(ipos/iglobdur)*100;

       int idialv=dialv;


      qDebug() << "-------------%%%%%%%%%%%%%%%%%%%%5; = " << idialv;


       ui->newslider->blockSignals(true);
    ui->newslider->setValue(idialv);
      ui->newslider->blockSignals(false);



        QString spos = QString::number(posmin);


         ui->label_3->setText(spos);


    });

    player->setVideoOutput(video);
    //player->setMedia(QUrl::fromLocalFile("/home/debian9/BlenderProjects/millie01/00001.MTS"));
     player->setMedia(QUrl::fromLocalFile(vvfilePath));





    //qDebug() << "duration marker" << player->duration();

    //player->position();


    //video->setGeometry(100, 200, 300, 300);
    //video->setParent(ui->widget);

    player->play();
    video->show();
    player->pause();


    video->setAttribute( Qt::WA_DeleteOnClose );





}




void MainWindow::startpoint()
{

    //const char* startvar;


    qint64 pos = player->position();

     //ui->plainTextEdit->setPlainText(QString::number(pos));


    //
    float ipos = pos;

    //QString spos = QString::number(pos);


    //ui->label_3->setText(QString::number(pos));

    float secpos=(ipos/1000);

   float minpos= (ipos/1000)/60;

   //add
    iposstart=secpos;




   QString startlabelmin= QString::number(minpos);


//   float f = 2.45;
//   char *s = (char *) &secpos;
   //char *startvarp = (char *) &secpos;


  //  qDebug() << "float secpos" << secpos;
   // qDebug() << "char startvar" << startvar;






    //

     //ui->label->setText(QString::number(pos));
     ui->label->setText(startlabelmin);

     //qDebug() << "-------------------pos " <<  player->position();

//     ui->plainTextEdit->setPlainText(QString::number(position));

//    connect(player, &QMediaPlayer::positionChanged, this, [&](qint64 pos)
//    {
//        qDebug() << "position connect = " << pos;
//        int ipos = pos;



//        ui->plainTextEdit->setPlainText(QString::number(pos));





//    });




    //QString startp = ui->plainTextEdit->toPlainText();
    //ui->label->setText(startp);

}


void MainWindow::endpoint()
{


      const char* endvar;


    qint64 pos2 = player->position();


    float ipos = pos2;



   float minpos= (ipos/1000)/60;


   float secpos= (ipos/1000);

   iposend=secpos;


   QString startlabelmin= QString::number(minpos);
//    QString startlabelsec= QString::number(secpos);

//   std::string str = startlabelsec.toStdString();

//   endvar = str.c_str();



    // ui->label_2->setText(QString::number(pos2));
      ui->label_2->setText(startlabelmin);

}

void MainWindow::startgoto()
{
QString gotostartpoint = ui->label->text();

double gostfl = gotostartpoint.toFloat();

double gostflms = gostfl*60*1000;

int gostflmsint = gostflms ;

qDebug() << "-----------------gostfl " <<  gostflms;
qDebug() << "----------int-------gostfl " <<  gostflmsint;


if(gotostartpoint!="")
{
    player->setPosition(gostflmsint);
}


}

void MainWindow::endgoto()
{
    QString gotostartpoint = ui->label_2->text();

    double gostfl = gotostartpoint.toFloat();

    double gostflms = gostfl*60*1000;

    int gostflmsint = gostflms ;

    qDebug() << "-----------------gostfl " <<  gostflms;
    qDebug() << "----------int-------gostfl " <<  gostflmsint;


    if(gotostartpoint!="")
    {
        player->setPosition(gostflmsint);
    }




}

//plus
void MainWindow::reset()
{

    //double xval=ui->horizontalSlider_2->value();

     double xval=ui->dial->value();

     //qDebug() << "oooooooooooo dial = " << xval;

     //player->setPosition(0);
    qint64 pos = player->position();
     //player->setPosition(pos-500);
    // player->setPosition(pos+(xval*100));


//     if(xval==0)
//     {
//      player->setPosition(pos+(500));
//     }
//     else
//     {
        player->setPosition(pos+(xval*100));
  //   }

    // qDebug() << "setPosition(pos+xval) = " << xval;

}

//minus
void MainWindow::stop()
{

 //player->setPlaybackRate(2);

   // player->setPlaybackRate(4);



 // qint64 pos = player->position();
//    player->setPosition(pos+5000);
  //    player->setPosition(pos+16);

   // double xval=ui->horizontalSlider_2->value();

    double xval=ui->dial->value();

    qint64 pos = player->position();
     //player->setPosition(pos-500);

    if(xval==0)
    {
     player->setPosition(pos-(500));
    }
    else
    {
       player->setPosition(pos-(xval*100));
    }

  //player->pause();

     //player->play();




}


void MainWindow::play()
{

    //player->setPlaybackRate(1);

        if(i==0)
        {
    player->play();
    i=i+1;
        }

       else
        {
    player->pause();
    i=0;
        }






}

void MainWindow::slider()
{

    //double xval=ui->horizontalSlider->value();
     double xval=ui->newslider->value();

   //qDebug() << "-------------------slider " <<  xval;

   int spos= ((globdur/100)*xval);

   player->setPosition(spos);



}

void MainWindow::slow()
{

    player->pause();


//player->setPlaybackRate(0.5);

    //player->setPlaybackRate(1);

        if(j==0)
        {
   player->setPlaybackRate(0.5);
   ui->slowButton->setText("0.5");

    j=j+1;
        }

       else if(j==1)
        {
   player->setPlaybackRate(2);
   ui->slowButton->setText("2");

    j=j+1;
        }

      else if(j==2)
        {
    player->setPlaybackRate(1);
    ui->slowButton->setText("1");
    j=0;
        }

        qint64 pos = player->position();
         //player->setPosition(pos-500);


         player->setPosition(pos-(1000));




  //qint64 pos = player->position();
   //player->setPosition(pos-500);
  // player->setPosition(pos-500);

    player->play();
}





void MainWindow::dir()
{




   QString savefilePath = QFileDialog::getExistingDirectory(this, tr("Save File"));

//    savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



   qDebug() << "--------------savefileName ----------- " << savefilePath ;

   ui->plainTextEdit->setPlainText(savefilePath);


//     if(savefileName!="")

//     {


//         cut();
//     }


}



void MainWindow::cut()
{

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;
    QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(iposend<iposstart)||(iposend==iposstart)||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path or Start/End Point Error.");
        msgBox.exec();
    }

     else
    {

ui->statusBar->showMessage("Please wait...");
//QString startminu = ui->label->text();

// qDebug() << "---------------QString ---startminu----------- " << startminu;


//float iposstart = startminu.toFloat();

 qDebug() << "--------------float iposstart ---------- " << iposstart ;
 qDebug() << "--------------float  iposend ---------- " <<  iposend ;


//STARTPOINT
      //float secpos= (iposstart*60);
      float secpos= iposstart;
       qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
    //format in seconds.ms (3 digits ms)
       std::stringstream stream;
       stream << std::fixed << std::setprecision(3) << secpos;
       std::string str = stream.str();
   const char* startvar = str.c_str();
    qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


//ENDPOINT
    float secposend= iposend ;
     qDebug() << "-------------float secposend---------- " << secposend ;
  //format in seconds.ms (3 digits ms)
     std::stringstream stream2;
     stream2 << std::fixed << std::setprecision(3) << secposend;
     std::string str2 = stream2.str();
 const char* endvar = str2.c_str();
qDebug() << "------------------endvar-------------- " << endvar;

//    const char* startvar = "60.768";
   //const char* endvar = "120.876";


    //const char* filePathfromqs = filePath.toStdString().c_str();

//original file
    QByteArray array = vvfilePath.toLocal8Bit();
    char* filePathfromqs = array.data();
    qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





 //name of saved file
     QByteArray array2 = savefileName.toLocal8Bit();
     char* savefileNamefromqs = array2.data();
     qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;


      //const char* savefileNamefromqs = savefileName.toStdString().c_str();





    char result[1000];

    strcpy(result,"ffmpeg -y -i '");
    strcat(result,filePathfromqs);
    //strcat(result,"' -c copy -ss ");
    //strcat(result,"' -c:v libx264 -preset fast -crf 17 -tune film -c:a copy -ss ");
    //strcat(result,"' -c:v libx264 -preset veryfast -crf 18 -c:a copy -ss ");
    strcat(result,"' -c:v libx264 -preset veryfast -crf 15 -c:a copy -ss ");
    strcat(result,startvar);
    strcat(result," -to ");
    strcat(result,endvar);
    strcat(result," '");
    strcat(result,savefileNamefromqs);
    strcat(result,"'");




    qDebug() << "-------------------result--------------- " << result;


    //00:01:00 -to 00:02:00
    if(system(result) != 0)
    {
        qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

        ui->statusBar->showMessage("");
        QMessageBox msgBox;
        msgBox.setText("Error: ffmpeg failed.");
        msgBox.exec();

    }
    else
    {
        ui->statusBar->showMessage("");
        QMessageBox msgBox;
        msgBox.setText("File saved.");
        msgBox.exec();

    }


    }

}

void MainWindow::conc()
{


    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;

    //name of saved file
        QByteArray array3 = savefileName.toLocal8Bit();
        char* savefileNamefromqs_c = array3.data();
        qDebug() << "-----conc()----------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs_c << "  ///  "<< array3;

    //



     QString savePathName = ui->plainTextEdit->toPlainText();

     //if empty...


QList<QString>  files;
QList<QString>  filenames;


     QDirIterator it(savePathName, {"*.*"}, QDir::Files);
     while (it.hasNext())
     {
         //qDebug() << "it--------------" << it.next();
         files.append(it.next());

         //
         QFileInfo fileInfo(it.fileName());
         QString filename(fileInfo.fileName());
         qDebug() << "it--- filename  -----------" <<  filename;
         filenames.append(filename);
     }

      qDebug() << "it--LIST------------" << files;
     files.sort();
     filenames.sort();
       qDebug() << "it--LIST----sort--------" << files;
       int dsize = files.size();
        qDebug() << "it--LIST----size-----" << dsize;

        //int to char
        int sizetochar= dsize ;

        std::string s = std::to_string(sizetochar);
        char const *size_c = s.c_str();

//*****
//        if((pname=="")||(fname=="")||(dsize==0)||(QFileInfo(savefileName).exists()))

//       {
//            QMessageBox msgBox;
//            msgBox.setText("Error: File/File Name or Path Error.");
//            msgBox.exec();
//        }
    //---------
        if((pname=="")||(fname==""))

       {
            QMessageBox msgBox;
            msgBox.setText("Error: File name or path name missing.");
            msgBox.exec();
        }

       else if((dsize==0))

       {
            QMessageBox msgBox;
            msgBox.setText("Error: Empty folder.");
            msgBox.exec();
        }

        else if((QFileInfo(savefileName).exists()))

       {
            QMessageBox msgBox;
            msgBox.setText("Error: File name already exists.");
            msgBox.exec();
        }




  //----------

         else
        {




        //--


QString filesasstring = "";

        for (int i = 0; i < files.size(); ++i)
           {

            if((files.at(i))!="")
            {
            qDebug() << i << "   it--LIST----AT----" << files.at(i);
            //filesasstring=filesasstring + "\n" + files.at(i);
            QString s = QString::number(i+1);
             filesasstring=filesasstring + "\n" + s + ": " + files.at(i);

            }

           // filesasstring=filesasstring + "\n" + files.at(i);

        }

        //

        QString filenamesasstring = "";

                for (int i = 0; i < files.size(); ++i)
                   {

                    if((files.at(i))!="")
                    {
                    qDebug() << i << "   it--LIST----AT----" << filenames.at(i);
                    //filesasstring=filesasstring + "\n" + files.at(i);
                    QString s = QString::number(i+1);
                     filenamesasstring=filenamesasstring + " --> " + s + ": " + filenames.at(i);
                     // filenamesasstring=filenamesasstring + "\n" + s + ": " + filenames.at(i);

                    }

                   // filesasstring=filesasstring + "\n" + files.at(i);

                }



        QMessageBox msgBox;
        msgBox.setStyleSheet("QLabel{min-width: 700px;}");
        msgBox.setText("Create sequence?");
        msgBox.setInformativeText(filenamesasstring);
        msgBox.setDetailedText(filesasstring);
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();


        switch (ret)
        {
          case QMessageBox::Save:
                 qDebug() << "   Save was clicked" ;

                 //start "   Save was clicked"


                 ui->statusBar->showMessage("Please wait...");



              //--------------

                  char result[50000];

                  strcpy(result,"ffmpeg -y");



                  for (int i = 0; i < files.size(); ++i)
                     {

                      if((files.at(i))!="")
                      {
                      QString clippath= files.at(i);

                      QByteArray array4 = clippath.toLocal8Bit();
                      char* clipfileNamefromqs_c = array4.data();

                      strcat(result," -i '");
                      strcat(result,clipfileNamefromqs_c);
                      strcat(result,"'");

                        qDebug() << i << "   clipfileNamefromqs_c--" << clipfileNamefromqs_c;

                      }

                  }

                  strcat(result," -filter_complex concat=n=");
                  //strcat(result,"2");
                  strcat(result,size_c);
                  strcat(result,":v=1:a=1 -c:v libx264 -preset veryfast -crf 15  '");
                  //strcat(result,"/home/debian9/000000GNU_ViT_Test/Output_02.mp4");
                  strcat(result,savefileNamefromqs_c);
                  strcat(result,"'");



                  qDebug() << "-------------------result--------------- " << result;


              //if(system("ffmpeg -i '/home/debian9/BlenderProjects/millie01/00001_cutmilliesecVAR22.MTS' -i '/home/debian9/BlenderProjects/millie01/00001_cutmilliesecVAR23.MTS' -filter_complex concat=n=2:v=1:a=1 -c:v libx264 -preset veryfast -crf 15  '/home/debian9/BlenderProjects/millie01/output2222_555.mp4'") != 0)

                  //if(system(0) != 0)
                   if(system(result) != 0)
                  {
                      qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                      ui->statusBar->showMessage("");
                      QMessageBox msgBox;
                      msgBox.setText("Error: ffmpeg failed.");
                      msgBox.exec();
                  }
                  else
                  {
                      ui->statusBar->showMessage("");
                      QMessageBox msgBox;
                      msgBox.setText("File saved.");
                      msgBox.exec();
                  }

                 //end "   Save was clicked"

              break;

          case QMessageBox::Cancel:
              // Cancel was clicked
              break;
          default:
              // should never be reached
              break;
        }

//--------------

}

}


void MainWindow::ffprobe()
{


      QString vvfilePath = ui->plainTextEdit_3->toPlainText();
    QProcess process;

    if(vvfilePath!="")
    {


 QString aCommand = "ffprobe -show_streams -show_format '" + vvfilePath + "'";
  // QString program = "gnome-terminal";
  // QString program = "x-terminal-emulator";
    QString program = "xterm";
   QStringList arguments;

    arguments << "-hold" << "-e" << aCommand ;

   process.start(program, arguments,QIODevice::ReadOnly);
   process.waitForFinished(-1);
}
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error: File Error.");
        msgBox.exec();
    }




}




void MainWindow::openhelp()
{




    QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel{min-width: 500px;}");
    msgBox.setText("GNU_ViT - Video Editor Tool");
    msgBox.setInformativeText(version);
    msgBox.setDetailedText(license);
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();

}

void MainWindow::openwav()
{
    QString hpath = QDir::homePath();

    if(oppath=="")
    {

   wavfilePath= QFileDialog::getOpenFileName(this, "Select a wav file to open...", hpath);

   oppath = QFileInfo(wavfilePath).path();

    }

    else
    {
        wavfilePath= QFileDialog::getOpenFileName(this, "Select a wav file to open...", oppath);
        oppath = QFileInfo(wavfilePath).path();

    }

    qDebug() << "wavfilePath = " << wavfilePath;

    qDebug() << "directoryPath = " << oppath;

    //ui->statusBar->showMessage(filePath);
    ui->plainTextEdit_wav->setPlainText(wavfilePath);

}

void MainWindow::openpng()
{
    QString hpath = QDir::homePath();

    if(oppath=="")
    {

   pngfilePath= QFileDialog::getOpenFileName(this, "Select a png file to open...", hpath);

   oppath = QFileInfo(pngfilePath).path();

    }

    else
    {
        pngfilePath= QFileDialog::getOpenFileName(this, "Select a png file to open...", oppath);
        oppath = QFileInfo(pngfilePath).path();

    }

    qDebug() << "pngfilePath = " << pngfilePath;

    qDebug() << "directoryPath = " << oppath;

    //ui->statusBar->showMessage(filePath);
    ui->plainTextEdit_png->setPlainText(pngfilePath);

}

void MainWindow::to24fps()
{

    QByteArray array;
    char* filePathfromqs;



    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;

    QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -r 24000/1001 -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");


         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}



}

void MainWindow::to30fps()
{

    QByteArray array;
    char* filePathfromqs;

        //qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;

     QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -r 30000/1001 -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");


         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}

}

void MainWindow::to60fps()
{

    QByteArray array;
    char* filePathfromqs;

       // qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;

     QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -r 60000/1001 -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");


         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}

}

//mft to 4k


void MainWindow::con43_4k()
{

    QByteArray array;
    char* filePathfromqs;

       // qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;

     QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

    //ffmpeg -i P1060024.MP4 -vf "scale=3840:2160:force_original_aspect_ratio=decrease,pad=3840:2160:-1:-1:color=black" 4koutputP1060024.MP4

     strcpy(result,"ffmpeg -y -i ");
     strcat(result,filePathfromqs);
      strcat(result," -vf 'scale=3840:2160:force_original_aspect_ratio=decrease,pad=3840:2160:-1:-1:color=black' ");
       strcat(result,savefileNamefromqs);
        //strcat(result,"'");


         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}

}


//mft to 4k END


//mft to FHD

void MainWindow::con43_FHD()
{

    QByteArray array;
    char* filePathfromqs;

       // qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;

     QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

    //ffmpeg -i P1060024.MP4 -vf "scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:-1:color=black" FHDoutputP1060024.MP4

     strcpy(result,"ffmpeg -y -i ");
     strcat(result,filePathfromqs);
      strcat(result," -vf 'scale=1920:1080:force_original_aspect_ratio=decrease,pad=1920:1080:-1:-1:color=black' ");
       strcat(result,savefileNamefromqs);
        //strcat(result,"'");


         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}

}



//mft to FHD END

void MainWindow::towav()
{

    QByteArray array;
    char* filePathfromqs;

        //qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;
     QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -q:a 0 -map a '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");

        //ffmpeg -i 00001.MTS -q:a 0 -map a audioexport01.wav


         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}

}

void MainWindow::tofullhd()
{


    QByteArray array;
    char* filePathfromqs;

        //qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;
     QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -vf scale=1920:1080:flags=lanczos,setsar=1 -c:v libx264 -crf 15 -preset veryfast -c:a copy '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");

       // ffmpeg -y -i MAH00642.MP4 -vf "scale=1920:1080:flags=lanczos,setsar=1" -c:v libx264 -crf 15 -preset veryfast -c:a copy MAH00642_1920crf15.MP4


         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}





}


//to4K


void MainWindow::to4K()
{


    QByteArray array;
    char* filePathfromqs;

        //qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;
     QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -vf scale=3840:2160:flags=lanczos,setsar=1 -c:v libx264 -crf 15 -preset veryfast -c:a copy '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");

       // ffmpeg -y -i MAH00642.MP4 -vf "scale=1920:1080:flags=lanczos,setsar=1" -c:v libx264 -crf 15 -preset veryfast -c:a copy MAH00642_1920crf15.MP4


         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}





}



//end to4K


void MainWindow::tomp4aac()
{



    QByteArray array;
    char* filePathfromqs;

       // qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;
     QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -c:v libx264 -crf 15 -preset veryfast -c:a aac '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");

     //  convert video+audio: -c:v libx264 -crf 15 -preset veryfast -c:a aac
     //just audio (sync issues?):  -c copy -c:a aac




         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}





}

void MainWindow::replaceaudio()
{


    QByteArray array;
    char* filePathfromqs;

        //qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;

     QString vvfilePath = ui->plainTextEdit_3->toPlainText();
     QString wavname = ui->plainTextEdit_wav->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(wavname=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



         //name of input wav
             QByteArray array3 = wavname.toLocal8Bit();
             char* wavfilePathfromqs = array3.data();
             qDebug() << "---------------wavfilePathfromqs---------- " << wavname << "  ---  "  << wavfilePathfromqs << "  ///  "<< array3;

    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -i '");
     strcat(result,wavfilePathfromqs);
      strcat(result,"' -c copy -map 0:v:0 -map 1:a:0 '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");

  //ffmpeg -y -i mkv.mkv -i S06BlackKnightV3.wav -c copy -map 0:v:0 -map 1:a:0 output_wav_sound.mkv




         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}




}

void MainWindow::titles()
{



    QByteArray array;
    char* filePathfromqs;

        //qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;

     QString vvfilePath = ui->plainTextEdit_3->toPlainText();
     QString pngname = ui->plainTextEdit_png->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(pngname=="")||(iposend<iposstart)||(iposend==iposstart)||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path or Start/End Point Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



         //name of input png
             QByteArray array3 = pngname.toLocal8Bit();
             char* pngfilePathfromqs = array3.data();
             qDebug() << "---------------pngfilePathfromqs---------- " << pngname << "  ---  "  << pngfilePathfromqs << "  ///  "<< array3;


             //STARTPOINT
                   //float secpos= (iposstart*60);
                   float secpos= iposstart;
                    qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
                 //format in seconds.ms (3 digits ms)
                    std::stringstream stream;
                    stream << std::fixed << std::setprecision(3) << secpos;
                    std::string str = stream.str();
                const char* startvar = str.c_str();
                 qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


             //ENDPOINT
                 float secposend= iposend ;
                  qDebug() << "-------------float secposend---------- " << secposend ;
               //format in seconds.ms (3 digits ms)
                  std::stringstream stream2;
                  stream2 << std::fixed << std::setprecision(3) << secposend;
                  std::string str2 = stream2.str();
              const char* endvar = str2.c_str();
             qDebug() << "------------------endvar-------------- " << endvar;


    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -i '");
     strcat(result,pngfilePathfromqs);
      strcat(result,"' -filter_complex \"[0:v][1:v] overlay=25:25:enable='between(t,");
      strcat(result,startvar);
      strcat(result,",");
      strcat(result,endvar);
      strcat(result,")'\" -pix_fmt yuv420p -c:a copy '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");



        //QString sf="ffmpeg -y -i mkv.mkv -i title.png -filter_complex \"[0:v][1:v] overlay=25:25:enable='between(t,1.234,3.543)'\" -pix_fmt yuv420p -c:a copy outps33.mkv";



         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}





}



//crop from bottom right
void MainWindow::crop()
{


    bool ok;
       int i = QInputDialog::getInt(this, tr("Crop"),
                                 tr("Percentage:"), 25, 50, 99, 1, &ok);
    if (ok)
    {
        //integerLabel->setText(tr("%1%").arg(i));

         qDebug() << "+++++++++++++++++++++++++CROP   " << i;

//         80%
//
//         x: of 1920: 1536
//         y: of 1080: 864

         double ii=i;


         float x= (1920.0/100.0)*ii;
          double y= (1080.0/100.0)*ii;

           qDebug() << "++++++++   x   +++++++++++++++++CROP   " << x;

            qDebug() << "++++++++   y   +++++++++++++++++CROP   " << y;


//************



            QByteArray array;
            char* filePathfromqs;

                //qDebug() << "--------------filePath---------- " << filePath;

            QString pname = ui->plainTextEdit->toPlainText();
            QString fname = ui->plainTextEdit_2->toPlainText();
            QString savefileName = pname + "/" + fname;

             QString vvfilePath = ui->plainTextEdit_3->toPlainText();



             qDebug() << "-------savefileName------- " << savefileName ;

            if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))


           {
                QMessageBox msgBox;
                msgBox.setText("Error: File Name/Path Error.");
                msgBox.exec();
            }



             else
            {


                 // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



                   ui->statusBar->showMessage("Crop Preview");

            //original file
                array = vvfilePath.toLocal8Bit();
                filePathfromqs = array.data();
                qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





             //name of saved file
                 QByteArray array2 = savefileName.toLocal8Bit();
                 char* savefileNamefromqs = array2.data();
                 qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;





                     //STARTPOINT
                           //float secpos= (iposstart*60);
                           float secpos= x;
                            qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream;
                            stream << std::fixed << std::setprecision(3) << secpos;
                            std::string str = stream.str();
                        const char* startvar = str.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


                     //ENDPOINT
                         float secposend= y ;
                          qDebug() << "-------------float secposend---------- " << secposend ;
                       //format in seconds.ms (3 digits ms)
                          std::stringstream stream2;
                          stream2 << std::fixed << std::setprecision(3) << secposend;
                          std::string str2 = stream2.str();
                      const char* endvar = str2.c_str();
                     qDebug() << "------------------endvar-------------- " << endvar;


            char result[50000];

             strcpy(result,"ffplay -i '");
             strcat(result,filePathfromqs);
              strcat(result,"' -vf \"crop=");
              strcat(result,startvar);
              strcat(result,":");
              strcat(result,endvar);
              strcat(result,":0:0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1\"");



                      qDebug() << "-------crop------------result--------------- " << result;


                      if(system(result) != 0)
                     {
                         qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                         ui->statusBar->showMessage("");
                         QMessageBox msgBox;
                         msgBox.setText("Error: ffmpeg failed.");
                         msgBox.exec();
                     }
                     else
                     {
                         ui->statusBar->showMessage("");
//                         QMessageBox msgBox;
//                         msgBox.setText("???");
//                         msgBox.exec();

                         QMessageBox::StandardButton reply;
                          reply = QMessageBox::question(this, "Crop", "Save?",QMessageBox::Yes|QMessageBox::No);
                          if (reply == QMessageBox::Yes)
                          {
                             ui->statusBar->showMessage("Please wait...");
                         //saving crop

                              char result2[50000];

                               strcpy(result2,"ffmpeg -y -i '");
                               strcat(result2,filePathfromqs);
                                strcat(result2,"' -filter:v \"crop=");
                                strcat(result2,startvar);
                                strcat(result2,":");
                                strcat(result2,endvar);
                                strcat(result2,":0:0,scale=1920:1080:flags=lanczos,setsar=1\" -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
                                strcat(result2,savefileNamefromqs);
                                strcat(result2,"'");


//ffmpeg -y -i mkv.mkv -filter:v "crop=1920:1030:0:50,scale=1920:1080:flags=lanczos,setsar=1" -c:v libx264 -preset veryfast -crf 15 -c:a copy mkv_crop50topHQ2scaled.mkv


                                        qDebug() << "-------crop------------result2--------------- " << result2;


                                        if(system(result2) != 0)
                                       {
                                           qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("Error: ffmpeg failed.");
                                           msgBox.exec();
                                       }
                                       else
                                       {
                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("File saved.");
                                           msgBox.exec();
                                       }




                          //end: saving crop




                          } else
                          {
                              QMessageBox msgBox;
                              msgBox.setText("Crop not saved.");
                              msgBox.exec();
                          }

                     }


    }
//***********



//ffplay -i mkv.mkv -vf "crop=1536:864:0:0,drawtext=text='%{pts\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1"






    }



}



//crop bottom left


void MainWindow::cropbottomleft()
{


    bool ok;
       int i = QInputDialog::getInt(this, tr("Crop"),
                                 tr("Percentage:"), 25, 50, 99, 1, &ok);
    if (ok)
    {
        //integerLabel->setText(tr("%1%").arg(i));

         qDebug() << "+++++++++++++++++++++++++CROP   " << i;

//         80%
//
//         x: of 1920: 1536
//         y: of 1080: 864
//         xdelta = 1920 - 1536

         double ii=i;


         double x= (1920.0/100.0)*ii;
          double y= (1080.0/100.0)*ii;
          double xdelta= 1920.0-x;

           qDebug() << "++++++++   x   +++++++++++++++++CROP   " << x;

            qDebug() << "++++++++   y   +++++++++++++++++CROP   " << y;

             qDebug() << "++++++++   xdelta   +++++++++++++++++CROP   " << xdelta;


//************



            QByteArray array;
            char* filePathfromqs;

                //qDebug() << "--------------filePath---------- " << filePath;

            QString pname = ui->plainTextEdit->toPlainText();
            QString fname = ui->plainTextEdit_2->toPlainText();
            QString savefileName = pname + "/" + fname;

             QString vvfilePath = ui->plainTextEdit_3->toPlainText();



             qDebug() << "-------savefileName------- " << savefileName ;

            if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))


           {
                QMessageBox msgBox;
                msgBox.setText("Error: File Name/Path Error.");
                msgBox.exec();
            }



             else
            {


                 // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



                   ui->statusBar->showMessage("Crop Preview");

            //original file
                array = vvfilePath.toLocal8Bit();
                filePathfromqs = array.data();
                qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





             //name of saved file
                 QByteArray array2 = savefileName.toLocal8Bit();
                 char* savefileNamefromqs = array2.data();
                 qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;





                     //STARTPOINT
                           //float secpos= (iposstart*60);
                           float secpos= x;
                            qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream;
                            stream << std::fixed << std::setprecision(3) << secpos;
                            std::string str = stream.str();
                        const char* startvar = str.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


                     //ENDPOINT
                         float secposend= y ;
                          qDebug() << "-------------float secposend---------- " << secposend ;
                       //format in seconds.ms (3 digits ms)
                          std::stringstream stream2;
                          stream2 << std::fixed << std::setprecision(3) << secposend;
                          std::string str2 = stream2.str();
                      const char* endvar = str2.c_str();
                     qDebug() << "------------------endvar-------------- " << endvar;


                     //xdelta
                           //float secpos= (iposstart*60);
                           float secpos2= xdelta;
                            qDebug() << "-------------float secpos2= xdelta; ---------- " << secpos2 ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream3;
                            stream3 << std::fixed << std::setprecision(3) << secpos2;
                            std::string str3 = stream3.str();
                        const char* startvar2 = str3.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar2;


            char result[50000];

             strcpy(result,"ffplay -i '");
             strcat(result,filePathfromqs);
              strcat(result,"' -vf \"crop=");
              strcat(result,startvar);
              strcat(result,":");
              strcat(result,endvar);
               strcat(result,":");
                strcat(result,startvar2);
             // strcat(result,":0:0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1\"");
            strcat(result,":0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1\"");


                      qDebug() << "-------crop------------result--------------- " << result;


                      if(system(result) != 0)
                     {
                         qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                         ui->statusBar->showMessage("");
                         QMessageBox msgBox;
                         msgBox.setText("Error: ffmpeg failed.");
                         msgBox.exec();
                     }
                     else
                     {
                         ui->statusBar->showMessage("");
//                         QMessageBox msgBox;
//                         msgBox.setText("???");
//                         msgBox.exec();

                         QMessageBox::StandardButton reply;
                          reply = QMessageBox::question(this, "Crop", "Save?",QMessageBox::Yes|QMessageBox::No);
                          if (reply == QMessageBox::Yes)
                          {
                                ui->statusBar->showMessage("Please wait...");
                         //saving crop

                              char result2[50000];

                               strcpy(result2,"ffmpeg -y -i '");
                               strcat(result2,filePathfromqs);
                                strcat(result2,"' -filter:v \"crop=");
                                strcat(result2,startvar);
                                strcat(result2,":");
                                strcat(result2,endvar);
                                strcat(result2,":");
                                 strcat(result2,startvar2);
                                strcat(result2,":0,scale=1920:1080:flags=lanczos,setsar=1\" -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
                                strcat(result2,savefileNamefromqs);
                                strcat(result2,"'");


//ffmpeg -y -i mkv.mkv -filter:v "crop=1920:1030:0:50,scale=1920:1080:flags=lanczos,setsar=1" -c:v libx264 -preset veryfast -crf 15 -c:a copy mkv_crop50topHQ2scaled.mkv


                                        qDebug() << "-------crop------------result2--------------- " << result2;


                                        if(system(result2) != 0)
                                       {
                                           qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("Error: ffmpeg failed.");
                                           msgBox.exec();
                                       }
                                       else
                                       {
                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("File saved.");
                                           msgBox.exec();
                                       }




                          //end: saving crop




                          } else
                          {
                              QMessageBox msgBox;
                              msgBox.setText("Crop not saved.");
                              msgBox.exec();
                          }

                     }


    }
//***********



//ffplay -i mkv.mkv -vf "crop=1536:864:0:0,drawtext=text='%{pts\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1"






    }



}


//END crop bottom left
//-----------------------


//crop top right

void MainWindow::croptopright()
{


    bool ok;
       int i = QInputDialog::getInt(this, tr("Crop"),
                                 tr("Percentage:"), 25, 50, 99, 1, &ok);
    if (ok)
    {
        //integerLabel->setText(tr("%1%").arg(i));

         qDebug() << "+++++++++++++++++++++++++CROP   " << i;

//         80%
//
//         x: of 1920: 1536
//         y: of 1080: 864
//         xdelta = 1920 - 1536

         double ii=i;


         double x= (1920.0/100.0)*ii;
          double y= (1080.0/100.0)*ii;
          double ydelta= 1080.0-y;

           qDebug() << "++++++++   x   +++++++++++++++++CROP   " << x;

            qDebug() << "++++++++   y   +++++++++++++++++CROP   " << y;

             qDebug() << "++++++++   ydelta   +++++++++++++++++CROP   " << ydelta;


//************



            QByteArray array;
            char* filePathfromqs;

                //qDebug() << "--------------filePath---------- " << filePath;

            QString pname = ui->plainTextEdit->toPlainText();
            QString fname = ui->plainTextEdit_2->toPlainText();
            QString savefileName = pname + "/" + fname;

             QString vvfilePath = ui->plainTextEdit_3->toPlainText();



             qDebug() << "-------savefileName------- " << savefileName ;

            if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))


           {
                QMessageBox msgBox;
                msgBox.setText("Error: File Name/Path Error.");
                msgBox.exec();
            }



             else
            {


                 // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



                   ui->statusBar->showMessage("Crop Preview");

            //original file
                array = vvfilePath.toLocal8Bit();
                filePathfromqs = array.data();
                qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





             //name of saved file
                 QByteArray array2 = savefileName.toLocal8Bit();
                 char* savefileNamefromqs = array2.data();
                 qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;





                     //STARTPOINT
                           //float secpos= (iposstart*60);
                           float secpos= x;
                            qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream;
                            stream << std::fixed << std::setprecision(3) << secpos;
                            std::string str = stream.str();
                        const char* startvar = str.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


                     //ENDPOINT
                         float secposend= y ;
                          qDebug() << "-------------float secposend---------- " << secposend ;
                       //format in seconds.ms (3 digits ms)
                          std::stringstream stream2;
                          stream2 << std::fixed << std::setprecision(3) << secposend;
                          std::string str2 = stream2.str();
                      const char* endvar = str2.c_str();
                     qDebug() << "------------------endvar-------------- " << endvar;


                     //ydelta
                           //float secpos= (iposstart*60);
                           float secpos2= ydelta;
                            qDebug() << "-------------float secpos2= xdelta; ---------- " << secpos2 ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream3;
                            stream3 << std::fixed << std::setprecision(3) << secpos2;
                            std::string str3 = stream3.str();
                        const char* startvar2 = str3.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar2;


            char result[50000];

             strcpy(result,"ffplay -i '");
             strcat(result,filePathfromqs);
              strcat(result,"' -vf \"crop=");
              strcat(result,startvar);
              strcat(result,":");
              strcat(result,endvar);
               strcat(result,":0:");
                strcat(result,startvar2);
             // strcat(result,":0:0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1\"");
            strcat(result,",drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1\"");


                      qDebug() << "-------crop------------result--------------- " << result;


                      if(system(result) != 0)
                     {
                         qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                         ui->statusBar->showMessage("");
                         QMessageBox msgBox;
                         msgBox.setText("Error: ffmpeg failed.");
                         msgBox.exec();
                     }
                     else
                     {
                         ui->statusBar->showMessage("");
//                         QMessageBox msgBox;
//                         msgBox.setText("???");
//                         msgBox.exec();

                         QMessageBox::StandardButton reply;
                          reply = QMessageBox::question(this, "Crop", "Save?",QMessageBox::Yes|QMessageBox::No);
                          if (reply == QMessageBox::Yes)
                          {
                                ui->statusBar->showMessage("Please wait...");
                         //saving crop

                              char result2[50000];

                               strcpy(result2,"ffmpeg -y -i '");
                               strcat(result2,filePathfromqs);
                                strcat(result2,"' -filter:v \"crop=");
                                strcat(result2,startvar);
                                strcat(result2,":");
                                strcat(result2,endvar);
                                strcat(result2,":0:");
                                 strcat(result2,startvar2);
                                strcat(result2,",scale=1920:1080:flags=lanczos,setsar=1\" -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
                                strcat(result2,savefileNamefromqs);
                                strcat(result2,"'");


//ffmpeg -y -i mkv.mkv -filter:v "crop=1920:1030:0:50,scale=1920:1080:flags=lanczos,setsar=1" -c:v libx264 -preset veryfast -crf 15 -c:a copy mkv_crop50topHQ2scaled.mkv


                                        qDebug() << "-------crop------------result2--------------- " << result2;


                                        if(system(result2) != 0)
                                       {
                                           qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("Error: ffmpeg failed.");
                                           msgBox.exec();
                                       }
                                       else
                                       {
                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("File saved.");
                                           msgBox.exec();
                                       }




                          //end: saving crop




                          } else
                          {
                              QMessageBox msgBox;
                              msgBox.setText("Crop not saved.");
                              msgBox.exec();
                          }

                     }


    }
//***********



//ffplay -i mkv.mkv -vf "crop=1536:864:0:0,drawtext=text='%{pts\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1"






    }



}


//END top right
//-----------------------



//crop top left

void MainWindow::croptopleft()
{



    bool ok;
       int i = QInputDialog::getInt(this, tr("Crop"),
                                 tr("Percentage:"), 25, 50, 99, 1, &ok);
    if (ok)
    {
        //integerLabel->setText(tr("%1%").arg(i));

         qDebug() << "+++++++++++++++++++++++++CROP   " << i;

//         80%
//
//         x: of 1920: 1536
//         y: of 1080: 864
//         xdelta = 1920 - 1536

         double ii=i;


         double x= (1920.0/100.0)*ii;
          double y= (1080.0/100.0)*ii;
          double xdelta= 1920.0-x;
          double ydelta= 1080.0-y;

           qDebug() << "++++++++   x   +++++++++++++++++CROP   " << x;

            qDebug() << "++++++++   y   +++++++++++++++++CROP   " << y;

              qDebug() << "++++++++   xdelta   +++++++++++++++++CROP   " << xdelta;
             qDebug() << "++++++++   ydelta   +++++++++++++++++CROP   " << ydelta;


//************



            QByteArray array;
            char* filePathfromqs;

                //qDebug() << "--------------filePath---------- " << filePath;

            QString pname = ui->plainTextEdit->toPlainText();
            QString fname = ui->plainTextEdit_2->toPlainText();
            QString savefileName = pname + "/" + fname;

             QString vvfilePath = ui->plainTextEdit_3->toPlainText();



             qDebug() << "-------savefileName------- " << savefileName ;

            if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))


           {
                QMessageBox msgBox;
                msgBox.setText("Error: File Name/Path Error.");
                msgBox.exec();
            }



             else
            {


                 // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



                   ui->statusBar->showMessage("Crop Preview");

            //original file
                array = vvfilePath.toLocal8Bit();
                filePathfromqs = array.data();
                qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





             //name of saved file
                 QByteArray array2 = savefileName.toLocal8Bit();
                 char* savefileNamefromqs = array2.data();
                 qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;





                     //STARTPOINT
                           //float secpos= (iposstart*60);
                           float secpos= x;
                            qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream;
                            stream << std::fixed << std::setprecision(3) << secpos;
                            std::string str = stream.str();
                        const char* startvar = str.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


                     //ENDPOINT
                         float secposend= y ;
                          qDebug() << "-------------float secposend---------- " << secposend ;
                       //format in seconds.ms (3 digits ms)
                          std::stringstream stream2;
                          stream2 << std::fixed << std::setprecision(3) << secposend;
                          std::string str2 = stream2.str();
                      const char* endvar = str2.c_str();
                     qDebug() << "------------------endvar-------------- " << endvar;


                     //xdelta
                           //float secpos= (iposstart*60);
                           float secpos2= xdelta;
                            qDebug() << "-------------float secpos2= xdelta; ---------- " << secpos2 ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream3;
                            stream3 << std::fixed << std::setprecision(3) << secpos2;
                            std::string str3 = stream3.str();
                        const char* startvar2 = str3.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar2;

                     //ydelta
                           //float secpos= (iposstart*60);
                           float secpos3= ydelta;
                            qDebug() << "-------------float secpos2= xdelta; ---------- " << secpos3 ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream4;
                            stream4 << std::fixed << std::setprecision(3) << secpos3;
                            std::string str4 = stream4.str();
                        const char* startvar3 = str4.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar3;


            char result[50000];

             strcpy(result,"ffplay -i '");
             strcat(result,filePathfromqs);
              strcat(result,"' -vf \"crop=");
              strcat(result,startvar);
              strcat(result,":");
              strcat(result,endvar);
               strcat(result,":");
                strcat(result,startvar2);
                strcat(result,":");
                 strcat(result,startvar3);
             // strcat(result,":0:0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1\"");
            strcat(result,",drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1\"");


                      qDebug() << "-------crop------------result--------------- " << result;


                      if(system(result) != 0)
                     {
                         qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                         ui->statusBar->showMessage("");
                         QMessageBox msgBox;
                         msgBox.setText("Error: ffmpeg failed.");
                         msgBox.exec();
                     }
                     else
                     {
                         ui->statusBar->showMessage("");
//                         QMessageBox msgBox;
//                         msgBox.setText("???");
//                         msgBox.exec();

                         QMessageBox::StandardButton reply;
                          reply = QMessageBox::question(this, "Crop", "Save?",QMessageBox::Yes|QMessageBox::No);
                          if (reply == QMessageBox::Yes)
                          {
                                ui->statusBar->showMessage("Please wait...");
                         //saving crop

                              char result2[50000];

                               strcpy(result2,"ffmpeg -y -i '");
                               strcat(result2,filePathfromqs);
                                strcat(result2,"' -filter:v \"crop=");
                                strcat(result2,startvar);
                                strcat(result2,":");
                                strcat(result2,endvar);
                                strcat(result2,":");
                                 strcat(result2,startvar2);
                                 strcat(result2,":");
                                  strcat(result2,startvar3);
                                strcat(result2,",scale=1920:1080:flags=lanczos,setsar=1\" -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
                                strcat(result2,savefileNamefromqs);
                                strcat(result2,"'");


//ffmpeg -y -i mkv.mkv -filter:v "crop=1920:1030:0:50,scale=1920:1080:flags=lanczos,setsar=1" -c:v libx264 -preset veryfast -crf 15 -c:a copy mkv_crop50topHQ2scaled.mkv


                                        qDebug() << "-------crop------------result2--------------- " << result2;


                                        if(system(result2) != 0)
                                       {
                                           qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("Error: ffmpeg failed.");
                                           msgBox.exec();
                                       }
                                       else
                                       {
                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("File saved.");
                                           msgBox.exec();
                                       }




                          //end: saving crop




                          } else
                          {
                              QMessageBox msgBox;
                              msgBox.setText("Crop not saved.");
                              msgBox.exec();
                          }

                     }


    }
//***********



//ffplay -i mkv.mkv -vf "crop=1536:864:0:0,drawtext=text='%{pts\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=1920:1080:flags=lanczos,setsar=1"






    }



}


//END top left
//-----------------------



//slowmotion


void MainWindow::slowmotion()
{

    QByteArray array;
    char* filePathfromqs;

       // qDebug() << "--------------filePath---------- " << filePath;

    QString pname = ui->plainTextEdit->toPlainText();
    QString fname = ui->plainTextEdit_2->toPlainText();
    QString savefileName = pname + "/" + fname;

     QString vvfilePath = ui->plainTextEdit_3->toPlainText();


     qDebug() << "-------savefileName------- " << savefileName ;

    if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))

   {
        QMessageBox msgBox;
        msgBox.setText("Error: File Name/Path Error.");
        msgBox.exec();
    }



     else
    {


         // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



           ui->statusBar->showMessage("Please wait...");

    //original file
        array = vvfilePath.toLocal8Bit();
        filePathfromqs = array.data();
        qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





     //name of saved file
         QByteArray array2 = savefileName.toLocal8Bit();
         char* savefileNamefromqs = array2.data();
         qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;



    char result[50000];

     strcpy(result,"ffmpeg -y -i '");
     strcat(result,filePathfromqs);
      strcat(result,"' -filter_complex \"[0:v]setpts=2*PTS[v];[0:a]atempo=0.5[a]\" -map \"[v]\" -map \"[a]\" -r 30000/1001 -crf 15 '");
       strcat(result,savefileNamefromqs);
        strcat(result,"'");



//ffmpeg -y -i mkv.mkv -filter_complex "[0:v]setpts=2*PTS[v];[0:a]atempo=0.5[a]" -map "[v]" -map "[a]" -r 30000/1001 -crf 15 slowsoundoutput.mkv

         qDebug() << "-------------------result--------------- " << result;



        //if(system(0) != 0)
         if(system(result) != 0)
        {
            qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("Error: ffmpeg failed.");
            msgBox.exec();
        }
        else
        {
            ui->statusBar->showMessage("");
            QMessageBox msgBox;
            msgBox.setText("File saved.");
            msgBox.exec();
        }

}

}


//crop 4k



//4K crop from bottom right
void MainWindow::crop4Kbottomright()
{


    bool ok;
       int i = QInputDialog::getInt(this, tr("Crop"),
                                 tr("Percentage:"), 25, 50, 99, 1, &ok);
    if (ok)
    {
        //integerLabel->setText(tr("%1%").arg(i));

         qDebug() << "+++++++++++++++++++++++++CROP   " << i;

//         80%
//
//         x: of 3840: 1536
//         y: of 2160: 864

         double ii=i;


         float x= (3840.0/100.0)*ii;
          double y= (2160.0/100.0)*ii;

           qDebug() << "++++++++   x   +++++++++++++++++CROP   " << x;

            qDebug() << "++++++++   y   +++++++++++++++++CROP   " << y;


//************



            QByteArray array;
            char* filePathfromqs;

                //qDebug() << "--------------filePath---------- " << filePath;

            QString pname = ui->plainTextEdit->toPlainText();
            QString fname = ui->plainTextEdit_2->toPlainText();
            QString savefileName = pname + "/" + fname;

             QString vvfilePath = ui->plainTextEdit_3->toPlainText();



             qDebug() << "-------savefileName------- " << savefileName ;

            if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))


           {
                QMessageBox msgBox;
                msgBox.setText("Error: File Name/Path Error.");
                msgBox.exec();
            }



             else
            {


                 // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



                   ui->statusBar->showMessage("Crop Preview");

            //original file
                array = vvfilePath.toLocal8Bit();
                filePathfromqs = array.data();
                qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





             //name of saved file
                 QByteArray array2 = savefileName.toLocal8Bit();
                 char* savefileNamefromqs = array2.data();
                 qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;





                     //STARTPOINT
                           //float secpos= (iposstart*60);
                           float secpos= x;
                            qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream;
                            stream << std::fixed << std::setprecision(3) << secpos;
                            std::string str = stream.str();
                        const char* startvar = str.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


                     //ENDPOINT
                         float secposend= y ;
                          qDebug() << "-------------float secposend---------- " << secposend ;
                       //format in seconds.ms (3 digits ms)
                          std::stringstream stream2;
                          stream2 << std::fixed << std::setprecision(3) << secposend;
                          std::string str2 = stream2.str();
                      const char* endvar = str2.c_str();
                     qDebug() << "------------------endvar-------------- " << endvar;


            char result[50000];

             strcpy(result,"ffplay -i '");
             strcat(result,filePathfromqs);
              strcat(result,"' -vf \"crop=");
              strcat(result,startvar);
              strcat(result,":");
              strcat(result,endvar);
              strcat(result,":0:0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1\"");



                      qDebug() << "-------crop------------result--------------- " << result;


                      if(system(result) != 0)
                     {
                         qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                         ui->statusBar->showMessage("");
                         QMessageBox msgBox;
                         msgBox.setText("Error: ffmpeg failed.");
                         msgBox.exec();
                     }
                     else
                     {
                         ui->statusBar->showMessage("");
//                         QMessageBox msgBox;
//                         msgBox.setText("???");
//                         msgBox.exec();

                         QMessageBox::StandardButton reply;
                          reply = QMessageBox::question(this, "Crop", "Save?",QMessageBox::Yes|QMessageBox::No);
                          if (reply == QMessageBox::Yes)
                          {
                             ui->statusBar->showMessage("Please wait...");
                         //saving crop

                              char result2[50000];

                               strcpy(result2,"ffmpeg -y -i '");
                               strcat(result2,filePathfromqs);
                                strcat(result2,"' -filter:v \"crop=");
                                strcat(result2,startvar);
                                strcat(result2,":");
                                strcat(result2,endvar);
                                strcat(result2,":0:0,scale=3840:2160:flags=lanczos,setsar=1\" -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
                                strcat(result2,savefileNamefromqs);
                                strcat(result2,"'");


//ffmpeg -y -i mkv.mkv -filter:v "crop=3840:1030:0:50,scale=3840:2160:flags=lanczos,setsar=1" -c:v libx264 -preset veryfast -crf 15 -c:a copy mkv_crop50topHQ2scaled.mkv


                                        qDebug() << "-------crop------------result2--------------- " << result2;


                                        if(system(result2) != 0)
                                       {
                                           qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("Error: ffmpeg failed.");
                                           msgBox.exec();
                                       }
                                       else
                                       {
                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("File saved.");
                                           msgBox.exec();
                                       }




                          //end: saving crop




                          } else
                          {
                              QMessageBox msgBox;
                              msgBox.setText("Crop not saved.");
                              msgBox.exec();
                          }

                     }


    }
//***********



//ffplay -i mkv.mkv -vf "crop=1536:864:0:0,drawtext=text='%{pts\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1"






    }



}



//4K crop bottom left


void MainWindow::crop4Kbottomleft()
{


    bool ok;
       int i = QInputDialog::getInt(this, tr("Crop"),
                                 tr("Percentage:"), 25, 50, 99, 1, &ok);
    if (ok)
    {
        //integerLabel->setText(tr("%1%").arg(i));

         qDebug() << "+++++++++++++++++++++++++CROP   " << i;

//         80%
//
//         x: of 3840: 1536
//         y: of 2160: 864
//         xdelta = 3840 - 1536

         double ii=i;


         double x= (3840.0/100.0)*ii;
          double y= (2160.0/100.0)*ii;
          double xdelta= 3840.0-x;

           qDebug() << "++++++++   x   +++++++++++++++++CROP   " << x;

            qDebug() << "++++++++   y   +++++++++++++++++CROP   " << y;

             qDebug() << "++++++++   xdelta   +++++++++++++++++CROP   " << xdelta;


//************



            QByteArray array;
            char* filePathfromqs;

                //qDebug() << "--------------filePath---------- " << filePath;

            QString pname = ui->plainTextEdit->toPlainText();
            QString fname = ui->plainTextEdit_2->toPlainText();
            QString savefileName = pname + "/" + fname;

             QString vvfilePath = ui->plainTextEdit_3->toPlainText();



             qDebug() << "-------savefileName------- " << savefileName ;

            if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))


           {
                QMessageBox msgBox;
                msgBox.setText("Error: File Name/Path Error.");
                msgBox.exec();
            }



             else
            {


                 // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



                   ui->statusBar->showMessage("Crop Preview");

            //original file
                array = vvfilePath.toLocal8Bit();
                filePathfromqs = array.data();
                qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





             //name of saved file
                 QByteArray array2 = savefileName.toLocal8Bit();
                 char* savefileNamefromqs = array2.data();
                 qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;





                     //STARTPOINT
                           //float secpos= (iposstart*60);
                           float secpos= x;
                            qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream;
                            stream << std::fixed << std::setprecision(3) << secpos;
                            std::string str = stream.str();
                        const char* startvar = str.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


                     //ENDPOINT
                         float secposend= y ;
                          qDebug() << "-------------float secposend---------- " << secposend ;
                       //format in seconds.ms (3 digits ms)
                          std::stringstream stream2;
                          stream2 << std::fixed << std::setprecision(3) << secposend;
                          std::string str2 = stream2.str();
                      const char* endvar = str2.c_str();
                     qDebug() << "------------------endvar-------------- " << endvar;


                     //xdelta
                           //float secpos= (iposstart*60);
                           float secpos2= xdelta;
                            qDebug() << "-------------float secpos2= xdelta; ---------- " << secpos2 ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream3;
                            stream3 << std::fixed << std::setprecision(3) << secpos2;
                            std::string str3 = stream3.str();
                        const char* startvar2 = str3.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar2;


            char result[50000];

             strcpy(result,"ffplay -i '");
             strcat(result,filePathfromqs);
              strcat(result,"' -vf \"crop=");
              strcat(result,startvar);
              strcat(result,":");
              strcat(result,endvar);
               strcat(result,":");
                strcat(result,startvar2);
             // strcat(result,":0:0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1\"");
            strcat(result,":0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1\"");


                      qDebug() << "-------crop------------result--------------- " << result;


                      if(system(result) != 0)
                     {
                         qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                         ui->statusBar->showMessage("");
                         QMessageBox msgBox;
                         msgBox.setText("Error: ffmpeg failed.");
                         msgBox.exec();
                     }
                     else
                     {
                         ui->statusBar->showMessage("");
//                         QMessageBox msgBox;
//                         msgBox.setText("???");
//                         msgBox.exec();

                         QMessageBox::StandardButton reply;
                          reply = QMessageBox::question(this, "Crop", "Save?",QMessageBox::Yes|QMessageBox::No);
                          if (reply == QMessageBox::Yes)
                          {
                                ui->statusBar->showMessage("Please wait...");
                         //saving crop

                              char result2[50000];

                               strcpy(result2,"ffmpeg -y -i '");
                               strcat(result2,filePathfromqs);
                                strcat(result2,"' -filter:v \"crop=");
                                strcat(result2,startvar);
                                strcat(result2,":");
                                strcat(result2,endvar);
                                strcat(result2,":");
                                 strcat(result2,startvar2);
                                strcat(result2,":0,scale=3840:2160:flags=lanczos,setsar=1\" -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
                                strcat(result2,savefileNamefromqs);
                                strcat(result2,"'");


//ffmpeg -y -i mkv.mkv -filter:v "crop=3840:1030:0:50,scale=3840:2160:flags=lanczos,setsar=1" -c:v libx264 -preset veryfast -crf 15 -c:a copy mkv_crop50topHQ2scaled.mkv


                                        qDebug() << "-------crop------------result2--------------- " << result2;


                                        if(system(result2) != 0)
                                       {
                                           qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("Error: ffmpeg failed.");
                                           msgBox.exec();
                                       }
                                       else
                                       {
                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("File saved.");
                                           msgBox.exec();
                                       }




                          //end: saving crop




                          } else
                          {
                              QMessageBox msgBox;
                              msgBox.setText("Crop not saved.");
                              msgBox.exec();
                          }

                     }


    }
//***********



//ffplay -i mkv.mkv -vf "crop=1536:864:0:0,drawtext=text='%{pts\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1"






    }



}


//END 4K crop bottom left
//-----------------------


//4K crop top right

void MainWindow::crop4Ktopright()
{


    bool ok;
       int i = QInputDialog::getInt(this, tr("Crop"),
                                 tr("Percentage:"), 25, 50, 99, 1, &ok);
    if (ok)
    {
        //integerLabel->setText(tr("%1%").arg(i));

         qDebug() << "+++++++++++++++++++++++++CROP   " << i;

//         80%
//
//         x: of 3840: 1536
//         y: of 2160: 864
//         xdelta = 3840 - 1536

         double ii=i;


         double x= (3840.0/100.0)*ii;
          double y= (2160.0/100.0)*ii;
          double ydelta= 2160.0-y;

           qDebug() << "++++++++   x   +++++++++++++++++CROP   " << x;

            qDebug() << "++++++++   y   +++++++++++++++++CROP   " << y;

             qDebug() << "++++++++   ydelta   +++++++++++++++++CROP   " << ydelta;


//************



            QByteArray array;
            char* filePathfromqs;

                //qDebug() << "--------------filePath---------- " << filePath;

            QString pname = ui->plainTextEdit->toPlainText();
            QString fname = ui->plainTextEdit_2->toPlainText();
            QString savefileName = pname + "/" + fname;

             QString vvfilePath = ui->plainTextEdit_3->toPlainText();



             qDebug() << "-------savefileName------- " << savefileName ;

            if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))


           {
                QMessageBox msgBox;
                msgBox.setText("Error: File Name/Path Error.");
                msgBox.exec();
            }



             else
            {


                 // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



                   ui->statusBar->showMessage("Crop Preview");

            //original file
                array = vvfilePath.toLocal8Bit();
                filePathfromqs = array.data();
                qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





             //name of saved file
                 QByteArray array2 = savefileName.toLocal8Bit();
                 char* savefileNamefromqs = array2.data();
                 qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;





                     //STARTPOINT
                           //float secpos= (iposstart*60);
                           float secpos= x;
                            qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream;
                            stream << std::fixed << std::setprecision(3) << secpos;
                            std::string str = stream.str();
                        const char* startvar = str.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


                     //ENDPOINT
                         float secposend= y ;
                          qDebug() << "-------------float secposend---------- " << secposend ;
                       //format in seconds.ms (3 digits ms)
                          std::stringstream stream2;
                          stream2 << std::fixed << std::setprecision(3) << secposend;
                          std::string str2 = stream2.str();
                      const char* endvar = str2.c_str();
                     qDebug() << "------------------endvar-------------- " << endvar;


                     //ydelta
                           //float secpos= (iposstart*60);
                           float secpos2= ydelta;
                            qDebug() << "-------------float secpos2= xdelta; ---------- " << secpos2 ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream3;
                            stream3 << std::fixed << std::setprecision(3) << secpos2;
                            std::string str3 = stream3.str();
                        const char* startvar2 = str3.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar2;


            char result[50000];

             strcpy(result,"ffplay -i '");
             strcat(result,filePathfromqs);
              strcat(result,"' -vf \"crop=");
              strcat(result,startvar);
              strcat(result,":");
              strcat(result,endvar);
               strcat(result,":0:");
                strcat(result,startvar2);
             // strcat(result,":0:0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1\"");
            strcat(result,",drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1\"");


                      qDebug() << "-------crop------------result--------------- " << result;


                      if(system(result) != 0)
                     {
                         qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                         ui->statusBar->showMessage("");
                         QMessageBox msgBox;
                         msgBox.setText("Error: ffmpeg failed.");
                         msgBox.exec();
                     }
                     else
                     {
                         ui->statusBar->showMessage("");
//                         QMessageBox msgBox;
//                         msgBox.setText("???");
//                         msgBox.exec();

                         QMessageBox::StandardButton reply;
                          reply = QMessageBox::question(this, "Crop", "Save?",QMessageBox::Yes|QMessageBox::No);
                          if (reply == QMessageBox::Yes)
                          {
                                ui->statusBar->showMessage("Please wait...");
                         //saving crop

                              char result2[50000];

                               strcpy(result2,"ffmpeg -y -i '");
                               strcat(result2,filePathfromqs);
                                strcat(result2,"' -filter:v \"crop=");
                                strcat(result2,startvar);
                                strcat(result2,":");
                                strcat(result2,endvar);
                                strcat(result2,":0:");
                                 strcat(result2,startvar2);
                                strcat(result2,",scale=3840:2160:flags=lanczos,setsar=1\" -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
                                strcat(result2,savefileNamefromqs);
                                strcat(result2,"'");


//ffmpeg -y -i mkv.mkv -filter:v "crop=3840:1030:0:50,scale=3840:2160:flags=lanczos,setsar=1" -c:v libx264 -preset veryfast -crf 15 -c:a copy mkv_crop50topHQ2scaled.mkv


                                        qDebug() << "-------crop------------result2--------------- " << result2;


                                        if(system(result2) != 0)
                                       {
                                           qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("Error: ffmpeg failed.");
                                           msgBox.exec();
                                       }
                                       else
                                       {
                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("File saved.");
                                           msgBox.exec();
                                       }




                          //end: saving crop




                          } else
                          {
                              QMessageBox msgBox;
                              msgBox.setText("Crop not saved.");
                              msgBox.exec();
                          }

                     }


    }
//***********



//ffplay -i mkv.mkv -vf "crop=1536:864:0:0,drawtext=text='%{pts\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1"






    }



}


//4K END top right
//-----------------------



//4K crop top left

void MainWindow::crop4Ktopleft()
{



    bool ok;
       int i = QInputDialog::getInt(this, tr("Crop"),
                                 tr("Percentage:"), 25, 50, 99, 1, &ok);
    if (ok)
    {
        //integerLabel->setText(tr("%1%").arg(i));

         qDebug() << "+++++++++++++++++++++++++CROP   " << i;

//         80%
//
//         x: of 3840: 1536
//         y: of 2160: 864
//         xdelta = 3840 - 1536

         double ii=i;


         double x= (3840.0/100.0)*ii;
          double y= (2160.0/100.0)*ii;
          double xdelta= 3840.0-x;
          double ydelta= 2160.0-y;

           qDebug() << "++++++++   x   +++++++++++++++++CROP   " << x;

            qDebug() << "++++++++   y   +++++++++++++++++CROP   " << y;

              qDebug() << "++++++++   xdelta   +++++++++++++++++CROP   " << xdelta;
             qDebug() << "++++++++   ydelta   +++++++++++++++++CROP   " << ydelta;


//************



            QByteArray array;
            char* filePathfromqs;

                //qDebug() << "--------------filePath---------- " << filePath;

            QString pname = ui->plainTextEdit->toPlainText();
            QString fname = ui->plainTextEdit_2->toPlainText();
            QString savefileName = pname + "/" + fname;

             QString vvfilePath = ui->plainTextEdit_3->toPlainText();



             qDebug() << "-------savefileName------- " << savefileName ;

            if((pname=="")||(fname=="")||(vvfilePath=="")||(QFileInfo(savefileName).exists()))


           {
                QMessageBox msgBox;
                msgBox.setText("Error: File Name/Path Error.");
                msgBox.exec();
            }



             else
            {


                 // savefileName = QFileDialog::getSaveFileName(this, tr("Save File"));



                   ui->statusBar->showMessage("Crop Preview");

            //original file
                array = vvfilePath.toLocal8Bit();
                filePathfromqs = array.data();
                qDebug() << "---------------filePathfromqs---------- " << vvfilePath << "  ---  "  << filePathfromqs << "  ///  "<< array;





             //name of saved file
                 QByteArray array2 = savefileName.toLocal8Bit();
                 char* savefileNamefromqs = array2.data();
                 qDebug() << "---------------filePathfromqs---------- " << savefileName << "  ---  "  << savefileNamefromqs << "  ///  "<< array2;





                     //STARTPOINT
                           //float secpos= (iposstart*60);
                           float secpos= x;
                            qDebug() << "-------------float secpos= (iposstart*60); ---------- " << secpos ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream;
                            stream << std::fixed << std::setprecision(3) << secpos;
                            std::string str = stream.str();
                        const char* startvar = str.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar;


                     //ENDPOINT
                         float secposend= y ;
                          qDebug() << "-------------float secposend---------- " << secposend ;
                       //format in seconds.ms (3 digits ms)
                          std::stringstream stream2;
                          stream2 << std::fixed << std::setprecision(3) << secposend;
                          std::string str2 = stream2.str();
                      const char* endvar = str2.c_str();
                     qDebug() << "------------------endvar-------------- " << endvar;


                     //xdelta
                           //float secpos= (iposstart*60);
                           float secpos2= xdelta;
                            qDebug() << "-------------float secpos2= xdelta; ---------- " << secpos2 ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream3;
                            stream3 << std::fixed << std::setprecision(3) << secpos2;
                            std::string str3 = stream3.str();
                        const char* startvar2 = str3.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar2;

                     //ydelta
                           //float secpos= (iposstart*60);
                           float secpos3= ydelta;
                            qDebug() << "-------------float secpos2= xdelta; ---------- " << secpos3 ;
                         //format in seconds.ms (3 digits ms)
                            std::stringstream stream4;
                            stream4 << std::fixed << std::setprecision(3) << secpos3;
                            std::string str4 = stream4.str();
                        const char* startvar3 = str4.c_str();
                         qDebug() << "----------iiiiiiiiii--------startvar----------- " << startvar3;


            char result[50000];

             strcpy(result,"ffplay -i '");
             strcat(result,filePathfromqs);
              strcat(result,"' -vf \"crop=");
              strcat(result,startvar);
              strcat(result,":");
              strcat(result,endvar);
               strcat(result,":");
                strcat(result,startvar2);
                strcat(result,":");
                 strcat(result,startvar3);
             // strcat(result,":0:0,drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1\"");
            strcat(result,",drawtext=text='%{pts\\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1\"");


                      qDebug() << "-------crop------------result--------------- " << result;


                      if(system(result) != 0)
                     {
                         qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                         ui->statusBar->showMessage("");
                         QMessageBox msgBox;
                         msgBox.setText("Error: ffmpeg failed.");
                         msgBox.exec();
                     }
                     else
                     {
                         ui->statusBar->showMessage("");
//                         QMessageBox msgBox;
//                         msgBox.setText("???");
//                         msgBox.exec();

                         QMessageBox::StandardButton reply;
                          reply = QMessageBox::question(this, "Crop", "Save?",QMessageBox::Yes|QMessageBox::No);
                          if (reply == QMessageBox::Yes)
                          {
                                ui->statusBar->showMessage("Please wait...");
                         //saving crop

                              char result2[50000];

                               strcpy(result2,"ffmpeg -y -i '");
                               strcat(result2,filePathfromqs);
                                strcat(result2,"' -filter:v \"crop=");
                                strcat(result2,startvar);
                                strcat(result2,":");
                                strcat(result2,endvar);
                                strcat(result2,":");
                                 strcat(result2,startvar2);
                                 strcat(result2,":");
                                  strcat(result2,startvar3);
                                strcat(result2,",scale=3840:2160:flags=lanczos,setsar=1\" -c:v libx264 -preset veryfast -crf 15 -c:a copy '");
                                strcat(result2,savefileNamefromqs);
                                strcat(result2,"'");


//ffmpeg -y -i mkv.mkv -filter:v "crop=3840:1030:0:50,scale=3840:2160:flags=lanczos,setsar=1" -c:v libx264 -preset veryfast -crf 15 -c:a copy mkv_crop50topHQ2scaled.mkv


                                        qDebug() << "-------crop------------result2--------------- " << result2;


                                        if(system(result2) != 0)
                                       {
                                           qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++ffmpeg failed..." << endl;

                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("Error: ffmpeg failed.");
                                           msgBox.exec();
                                       }
                                       else
                                       {
                                           ui->statusBar->showMessage("");
                                           QMessageBox msgBox;
                                           msgBox.setText("File saved.");
                                           msgBox.exec();
                                       }




                          //end: saving crop




                          } else
                          {
                              QMessageBox msgBox;
                              msgBox.setText("Crop not saved.");
                              msgBox.exec();
                          }

                     }


    }
//***********



//ffplay -i mkv.mkv -vf "crop=1536:864:0:0,drawtext=text='%{pts\:hms}':box=1:x=(w-tw)/2:y=h-(2*lh) :fontsize=56,scale=3840:2160:flags=lanczos,setsar=1"






    }



}


//END 4K top left
//-----------------------



//End crop 4K

MainWindow::~MainWindow()
{
    delete ui;
}





