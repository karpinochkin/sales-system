#include "qstatisticstabwidget.h"

QStatisticsTabWidget::QStatisticsTabWidget(QSettings *settings, QNetManager *netManager,
                                           QWidget *parent)
    : QWidget(parent),
      networkManager(netManager),
      settings(settings),
      m_moneyStatistics(tr("Выручка (сравнение точек продаж)")),
      m_numberSoldProductsForPointSale(tr("Количество проданных товаров (для конкретной точки продаж)")),
      m_numberSoldProduct(tr("Количество продаж конкретного товара (сравнение точек продаж)")),
      m_moneyStatisticsForUsers(tr("Выручка (сравнение пользователей)"))
{
    comboBoxItems.push_back(m_moneyStatistics);
    comboBoxItems.push_back(m_moneyStatisticsForUsers);
    comboBoxItems.push_back(m_numberSoldProductsForPointSale);
    comboBoxItems.push_back(m_numberSoldProduct);

    this->loadSettings();
    this->createWidgets();
    this->fillChartList();
    this->setGui();
    this->connects();
    this->addToLayout();
//    this->fillStepperComboBox();
    this->refillStepperComboBox();
}


QStatisticsTabWidget::~QStatisticsTabWidget()
{

}

void QStatisticsTabWidget::createWidgets()
{
    mainLayout = new QVBoxLayout(this);
    calendarWidget = new QSalesCalendarInterval(this);
    graphComboBox = new SalesComboBox::QSalesComboBox(this);
    stepperComboBox = new QStepperComboBox(this);
    chartView = new QSalesChartView(this);
    boxLayout = new QHBoxLayout;
}

void QStatisticsTabWidget::fillChartList()
{
    QVector<SalesComboBox::ItemInformation> chartItems;

    int id = 1;
    for (auto comboBoxitem : comboBoxItems) {
        SalesComboBox::ItemInformation item;
        item.id = id;
        item.name = comboBoxitem;
        chartItems.push_back(item);
        id++;
    }

    graphComboBox->setItems(chartItems);
}

void QStatisticsTabWidget::fillStepperComboBox()
{
    QVector<StepperComboBox::In> inVec;
    StepperComboBox::In in;

    in.stepID = StatisticsStep::Day;
    in.stepName = tr("День");
    in.stepsCount = {1, 3, 5, 7};
    inVec.push_back(in);

    in.stepID = StatisticsStep::Hour;
    in.stepName = tr("Час");
    in.stepsCount = {1, 3, 5, 12, 24};
    inVec.push_back(in);

    in.stepID = StatisticsStep::Week;
    in.stepName = tr("Неделя");
    in.stepsCount = {1, 2, 3, 4};
    inVec.push_back(in);

    in.stepID = StatisticsStep::Month;
    in.stepName = tr("Месяц");
    in.stepsCount = {1, 3, 6, 12};
    inVec.push_back(in);

    in.stepID = StatisticsStep::Year;
    in.stepName = tr("Год");
    in.stepsCount = {1, 2, 5};
    inVec.push_back(in);

    stepperComboBox->setItems(inVec);
}

void QStatisticsTabWidget::refillStepperComboBox()
{
    stepperComboBox->clear();

    QVector<StepperComboBox::In> inVec;
    StepperComboBox::In hours;
    hours.stepID = StatisticsStep::Hour;
    hours.stepName = tr("Час");
    hours.stepsCount = {1, 3, 5, 12, 24};

    StepperComboBox::In days;
    days.stepID = StatisticsStep::Day;
    days.stepName = tr("День");
    days.stepsCount = {1, 3, 5, 7};

    StepperComboBox::In weeks;
    weeks.stepID = StatisticsStep::Week;
    weeks.stepName = tr("Неделя");
    weeks.stepsCount = {1, 2, 3, 4};

    StepperComboBox::In months;
    months.stepID = StatisticsStep::Month;
    months.stepName = tr("Месяц");
    months.stepsCount = {1, 3, 6, 12};

    StepperComboBox::In years;
    years.stepID = StatisticsStep::Year;
    years.stepName = tr("Год");
    years.stepsCount = {1, 2, 5};

    qint64 countDays = calendarWidget->getInterval();

    if (countDays <= 5) {
        inVec.push_back(hours);
        inVec.push_back(days);
        inVec.push_back(weeks);
        inVec.push_back(months);
        inVec.push_back(years);
    }
    else if (countDays <= 31) {
        inVec.push_back(days);
        inVec.push_back(weeks);
        inVec.push_back(months);
        inVec.push_back(years);
    }
    else if (countDays <= 183) {
        inVec.push_back(weeks);
        inVec.push_back(months);
        inVec.push_back(years);
    }
    else if (countDays <= 366) {
        inVec.push_back(months);
        inVec.push_back(years);
    }
    else {
        inVec.push_back(years);
    }

    stepperComboBox->setItems(inVec);
}

