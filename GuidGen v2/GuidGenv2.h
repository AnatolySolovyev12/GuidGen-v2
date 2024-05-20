#pragma once

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QApplication>
#include <Qlabel>
#include <QMainWindow>
#include <QStatusBar>


class GuidGen : public QWidget {

    Q_OBJECT

public:
    GuidGen(QWidget* parent = 0);

private slots:
    void addSomeIdFunc();
    void removeItem();
    void clearItems();
    void addSomeGuids();
    void copeAllID();
    QString RandomGenerateID();

private:
    QClipboard* pcb; // объект для работы с буффером
    int counter;
    QString countOfId;
    QString countOfIdCurrent;

    QLabel* countLabel;
    QListWidget* lw;
    QPushButton* addSSomeID;
    QPushButton* remove;
    QPushButton* removeAll;
    QPushButton* addID;
    QPushButton* copyAll;
    QStatusBar* statusBar;

};