#include "qsteppercombobox.h"

SalesWidgets::QStepperComboBox::QStepperComboBox(QWidget *parent)
    : QWidget(parent)
{
    setGui();
}

void SalesWidgets::QStepperComboBox::setItems(const QVector<SalesWidgets::StepperComboBox::In> &vector)
{
    for (auto val : vector) {
        comboBoxTypeStep->addItem(val.stepName, QVariant::fromValue(static_cast<int>(val.stepID)));
        countStepMap.insert(val.stepID, val.stepsCount);
    }
    emit(comboBoxTypeStep->activated(comboBoxTypeStep->currentIndex()));
}

SalesWidgets::StepperComboBox::Out SalesWidgets::QStepperComboBox::getSelectedItem()
{
    StepperComboBox::Out output;

    output.stepID = static_cast<StatisticsStep>(comboBoxTypeStep->currentData().toInt());
    output.stepName = comboBoxTypeStep->currentText();
    output.stepCount = comboBoxCountStep->currentData().toInt();

    return output;
}

void SalesWidgets::QStepperComboBox::clear()
{
    comboBoxTypeStep->clear();
    comboBoxCountStep->clear();
}

void SalesWidgets::QStepperComboBox::setGui()
{
    mainLayout = new QVBoxLayout(this);
    box = new QGroupBox(this);
    groupBoxLayout = new QHBoxLayout;
    titleLabelTypeStep = new QLabel(tr("Тип шага"), this);
    comboBoxTypeStep = new QComboBox(this);
    titleLabelCountStep = new QLabel(tr("Значение шага"), this);
    comboBoxCountStep = new QComboBox(this);

    groupBoxLayout->addWidget(titleLabelTypeStep);
    groupBoxLayout->addWidget(comboBoxTypeStep);
    groupBoxLayout->addWidget(titleLabelCountStep);
    groupBoxLayout->addWidget(comboBoxCountStep);

    box->setLayout(groupBoxLayout);
    mainLayout->addWidget(box);

    connect(comboBoxTypeStep, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
            this, [=](){
        StatisticsStep stepType = static_cast<StatisticsStep>(comboBoxTypeStep->currentData().toInt());
        auto iterator = countStepMap.find(stepType);
        comboBoxCountStep->clear();

        for (auto i : iterator.value()) {
            comboBoxCountStep->addItem(QString::number(i), QVariant::fromValue(i));
        }
    });

    box->setAlignment(Qt::AlignTop);
    groupBoxLayout->setAlignment(Qt::AlignTop);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setMargin(0);
}


