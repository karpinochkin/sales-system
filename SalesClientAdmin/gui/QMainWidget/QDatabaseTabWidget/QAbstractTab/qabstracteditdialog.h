#ifndef QABSTRACTEDITDIALOG_H
#define QABSTRACTEDITDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QMessageBox>
#include <QPushButton>
#include "../commonFiles/QDatabaseControl/qdatabaseconrol.h"
#include "../../widgets/QEdit/qedit.h"

using namespace SalesWidgets;

namespace Gui::DatabaseTabs::AbstractTab {

class QAbstractEditDialog : public QDialog
{
    Q_OBJECT
public:
    ~QAbstractEditDialog() = default;

    void addWidget(QWidget *widget)
    {
        mainInfoLayout->addWidget(widget);
    }

    void addWidget(QWidget *widget, int row, int column, int rowSpan, int columnSpan)
    {
        mainInfoLayout->addWidget(widget, row, column, rowSpan, columnSpan);
    }

protected:
    QDatabaseConrol *db;
    QEdit *nameWidget = nullptr;

private:
    QVBoxLayout *main = nullptr;
    QGridLayout *mainInfoLayout = nullptr;

    QGroupBox *box = nullptr;
    QScrollArea *scrollArea = nullptr;

    QVBoxLayout *mainLayout = nullptr;
    QHBoxLayout *buttonsLayout = nullptr;

    QPushButton *saveButton = nullptr;
    QPushButton *cancelButton = nullptr;

protected:
    virtual void paintEvent(QPaintEvent*)
    {
        this->resize(this->width(), this->height());
    }

    QAbstractEditDialog(QDatabaseConrol *control, QWidget *parent = nullptr)
        : QDialog(parent),
          db(control)
    {
        this->setWindowTitle(tr("Добавление"));
        this->createWidgets();
        this->setGui();
        this->addToMainLayout();
        this->connects();
    }

    void createWidgets()
    {
        main = new QVBoxLayout(this);
        box = new QGroupBox(this);
        scrollArea = new QScrollArea(this);

        mainLayout = new QVBoxLayout;
        mainInfoLayout = new QGridLayout();
        buttonsLayout = new QHBoxLayout;

        nameWidget = new QEdit(this);
        saveButton = new QPushButton(tr("Сохранить"), this);
        cancelButton = new QPushButton(tr("Отменить"), this);
    }

    void setGui()
    {
        this->setModal(true);
        this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        this->setMinimumSize(parentWidget()->size() / 2);
        this->setMaximumSize(parentWidget()->size() / 1.3);
        this->resize(this->maximumSize());
        mainLayout->setMargin(0);
        mainLayout->setAlignment(Qt::AlignTop);
        nameWidget->setTitle(tr("Название: "));
        box->setTitle(tr("Внесите изменения: "));
        scrollArea->setWidgetResizable(true);
        buttonsLayout->addWidget(saveButton);
        buttonsLayout->addWidget(cancelButton);
        saveButton->setMinimumWidth(65);
        saveButton->setMinimumHeight(30);
        cancelButton->setMinimumWidth(65);
        cancelButton->setMinimumHeight(30);
    }

    void connects()
    {
        connect(saveButton, &QPushButton::clicked,
                this, &QAbstractEditDialog::slotSaveChanges);
        connect(cancelButton, &QPushButton::clicked,
                this, &QAbstractEditDialog::reject);
    }

    void addToMainLayout()
    {
        mainLayout->addSpacing(20);
        mainInfoLayout->addWidget(nameWidget, 0, 0, 1, 1);
        mainInfoLayout->setAlignment(Qt::AlignTop);
        mainLayout->addLayout(mainInfoLayout);

        box->setLayout(mainLayout);
        scrollArea->setWidget(box);
        main->addWidget(scrollArea);
        main->addLayout(buttonsLayout);
    }

private slots:
    virtual void slotSaveChanges() = 0;
};

}

#endif // QABSTRACTEDITDIALOG_H

