#include "todolist.hpp"

TodoList::TodoList(QObject* parent)
{
    mItems.append({true,  "Do some task"});
    mItems.append({false, "Buy some groceries"});
    mItems.append({false, "Buy bitcoins"});
}

bool TodoList::setItemAt(int index, const TodoItem &item)
{
    if(index < 0 || index >= mItems.size())
        return false;
    const TodoItem& oldItem = mItems.at(index);

    if(item.done == oldItem.done && item.description == oldItem.description)
        return false;

    mItems[index] = item;
    return true;
}

QVector<TodoItem> TodoList::items() const
{
    return mItems;
}

void TodoList::appendItem()
{
    emit preItemAppended();
    TodoItem item;
    item.done = false;
    mItems.append(item);
    emit postItemAppended();

}

void TodoList::removeCompletedItems()
{
    for(int i = 0.; i < mItems.size(); )
    {
        if(mItems.at(i).done)
        {
            emit preItemRemoved(i);
            mItems.removeAt(i);
            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}
