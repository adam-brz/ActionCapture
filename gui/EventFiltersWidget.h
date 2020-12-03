#ifndef EVENTFILTERSWIDGET_H
#define EVENTFILTERSWIDGET_H

#include <QWidget>
#include <QCheckBox>

#include "input/EventFilter.h"

namespace Ui {
class EventFiltersWidget;
}

class EventFiltersWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::EventFiltersWidget *ui;
    QCheckBox *checkboxPrintable;
    QCheckBox *checkboxNonprintable;

    QCheckBox *checkboxMouseClick;
    QCheckBox *checkboxMouseMove;

public:
    explicit EventFiltersWidget(QWidget *parent = nullptr);
    ~EventFiltersWidget();

    EventFilter getFilter() const;

private slots:
    void updateFilters();

private:
    void createLayout();

signals:
    void filtersUpdated(EventFilter);
};

#endif // EVENTFILTERSWIDGET_H
