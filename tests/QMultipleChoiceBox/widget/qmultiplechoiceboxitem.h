#ifndef QMULTIPLECHOICEBOXITEM_H
#define QMULTIPLECHOICEBOXITEM_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QListWidget>

namespace MultipleChoiceBox {

struct ItemInformation
{
    int id = -1;
    QString name = "";
    bool status = false;
    bool isWasChanged = false;
};

class QMultipleChoiceItem: public QWidget
{
    Q_OBJECT
public:
    explicit QMultipleChoiceItem(const ItemInformation &item,
                           QWidget *parent = nullptr);
    ItemInformation getInfrotmation();
    void selectItem();
    void unselectItem();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *) override;

private:
    ItemInformation item;

    QHBoxLayout *mainLayout = nullptr;
    QLabel *itemName = nullptr;
    QCheckBox *itemCheckBox = nullptr;

    void setGui();
    void changeStatus(bool status);
private slots:
    void slotCheckBoxChanged();
};

}
#endif // QMULTIPLECHOICEBOXITEM_H
