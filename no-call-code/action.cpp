#include "action.h"
#include "ui_action.h"
#include <QScrollBar>

action::action(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::action)
{
    ui->setupUi(this);
    lexical_finished_ = 0;
    file_uploaded_ = 0;
    parser_finished_ = 0;
    semantics_finished = 0;
    this->ui->content->setReadOnly(true);

    this->ui->content->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QFont font("Arial", 12);  // Font family: Arial, Font size: 12

    // Set additional font properties if needed
    font.setBold(true);  // Set the font to bold

    // Apply the font to the text edit widget
    this->ui->content->setFont(font);

    this->setStyleSheet("background-color: #BFEFFF;");

    this->ui->filePath->setFont(font);
    this->ui->label->setFont(font);
    this->ui->exit->setFont(font);
    this->ui->reset->setFont(font);
    this->ui->upload->setFont(font);
    this->ui->grammar->setFont(font);
    this->ui->lexical->setFont(font);
    this->ui->production->setFont(font);

    this->ui->content->setStyleSheet("background-color: #E0E0E0;");
    this->ui->filePath->setStyleSheet("background-color: #E0E0E0;");

}

action::~action()
{
    delete ui;
}

void action::on_exit_clicked()
{
    this->close();
}

void action::on_lexical_clicked()
{
    if(!file_uploaded_) {
        msgBox.setText("请先上传文件");
        msgBox.exec();
        return;
    }
    // 开始进行词法分析
    std::string input = file_to_str(file_path_);

//    std::cout<<input<<std::endl;

    Lexical LC;
    is_LC_right = LC.Analyze(input);

    if(is_LC_right.first > 0){
        lexical_finished_ = 1;
        msgBox.setText("词法分析成功");
        msgBox.exec();
        // 打开文本文件
        QFile file("./lexical/lexical-result.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Could not open file";
            return ;
        }

        // 创建文本流
        QTextStream in(&file);
        QString fileContent = in.readAll();
        this->ui->content->setText(fileContent);

        /* 结束演示 */
        this->ui->label->setText("词法分析成功结果");
    }
    else {
        msgBox.setText("词法分析失败");
        msgBox.exec();
        QFile file("./lexical/lexical-wrong.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Could not open file";
            return ;
        }

        // 创建文本流
        QTextStream in(&file);
        QString fileContent = in.readAll();
        this->ui->content->setText(fileContent);
        this->ui->label->setText("词法分析错误信息");
        return;
    }
}

void action::on_grammar_clicked()
{

    if(lexical_finished_ != true) {
        msgBox.setText("请先完成词法分析");
        msgBox.exec();
        return;
    }
    // 开始进行语法分析
    PS.load_argument_def();
    PS.load_production();
    PS.show_production();
    PS.get_first();
    PS.get_item_group();
    PS.show_item_group();
    PS.get_LR1_table();
    PS.show_LR1_table();
    bool parser_success = PS.Analyse(is_LC_right.second);
    if(parser_success) {
        parser_finished_ = true;
        // 打开文本文件
        QFile file("./parser/parser-result.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Could not open file";
            return ;
        }

        // 创建文本流
        QTextStream in(&file);
        QString fileContent = in.readAll();
        this->ui->content->setText(fileContent);

        /* 提示语法分析成功 */
        msgBox.setText("语法分析成功");
        msgBox.exec();
        /* 结束提示 */
        this->ui->label->setText("语法分析过程展示");
        return;
    }
    else {
        msgBox.setText("语法分析失败");
        msgBox.exec();

        QFile file("./parser/parser-wrong.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Could not open file";
            return ;
        }

        // 创建文本流
        QTextStream in(&file);
        QString fileContent = in.readAll();
        this->ui->content->setText(fileContent);
        this->ui->label->setText("语法分析错误信息");
    }

    return;
}

/* 选取文件 */
void action::browse()
{
    QString str = QFileDialog::getOpenFileName(this, "open file", "/", "textfile(*.txt)");
    this->ui->filePath->setText(str.toUtf8());
    file_path_ = str.toStdString();
}

void action::on_upload_clicked()
{
    // 上传文件
    browse();
    file_uploaded_ = true;
}

void action::on_reset_clicked()
{
    action *new_window = new action();
    this->close();
    new_window->show();
}

void action::on_production_clicked()
{
    if(!parser_finished_) {
        msgBox.setText("请先完成语法分析");
        msgBox.exec();
    }
    QFile file("./parser/parser-production.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open file";
        return ;
    }
    // 创建文本流
    QTextStream in(&file);
    QString fileContent = in.readAll();

    this->ui->content->setText(fileContent);
    this->ui->label->setText("语法产生式展示");
}

void action::on_Semantics_clicked()
{
    if(!parser_finished_) {
        msgBox.setText("请先完成语法分析");
        msgBox.exec();
        return;
    }
    int is_SM_right = PS.semanticAnalyse();
    if (is_SM_right < 0) {
        msgBox.setText("语义分析失败");
        msgBox.exec();
        QFile file("./parser/parser-wrong.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Could not open file";
            return ;
        }

        // 创建文本流
        QTextStream in(&file);
        QString fileContent = in.readAll();
        this->ui->content->setText(fileContent);
        this->ui->label->setText("语义分析错误信息");
        return;
    }
    semantics_finished = true;
    semantic_result = PS.get_Q_ruple();
    msgBox.setText("语义分析成功");
    msgBox.exec();
}

void action::on_Quartuple_clicked()
{
    if(!semantics_finished) {
        msgBox.setText("请先完成语义分析");
        msgBox.exec();
        return;
    }
    QFile file("./parser/parser-4_ruple.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open file";
        return ;
    }
    // 创建文本流
    QTextStream in(&file);
    QString fileContent = in.readAll();

    this->ui->content->setText(fileContent);
    this->ui->label->setText("四元式展示");
}

void action::on_ShowTree_clicked()
{
    if(!semantics_finished) {
        msgBox.setText("请先完成语义分析");
        msgBox.exec();
        return;
    }
    QFile file("./parser/parser-grammar_tree.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open file";
        return ;
    }
    // 创建文本流
    QTextStream in(&file);
    QString fileContent = in.readAll();

    this->ui->content->setText(fileContent);
    this->ui->label->setText("语法树展示");

}
