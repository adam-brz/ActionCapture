#include "EventFiltersWidget.h"
#include "ui_EventFiltersWidget.h"

#include <QVBoxLayout>

EventFiltersWidget::EventFiltersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventFiltersWidget)
{
    ui->setupUi(this);

    checkboxPrintable = new QCheckBox(tr("Printable (eg. A, 6)"), this);
    checkboxNonprintable = new QCheckBox(tr("Non-printable (eg. Enter, Esc)"), this);

    checkboxPrintable->setChecked(true);
    checkboxNonprintable->setChecked(true);

    checkboxMouseClick = new QCheckBox(tr("Click"), this);
    checkboxMouseMove = new QCheckBox(tr("Move"), this);

    checkboxMouseClick->setChecked(true);
    checkboxMouseMove->setChecked(true);

    static const std::function<void(int)> update = [=](int){updateFilters();};

    connect(ui->mouseBox, &QGroupBox::clicked, update);
    connect(ui->keyboardBox, &QGroupBox::clicked, update);

    connect(checkboxPrintable, &QCheckBox::stateChanged, update);
    connect(checkboxNonprintable, &QCheckBox::stateChanged, update);
    connect(checkboxMouseClick, &QCheckBox::stateChanged, update);
    connect(checkboxMouseMove, &QCheckBox::stateChanged, update);

    createLayout();
}

void EventFiltersWidget::createLayout()
{
    QVBoxLayout *keyboardFilters = new QVBoxLayout;
    keyboardFilters->addWidget(checkboxPrintable);
    keyboardFilters->addWidget(checkboxNonprintable);
    ui->keyboardBox->setLayout(keyboardFilters);

    QVBoxLayout *mouseFilters = new QVBoxLayout;
    mouseFilters->addWidget(checkboxMouseClick);
    mouseFilters->addWidget(checkboxMouseMove);
    ui->mouseBox->setLayout(mouseFilters);
}

EventFiltersWidget::~EventFiltersWidget()
{
    delete ui;
}

EventFilter EventFiltersWidget::getFilter() const
{
    EventFilter filter;

    filter.printable = checkboxPrintable->isChecked() &&
                         ui->keyboardBox->isChecked();

    filter.nonprintable = checkboxNonprintable->isChecked() &&
                         ui->keyboardBox->isChecked();


    filter.mouseMove = checkboxMouseMove->isChecked() &&
                         ui->mouseBox->isChecked();

    filter.mousePress = checkboxMouseClick->isChecked() &&
                         ui->mouseBox->isChecked();

    return filter;
}

void EventFiltersWidget::updateFilters()
{
    emit filtersUpdated(getFilter());
}
