#include "GuidGenv2.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QTime>
#include <cstdlib> // ��� ������� rand(), srand(a), exit().
#include <ctime> // ��� ������� time(a)
#include <QClipboard> // ��� ������ � ������� ������
#include <QStatusBar>
#include <functional>
#include <QSplitter>


GuidGen::GuidGen(QWidget* parent) : QWidget(parent) {

    srand(static_cast<unsigned int>(time(0)));

    QVBoxLayout* vbox = new QVBoxLayout();
    QHBoxLayout* hbox = new QHBoxLayout(this);

    countOfId = ("count of ID's: ");
    counter = 0;
    countOfIdCurrent = countOfId + countOfIdCurrent.setNum(counter);

    countLabel = new QLabel(countOfIdCurrent, this);
    lw = new QListWidget(this);
    addID = new QPushButton("Add Guid", this);
    addSSomeID = new QPushButton("Add Some Guids", this);
    remove = new QPushButton("Remove", this);
    removeAll = new QPushButton("Remove All", this);
    copyAll = new QPushButton("Copy All", this);
    statusBar = new QStatusBar(lw);

    pcb = QApplication::clipboard(); // ��������������� ������ ��� ������ � �������

    //vbox->addStretch(50); // ��������� ��������������� ������ ������ ������� (���� ���������).
    vbox->setSpacing(10); // ���������� ����� ��������� ������ ������������� �����
    vbox->addStretch(1); // ������������ �� ���� ��� ���� ����
    vbox->addWidget(addID);
    vbox->addWidget(addSSomeID);
    vbox->addWidget(remove);
    vbox->addWidget(removeAll);
    vbox->addWidget(copyAll);
    vbox->addWidget(statusBar);
    vbox->addStretch(1); // ������������ �� ���� ��� ���� ����
    vbox->addWidget(countLabel);

    hbox->addWidget(lw);
    hbox->addSpacing(15);// ���������� ����� ��������� ������ ��������������� �����
    hbox->addLayout(vbox);

    connect(addSSomeID, &QPushButton::clicked, this, &GuidGen::addSomeIdFunc);
    connect(remove, &QPushButton::clicked, this, &GuidGen::removeItem);
    connect(removeAll, &QPushButton::clicked, this, &GuidGen::clearItems);
    connect(addID, &QPushButton::clicked, this, &GuidGen::addSomeGuids);
    connect(copyAll, &QPushButton::clicked, this, &GuidGen::copeAllID);

    //  connect(pcb, SIGNAL(dataChanged()), this, SLOT(paste())); // �������������. ��� ��� �������� � ������������. 

    setLayout(hbox); // ��� ����� ��������� �� ��������� 2 ������� � ����� ����. 
}


void GuidGen::addSomeIdFunc() {

    // ����� ����� InputDialog ������� �������� ���, ��� ������ � ������� �������� ID.
    QString c_text = QInputDialog::getText(this, "Generate ID", "How many ID's?"); // ������������ ���������� ���� ��� ����� �������� ������� ������� � ���� ������
    int value = c_text.simplified().toInt(); // ���������� ������, � ������� ������� ������� ������� � ������ � � �����, � ��� ����������� �������, ����������� ������ ������, �������� ����������;
    // int value = QInputDialog::getInt(this, "Generate ID", "Your ID's"); ����� � ��� ������������. ������ ������� ������ ������ ������ �����.


    for (int i = 0; i < value; i++)
    {
        QString currentString = RandomGenerateID();

        if (!currentString.isEmpty())
        {
            lw->addItem(currentString);
            int r = lw->count() - 1;
            lw->setCurrentRow(r); //�������, �������� ������� ����������� ������� � ������� ������ setCurrentRow().

            ++counter;
            countOfIdCurrent = countOfId + countOfIdCurrent.setNum(counter);
        }

    }
    countLabel->setText(countOfIdCurrent);
}

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // ���������� ������������ ��������� ����� � ����� ���������
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

QString genFourSign()
{
    QString idString;

    for (int val = 0; val < 4; val++)
    {
        int someNumber = 0;
        if (getRandomNumber(0, 1))
        {
            someNumber = getRandomNumber(97, 102);
        }
        else
        {
            someNumber = getRandomNumber(48, 57);
        }

        char randomChar = static_cast<char>(someNumber);
        QChar qch = randomChar;
        idString += qch;
    }

    return idString;
}

QString GuidGen::RandomGenerateID()
{
    QString idString;
    idString += genFourSign();
    idString += genFourSign();
    idString += "-";
    idString += genFourSign();
    idString += "-";
    idString += genFourSign();
    idString += "-";
    idString += genFourSign();
    idString += "-";
    idString += genFourSign();
    idString += genFourSign();
    idString += genFourSign();
    return idString;
}

void GuidGen::addSomeGuids()
{
    QString currentString = RandomGenerateID();

    QInputDialog inputDialog;

    // ������� ������� � ���� �������� ��� �������� ����� ���� �� ������� ������� �.�. ����������� ������ � �� �����.
    QString c_text = inputDialog.getText(this, "Generate ID", "Your ID                                                             ", QLineEdit::Normal, currentString);
    QString c_textSimp = c_text.simplified();


    if (!c_textSimp.isEmpty()) {

        lw->addItem(c_textSimp);
        int r = lw->count() - 1; // count() - ���������� ��������� � ������
        lw->setCurrentRow(r); //�������, �������� ������� ����������� ������� � ������� ������ setCurrentRow().
        ++counter;
        countOfIdCurrent = countOfId + countOfIdCurrent.setNum(counter);
        countLabel->setText(countOfIdCurrent);
    }
}

void GuidGen::removeItem() { // �������� ��������

    int r = lw->currentRow();


    if (r != -1) {

        QListWidgetItem* item = lw->takeItem(r);
        delete item;
        --counter;
        countOfIdCurrent = countOfId + countOfIdCurrent.setNum(counter);
        countLabel->setText(countOfIdCurrent);
    }
}


void GuidGen::clearItems() { // ����� clear() ������� ��� �������� �� ������� ������:


    if (lw->count() != 0)
    {
        lw->clear();
        counter = 0;
        countOfIdCurrent = countOfId + countOfIdCurrent.setNum(counter);
        countLabel->setText(countOfIdCurrent);
    }
}


void GuidGen::copeAllID()
{
    QString allBufferId;

    if (counter != 0)
    {
        lw->setCurrentRow(0);
        QListWidgetItem* curitem = lw->currentItem();
        QString c_text = curitem->text();

        for (int val = 0; val < lw->count(); val++)
        {
            lw->setCurrentRow(val);
            curitem = lw->currentItem();
            c_text = curitem->text() + "\n";
            allBufferId += c_text;
        }
    }
    pcb->setText(allBufferId, QClipboard::Clipboard); // ���������� � ������ ������ ��� ������. ����� ����� � ����������� �� ������ �������.

    statusBar->showMessage("Your Guids was copied", 2000);

}




