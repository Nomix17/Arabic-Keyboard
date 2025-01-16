#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QKeyEvent>
#include <string.h>
#include "clip.h"
#include <QString>
#include <QMessageBox>


#ifdef _WIN32
    #define OS "Windows"
#elif __linux__
    #define OS "Linux"
#elif __APPLE__
    #define OS "MacOs"
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VKeyboard)
{
    ui->setupUi(this);
    this->setWindowTitle("Arabic Keyboard");
    this->setFixedSize(1088,454);
    ui->textEdit->setLayoutDirection(Qt::RightToLeft);
    ui->textEdit->setAlignment(Qt::AlignRight);

    ui->textEdit->textCursor().movePosition(QTextCursor::Start);
    ui->textEdit->setFocus();

    arnumbers = {"ذ","١","٢","٣","٤","٥","٦","٧","٨","٩","."};
    
    arletters = {"ض", "ص", "ث", "ق", "ف", "غ", "ع", "ه", "خ","ح", "ج", "د",
                           "ش", "س", "ي", "ب","ل", "ا", "ت", "ن", "م", "ك", "ط",
                           "ئ", "ء", "ؤ", "ر", "لا", "ى", "ة", "و", "ز", "ظ", " "};

    shiftarnumbers = {"ّ","!","@","#","$","%","^","&","*","(",")"};
    shiftarletters = {"َ","ً","ُ","ٌ","لإ","إ","‘","÷","×","؛","<",">",
                        "ِ","ٍ","[","]","لأ","أ","ـ","،","/",":","\"",
                        "~","ْ","{","}","لآ","آ","’","،",".","؟"};
    ui->BLang->setText("تنظيف");
    buttons(arletters,arnumbers);

}

void MainWindow::buttons(QStringList letters,QStringList topbuttons){
        
        for(int i=0;i<letters.size();i++){
            QString Bname="b"+QString::number(i+1);
            QPushButton *button =this->findChild<QPushButton *>(Bname);
            if(button){
                disconnect(button,nullptr,this,nullptr);
                button->setText(letters[i]);
                connect(button,&QPushButton::clicked,this,[this,i,letters](){
                    QString text=ui->textEdit->toPlainText()+letters[i];
                    ui->textEdit->setText(text);
                    ui->textEdit->textCursor().movePosition(QTextCursor::Start);
                    ui->textEdit->setFocus();

                });
            }
        }
        
        for(int j=0;j<topbuttons.size();j++){
            QString Bname="b"+QString::number(j+1)+"_2";
            QPushButton *button =this->findChild<QPushButton *>(Bname);
            if(button){
                disconnect(button,nullptr,this,nullptr);
                button->setText(topbuttons[j]);
                connect(button,&QPushButton::clicked,this,[this,j,topbuttons](){
                    QString text=ui->textEdit->toPlainText()+topbuttons[j];
                    ui->textEdit->setText(text);
                    ui->textEdit->textCursor().movePosition(QTextCursor::Start);
                    ui->textEdit->setFocus();

                });
            }
        }
        
        QPushButton *button =this->findChild<QPushButton *>("testb14");
        button->setText("<=");
        disconnect(button,nullptr,this,nullptr);
        connect(button,&QPushButton::clicked,[this]{
            QString t=ui->textEdit->toPlainText();
            t.chop(1);
            ui->textEdit->setText(t);
            ui->textEdit->setFocus();
        });

}

void MainWindow::on_copy_clicked(){
    QString t = ui->textEdit->toPlainText();
    clip::set_text(t.toStdString());
}

void MainWindow::on_BLang_clicked(){
    ui->textEdit->clear();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    QString t=ui->textEdit->toPlainText();
    if(event->key()==Qt::Key_Backspace){
        t.chop(1);
    }else if(event->key()==Qt::Key_Space){
        t = t+" ";
    }else if(event->key()==Qt::Key_Shift){
        if(shifted){
            buttons(arletters,arnumbers);
            shifted=false;
        }else{
            buttons(shiftarletters,shiftarnumbers);
            shifted=true;
        }
    }
    ui->textEdit->setText(t);
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_BSearch_clicked()
{   
    if(!ui->textEdit->toPlainText().replace(" ","").isEmpty()){
        std::string command;
        std::string searchedtext = ui->textEdit->toPlainText().replace(" ","+").toStdString();

        if(OS=="Windows"){
            command = "start 'https://duckduckgo.com/?q='"+searchedtext;
        }else if(OS=="Linux"){
            command = "xdg-open 'https://duckduckgo.com/?q='"+searchedtext;
        }else if(OS=="MacOs"){
            command = "open 'https://duckduckgo.com/?q='"+searchedtext;
        }else{
            QMessageBox::critical(nullptr, "Error", "An error occurred!\nOperation system not supported.");
            command = "echo Unknown OS";
        }

        system(command.c_str());
    }
}

