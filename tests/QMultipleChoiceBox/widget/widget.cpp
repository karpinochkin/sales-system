#include "widget.h"
#include "QVBoxLayout"
#include "QPushButton"
#include "QDebug"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QVBoxLayout *m = new QVBoxLayout(this);
    QPushButton *b = new QPushButton("ok", this);

    QVector<MultipleChoiceBox::ItemInformation> vec;

    for (int i = 0; i < 10; i++) {
        MultipleChoiceBox::ItemInformation info;
        info.id = i + 1;
        info.name = QString::number(i+1);

        if( i < 3) {
            info.status = true;
        } else {
            info.status = false;
        }
        info.isWasChanged = false;

        vec.push_back(info);
    }



    QMultipleChoiceBox *box = new QMultipleChoiceBox(this);
    box->setItems(vec);

    m->addWidget(box);
    m->addWidget(b);

    connect(b, &QPushButton::clicked,
            this, [=](){
        qDebug() << "CHANGED: ";
        for (int i = 0; i < box->getChangedItems().size(); i++) {
            qDebug() << box->getChangedItems().at(i).name;
        }
        qDebug() << "SELECTED: ";
        for (int i = 0; i < box->getSelectedItems().size(); i++) {
            qDebug() << box->getSelectedItems().at(i).name;
        }
    });

}

Widget::~Widget()
{
}

