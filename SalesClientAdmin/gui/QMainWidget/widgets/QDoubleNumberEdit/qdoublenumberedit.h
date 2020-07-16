#ifndef QDOUBLENUMBEREDIT_H
#define QDOUBLENUMBEREDIT_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QVBoxLayout>

namespace SalesWidgets {

class QDoubleNumberEdit : public QWidget
{
public:
    explicit QDoubleNumberEdit(QWidget *parent = nullptr);
    ~QDoubleNumberEdit() = default;

    void setTitle(const QString &text);
    void setNumber(const double value);
    QString getTitle() const;
    double getNumber() const;

private:
    QVBoxLayout *layout = nullptr;
    QLabel *titleLabel = nullptr;
    QDoubleSpinBox *number = nullptr;

    void createWidgets();
    void addToLayout();
};

}

#endif // QDOUBLENUMBEREDIT_H
