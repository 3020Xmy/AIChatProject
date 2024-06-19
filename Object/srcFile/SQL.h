#ifndef SQL_H
#define SQL_H

#include <QtSql>
#include <QObject>
#include <QSqlError>
#include <QSqlDatabase>

class SQL : public QObject
{
    Q_OBJECT
public:
    explicit SQL();
    ~SQL();

private:
    QSqlDatabase *Data_Base;     //数据库对象
    QString *Sql_Data;           //记录查询结果
    QString query;               //记录查询语句
    QSqlError *Sql_Error;        //数据库错误信息
    QSqlQuery *Sql_Query;        //数据库查询语句

public:
    //验证数据
    bool testing_SqlQuery(const QString &outside,const QString &list=nullptr,const QString &data=nullptr);
    //查询数据
    const QStringList& get_SqkQuery(const QString &query);
    //添加数据
    bool add_SqkQuery(const QString &query);
    //修改数据
    bool set_SqlQuery(QString query);
    //获取表格列数
    int get_RowCount(const QString &list);
    //获取数据库对象地址
    void get_Path();
};

extern SQL my_SQL;   //声明全局变量

#endif // SQL_H
