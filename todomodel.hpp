#ifndef TODOMODEL_HPP
#define TODOMODEL_HPP

#include <QAbstractListModel>

// Forward declaration
class TodoList;

class TodoModel : public QAbstractListModel
{
    TodoList* mList;

    Q_OBJECT
    Q_PROPERTY(TodoList* list READ name READ list WRITE setList)
public:
    explicit TodoModel(QObject *parent = nullptr);

    enum class RoleType {
        DoneRole,
        DescriptionRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    TodoList *list() const;
    void setList(TodoList *list);
};

#endif // TODOMODEL_HPP
