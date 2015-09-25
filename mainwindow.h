#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnCargarArchivo_clicked();
    void on_btnSalvar_clicked();

private:
    Ui::MainWindow *ui;
    QString archivoACargar;
    QString retornarCodigoLegus(QString codigo);
};

#endif // MAINWINDOW_H
