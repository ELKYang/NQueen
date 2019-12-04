#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<vector>
#include<QPainter>
#include<iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_2->setReadOnly(true);//设置解决方案文本框只读
    n=25;//初始棋盘大小
    SolveNum=0;//初始解个数
    ChessboardPaintArray.resize(n,std::vector<int>(n));
    chessboard.resize(n);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()//初始化棋盘绘制数组。设置相邻格和横纵坐标相同的格为浅色，标志为1；其他格设置为深色，标志为2.
{
    for (int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j||(j-i)%2==0||(i-j)%2==0){
                    ChessboardPaintArray[i][j]=1;
            }
            else
                ChessboardPaintArray[i][j]=2;
        }
    }
}

//绘制棋盘
void MainWindow::paintEvent(QPaintEvent *)
{
    image1.load(":/chesspic/1.png");
    image2.load(":/chesspic/2.png");
    image3.load(":/chesspic/3.png");
    QPainter painter(this);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(ChessboardPaintArray[i][j]==1)
                painter.drawPixmap(100+j*450/n,50+i*450/n,450/n,450/n,image1);
            else if(ChessboardPaintArray[i][j]==2)
                painter.drawPixmap(100+j*450/n,50+i*450/n,450/n,450/n,image2);
            else if(ChessboardPaintArray[i][j]==3)
                painter.drawPixmap(100+j*450/n,50+i*450/n,450/n,450/n,image3);//绘制皇后
        }
    }
}

//即“开始”键的设置，开始后即执行初始化函数和递归Queen函数
void MainWindow::paint()
{
    n=ui->NumOfQueen->text().toInt();
    chessboard.resize(n);
    ChessboardPaintArray.resize(n,std::vector<int>(n));
    init();
    repaint();
    Queen(0);
    repaint();
}

//八皇后主函数递归Queen
void MainWindow::Queen(int row)
{
    if (row == n) {
        for (int i = 0; i < n; i++)
        {
            QString a;
            a=QString::number(i+1,10);
            QString b;
            b=QString::number(chessboard[i]+1,10);
            ui->textEdit_2->insertPlainText("("+a+","+b+")"+"  ");
        }
        ui->textEdit_2->insertPlainText("\n");
        SolveNum++;
        DisplaySolveNum();
        init();
        for(int i=0;i<n;i++)
        {
            ChessboardPaintArray[i][chessboard[i]]=3;
        }
        repaint();
    }
    else
        for (int col = 0; col < n; col++)
        {
            chessboard[row] = col;
            if (Judge(row))
                Queen(row + 1);
        }
}

//判断是否有皇后相吃的情况
bool MainWindow::Judge(int row)
{
    for (int j = 0; j < row; j++) {
        if (chessboard[row] == chessboard[j] || abs(row - j) == abs(chessboard[row] - chessboard[j])) {
            return false;
        }
    }
    return true;
}

//显示解的个数
void MainWindow::DisplaySolveNum()
{
    QString SolveNumTuStr;
    SolveNumTuStr=QString::number(SolveNum,10);
    ui->textEdit->setText(SolveNumTuStr);
}

void MainWindow::on_Start_clicked()
{
    SolveNum=0;
    ui->textEdit_2->clear();
    paint();
}


void MainWindow::on_textEdit_2_textChanged()
{
    ui->textEdit_2->moveCursor(QTextCursor::End);
}

void MainWindow::on_NumOfQueen_returnPressed()
{
    on_Start_clicked();
}
