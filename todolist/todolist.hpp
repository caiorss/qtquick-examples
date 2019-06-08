#ifndef TODOLIST_HPP
#define TODOLIST_HPP

#include <QObject>
#include <QVector>

struct TodoItem
{
    bool    done;
    QString description;
};

class TodoList: public QObject
{
    Q_OBJECT
public:
    explicit TodoList(QObject* parent = nullptr);
    bool setItemAt(int idnex, TodoItem const& item);

    QVector<TodoItem> items() const;

signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeCompletedItems();

private:
    QVector<TodoItem> mItems;

};

#endif // TODOLIST_HPP
