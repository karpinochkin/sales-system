#ifndef QSINGLECHOICEBOXITEM_H
#define QSINGLECHOICEBOXITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>

namespace SalesWidgets::SingleChoiceBox {

struct ItemInformation
{
    int id = -1;
    QString name = "";
    bool status = false;

    QString toString() {
        return "id: " + QString::number(id) + ";"
                + "name: " + name + ";"
                + "status: " + status + ";";
    }

    bool operator != (const ItemInformation &item) {
        if (this->id == item.id
                && this->name == item.name
                && this->status == item.status) {
            return false;
        }
        return true;
    }
};


class QSingleChoiceBoxItem : public QWidget
{
    Q_OBJECT
public:
    explicit QSingleChoiceBoxItem(const SingleChoiceBox::ItemInformation &item,
                                  QWidget *parent = nullptr);
    SingleChoiceBox::ItemInformation getInformation();
    void setSelected();
    void setUnselected();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *) override;

private:
    SingleChoiceBox::ItemInformation item;

    QHBoxLayout *mainLayout = nullptr;
    QLabel *itemName = nullptr;
    QRadioButton *itemRadioButton = nullptr;

    void setGui();

private slots:
    void select();

signals:
    void signalItemWasSelected(const SingleChoiceBox::ItemInformation &);
};

}

#endif // QSINGLECHOICEBOXITEM_H
