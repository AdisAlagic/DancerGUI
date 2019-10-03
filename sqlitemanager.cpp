#include "sqlitemanager.h"
#include "mainwindow.h"
#include <map>
SQLiteManager::SQLiteManager()
{
}

void SQLiteManager::getData(){
        QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
       // sdb.setDatabaseName(MainWindow::path.path() + "\\dancer.db");
        bool ok = sdb.open();
        if (ok){
            QSqlQuery query("SELECT beatmaps.title, beatmaps.version FROM beatmaps");
            bool queryOk = query.exec();
            if (queryOk){
                while(query.next()){
                    QVariant one = query.value(1);
                    QVariant two = query.value(2);
                    songs.insert(std::make_pair(one, two));
                }
            }
        }

}
