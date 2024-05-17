#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include <QFile>
#include <QMainWindow>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFile>
#include <QProcess>
#include <QMessageBox>
#include <QMutex>
#include <QDirIterator>
//#include "fileexployer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FileExployer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVector<QString> arraysOfFiles(QString line);

private slots:
    bool startExplore();
public slots:
    void handleResults(const QStringList &);

private:
    QString searchDir, filesearch;
    Ui::MainWindow *ui;
    FileExployer *searchThread;
    QMutex mutex1;
};


class FileExployer : public QThread
{
public:
    FileExployer(MainWindow *m_0, const QVector<QString> &files, const QString &dir);
    FileExployer(const QVector<QString> &file, const QString &dir);
    Q_OBJECT
    void run() override;
signals:
    void resultReady(const QStringList &s);
    //void startSearch();
private:
    QString dirsearch;
    QVector<QString> filesSearch;
    QStringList result;

    static inline QMutex mutex2;
    static inline MainWindow *m = nullptr;
};
#endif // MAINWINDOW_H
