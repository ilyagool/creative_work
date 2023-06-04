#include "TMainWnd.h"
#include "TSettings.h"
#include "TCategoryModel.h"
#include "TProductModel.h"
#include "TProductDelegate.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QMessageBox>

#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>
#include <QDate>
#include <QDir>

#include <QInputDialog>

TMainWnd::TMainWnd(QWidget *parent) : QMainWindow(parent)
  {
  setupUi(this);
  connect(qApp,&QApplication::aboutToQuit,this,&TMainWnd::aboutToQuit);

  QDir directory;
  if (directory.exists(qApp->applicationDirPath()+"/database")==false)
    directory.mkpath(qApp->applicationDirPath()+"/database");

  if (!openDatabase(qApp->applicationDirPath()+"/database/store.db"))
    {
    QMessageBox::critical(this,tr("Error"),tr("Can't open database."),QMessageBox::Ok);
    return;
    }

  m_categoryModel=new TCategoryModel(this,m_dataBase);
  m_categoryModel->select();
  m_categoryModel->setHeaders();

  m_productModel=new TProductModel(this,m_dataBase);
  m_productModel->select();
  m_productModel->setHeaaders();

  m_productDelegate=new TProductDelegate(this);

  categoryTable->setModel(m_categoryModel);
  productTable->setModel(m_productModel);
  productTable->setItemDelegate(m_productDelegate);

  connect(categoryTable->selectionModel(),&QItemSelectionModel::currentRowChanged,this,&TMainWnd::categoryChanged);
  categoryTable->selectRow(0);

  connect(appendBtn,&QPushButton::clicked,this,&TMainWnd::appendProduct);
  connect(removeBtn,&QPushButton::clicked,this,&TMainWnd::removeProduct);
  connect(searchBtn,&QPushButton::clicked,this,&TMainWnd::searchProduct);

  readSettings();

  categoryTable->setColumnHidden(m_categoryModel->record().indexOf("id"),true);
  productTable->setColumnHidden(m_productModel->record().indexOf("id"),true);
  productTable->setColumnHidden(m_productModel->record().indexOf("category_id"),true);
  }

bool TMainWnd::openDatabase(const QString &databaseName)
  {
  if (!QSqlDatabase::contains("store"))
    m_dataBase=QSqlDatabase::addDatabase("QSQLITE","store");

  m_dataBase.setDatabaseName(databaseName);
  if (!m_dataBase.open())
    return false;

  QSqlQuery query(m_dataBase);
  query.prepare("CREATE TABLE IF NOT EXISTS categories ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                "category VARCHAR(32) UNIQUE);");
  if (!query.exec())
    return false;

  query.prepare("CREATE INDEX IF NOT EXISTS categories_idx ON categories(category ASC);");
  if (!query.exec())
    return false;

  query.prepare("CREATE TABLE IF NOT EXISTS products("
                "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                "category_id INTEGER,"
                "article VARCHAR(32),"
                "name VARCHAR(64),"
                "amount INTEGER,"
                "entrance_date DATE);");
  if (!query.exec())
    return false;

  query.prepare("CREATE INDEX IF NOT EXISTS products_idx ON products(name ASC);");
  if (!query.exec())
    return false;

  query.prepare("INSERT OR IGNORE INTO categories(category) values('Компьютерные комплектующие');");
  if (!query.exec())
    return false;

  query.prepare("INSERT OR IGNORE INTO categories(category) values('Автозапчасти');");
  if (!query.exec())
    return false;

  query.prepare("INSERT OR IGNORE INTO categories(category) values('Бытовая техника');");
  if (!query.exec())
    return false;

  return true;
  }
//
void TMainWnd::writeSettings()
  {
  TSettings settings;
  settings.setXmlValue("interface/main_window/state","",saveState());
  settings.setXmlValue("interface/main_window/geometry","",saveGeometry());
  settings.setXmlValue("interface/main_window/splitter","",mainSplitter->saveState());

  settings.setXmlValue("interface/main_window/product_table","",productTable->horizontalHeader()->saveState());
  settings.setXmlValue("interface/main_window/category_table","",categoryTable->horizontalHeader()->saveState());
  return;
  }
