#ifndef QSALESCOMBOBOX_H
#define QSALESCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

namespace SalesComboBox {

struct ItemInformation {
    int id = -1;
    QString name = "";

    QString toString() const {
        return "id = "+ QString::number(id) + "; " + "name " + name + ";";
    }
};

class QSalesComboBox : public QWidget
{
    Q_OBJECT
public:
    explicit QSalesComboBox(QWidget *parent = nullptr);
    ~QSalesComboBox() = default;

    void setItems(const QVector<ItemInformation> &items);
    QVector<ItemInformation> getItems() const;
    ItemInformation getSelected() const;
    void setTitle(const QString &text);
    void setButtonText(const QString &text);
    QString getTitle() const;
    void hideTitle() const;
    void enableButton();
    void disableButton();

private:
    QVBoxLayout *mainLayout = nullptr;
    QLabel *titleLabel = nullptr;
    QComboBox *comboBox = nullptr;
    QPushButton *button = nullptr;

    void setGui();

signals:
    void clicked();
    void clickedSendItem(const ItemInformation &item);
};

}


#endif // QSALESCOMBOBOX_H
