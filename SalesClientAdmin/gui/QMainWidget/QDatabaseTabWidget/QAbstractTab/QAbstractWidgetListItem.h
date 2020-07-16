#ifndef QABSTRACTWIDGETLISTITEM_H
#define QABSTRACTWIDGETLISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QMenu>
#include "../commonFiles/SalesSystem/QSalesObjects/qsalesobjects.h"

namespace Gui::DatabaseTabs::AbstractTab {

class QAbstractWidgetListItem : public QWidget
{
    Q_OBJECT
public:
    ~QAbstractWidgetListItem() = default;

    void updateDisplayInformation(const QString &name, const QByteArray &pictureData)
    {
        this->setItemName(name);
        this->setItemPicture(pictureData);
    }

    QString getItemName() const
    {
        return itemName;
    }

private:
    QLabel *mainLabel = nullptr;
    QLabel *nameLabel = nullptr;
    QVBoxLayout *layout = nullptr;

    QString itemName;
    QByteArray itemPictureData;

    QAction *actionRemoveItem = nullptr;

protected:
    QAbstractWidgetListItem(const QString &pictureName,
                            const QByteArray &pictureData,
                            bool isContextMenuEnable,
                            QWidget *parent = nullptr)
        : QWidget(parent),
          itemName(pictureName),
          itemPictureData(pictureData)
    {
        this->createWidgets();
        this->setGui();
        this->addToLayouts();
        this->update();
        this->contextMenu(isContextMenuEnable);
    }

    void contextMenu(bool isContextMenuEnable)
    {
        if (isContextMenuEnable) {
            setContextMenuPolicy(Qt::CustomContextMenu);
            connect(this, &QAbstractWidgetListItem::customContextMenuRequested,
                    this, &QAbstractWidgetListItem::slotShowMenuContext);
        }
    }

    QByteArray getItemPictureData() const
    {
        return itemPictureData;
    }

    void setItemName(const QString &text)
    {
        if (itemName != "") {
            itemName = text;
            this->updateDisplayText();
        }
    }

    void setItemPicture(const QByteArray &value)
    {
        if (value != "") {
            itemPictureData = value;
            this->updateDisplayPicture();
        }
    }

    virtual void updateInformation()
    {
        this->updateDisplayInformation();
    }

protected:
    virtual void paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setBrush(QBrush(QColor(168,
                                       228,
                                       255,
                                       50)));
        QRectF rectangle(5, 70, width() - 5, height() - 70);
        painter.drawRoundedRect(rectangle, 100, 100);
    }

    virtual void mouseDoubleClickEvent(QMouseEvent*) = 0;

private:
    void createWidgets()
    {
        layout = new QVBoxLayout(this);
        nameLabel = new QLabel(this);
        mainLabel = new QLabel(this);
    }

    void setGui()
    {
        this->updateDisplayInformation();
        nameLabel->setAlignment(Qt::AlignCenter);
        nameLabel->setMinimumHeight(60);
        nameLabel->setFont(QFont("Sans",11));
        nameLabel->setWordWrap(true);
        mainLabel->setAlignment(Qt::AlignCenter);
        mainLabel->setWordWrap(true);
        mainLabel->setMinimumSize(130,120);
    }

    void addToLayouts()
    {
        layout->addWidget(nameLabel);
        layout->addWidget(mainLabel);
    }

    void updateDisplayInformation()
    {
        this->updateDisplayText();
        this->updateDisplayPicture();
    }

    void updateDisplayText()
    {
        if (itemName != "") {
            nameLabel->setText(itemName);
            mainLabel->setText(itemName);
        }
    }

    void updateDisplayPicture()
    {
        if (itemPictureData != "") {
            QPixmap pixmap;
            pixmap.loadFromData(itemPictureData);
            pixmap = pixmap.scaled(135, 135, Qt::KeepAspectRatio);
            mainLabel->setPixmap(pixmap);
        }
    }

signals:
    void signalEdit(QSalesObjects&);
    void signalRemove(int id);

protected slots:
    virtual void sendRemoveSignal() = 0;

    void slotShowMenuContext(QPoint pos)
    {
        QMenu contextMenu(tr("Menu"),this);

        actionRemoveItem = new QAction(tr("Delete"),this);
        connect(actionRemoveItem, &QAction::triggered,
                this, &QAbstractWidgetListItem::sendRemoveSignal);
        contextMenu.addAction(actionRemoveItem);

        contextMenu.exec(mapToGlobal(pos));
    }

};

}

#endif // QABSTRACTWIDGETLISTITEM_H
