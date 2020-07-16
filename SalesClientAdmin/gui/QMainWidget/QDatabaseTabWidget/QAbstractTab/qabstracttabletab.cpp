#include "qabstracttabletab.h"

using namespace Gui::DatabaseTabs::AbstractTableTab;

QAbstractTableTab::QAbstractTableTab(const ColumnsSettings &colSettings,
                                     QWidget *parent)
    : QWidget(parent)
{
    createWidgets();
    setGui();
    connects();

    setColumnsSettings(colSettings);
//    slotUpdateItems();
}

void QAbstractTableTab::closeEvent(QCloseEvent *)
{

}

void QAbstractTableTab::setColumnsSettings(const ColumnsSettings &colSettings)
{
    setColumnsCount(colSettings.columnCount);
    setColumnsLabel(colSettings.labels);
}

QTableWidgetItem *QAbstractTableTab::createItem(const QString &text, int id)
{
    auto *item = new QTableWidgetItem();
    item->setText(text);
    item->setData(Qt::UserRole, id);
    return item;
}

void QAbstractTableTab::setItemToTable(int row, int column, QTableWidgetItem *item)
{
    table->setItem(row, column, item);
}

void QAbstractTableTab::createWidgets()
{
    mainLayout = new QVBoxLayout(this);
    table = new QTableWidget(this);
    upperLayout = new QHBoxLayout;
    addItemButton = new QPushButton(tr("Добавить"), this);
    searchIconLabel = new QLabel(this);
    searchEdit = new QLineEdit(this);
    searchIcon = new QPixmap(":/images/icons/other/Search.png");

    selectionModel = new QItemSelectionModel(table->model(), table);
    shortcutCopy = new QShortcut(Qt::CTRL + Qt::Key_C, table);
    shortcutSelectAll = new QShortcut(Qt::CTRL + Qt::Key_A, table);

}

void QAbstractTableTab::setGui()
{
    this->setLayout(mainLayout);
    *searchIcon = searchIcon->scaled(24,24,Qt::KeepAspectRatio);
    searchIconLabel->setPixmap(*searchIcon);

    upperLayout->addWidget(searchIconLabel);
    upperLayout->addWidget(searchEdit, 1);
    upperLayout->addWidget(addItemButton);

    mainLayout->addLayout(upperLayout);
    mainLayout->addWidget(table);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setContextMenuPolicy(Qt::CustomContextMenu);

    table->setSelectionModel(selectionModel);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    this->setEnabled(true);

}

void QAbstractTableTab::connects()
{
    connect(this, &QAbstractTableTab::updateItems,
            this, &QAbstractTableTab::slotUpdateItems);
    connect(searchEdit, &QLineEdit::textChanged,
            this, &QAbstractTableTab::slotSearchTextChanged);
    connect(table, &QTableWidget::doubleClicked,
            this, [=](const QModelIndex &index) {
        emit(editItem(index.data(Qt::UserRole).toInt()));
    });
    connect(table, &QTableWidget::customContextMenuRequested,
            this, &QAbstractTableTab::slotMenuRequested);
    connect(addItemButton, &QPushButton::clicked,
            this, [this](){
        emit(addItem());
    });
    connect(shortcutCopy, &QShortcut::activated,
            this, &QAbstractTableTab::slotCopy);
    connect(shortcutSelectAll, &QShortcut::activated,
            this, &QAbstractTableTab::slotSelectAll);
}

void QAbstractTableTab::setColumnsCount(int count)
{
    table->setColumnCount(count);
}

void QAbstractTableTab::setColumnsLabel(const QStringList &list)
{
    table->setHorizontalHeaderLabels(list);
}

void QAbstractTableTab::slotSearchTextChanged(QString text)
{
    auto items = table->findItems(text, Qt::MatchContains);

    for(int i = 0; i < table->rowCount(); i++) {
        table->showRow(i);
    }

    QList<int> showID;
    for (int i = 0; i < table->rowCount(); i++) {
        for (auto val : items) {
            if (val->row() == table->rowAt(i)
                    || text.isEmpty()) {
                showID.push_back(val->row());
            }
        }
        table->hideRow(i);
    }

    for (auto id : showID) {
        table->showRow(id);
    }
}

void QAbstractTableTab::slotUpdateItems()
{
    table->clearContents();
    auto vector = getSalesObjectVector();

    if (table->rowCount() != vector.count()) {
        table->setRowCount(vector.count());
    }

    int row = 0;
    for (auto val : vector) {
        processingAddItemsToTable(row, val);
        ++row;
    }
}

void QAbstractTableTab::slotMenuRequested(QPoint pos)
{
    menuTable = new QMenu(this);

    connect(menuTable, &QMenu::aboutToHide,
            this, [=](){
        menuTable->deleteLater();
    });

    actionSelectAll = new QAction(tr("Выделить все"), menuTable);
    connect(actionSelectAll, &QAction::triggered,
            this, &QAbstractTableTab::slotSelectAll);

    menuTable->addAction(actionSelectAll);
    actionCopy = new QAction(tr("Копировать"), menuTable);
    connect(actionCopy, &QAction::triggered,
            this, &QAbstractTableTab::slotCopy);

    actionCopy->setEnabled(selectionModel->hasSelection());
    menuTable->addAction(actionCopy);


    menuTable->popup(table->viewport()->mapToGlobal(pos));
}

void QAbstractTableTab::slotSelectAll()
{
    table->selectAll();
}

void QAbstractTableTab::slotCopy()
{
    QModelIndexList selected = selectionModel->selectedIndexes();

    if (selected.length()>0) {
        QString buf;
        int currentRow = 0;
        QModelIndex currentItem;
        buf = selected.at(0).data().toString();

        for (int i=1;i<selected.length();i++) {
            currentItem = selected.at(i);
            if (currentItem.row() == currentRow) {
                buf = buf + "\t" + currentItem.data().toString();
            } else {
                buf = buf + "\r\n" + currentItem.data().toString();
                currentRow = currentItem.row();
            }
        }
            QClipboard *clipBoard = QApplication::clipboard();
            clipBoard->setText(buf);
    }
}

