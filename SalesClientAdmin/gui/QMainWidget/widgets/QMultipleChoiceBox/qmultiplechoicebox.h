#ifndef QMULTIPLECHOICEBOX_H
#define QMULTIPLECHOICEBOX_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QListWidget>
#include "QMultipleChoiceBoxItem/qmultiplechoiceboxitem.h"

namespace SalesWidgets {

class QMultipleChoiceBox : public QWidget
{
    Q_OBJECT
public:
    explicit QMultipleChoiceBox(QWidget *parent = nullptr);
    ~QMultipleChoiceBox() = default;

    void setTitle(const QString &text);
    void setItems(const QVector<MultipleChoiceBox::ItemInformation> &itemsInformation);
    void setHeight(int min, int max);
    QString getTitle() const;
    QVector<MultipleChoiceBox::ItemInformation> getSelectedItems();
    QVector<MultipleChoiceBox::ItemInformation> getChangedItems();

private:
    QVBoxLayout *mLayout = nullptr;
    QLabel *titleLabel = nullptr;
    QVBoxLayout *groupBoxLayout = nullptr;
    QHBoxLayout *searchLayout = nullptr;
    QHBoxLayout * buttonsLayout = nullptr;

    QGroupBox *box = nullptr;
    QLineEdit *searchEdit = nullptr;
    QLabel *iconSearchLabel = nullptr;
    QPixmap *iconSearch = nullptr;
    QPushButton *selectAllButton = nullptr;
    QPushButton *unselectAllButton = nullptr;

    QListWidget *listWidget = nullptr;
    MultipleChoiceBox::QMultipleChoiceItem *mItem = nullptr;

    void createWidgets();
    void setGui();
    void connects();
    void addToLayouts();

private slots:
    void slotSearchTextChanged(QString);
    void slotSelectAll();
    void slotUnselectAll();
};

}

#endif // QMULTIPLECHOICEBOX_H
