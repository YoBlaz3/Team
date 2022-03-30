#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>


class DataBase;

class DataBaseDestroyer
{
    private:
        DataBase * DataBasePointer;
    public:
        ~DataBaseDestroyer() {
            delete DataBasePointer;
        }
        void initialize(DataBase * p){
            DataBasePointer = p;
        }
};


class DataBase
{
    private:
        static DataBase * p_instance;
        static DataBaseDestroyer destroyer;
        QSqlDatabase db;
    protected:
        DataBase(){}
        DataBase(const DataBase& );
        DataBase& operator = (DataBase &);
        ~DataBase() {}
        friend class DataBaseDestroyer;
    public:
        static DataBase* getInstance(){
            if (!p_instance)
            {
                QSqlDatabase db =
                QSqlDatabase::addDatabase("QSQLITE");
                db.setDatabaseName("Test");

                if(!db.open())
                qDebug()<<db.lastError().text();

                p_instance = new DataBase();
                destroyer.initialize(p_instance);
            }
            return p_instance;
        }
};

#endif // DATABASE_H
