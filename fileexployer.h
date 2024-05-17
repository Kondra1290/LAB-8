#ifndef FILEEXPLOYER_H
#define FILEEXPLOYER_H

#include <QThread>
#include <QFile>
#include <QMainWindow>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDesktopServices>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QMutex>
#include <QMessageBox>
/*
class FileExployer : public QThread
{
public:
    FileExployer(const QString &file, const QString &dir);
    Q_OBJECT
    void run() override;
signals:
    void resultReady(const QStringList &s);
    //void startSearch();
private:
    QString dirsearch, filesearch;
    QStringList result;
    static inline QMutex mutex2;
};
*/
#endif // FILEEXPLOYER_H
