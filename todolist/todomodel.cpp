#include "todomodel.hpp"
#include "todolist.hpp"

TodoModel::TodoModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int TodoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList )
        return 0;

    return mList->items().size();
}

QVariant TodoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const TodoItem item = mList->items().at(index.row());

    RoleType t = static_cast<RoleType>(role);

    if(t == RoleType::DoneRole)
        return QVariant(item.done);

    if(t == RoleType::DescriptionRole)
        return QVariant(item.description);

    return QVariant();
}

bool TodoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    TodoItem item = mList->items().at(index.row());

    RoleType t = static_cast<RoleType>(role);

    if(t == RoleType::DoneRole)
        item.done = value.toBool();

    if(t == RoleType::DescriptionRole)
        item.description = value.toString();

    if (mList->setItemAt(index.row(), item)) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TodoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray>
TodoModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[static_cast<int>(RoleType::DoneRole)] = "done";
    names[static_cast<int>(RoleType::DescriptionRole)] = "description";
    return names;
}

TodoList *TodoModel::list() const
{
    return mList;
}

void TodoModel::setList(TodoList *list)
{
    beginResetModel();
    if(mList) mList->disconnect(this);
    mList = list;
    if(mList){
        this->connect(mList, &TodoList::preItemAppended, this, [=]()
                      {
                          const int index = mList->items().size();
                          beginInsertRows(QModelIndex(), index, index);
                      });

        this->connect(mList, &TodoList::postItemAppended, this, [=]()
                      {
                          endInsertRows();
                      });

        this->connect(mList, &TodoList::preItemRemoved, this, [=](int index)
                      {
                          beginRemoveRows(QModelIndex(), index, index);
                      });

        this->connect(mList, &TodoList::postItemRemoved, this, [=]()
                      {
                          endRemoveRows();
                      });

    }

    endResetModel();
}