void QStatisticsTabWidget::setGui()
{
    graphComboBox->hideTitle();
    graphComboBox->setButtonText(tr("Построить график"));
    calendarWidget->setMaximumHeight(70);
    calendarWidget->setStartDate(QDate::currentDate().addDays(-7));
    graphComboBox->setMaximumHeight(70);
    mainLayout->setAlignment(Qt::AlignTop);

    boxLayout->setMargin(0);
    boxLayout->setAlignment(Qt::AlignTop);

    mainLayout->setMargin(0);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::RubberBand::HorizontalRubberBand);
}

void QStatisticsTabWidget::connects()
{
    connect(graphComboBox, &SalesComboBox::QSalesComboBox::clicked,
            this, &QStatisticsTabWidget::getStatistics);
    connect(networkManager, &QNetManager::signalStatisticsLoaded,
            this, &QStatisticsTabWidget::printStatistics);
    connect(calendarWidget, &SalesWidgets::QSalesCalendarInterval::startDateChanged,
            this, &QStatisticsTabWidget::refillStepperComboBox);
    connect(calendarWidget, &SalesWidgets::QSalesCalendarInterval::endDateChanged,
            this, &QStatisticsTabWidget::refillStepperComboBox);
}

void QStatisticsTabWidget::addToLayout()
{
    mainLayout->addLayout(boxLayout);
    boxLayout->addWidget(calendarWidget);
    boxLayout->addWidget(stepperComboBox);
    mainLayout->addWidget(graphComboBox);
    mainLayout->addWidget(chartView, 1);
}

void QStatisticsTabWidget::loadSettings()
{
    isNotFirstStart = settings->value("/SalesAdminClient/isNotFirstStart").toBool();
}

void QStatisticsTabWidget::saveSettings()
{
    settings->setValue("/SalesAdminClient/isNotFirstStart", isNotFirstStart);
}

void QStatisticsTabWidget::helpMessageBox()
{
    if (!isNotFirstStart) {
        QMessageBox::information(this, tr("Подсказки"),
                                 tr("1. Для получения более точной информации о значении вы можете дважды кликнуть левой кнопкой мыши по макреру данных. \n\n"
                                    "2. Вы можете выделить нужные вам дни левой кнопкой мыши для приближения. \n\n"
                                    "3. Вы можете дважды кликнуть правой кнопкой мыши в области графика для отдаления."),
                                 QMessageBox::StandardButton::Ok);
        isNotFirstStart = true;
        saveSettings();
    }
}

///void QStatisticsTabWidget::printMoneyForUsersGraph()
///{
///    GraphicsPrinter::GraphicsPrinterInformation info {
///        calendarWidget->getStartDate(),
///                calendarWidget->getEndDate(),
///                calendarWidget->getInterval(),
///                m_moneyStatisticsForUsers,
///                tr("руб.")
///    };

///    auto countPrinter = new GraphicsPrinter::
///            QMoneyForUsersGraphicsPrinter(networkManager, this);
///    countPrinter->Print(info, chartView);
///}

