#include "includes/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Exit,SIGNAL(triggered(bool)),this,SIGNAL(exitClicked(bool)));
}

void MainWindow::on_modeComboBox_currentIndexChanged(int index)
{
    ui->chosenLetter_edit->setEnabled(false);
    ui->chosenLetter_label->setEnabled(false);
    ui->blockSize_edit->setEnabled(false);
    ui->blockSize_label->setEnabled(false);
    ui->keyPhrase_edit->setEnabled(false);
    ui->keyPhrase_label->setEnabled(false);

    switch(index){
        case 2:
        {
            ui->chosenLetter_edit->setEnabled(true);
            ui->chosenLetter_label->setEnabled(true);
            break;
        }
        case 3:
        {
            ui->blockSize_edit->setEnabled(true);
            ui->blockSize_label->setEnabled(true);
            break;
        }
        case 4:
        {
            ui->keyPhrase_edit->setEnabled(true);
            ui->keyPhrase_label->setEnabled(true);
            break;
        }
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}
