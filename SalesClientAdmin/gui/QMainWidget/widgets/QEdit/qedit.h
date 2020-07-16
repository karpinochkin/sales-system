#ifndef QEDIT_H
#define QEDIT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

namespace SalesWidgets {

class QEdit : public QWidget
{
public:
    QEdit(QWidget *parent = nullptr);
    ~QEdit() = default;

    void setTitle(const QString &text);
    void setEditText(const QString &text);
    QString getTitle();
    QString getEditText();

private:
    QVBoxLayout *layout = nullptr;
    QLabel *titleLabel = nullptr;
    QLineEdit *edit = nullptr;

    void createWidgets();
    void addToLayout();

};

}

#endif // QEDIT_H
