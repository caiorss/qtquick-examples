#include "textfilemodel.hpp"
#include <iostream>
#include <QFile>

QUrl
TextFileModel::file() const
{
    return m_file;
}

void
TextFileModel::setFile(const QUrl &file)
{
    std::cout << " [INFO] File set to " << file.toString().toStdString() << std::endl;
    m_file = file;
    emit this->fileChanged();
}

QString
TextFileModel::text() const
{
    QFile file(m_file.toLocalFile());
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString txt = file.readAll();
        // std::cout << "Text = " << txt.toStdString() << std::endl;
        return txt;
    }
    return "";
}

TextFileModel::TextFileModel(QObject *parent) : QObject(parent)
{

}
