#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [this](){
        searchDir =  QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);;
        QDir dir(searchDir);
        ui->lineEdit_2->setText(dir.path());
    });
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::startExplore);
}
MainWindow::~MainWindow()
{
    delete ui;
    delete searchThread;
}
bool MainWindow::startExplore(){
    ui->textEdit->clear();
    QDir dir(searchDir);
    QVector<QString> files = ui->lineEdit->text().simplified().split(", ");
    searchThread = new FileExployer(this, files, dir.path());
    connect(searchThread, &FileExployer::resultReady, this, &MainWindow::handleResults);
    connect(searchThread, &FileExployer::finished, searchThread, &QObject::deleteLater);
    searchThread->start();
}
void MainWindow::handleResults(const QStringList &list){
    mutex1.lock();
    for(QString path: list)
        ui->textEdit->append(path);
    mutex1.unlock();
}

QVector<QString> MainWindow::arraysOfFiles(QString line){
    QVector<QString> arr = line.simplified().split(", ");
    return arr;
}


FileExployer::FileExployer(MainWindow *m_0, const QVector<QString>& files, const QString& dir)
{
    m=m_0;
    dirsearch = dir;
    filesSearch = files;
}
FileExployer::FileExployer(const QVector<QString>& files, const QString& dir)
{
    dirsearch = dir;
    filesSearch = files;
}
void FileExployer::run()
{
    QDir dir(dirsearch);
    qDebug() << dir.path();
    if(!dir.exists() || !dir.isEmpty()){
        for (const QFile file : dir.entryList(QDir::Files))
            for(QString f: filesSearch)
                if(file.fileName().contains(f)){
                    mutex2.lock();
                    result.append(dirsearch + '/' + file.fileName());
                    mutex2.unlock();
                }

        QDirIterator it(dir.path(), QDir::Dirs);
        it.next();
        it.next();
        while (it.hasNext()) {
            QString dirname = it.next();

            QDir d(dirname);
            FileExployer *searchThread = new FileExployer(filesSearch, d.path());
            connect(searchThread, &FileExployer::resultReady, m, &MainWindow::handleResults);
            connect(searchThread, &FileExployer::finished, searchThread, &QObject::deleteLater);
            searchThread->start();
        }
        /*
        for (const QString &dirname : dir.entryList(QDir::Dirs)){
            QDir d(dirname);
            FileExployer *searchThread = new FileExployer(filesearch, d.path());
            connect(searchThread, &FileExployer::resultReady, m, &MainWindow::handleResults);
            connect(searchThread, &FileExployer::finished, searchThread, &QObject::deleteLater);
            searchThread->start();
        }
        */

    }

    emit resultReady(result);
}


