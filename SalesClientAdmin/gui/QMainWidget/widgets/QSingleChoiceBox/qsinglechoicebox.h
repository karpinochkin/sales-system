#ifndef QSINGLECHOICEBOX_H
#define QSINGLECHOICEBOX_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include "qsinglechoiceboxitem.h"

namespace SalesWidgets {

class QSingleChoiceBox : public QWidget
{
    Q_OBJECT
public:
    explicit QSingleChoiceBox(QWidget *parent = nullptr);
    ~QSingleChoiceBox() = default;

    void setTitle(const QString &text);
    void setItems(const QVector<SingleChoiceBox::ItemInformation> &itemsInformation);
    void setHeight(int min, int max);
    QString getTitle() const;
    SingleChoiceBox::ItemInformation getSelectedItem();

private:
    QVBoxLayout *mainLayout = nullptr;
    QLabel *titleLabel = nullptr;
    QVBoxLayout *groupBoxLayout = nullptr;
    QHBoxLayout *searchLayout = nullptr;
    QGroupBox *box = nullptr;
    QLineEdit *searchEdit = nullptr;
    QLabel *iconSearchLabel = nullptr;
    QPixmap *iconSearch = nullptr;

    QListWidget *listWidget = nullptr;
    SingleChoiceBox::QSingleChoiceBoxItem *mItem = nullptr;

    void createWidgets();
    void setGui();
    void connects();
    void addToLayouts();
    void check();

private slots:
    void slotItemWasSelected(const SingleChoiceBox::ItemInformation &);
    void slotSearchTextChanged(QString);

};

}

#endif // QSINGLECHOICEBOX_H
