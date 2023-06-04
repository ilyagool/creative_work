#pragma once

#include <QByteArray>
#include <QString>
#include <QVariant>
#include <QApplication>

#include <QDomDocument>
#include <QFile>

class TSettings
  {
    //Q_OBJECT
  public:
    explicit TSettings(QString fileName=qApp->applicationDirPath()+QStringLiteral("/store.xml"), QString info=QString());
    ~TSettings();

    // НЕ статика
    void saveSettings();

    void setXmlValue(const QStringList &path, const QString &key, const QVariant &value);
    void setXmlValue(const QString &path, const QString &key, const QVariant &value); // оставить только такие методы, с const QString &path ?

    QVariant getXmlValue(const QStringList &path, const QString &key, const QVariant &defaultValue=QVariant());
    QVariant getXmlValue(const QString &path,const QString &key,const QVariant &defaultValue=QVariant());

    void writeXmlComment(const QStringList &path, const QString &value);
    void writeXmlComment(const QString &path,const QString &value);

    void setXmlMaps(const QStringList &path, bool isAttrs, const QList<QMap<QString,QVariant>> &values);
    void setXmlMaps(const QString &path, bool isAttrs, const QList<QMap<QString,QVariant>> &values);

    QList<QMap<QString, QVariant>> getXmlMaps(const QStringList &path,bool isAttrs);
    QList<QMap<QString, QVariant>> getXmlMaps(const QString &path, bool isAttrs);

    void removeXmlEntry(const QStringList &path);
    void removeXmlEntry(const QString &path);

    void removeXmlComment(const QStringList &path, const QString &value);
    void removeXmlComment(const QString &path, const QString &value);

    bool containsXmlValue(const QStringList &path, const QString &key);
    bool containsXmlValue(const QString &path,const QString &key);

  protected:
    void setInitNode();
    // то для удобства представления, видеть смысл записей просто открыв XML
    static QString variantToString(const QVariant &variant);
    static QVariant stringToVariant(const QString &string);
  private:
   QString m_fileName;
   QString m_info;

   QDomDocument m_document;
   bool m_changed;
  };
