#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:

    void on_pushButton_clicked();

    void on_pushButton_pollard_clicked();

    void on_pushButton_affine_clicked();

    void on_pushButton_vigenere_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

signals:
    void change(int id);

private slots:
    void on_btn_inverse_clicked();

    void on_btnMatrix_clicked();

    void on_btnGcd_clicked();

    void on_btnPollardFind_clicked();

    void on_btnRho_clicked();

    void on_btn_shift_clicked();


    void on_btn_affine_num_clicked();

    void on_btnHill_clicked();

    void on_btnRsa_clicked();

    void on_btnGamal_clicked();

    void on_btnSignElg_clicked();

    void on_btnSignRsa_clicked();

    void on_btnShank_clicked();

    void on_rb_mac_affine_clicked();

    void on_rb_mac_caesar_clicked();

    void on_btnMac_clicked();

private:
    Ui::MainWindow *ui;
    
    void setValidators();
    void setUpPages();
    void setUpTreeView();
};
#endif // MAINWINDOW_H
