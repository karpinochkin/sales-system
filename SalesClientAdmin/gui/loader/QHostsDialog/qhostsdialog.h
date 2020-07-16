#ifndef QHOSTSDIALOG_H
#define QHOSTSDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>

#include "../commonFiles/QUnNetProtokol/commonunnetworktypes.h"

namespace Gui::Loader {

class QHostsDialog : public QDialog
{
    Q_OBJECT

public:
    static HostInfo getHost(bool *ok = nullptr,
                            QWidget *parent = nullptr);
    static HostInfo getHost(HostInfo host,
                            bool *ok = nullptr,
                            QWidget *parent = nullptr);
    static HostInfo editHost(HostInfo host,
                             bool *ok = nullptr,
                             QWidget *parent = nullptr);

    ~QHostsDialog() = default;

private:
    QGridLayout *mainlayout = nullptr;
    QLabel *labelAddress = nullptr;
    QLineEdit *editAddress = nullptr;
    QLabel *labelPort = nullptr;
    QLineEdit *editPort = nullptr;
    QHBoxLayout *layoutButtons = nullptr;
    QPushButton *buttonOk = nullptr;
    QPushButton *buttonCancel = nullptr;

    QHostsDialog(QWidget *parent = nullptr);
    QHostsDialog(HostInfo host,
                 QWidget *parent = nullptr);
    void createForm();
    void connects();
    void addToWidget();
};

}

#endif // QHOSTSDIALOG_H
