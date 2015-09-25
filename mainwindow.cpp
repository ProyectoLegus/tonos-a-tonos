#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->setStyle(new QPlastiqueStyle());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCargarArchivo_clicked()
{
    archivoACargar = QFileDialog::getOpenFileName(this, "Abrir Archivo",
                                                  QDir::homePath(), tr("Archivos de Texto (*.txt)"));

    if( archivoACargar.isEmpty() )
    {
        QMessageBox::critical(this,"Error", "Error al abrir el archivo");
        return;
    }
    ui->txtArchivo->setText(archivoACargar);
}

void MainWindow::on_btnSalvar_clicked()
{
    if( archivoACargar.isEmpty() )
    {
        QMessageBox::critical(this,"Error", "Favor seleccione un archivo");
        return;
    }

    QFile archivo( archivoACargar );
    if( !archivo.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this, "Error", "No se pudo leer el archivo");
        return;
    }

    QTextStream flujo(&archivo);
    QString text = QString(flujo.readAll());

    archivo.close();

    QString cod = retornarCodigoLegus(text);


    QFile archivoEscribir(archivoACargar + ".legus");
    if( !archivoEscribir.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "No se creo el archivo");
        return;
    }

    QTextStream fl(&archivoEscribir);
    fl << cod;

    archivoEscribir.close();
    QMessageBox::about(this,"Mensaje","Archivo guardado exitosamente");
}

QString MainWindow::retornarCodigoLegus(QString codigo)
{
    QStringList lineas = codigo.split("\n");
    QString cod = "";
    foreach(QString line, lineas )
    {
        if(line.trimmed() == "")
        {
            continue;
        }

        if( line.startsWith(":beep"))
        {
            QString nuevo = line.mid(6, line.length()-1);
            QStringList freqDur = nuevo.split(" ");

            QStringList frecuencia = freqDur.at(0).split("=");
            QStringList duracion = freqDur.at(1).split("=");

            QString d = duracion.at(1);
            cod += "tono(";
            cod += frecuencia.at(1);
            cod +=  ",";
            cod += d.replace("ms;","");
        }
        else if( line.startsWith(":delay"))
        {
            QString nuevo = line.mid(7, line.length()-1);
            cod += "," + nuevo.replace("ms;","") + ")\n";
        }
    }
    return cod;
}
