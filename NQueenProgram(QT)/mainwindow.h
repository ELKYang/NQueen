#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    int n;//输入的皇后的个数
    int SolveNum;//记录解的个数
    std::vector<int> chessboard;//结果用一维数组表示
    std::vector<std::vector<int>> ChessboardPaintArray;//棋盘绘制
    void init();//用于初始化棋盘
    bool Judge(int row);//判断函数
    void Queen(int row);//递归寻找最佳方案
    void paintEvent(QPaintEvent *);//绘图
    void paint();//动态绘制棋盘
    QPixmap image1;//淡色格
    QPixmap image2;//深色格
    QPixmap image3;//皇后
    void DisplaySolveNum();//显示输出
private:
    Ui::MainWindow *ui;
public slots:
    void on_Start_clicked();//开始按钮
private slots:
    void on_textEdit_2_textChanged();//控制解决方案文本框中得滚动条向下移动而不是默认的向上移动
    void on_NumOfQueen_returnPressed();//输入皇后数回车即可开始
};
#endif // MAINWINDOW_H