//
void TMainWnd::readSettings()
  {
  TSettings settings;
  restoreState(settings.getXmlValue("interface/main_window/state","",0).toByteArray());
  restoreGeometry(settings.getXmlValue("interface/main_window/geometry","",0).toByteArray());
  mainSplitter->restoreState(settings.getXmlValue("interface/main_window/splitter","",0).toByteArray());

  productTable->horizontalHeader()->restoreState(settings.getXmlValue("interface/main_window/product_table","",0).toByteArray());
  categoryTable->horizontalHeader()->restoreState(settings.getXmlValue("interface/main_window/category_table","",0).toByteArray());
  return;
  }
//
void TMainWnd::closeEvent(QCloseEvent *event)
  {
  if (QMessageBox::question(this,tr("Confirmation"),tr("Exit program?"),QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
    event->accept();
  else
    event->ignore();
  return;
  }
//
void TMainWnd::aboutToQuit()
  {
  m_dataBase.commit();
  if (QSqlDatabase::contains("store"))
    m_dataBase=QSqlDatabase::addDatabase("QSQLITE","dictionary");

  writeSettings();
  return;
  }

void TMainWnd::categoryChanged(const QModelIndex &current, const QModelIndex &previous)
  {
  quint16 category_id=m_categoryModel->index(current.row(),m_categoryModel->record().indexOf("id")).data().toUInt();
  if (category_id==0)
    m_productModel->setFilter("");
  else
    m_productModel->setFilter("category_id="+QString::number(category_id));

  m_productModel->select();
  }

void TMainWnd::appendProduct()
  {
  QString name=QInputDialog::getText(this,tr("New product"),tr("Enter name:"));
  if (name.isEmpty())
    return;

  QString article=QInputDialog::getText(this,tr("New product"),tr("Enter article:"));
  if (article.isEmpty())
    return;

  quint16 amount=QInputDialog::getInt(this,tr("New product"),tr("Enter amount:"),1,1,16385);
  if (amount==0)
    return;

  quint16 category_id;
  QModelIndexList selected=categoryTable->selectionModel()->selectedRows();
  if (selected.size())
    category_id=m_categoryModel->index(selected.first().row(),m_categoryModel->record().indexOf("id")).data().toUInt();
  else
    category_id=1;

  QSqlQuery query(m_dataBase);
  query.prepare("insert into products(category_id,article,name,amount,entrance_date) values (:category_id,:article,:name,:amount,:date)");
  query.bindValue(":category_id",QString::number(category_id));
  query.bindValue(":name",name);
  query.bindValue(":article",article);
  query.bindValue(":amount",amount);
  query.bindValue(":date",QDate::currentDate().toString("yyyy-MM-dd"));

  if (query.exec())
    m_productModel->select();
  }

void TMainWnd::removeProduct()
  {
  QModelIndexList selected=productTable->selectionModel()->selectedRows();
  if (selected.size()==0)
    return;

  quint16 product_id=m_productModel->index(selected.first().row(),m_productModel->record().indexOf("id")).data().toUInt();
  QSqlQuery query(m_dataBase);
  query.prepare("delete from products where id=:product_id");
  query.bindValue(":product_id",QString::number(product_id));

  if (query.exec())
    m_productModel->select();
  }

void TMainWnd::searchProduct()
  {
  QString name=QInputDialog::getText(this,tr("New product"),tr("Enter name:"));
  if (name.isEmpty())
    return;

  QModelIndexList found=m_productModel->match(m_productModel->index(0,m_productModel->record().indexOf("name")),Qt::DisplayRole,name,1,Qt::MatchStartsWith);
  if (found.size()==0)
    return;

  productTable->selectRow(found.first().row());
  productTable->setFocus();
  }

//
