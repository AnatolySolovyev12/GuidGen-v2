#include "GuidGenv2.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QTime>
#include <cstdlib> // для функций rand(), srand(a), exit().
#include <ctime> // для функции time(a)
#include <QClipboard> // для работы с буфером обмена
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

    pcb = QApplication::clipboard(); // инициализирууем объект для работы с буфером

    //vbox->addStretch(50); // Добавляем нерастягиваемый отступ внутри виджета (надо пробовать).
    vbox->setSpacing(10); // расстояние между виджетами внутри вертикального бокса
   // vbox->addStretch(1); // равноудаляет от краёв или типо того
    vbox->addWidget(addID);
    vbox->addWidget(addSSomeID);
    vbox->addWidget(remove);
    vbox->addWidget(removeAll);
    vbox->addWidget(copyAll);
    vbox->addWidget(statusBar);
    vbox->addStretch(1); // равноудаляет от краёв или типо того
    vbox->addWidget(countLabel);

    hbox->addWidget(lw);
    hbox->addSpacing(15);// расстояние между виджетами внутри горизонтального бокса
    hbox->addLayout(vbox);

    connect(addSSomeID, &QPushButton::clicked, this, &GuidGen::addSomeIdFunc);
    connect(remove, &QPushButton::clicked, this, &GuidGen::removeItem);
    connect(removeAll, &QPushButton::clicked, this, &GuidGen::clearItems);
    connect(addID, &QPushButton::clicked, this, &GuidGen::addSomeGuids);
    connect(copyAll, &QPushButton::clicked, this, &GuidGen::copeAllID);

    //  connect(pcb, SIGNAL(dataChanged()), this, SLOT(paste())); // необязательно. Это для контроля и реагирования. 

    setLayout(hbox); // без этого нормально не уживаются 2 виджета в одном окне. 
}


void GuidGen::addSomeIdFunc() {

    // ТАкже можно InputDialog создать отдельно так, как сделал в штучном создании ID.
    QString c_text = QInputDialog::getText(this, "Generate ID", "How many ID's?"); // откруывается диалоговое окно для ввода значения которое вернётся в виде строки
    int value = c_text.simplified().toInt(); // возвращает строку, в которой символы пробела удалены в начале и в конце, а все неодиночные пробелы, находящиеся внутри строки, заменены одиночными;
    // int value = QInputDialog::getInt(this, "Generate ID", "Your ID's"); можно и так использовать. Правда немного другой формат строки ввода.


    for (int i = 0; i < value; i++)
    {
        QString currentString = RandomGenerateID();

        if (!currentString.isEmpty())
        {
            lw->addItem(currentString);
            int r = lw->count() - 1;
            lw->setCurrentRow(r); //наконец, выделяем текущий добавленный элемент с помощью метода setCurrentRow().

            ++counter;
            countOfIdCurrent = countOfId + countOfIdCurrent.setNum(counter);
        }

    }
    countLabel->setText(countOfIdCurrent);
}

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
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

    // добавил костыль в виде пробелов для увеления длины окна до нужного размера т.к. подходящего метода я не нашёл.
    QString c_text = inputDialog.getText(this, "Generate ID", "Your ID                                                             ", QLineEdit::Normal, currentString);
    QString c_textSimp = c_text.simplified();


    if (!c_textSimp.isEmpty()) {

        lw->addItem(c_textSimp);
        int r = lw->count() - 1; // count() - количество элементов в списке
        lw->setCurrentRow(r); //наконец, выделяем текущий добавленный элемент с помощью метода setCurrentRow().
        ++counter;
        countOfIdCurrent = countOfId + countOfIdCurrent.setNum(counter);
        countLabel->setText(countOfIdCurrent);
    }
}

void GuidGen::removeItem() { // удаление элемента

    int r = lw->currentRow();


    if (r != -1) {

        QListWidgetItem* item = lw->takeItem(r);
        delete item;
        --counter;
        countOfIdCurrent = countOfId + countOfIdCurrent.setNum(counter);
        countLabel->setText(countOfIdCurrent);
    }
}


void GuidGen::clearItems() { // метод clear() удаляет все элементы из виджета списка:


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
    pcb->setText(allBufferId, QClipboard::Clipboard); // отправляем в буффер нужную нам строку. также можно и изображения но другим методом.

    statusBar->showMessage("Your Guids was copied", 2000);

}




