#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H
#include <QtSql>
#include <QMap>
typedef std::string String;
class SQLiteManager
{
public:
    std::vector<QString> getSongs(QString path);
    std::vector<QString> getDifficulty(QString song);
    SQLiteManager();
private:
    QSqlDatabase sdb;
};


#endif // SQLITEMANAGER_H
