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

signals:
    void exitClicked(bool);
    void openClicked(bool);
    void saveClicked(bool);

private slots:
    void on_modeComboBox_currentIndexChanged(int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
