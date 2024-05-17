
#include "fileexployer.h"
/*
FileExployer::FileExployer(const QString& file, const QString& dir)
{
    dirsearch = dir;
    filesearch = file;
}

void FileExployer::run()
{
    QDir dir(dirsearch);
    if(!dir.exists() && !dir.isEmpty()){
        for (const QFile file : dir.entryList(QDir::Files))
            if(file.fileName().compare(filesearch)){

                mutex2.lock();
                result.append(file.fileName());
                mutex2.unlock();
            }

        for (const QString &dirname : dir.entryList(QDir::Dirs)){
            FileExployer *searchThread = new FileExployer(filesearch, filesearch);
            connect(searchThread, &FileExployer::finished, searchThread, &QObject::deleteLater);
            searchThread->start();
        }

    }

    emit resultReady(result);
}
*/


