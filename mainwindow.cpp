#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(QSize(1200, 720));

    //model.setRootPath(QDir::rootPath());
    model.setRootPath(QDir::homePath());
    model.setFilter(QDir::AllEntries | QDir::System | QDir::Hidden | QDir::NoDot | QDir::NoDotDot);
    ui->treeView->setModel(&model);

    proxyModel.setSourceModel(&model);

    ui->tableView->setModel(&proxyModel);

    auto homeTreeIndex = model.index(QDir::homePath());
    ui->treeView->setCurrentIndex(homeTreeIndex);
    ui->treeView->setExpanded(homeTreeIndex, true);

    ui->treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    proxyModel.setRoot(homeTreeIndex);
    auto homeTableIndex = proxyModel.mapFromSource(homeTreeIndex);
    ui->tableView->setRootIndex(homeTableIndex);         // В таблице справа изначально устанавливаем home dir

    ui->currentPathEdit->setText(QDir::homePath());

    QObject::connect(ui->filterEdit, &QLineEdit::returnPressed, this, &MainWindow::on_pushButton_clicked);  // Соединяем нажатие энтера (такой же эффект, как от нажатия кнопки)

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if(index.column() != 0) return;
    if(!model.hasChildren(index)) return;
    proxyModel.setFilterRegExp("");     // Очищаем фильтр

    auto newIndex = proxyModel.mapFromSource(index);
    ui->tableView->setRootIndex(newIndex);
    proxyModel.setRoot(index);

    auto curPath = model.filePath(index);
    ui->currentPathEdit->setText(curPath);
}


void MainWindow::on_pushButton_clicked()
{
    auto filterText = ui->filterEdit->text();
    proxyModel.setFilterFixedString(filterText);
}