void QStatisticsTabWidget::getStatistics()
{
    this->helpMessageBox();

    if (!calendarWidget->isDateValid()) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Вы выбрали некорректные даты"),
                             QMessageBox::StandardButton::Ok);
        return;
    }

    if (!networkManager->isAuthorized()) {
        QMessageBox::warning(this, tr("Ошибка"),
                             tr("Нет соединения с сервером!"),
                             QMessageBox::StandardButton::Ok);
        return;
    }

    QString selected = graphComboBox->getSelected().name;
    graphComboBox->disableButton();

    StatisticsInput input;
    auto i = stepperComboBox->getSelectedItem();
    input.startDate.setDate(calendarWidget->getStartDate());
    input.endDate.setDate(calendarWidget->getEndDate());
    input.step = static_cast<StatisticsStep>(i.stepID);
    input.stepValue = i.stepCount;

    if (selected == m_moneyStatistics) {
        input.type = StatisticsType::Money;

        graphTitle = m_moneyStatistics;
        graphAsixYTitle = "руб";
        networkManager->CommandsToServer()->statistics->load(input);
    }

    else if (selected == m_numberSoldProductsForPointSale) {
        input.type = StatisticsType::NumberSoldProductsForPointSale;
        input.id = getSelectedPointSaleId();

        graphTitle = m_numberSoldProductsForPointSale;
        graphAsixYTitle = "шт";
        networkManager->CommandsToServer()->statistics->load(input);
    }

    else if (selected == m_numberSoldProduct) {
        input.type = StatisticsType::NumberSoldProduct;
        input.id = getSelectedProductId();

        graphTitle = m_numberSoldProduct;
        graphAsixYTitle = "шт";
        networkManager->CommandsToServer()->statistics->load(input);
    }

    else if (selected == m_moneyStatisticsForUsers) {
        input.type = StatisticsType::MoneyUsers;

        graphTitle = m_moneyStatisticsForUsers;
        graphAsixYTitle = "руб";
        networkManager->CommandsToServer()->statistics->load(input);
    }
}

void QStatisticsTabWidget::printStatistics(const QVector<QStatistics> &statistics, double maxValue)
{
    graphComboBox->enableButton();

    QGraphicsPrinter *printer = new QGraphicsPrinter(this);
    printer->Print(statistics, maxValue, graphTitle, graphAsixYTitle, chartView);
    delete printer;

    graphTitle = "";
    graphAsixYTitle = "";
}

int QStatisticsTabWidget::getSelectedPointSaleId()
{
    bool result = false;
    QVector<QPointSale> pointSales = networkManager->DatabaseCommands()
            ->pointSale->getPointSales();
    QVector<SalesComboBox::ItemInformation> items;

    for (auto pointSale : pointSales) {
        SalesComboBox::ItemInformation item;
        item.id = pointSale.id;
        item.name = pointSale.name;
        items.push_back(item);
    }

    SalesComboBox::ItemInformation info = QStatisticsChoiceDialog::show(tr("Выберите точку продаж"),
                                                                        items,
                                                                        &result,
                                                                        this);
    return info.id;
}

int QStatisticsTabWidget::getSelectedProductId()
{
    bool result = false;
    QVector<QProduct> products = networkManager->DatabaseCommands()
            ->product->getProducts();
    QVector<SalesComboBox::ItemInformation> items;

    for (auto product : products) {
        SalesComboBox::ItemInformation item;
        item.id = product.id;
        item.name = product.name;
        items.push_back(item);
    }

    SalesComboBox::ItemInformation info = QStatisticsChoiceDialog::show(tr("Выберите товар"),
                                                                        items,
                                                                        &result,
                                                                        this);
    return info.id;
}

int QStatisticsTabWidget::getSelectedUserId()
{
    bool result = false;
    QVector<QUser> users = networkManager->DatabaseCommands()
            ->user->getUsers();
    QVector<SalesComboBox::ItemInformation> items;

    for (auto user : users) {
        SalesComboBox::ItemInformation item;
        item.id = user.id;
        item.name = user.surname;
        items.push_back(item);

    }
    SalesComboBox::ItemInformation info = QStatisticsChoiceDialog::show(tr("Выберите пользователя"),
                                                                        items,
                                                                        &result,
                                                                        this);
    return info.id;
}
