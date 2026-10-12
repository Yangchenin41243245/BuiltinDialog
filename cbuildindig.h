#ifndef CBUILDINDIG_H
#define CBUILDINDIG_H

#include <QDialog>
#include <QtWidgets>

class CBuildinDig : public QDialog
{
    Q_OBJECT

public:
    explicit CBuildinDig(QWidget *parent = nullptr);
    ~CBuildinDig() override;

private:
    QTextEdit* displayTextEdit;
    QPushButton* colorPushBtn;
    QPushButton* errorPushBtn;
    QPushButton* filePushBtn;
    QPushButton* fontPushBtn;
    QPushButton* inputPushBtn;
    QPushButton* pagePushBtn;
    QPushButton* progressPushBtn;
    QPushButton* printPushBtn;

    //作業部分：文字顏色控制_qpushbutton定義
    QPushButton* textcolorPushBtn;

    QErrorMessage* errorBox = nullptr;

private slots:
    void doPushBtn();
};
#endif // CBUILDINDIG_H
