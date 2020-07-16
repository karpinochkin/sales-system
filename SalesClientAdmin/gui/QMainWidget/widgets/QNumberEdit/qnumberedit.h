#ifndef QNUMBEREDIT_H
#define QNUMBEREDIT_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

namespace SalesWidgets {

class QNumberEdit : public QWidget
{
public:
    explicit QNumberEdit(QWidget *parent = nullptr);
    ~QNumberEdit() = default;

    void setTitle(const QString &text);
    void setNumber(const int value);
    QString getTitle() const;
    int getNumber() const;

private:
    QVBoxLayout *layout = nullptr;
    QLabel *titleLabel = nullptr;
    QSpinBox *number = nullptr;

    void createWidgets();
    void addToLayout();

};

}

#endif // QNUMBEREDIT_H
