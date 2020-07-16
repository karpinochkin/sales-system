#include "qstatisticschoicedialog.h"

void QStatisticsChoiceDialog::setTitle(const QString &title)
{
    comboBox->setTitle(title);
}

void QStatisticsChoiceDialog::setItems(QVector<SalesComboBox::ItemInformation> &items)
{
    comboBox->setItems(items);
}

SalesComboBox::ItemInformation QStatisticsChoiceDialog::show(const QString &title,
                                                             QVector<SalesComboBox::ItemInformation> &items,
                                                             bool *result,
                                                             QWidget *parent)
{
    SalesComboBox::ItemInformation output;
    QStatisticsChoiceDialog dlg(title, items, parent);
    int answer = dlg.exec();

    if (answer == QDialog::Accepted) {
        output.id = dlg.information.id;
        output.name = dlg.information.name;

        *result = true;
    }
    else {
        *result = false;
    }
    return output;
}

QStatisticsChoiceDialog::QStatisticsChoiceDialog(const QString &title,
                                                 QVector<SalesComboBox::ItemInformation> &items,
                                                 QWidget *parent)
    : QDialog(parent)
{
    this->setGui();
    this->setTitle(title);
    this->setItems(items);
}

void QStatisticsChoiceDialog::setGui()
{
    this->setWindowTitle(tr("Сделайте выбор"));
    mainLayout = new QVBoxLayout(this);
    comboBox = new SalesComboBox::QSalesComboBox(this);
    connect(comboBox, &SalesComboBox::QSalesComboBox::clicked,
            this, [=](){
        information = comboBox->getSelected();
        this->accept();
    });
    comboBox->setButtonText(tr("Выбрать"));

    mainLayout->addWidget(comboBox);

    this->setModal(true);
    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setMinimumSize(parentWidget()->size() / 2);
    this->setMaximumSize(parentWidget()->size() / 1.3);
    this->resize(this->maximumSize());
    mainLayout->setMargin(0);
}
