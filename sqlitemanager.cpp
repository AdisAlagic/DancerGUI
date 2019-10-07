#include "sqlitemanager.h"
#include "mainwindow.h"
#include <map>
SQLiteManager::SQLiteManager()
{
    sdb = QSqlDatabase::addDatabase("QSQLITE");
}

std::vector<QString> SQLiteManager::getSongs(QString path){
    QString fullpath = path + "/danser.db";
    sdb.setDatabaseName(fullpath);
    sdb.open();
    std::vector<QString> res;
    QSqlQuery query(sdb);

    bool queryOk = query.exec("SELECT beatmaps.title FROM beatmaps");
    qDebug() << query.lastError();
    if(queryOk){
       QString lastSong = "";
       while(query.next()) {
           QString song = query.value(0).toString();
           if (lastSong != song){
               //qDebug() << song;
               res.push_back(song);
               lastSong = song;
           }
       }
       sdb.close();
    }
    std::sort(res.begin(), res.end());
    return res;
}

std::vector<QString> SQLiteManager::getDifficulty(QString song)
{
    sdb.open();
    std::vector<QString> res;
    QSqlQuery query(sdb);
    bool queryOk = query.exec("SELECT beatmaps.version FROM beatmaps WHERE beatmaps.title=\"" + song + "\"");
    qDebug() << query.lastError();
    qDebug() << query.executedQuery();
    if (queryOk){
        while(query.next()){
            res.push_back(query.value(0).toString());
        }
    }
    return res;
}
