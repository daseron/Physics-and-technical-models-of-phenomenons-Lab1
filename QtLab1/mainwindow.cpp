#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

const int N = 101;//количество точек по длинне
int M = 1000000;//Количество временных слоев

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setFixedSize(1020,460);
    ui->setupUi(this);



    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
      //Добавляем один график в widget
      ui->widget->addGraph();
      //Говорим, что отрисовать нужно график по нашим двум массивам x и y
     // ui->widget->graph(0)->setData(x, y);

      //Подписываем оси Ox и Oy
      ui->widget->xAxis->setLabel("Length's points");
      ui->widget->yAxis->setLabel("Temperature");

      //Установим область, которая будет показываться на графике
      ui->widget->xAxis->setRange(0, N);//Для оси Ox
      ui->widget->yAxis->setRange(299, 450);//Для оси Oy

      //И перерисуем график на нашем widget
      ui->widget->replot();
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    ui->textEdit->setText(text);

    cout<<"\n\n Text from textEdit is = ";
    cout<<text.toStdString()<<"\n\n" ;

    M = text.toInt();

    cout.precision(8);


    double k=0.401;

    double l = 1;//  длинна стержня в см

    const double h = l/(N-1);
    cout<<"H = "<<h<<"\n";

    double Tau=0.0000001;
    cout<<"Tau = "<<Tau<<"\n";

    double gamma;
    gamma = (k*Tau)/h;
    cout<<"Gamma= "<<gamma<<"\n";

    double Time = M * Tau;// общее время нагрева
     cout<<"Time= "<<Time<<"\n";

    double *X = NULL;
    double *T = NULL;
    double *T2 = NULL;

    QVector<double> X1(N) , Temper(N);

    X = new double [N];
    T = new double [N];
    T2 = new double [N];

    X[0]=0; // Заполнение массива иксов (точек на стержне
    for (int i=0;i<N;i++)
    {X[i]=i*h;

        cout<<"X["<<i<<"]="<<X[i]<<"\n";
    }


    // Цикл заполнения массива



    for (int i = 0 ; i < N ; ++i){ //начальные условия
        if ( i == 0 )
            T[i]=450;
        if ( i != 0 )
            T[i]=300;
    }

    double check=(k*Tau)/(2*h*h);
    cout <<"Check = "<<check<<"\n\n";

    for (int j = 0 ; j < M ; ++j ) {



    for (int i = 0 ; i < N  ; ++i){


        if (i != 0 && i != N-1)
     T2[i]=T[i]+((k*(T[i-1]-300)*Tau)/(2*h*h))*(T[i-1]+T[i+1]-2*T[i]);
        if (i == 0)
            T2[i]=450;
        if (i == N - 1)
            T2[i]=300;

           }

        for (int i = 0 ; i < N ; ++i){
            T[i] = T2[i];

        }


    }


    //Приводим значения температуры от double к int , чтобы фукнкция отображения на графике работала корректно
  for (int i = 0 ; i < N  ; ++i){
   Temper[i] = T2[i];
   X1[i] = X[i]*100;
   }



    //графическая часть


      //Говорим, что отрисовать нужно график по нашим двум массивам x и y
      ui->widget->graph(0)->setData(X1, Temper);

      //И перерисуем график на нашем widget
      ui->widget->replot();


      delete [] X;
      delete [] T;
      delete [] T2;

}


