#include "qsinglechoicebox.h"

using namespace SalesWidgets;

QSingleChoiceBox::QSingleChoiceBox(QWidget *parent) : QWidget(parent)
{
    this->createWidgets();
    this->setGui();
    this->connects();
    this->addToLayouts();
}

void QSingleChoiceBox::setTitle(const QString &text)
{
    titleLabel->setText(text);
}

void QSingleChoiceBox::setItems(const QVector<SingleChoiceBox::ItemInformation> &itemsInformation)
{
    listWidget->clear();
    for (int i = 0; i < itemsInformation.count(); i++) {
        QListWidgetItem *item = new QListWidgetItem(listWidget);
        listWidget->addItem(item);

        mItem = new SingleChoiceBox::QSingleChoiceBoxItem(itemsInformation.at(i),
                                                           listWidget);
        connect(mItem, &SingleChoiceBox::QSingleChoiceBoxItem::signalItemWasSelected,
                this, &QSingleChoiceBox::slotItemWasSelected);
        item->setSizeHint(mItem->sizeHint());
        listWidget->setItemWidget(item, mItem);
    }

    this->check();
}

void QSingleChoiceBox::setHeight(int min, int max)
{
    this->setMinimumHeight(min);
    this->setMaximumHeight(max);
}

QString QSingleChoiceBox::getTitle() const
{
    return titleLabel->text();
}

SingleChoiceBox::ItemInformation QSingleChoiceBox::getSelectedItem()
{
    SingleChoiceBox::ItemInformation output;

    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<SingleChoiceBox::QSingleChoiceBoxItem*>
                (listWidget->itemWidget(listWidget->item(i)));

        if (mItem->getInformation().status) {
            output = mItem->getInformation();
            break;
        }
    }
    return output;
}

void QSingleChoiceBox::createWidgets()
{
    mainLayout = new QVBoxLayout(this);
    titleLabel = new QLabel(this);

    groupBoxLayout = new QVBoxLayout();
    searchLayout = new QHBoxLayout();

    listWidget = new QListWidget(this);
    box = new QGroupBox(this);
    searchEdit = new QLineEdit(this);
    iconSearchLabel = new QLabel(this);
    iconSearch = new QPixmap(":/images/icons/other/Search.png");
}

void QSingleChoiceBox::setGui()
{
    this->setMinimumHeight(200);
    this->setMaximumHeight(200);

    *iconSearch = iconSearch->scaled(24, 24, Qt::KeepAspectRatio);
    iconSearchLabel->setPixmap(*iconSearch);
}

void QSingleChoiceBox::connects()
{
    connect(searchEdit, &QLineEdit::textEdited,
            this, &QSingleChoiceBox::slotSearchTextChanged);
}

void QSingleChoiceBox::addToLayouts()
{
    mainLayout->addWidget(box);
    box->setLayout(groupBoxLayout);
    groupBoxLayout->addWidget(titleLabel);
    groupBoxLayout->addLayout(searchLayout);
    searchLayout->addWidget(iconSearchLabel);
    searchLayout->addWidget(searchEdit, 1);
    groupBoxLayout->addWidget(listWidget, 1);
}

void QSingleChoiceBox::check()
{
    SingleChoiceBox::ItemInformation info;
    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<SingleChoiceBox::QSingleChoiceBoxItem*>
                (listWidget->itemWidget(listWidget->item(i)));

        if (mItem->getInformation().status == true) {
            info = mItem->getInformation();
            break;
        }
    }

    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<SingleChoiceBox::QSingleChoiceBoxItem*>
                (listWidget->itemWidget(listWidget->item(i)));

        if (mItem->getInformation() != info) {
            mItem->setUnselected();
        }
    }
}

void QSingleChoiceBox::slotItemWasSelected(const SingleChoiceBox::ItemInformation &itemInfo)
{
    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<SingleChoiceBox::QSingleChoiceBoxItem*>
                (listWidget->itemWidget(listWidget->item(i)));

        if (mItem->getInformation() != itemInfo) {
            mItem->setUnselected();
        }
    }

}

void QSingleChoiceBox::slotSearchTextChanged(QString text)
{
    for (int i = 0; i < listWidget->count(); i++) {
        mItem = dynamic_cast<SingleChoiceBox::QSingleChoiceBoxItem*>
                (listWidget->itemWidget(listWidget->item(i)));

        if (mItem->getInformation().name.contains(text)
                || text.isEmpty()) {
            listWidget->item(i)->setHidden(false);
        }
        else {
            listWidget->item(i)->setHidden(true);
        }
    }
}
