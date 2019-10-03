#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H
#include <QtSql>
#include <QMap>
typedef std::string String;
class SQLiteManager
{
public:
    static std::multimap<QVariant, QVariant> songs;
    static void getData();
private:
    SQLiteManager();
};


#endif // SQLITEMANAGER_H
