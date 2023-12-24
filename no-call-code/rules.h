#ifndef RULES_H
#define RULES_H

#include <QWidget>
#include <action.h>
#include <mainwindow.h>

namespace Ui {
class rules;
}

class rules : public QWidget
{
    Q_OBJECT

public:
    explicit rules(QWidget *parent = nullptr);
    ~rules();

private slots:
    void on_back_clicked();

    void on_next_clicked();

private:
    Ui::rules *ui;
};

#endif // RULES_H
