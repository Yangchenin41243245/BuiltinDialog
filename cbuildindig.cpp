#include "cbuildindig.h"
#include <QPrinter>
#include <QPageSetupDialog>
#include <QtPrintSupport/qprinter.h>
#include <QtPrintSupport/qpagesetupdialog.h>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

CBuildinDig::CBuildinDig(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* gridLayout = new QGridLayout;
    displayTextEdit= new QTextEdit(QStringLiteral("Qt的標準通用對話盒")); //產生物件實體於記憶體中,將記憶體的位址存於 displayTextEdit變數
    colorPushBtn = new QPushButton(QStringLiteral("顏色對話盒"));
    errorPushBtn = new QPushButton(QStringLiteral("錯誤訊息盒"));
    filePushBtn = new QPushButton(QStringLiteral("檔案對話盒"));
    fontPushBtn =new QPushButton(QStringLiteral("字體對話盒"));
    inputPushBtn = new QPushButton(QStringLiteral("輸入對話盒"));
    pagePushBtn = new QPushButton(QStringLiteral("頁面設定對話盒"));
    progressPushBtn = new QPushButton(QStringLiteral("進度對話盒"));
    printPushBtn = new QPushButton(QStringLiteral("列印對話盒"));

    //作業部分：文字顏色控制
    textcolorPushBtn = new QPushButton(QStringLiteral("文字顏色對話盒"));

    gridLayout->addWidget (colorPushBtn, 0, 0, 1, 1) ;
    gridLayout->addWidget (errorPushBtn, 0, 1, 1, 1) ;
    gridLayout->addWidget (filePushBtn, 0, 2, 1, 1) ;
    gridLayout->addWidget (fontPushBtn, 1, 0, 1, 1) ;
    gridLayout->addWidget (inputPushBtn, 1, 1, 1, 1) ;
    gridLayout->addWidget (pagePushBtn, 1, 2, 1, 1) ;
    gridLayout->addWidget (progressPushBtn, 2, 0, 1, 1) ;
    gridLayout->addWidget (printPushBtn, 2, 1, 1, 1) ;

    //作業部分：文字顏色控制_按鍵位置
    gridLayout->addWidget (textcolorPushBtn, 2, 2, 1, 1) ;

    gridLayout->addWidget (displayTextEdit, 3, 0, 3, 3) ;

        setLayout (gridLayout) ;
        setWindowTitle(QStringLiteral("內建對話盒展示"));
        resize (400,300) ;

    connect (colorPushBtn, SIGNAL (clicked () ), this, SLOT (doPushBtn () ) ) ;
    connect (errorPushBtn, SIGNAL (clicked () ) , this, SLOT (doPushBtn () ) ) ;
    connect (filePushBtn, SIGNAL (clicked () ) , this, SLOT (doPushBtn () ) ) ;
    connect (fontPushBtn, SIGNAL (clicked () ) , this, SLOT (doPushBtn () ) ) ;
    connect (inputPushBtn, SIGNAL (clicked () ) , this, SLOT (doPushBtn () ) ) ;
    connect (progressPushBtn, SIGNAL (clicked () ) , this, SLOT (doPushBtn () ) ) ;
    connect (pagePushBtn, SIGNAL (clicked () ), this, SLOT (doPushBtn () ) ) ;
    connect (printPushBtn, SIGNAL (clicked () ) , this, SLOT (doPushBtn () ) ) ;

    //作業部分：文字顏色控制_connect
    connect (textcolorPushBtn, SIGNAL (clicked () ) , this, SLOT (doPushBtn () ) ) ;
}

void CBuildinDig:: doPushBtn()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn == colorPushBtn)
    {
        QPalette palette=displayTextEdit->palette ();
        const QColor& color=
        QColorDialog::getColor(palette. color (QPalette::Base),this,QStringLiteral("設定背景顏色"));

        if(color.isValid())
        {
            palette.setColor (QPalette :: Base, color) ;
            displayTextEdit->setPalette (palette);
        }
    }

    //作業部分：文字顏色控制_按鍵功能實作
    if (btn == textcolorPushBtn)
    {
        QPalette palette = displayTextEdit->palette();
        const QColor color =
            QColorDialog::getColor(palette.color(QPalette::Text), this,QStringLiteral("設定文字顏色"));

        if (color.isValid())
        {
            palette.setColor(QPalette::Text, color);
            displayTextEdit->setPalette(palette);
        }
    }

    // cbuildindig.cpp
    if (btn == errorPushBtn)
    {
        if (!errorBox) {
            errorBox = new QErrorMessage(this);   // parent 是 this，Qt 會自動釋放
            errorBox->setWindowTitle(QStringLiteral("錯誤訊息盒"));
        }
        errorBox->showMessage(QStringLiteral("錯誤訊息盒實例xx:"));
        errorBox->showMessage(QStringLiteral("錯誤訊息盒實例yy:"));
        errorBox->showMessage(QStringLiteral("錯誤訊息盒實例zz:"));
    }

    if (btn == filePushBtn)
    {
        QString fileName = QFileDialog :: getOpenFileName (this,
        QStringLiteral("打開檔案"),".",QStringLiteral("任何檔案(*.*)"";;文字檔( *.txt)"";;XML檔( *.xml)"));
        displayTextEdit->setText (fileName);
    }

    if (btn == fontPushBtn)
    {
        bool ok;
        const QFont& font = QFontDialog::getFont (&ok, displayTextEdit->font(), this, QStringLiteral("字體對話盒"));
        if (ok) displayTextEdit->setFont (font) ;
    }

    if (btn == inputPushBtn)
    {
        bool ok;
        QString text = QInputDialog::getText(this,QStringLiteral("輸入對話盒"),QStringLiteral("輸入文字"),QLineEdit::Normal,
        QDir::home ().dirName(),
        &ok);
        if (ok && !text.isEmpty())
        {
            displayTextEdit->setText(text);
        }
    }

    if (btn == pagePushBtn)
    {
        QPrinter printer (QPrinter :: HighResolution) ;
        QPageSetupDialog* dlg = new QPageSetupDialog(&printer, this) ;
        dlg->setWindowTitle(QStringLiteral("頁面設定話方塊"));
        if (dlg->exec() == QDialog::Accepted){}
    }

    if (btn == progressPushBtn)
    {
        QProgressDialog progress(QStringLiteral("正在複製檔案..."),
        QStringLiteral ("A") , 0, 10000, this) ;
        progress.setWindowTitle(QStringLiteral("進度對話方塊"));
        progress. show () ;
        for (int i=0; i<10000; i++)
        {
            progress.setValue (i) ;
            qApp->processEvents ();
            if (progress.wasCanceled () )
            break;
            qDebug() << i;
        }
        progress.setValue (10000);
    }

    if (btn == printPushBtn)
    {
        QPrinter printer(QPrinter::HighResolution) ;
        QPrintDialog dialog(&printer, this);
        if (dialog. exec() != QDialog::Accepted)
            return;
    }
}
CBuildinDig::~CBuildinDig() = default;