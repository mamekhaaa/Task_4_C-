
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <qpushbutton.h>
#include <QLabel>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QPushButton *button = new QPushButton("Прочитать Граф", this);
    button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));


    graph = new QTextEdit(this);
    graph->setGeometry(QRect(QPoint(350, 50), QSize(300, 200)));
    graph->setReadOnly(true);

    result = new QTextEdit(this);
    result->setGeometry(QRect(QPoint(350, 300), QSize(300, 200)));
    result->setReadOnly(true);

    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

        this->resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");
    graph->setPlainText("");
    directedGraph.clear();
    if (!filePath.isEmpty())
    {

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();

                qDebug() << line;
                QStringList parts = line.split(' ');

                if (parts.size() != 2) {
                    QString nodeName = parts[0];

                     graph->append(parts[0]);
                    continue;
                }
                graph->append(parts[0]+"->"+parts[1]);
                QString nodeName = parts[0];
                QStringList neighbours = parts[1].split(',');

                Node<QString> *node = directedGraph.findNodeByValue(nodeName);

                for (const QString &neighbourName : neighbours) {
                    Node<QString> *neighbourNode = directedGraph.findNodeByValue(neighbourName);
                    directedGraph.addEdge(node, neighbourNode);
                }


            }

            for (std::vector<Node<QString>*> &component : directedGraph.findConnectedComponents()){
                for (Node<QString>* node : component){
                    result->append(node->getValue());
                }
                result->append("\n");
            }
            file.close();



            directedGraph.dfsFromFirst();

        }
        else
        {
            qDebug() << "Не удалось открыть файл";
        }
    }

}



