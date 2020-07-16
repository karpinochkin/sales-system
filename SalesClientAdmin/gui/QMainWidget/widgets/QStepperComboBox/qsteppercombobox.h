#ifndef QSTEPPERCOMBOBOX_H
#define QSTEPPERCOMBOBOX_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include "../commonFiles/SalesSystem/QStatistics/qstatistics.h"

namespace SalesWidgets::StepperComboBox {

struct In {
    StatisticsStep stepID = StatisticsStep::NoneStep;
    QString stepName = "";
    QVector<int> stepsCount{};
};

struct Out {
    StatisticsStep stepID = StatisticsStep::NoneStep;
    QString stepName = "";
    int stepCount = -1;
};

}

namespace SalesWidgets {

class QStepperComboBox : public QWidget
{
    Q_OBJECT
public:
    explicit QStepperComboBox(QWidget *parent = nullptr);
    ~QStepperComboBox() override = default;

    void setItems(const QVector<StepperComboBox::In> &vector);
    StepperComboBox::Out getSelectedItem();
    void clear();

private:
    void setGui();

    QVBoxLayout *mainLayout = nullptr;
    QHBoxLayout *groupBoxLayout = nullptr;
    QGroupBox *box = nullptr;
    QLabel *titleLabelTypeStep = nullptr;
    QComboBox *comboBoxTypeStep = nullptr;

    QLabel *titleLabelCountStep = nullptr;
    QComboBox *comboBoxCountStep = nullptr;

    QMap<StatisticsStep, QVector<int>> countStepMap;
};

}


#endif // QSTEPPERCOMBOBOX_H
