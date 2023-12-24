#ifndef ACTION_H
#define ACTION_H

#include <QWidget>
#include <QFileDialog>
#include <lexical.h>
#include <parser.h>
#include <tool.h>
#include <common.h>
#include <string>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QtDebug>
#include <QTimer>
#include <windows.h>

namespace Ui {
class action;
}

class action : public QWidget
{
    Q_OBJECT

public:
    explicit action(QWidget *parent = nullptr);
    ~action();

private slots:
    void on_exit_clicked();

    void on_lexical_clicked();

    void on_grammar_clicked();

    void on_upload_clicked();

    void on_reset_clicked();

    void on_production_clicked();

    void on_Semantics_clicked();

    void on_Quartuple_clicked();

    void on_ShowTree_clicked();

private:
    Ui::action *ui;
    void browse();
    Parser PS;
    std::string file_path_;
    std::vector<std::pair<int, Quadruple>> semantic_result;
    bool lexical_finished_;
    bool parser_finished_;
    bool file_uploaded_;
    bool semantics_finished;
    std::pair<int, std::vector<token>> is_LC_right;
//    void read_line(std::ifstream &);
    QTimer timer;
    QMessageBox msgBox;
};

#endif // ACTION_H
