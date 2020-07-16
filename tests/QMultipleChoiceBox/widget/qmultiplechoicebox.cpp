#include "qmultiplechoicebox.h"

QMultipleChoiceBox::QMultipleChoiceBox(QWidget *parent)
    : QWidget(parent)
{
    this->createWidgets();
    this->setGui();
    this->connects();
    this->addToLayouts();
}

QMultipleChoiceBox::~QMultipleChoiceBox()
{

}

void QMultipleChoiceBox::setTitle(const QString &text)
{
    titleLabel->setText(text);
}

void QMultipleChoiceBox::setItems(const QVector<MultipleChoiceBox::ItemInformation> &itemsInformation)
{
    listWidget->clear();
    for (int i = 0; i < itemsInformation.count(); i++) {
        QListWidgetItem *item = new QListWidgetItem(listWidget);
        listWidget->addItem(item);

        mItem = new MultipleChoiceBox::QMultipleChoiceItem(itemsInformation.at(i),
                                                           listWidget);
        item->setSizeHint(mItem->sizeHint());
        listWidget->setItemWidget(item, mItem);
    }
}

void QMultipleChoiceBox::setHeight(int min, int max)
{
    this->setMinimumHeight(min);
    this->setMaximumHeight(max);
}

QString QMultipleChoiceBox::getTitle() const
{
    return titleLabel->text();
}

QVector<MultipleChoiceBox::ItemInformation> QMultipleChoiceBox::getSelectedItems()
{
    QVector<MultipleChoiceBox::ItemInformation> output;
    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<MultipleChoiceBox::QMultipleChoiceItem*>
                (listWidget->itemWidget(listWidget->item(i)));

        if (mItem->getInfrotmation().status) {
            output.push_back(mItem->getInfrotmation());
        }
    }
    return output;
}

QVector<MultipleChoiceBox::ItemInformation> QMultipleChoiceBox::getChangedItems()
{
    QVector<MultipleChoiceBox::ItemInformation> output;
    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<MultipleChoiceBox::QMultipleChoiceItem*>
                (listWidget->itemWidget(listWidget->item(i)));

        if (mItem->getInfrotmation().isWasChanged) {
            output.push_back(mItem->getInfrotmation());
        }
    }
    return output;
}

void QMultipleChoiceBox::createWidgets()
{
    mLayout = new QVBoxLayout(this);
    titleLabel = new QLabel(this);

    groupBoxLayout = new QVBoxLayout();
    searchLayout = new QHBoxLayout();
    buttonsLayout = new QHBoxLayout();

    listWidget = new QListWidget(this);
    box = new QGroupBox(this);
    searchEdit = new QLineEdit(this);
    iconSearchLabel = new QLabel(this);
    iconSearch = new QPixmap(":/images/icons/other/Search.png");
    selectAllButton = new QPushButton(tr("Отметить все"), this);
    unselectAllButton = new QPushButton(tr("Снять отметки"), this);
}

void QMultipleChoiceBox::setGui()
{
    this->setMinimumHeight(200);
    this->setMaximumHeight(200);

    *iconSearch = iconSearch->scaled(24, 24, Qt::KeepAspectRatio);
    iconSearchLabel->setPixmap(*iconSearch);
}

void QMultipleChoiceBox::connects()
{
    connect(searchEdit, &QLineEdit::textEdited,
            this, &QMultipleChoiceBox::slotSearchTextChanged);
    connect(selectAllButton, &QPushButton::clicked,
            this, &QMultipleChoiceBox::slotSelectAll);
    connect(unselectAllButton, &QPushButton::clicked,
            this, &QMultipleChoiceBox::slotUnselectAll);
}

void QMultipleChoiceBox::addToLayouts()
{
    mLayout->addWidget(titleLabel);
    mLayout->addWidget(box);
    box->setLayout(groupBoxLayout);
    groupBoxLayout->addLayout(searchLayout);
    searchLayout->addWidget(iconSearchLabel);
    searchLayout->addWidget(searchEdit, 1);
    groupBoxLayout->addWidget(listWidget, 1);

    groupBoxLayout->addLayout(buttonsLayout);
    buttonsLayout->addWidget(selectAllButton);
    buttonsLayout->addSpacing(5);
    buttonsLayout->addWidget(unselectAllButton);
}

void QMultipleChoiceBox::slotSearchTextChanged(QString text)
{
    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<MultipleChoiceBox::QMultipleChoiceItem*>
                (listWidget->itemWidget(listWidget->item(i)));

        if (mItem->getInfrotmation().name.contains(text)
                || text.isEmpty()) {
            listWidget->item(i)->setHidden(false);
        }
        else {
            listWidget->item(i)->setHidden(true);
        }
    }
}

void QMultipleChoiceBox::slotSelectAll()
{
    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<MultipleChoiceBox::QMultipleChoiceItem*>
                (listWidget->itemWidget(listWidget->item(i)));
        mItem->selectItem();
    }
}

void QMultipleChoiceBox::slotUnselectAll()
{
    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<MultipleChoiceBox::QMultipleChoiceItem*>
                (listWidget->itemWidget(listWidget->item(i)));
        mItem->unselectItem();
    }
}
