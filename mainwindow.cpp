#include "QMessageBox"
#include <iostream>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStackedWidget>
#include <QObject>
#include <QFontDatabase>
#include <QRegExp>
#include <math.h>
#include <QBoxLayout>
#include <QListWidgetItem>
#include "algorithms.h"
#include "asymmetric.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculations.h"
#include "symmetric.h"
#include "sign.h"
#include "mac.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/fonts/whitrabt.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont whiterabbit(family);

    this->setFont(whiterabbit);

    this->setCentralWidget(ui->splitter);
    this->setStyleSheet("QLineEdit { height: 25px; border: 1px solid #39ff14; border-radius: 5px; color: #39ff14; font-size: 14pt;}"
                        "QLabel { font-family: White Rabbit; color: #39ff14; font-size: 14pt}"
                        "QGroupBox { color: #39ff14; font-size: 14pt;}"
                        "QPushButton { height: 25px; width: 100px; color: #39ff14; border: 0.5px solid #39ff14; border-radius: 5px }"
                        "QPushButton::hover { background-color: #39ff14; color: black }"
                        "QWidget { background-color: black; } "
                        "QTreeView { color: #39ff14; border-right: 1px solid #39ff14; font-size: 14pt; } "
                        "QTreeView::item { padding: 10px }"
                        "QRadioButton { margin: 10px 0 10px 0; color: #39ff14; font-size: 14pt; } "
                        "QMessageBox QLabel { font-family: White Rabbit; } "
                        "QSplitter { color: #39ff14; }");
    setUpTreeView();
    setUpPages();
    setValidators();

    ui->stackedWidget->setCurrentIndex(0);
    QObject::connect(this, SIGNAL(change(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)));

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::setValidators()
{
    QRegularExpression onlyNums("^[0-9]+$");
    QRegularExpression onlyText("^[a-zA-Z ]*$");
    QRegularExpression onlyBinary("[0-1]+$^");
    QRegularExpression numsAndComma("^[-,0-9]+$");



    QList<QWidget*> pageList;

    for(int i = 0; i < ui->stackedWidget->count(); i++){
        pageList.append(ui->stackedWidget->widget(i));
    }
    
    int counter = 0;
    for(QWidget* page : pageList){
        QList<QLineEdit*> itemList = page->findChildren<QLineEdit*>(QString(),Qt::FindChildrenRecursively);

        switch(counter){
        case 0:
            break;
        case 1:
            for(QLineEdit* line : itemList){
                line->setValidator(new QRegularExpressionValidator(onlyNums, this));
            }

            break;
        case 2:
            for(QLineEdit* line : itemList){
                line->setValidator(new QRegularExpressionValidator(onlyNums, this));
            }

            break;
        case 3:
            for(QLineEdit* line : itemList){
                line->setValidator(new QRegularExpressionValidator(onlyNums, this));
            }
            break;
        case 4:
            for(QLineEdit* line : itemList){
                line->setValidator(new QRegularExpressionValidator(onlyNums, this));
            }
            break;
        case 5:
            for(QLineEdit* line : itemList){
                if(line->objectName() == "le_shift_text"){
                    line->setValidator(new QRegularExpressionValidator(onlyText, this));
                }else{
                    line->setValidator(new QRegularExpressionValidator(onlyNums, this));
                }
            }
            break;
        case 6:
            for(QLineEdit* line : itemList){
                if(line->objectName() == "lineEdit_affine_input"){
                    line->setValidator(new QRegularExpressionValidator(onlyText, this));
                }else{
                    line->setValidator(new QRegularExpressionValidator(onlyNums, this));
                }
            }
            break;
        case 7:
            for(QLineEdit* line : itemList){
                line->setValidator(new QRegularExpressionValidator(onlyText, this));
            }
            break;
        case 8:
            for(QLineEdit* line : itemList){
                if(line->objectName() == "le_hill_text"){
                    line->setValidator(new QRegularExpressionValidator(onlyText, this));
                }else{
                    line->setValidator(new QRegularExpressionValidator(onlyNums, this));
                }
            }
            break;
        case 9:
            for(QLineEdit* line : itemList){
                if(line->objectName() == "le_mac_IV" || line->objectName() == "le_mac_x"){
                    line->setValidator(new QRegularExpressionValidator(onlyBinary, this));
                }else{
                    line->setValidator(new QRegularExpressionValidator(onlyNums, this));
                }
            }
            break;
        case 10:
            for(QLineEdit* line : itemList){
                line->setValidator(new QRegularExpressionValidator(onlyNums, this));
            }
            break;
        case 11:
            for(QLineEdit* line : itemList){
                if(!(line->objectName() == "le_gamal_input")){
                    line->setValidator(new QRegularExpressionValidator(onlyNums, this));
                }

            }
            break;
        case 12:
            for(QLineEdit* line : itemList){
                if(line->objectName() != "le_sign_rsa_input" && line->objectName() != "le_sign_elg_input"){
                    line->setValidator(new QRegularExpressionValidator(onlyNums, this));
                }
            }
            break;
        }
    counter++;
    }
}

void MainWindow::setUpPages()
{
    QList<QWidget*> pageList;
    QList<QBoxLayout*> layoutList;

    for(int i = 0; i < ui->stackedWidget->count(); i++){
        pageList.append(ui->stackedWidget->widget(i));
    }

    for(QWidget* page : pageList){
        QList<QWidget*> itemList = page->findChildren<QWidget*>(QString(),Qt::FindDirectChildrenOnly);
        QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, page);
        for(QWidget* item : itemList){
            layout->addWidget(item);
            layout->setAlignment(item, Qt::AlignCenter);
            layout->setSpacing(20);
        }
        layoutList.append(layout);
        page->setLayout(layout);
    }
}

void MainWindow::setUpTreeView()
{
    QVector<QTreeWidgetItem*> list;
    QTreeWidget* tree = ui->treeWidget;
    for(int i = 0; i < tree->topLevelItemCount(); i++){
        list.append(tree->topLevelItem(i));
    }
    for(int i = 0; i < list.size(); i++){
        list.at(i)->setData(0, Qt::UserRole, i);
    }
}

//************************** MODULO CALCULATIONS ****************************************************************************************************************



// ************************* INVERSE MODULO *******************************************************************************************************************************



void MainWindow::on_btn_inverse_clicked()
{

    if(ui->le_inverse_a->text().isEmpty() || ui->le_inverse_b->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter necessary input.");
        return;
    }

    int a = ui->le_inverse_a->text().toInt();
    int n = ui->le_inverse_b->text().toInt();

    if(a == 0){
        QMessageBox::warning(this, "Warning", "a can not be 0.");
        return;
    }

    int res = findInverse(a, n);
    if(res != -1){
        QMessageBox::information(this, "Results", "inverse(" + QString::number(a) + ") mod " + QString::number(n) + " = " + QString::number(res));
        return;
    }else{
        QMessageBox::warning(this, "Warning", QString::number(a) + " doesn't have an inverse mod " + QString::number(n) + ".");
        return;
    }

}

// *************************** SQUARE AND MULTIPLY *************************************************************************************************************************



void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit_a->text().isEmpty() || ui->lineEdit_c->text().isEmpty() || ui->lineEdit_n->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter necessary input.");
        return;
    }

    int a = ui ->lineEdit_a->text().toInt();
    int c = ui ->lineEdit_c->text().toInt();
    int n = ui ->lineEdit_n->text().toInt();

    if(n == 0){
        QMessageBox::warning(this, "Warning", "modulo 0 is not allowed.");
        return;
    }

    QString text;
    squareAndMultiply(n, c, a, text);

    QMessageBox::information(this, "Result", text);
    return;

}

// ******************************** INVERSE MATRIX ******************************************************************************************************************



void MainWindow::on_btnMatrix_clicked()
{

    if(ui->le_matrix_11->text().isEmpty() || ui->le_matrix_12->text().isEmpty() || ui->le_matrix_21->text().isEmpty() ||
            ui->le_matrix_22->text().isEmpty() || ui->le_matrix_n->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter necessary input.");
        return;
    }

    int a11 = ui->le_matrix_11->text().toInt();
    int a12 = ui->le_matrix_12->text().toInt();
    int a21 = ui->le_matrix_21->text().toInt();
    int a22 = ui->le_matrix_22->text().toInt();
    int n = ui->le_matrix_n->text().toInt();

    if(n == 1){
        QMessageBox::warning(this, "Warning", "Modulo 1 is not allowed.");
        return;
    }else if(n == 0){
        QMessageBox::warning(this, "Warning", "Modulo 0 is not allowed.");
        return;
    }

    int array[2][2] = {{a11, a12}, {a21, a22}};
    QVector<QVector<int>> res =  findInverseMatrix(array, n);

    QString resString;
    resString += "det(A) = " + QString::number(res[2][0]) + "\r\n\r\n";
    if(res[2][1] == -1 || res[2][1] == 0){
        resString += "The matrix A doesn't have an inverse mod " + QString::number(n) + ".";

    }else{
        resString += "inverse(det A) = " + QString::number(res[2][1]) + "\r\n\r\n";
        resString += "\r\ninverse(A) = \r\n\r\n";
        resString += "[ ";
        for(int i = 0; i < 2; i++){
            if(i == 1){
                resString += "\r\n";
                resString += "[ ";
            }
            for(int j = 0; j < 2; j++){
                resString += QString::number(res[i][j]) + " ";
            }
            resString += " ]";
        }
    }

    QMessageBox::information(this, "Results", resString);
    return;
}

// ************************************** EXTENDED EUCLIDS ALGORITHM *********************************************************************************************************



void MainWindow::on_btnGcd_clicked()
{
    if(ui->le_gcd_a->text().isEmpty() || ui->le_gcd_b->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter a number in all fields.");
        return;
    }

    int a = ui->le_gcd_a->text().toInt();
    int b = ui->le_gcd_b->text().toInt();

    if(b == 0){
        QMessageBox::warning(this, "Warning", "b can not be 0.");
        return;
    }

    QVector<int> vec = extended(a, b);

    QString resString = "gcd(" + QString::number(a) + ", " + QString::number(b) + ") = " + QString::number(vec[0]) + "\r\n\r\n" +
            QString::number(vec[1]) + " * " + QString::number(a) + " + " + QString::number(vec[2]) + " * " + QString::number(b) +
            " = " + QString::number(vec[0]);

    QMessageBox::information(this, "Results", resString);
    return;

}

// ************************************* POLLARDS ALGORITHMS *********************************************************************************************************


// ************************************* POLLARD P -1 ****************************************************************************************************************

void MainWindow::on_pushButton_pollard_clicked()
{
    if(ui->lineEdit_pollard_B->text().isEmpty() || ui->lineEdit_pollard_n->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter a number in all fields.");
        return;
    }

    int n = ui -> lineEdit_pollard_n->text().toLong();
    int B = ui -> lineEdit_pollard_B->text().toInt();

    if(n > 10000000){
        QMessageBox::warning(this, "Warning", "10,000,000 > n > 0.");
        return;
    }

    int z = pollard(n, B);

    QString resString;
    if(z == -1){
        resString = "No factors found.";
    }else{
        resString = "A factor in " + QString::number(n) + " is " + QString::number(z) + ".";
    }
    QMessageBox::information(this, "Result", resString);

}


// ************************************ POLLARD FIND B ****************************************************************************************************************


void MainWindow::on_btnPollardFind_clicked()
{
    if(ui->le_pollard_find_n->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
        return;
    }
    int n = ui->le_pollard_find_n->text().toInt();

    if(isPrime(n)){
        QMessageBox::warning(this, "Warning", "n is a prime.");
        return;
    }

    if(n > 10000000){
        QMessageBox::warning(this, "Warning", "10,000,000 > n > 0.");
        return;
    }

    int B = pollard_findB(n);

    QString resString = "B = " + QString::number(B);

    QMessageBox::information(this, "Results", resString);

}


//************************************** POLLARD RHO *******************************************************************************************************************


void MainWindow::on_btnRho_clicked()
{
    if(ui->le_rho_x->text().isEmpty() || ui->le_rho_x1->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
        return;
    }
    long x = ui->le_rho_x->text().toLong();
    int x1 = ui->le_rho_x1->text().toInt();

    if(x > 1000000 || x == 0){
        QMessageBox::warning(this, "Warning", "1,000,000 > n > 0.");
        return;
    }
    int r = rho(x, x1);

    QString res = QString::number(r);

    QMessageBox::information(this, "Results", "A factor in " + QString::number(x) + " is " + res);

}


// **************************************************** SHANKS ALGORITHM ***************************************************************************************************



void MainWindow::on_btnShank_clicked()
{
    if(ui->le_shank_alpha->text().isEmpty() || ui->le_shank_beta->text().isEmpty() || ui->le_shank_p->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter necessary input.");
        return;
    }

    int alpha = ui->le_shank_alpha->text().toInt();
    int beta = ui->le_shank_beta->text().toInt();
    int p = ui->le_shank_p->text().toInt();
    if(p == 0 || alpha == 0){
        QMessageBox::warning(this, "Warning", "p or alpha may not be 0.");
        return;
    }
    if(p == 1){
        QMessageBox::warning(this, "Warning", "p may not be 1");
        return;
    }

    if(!isPrime(p)){
        QMessageBox::warning(this, "Warning", "p has to be a prime.");
        return;
    }

    if(beta > p){
        QMessageBox::warning(this, "Warning", "b should be smaller than p.");
        return;
    }

    QString resString;
    int res = shank(p, alpha, beta);
    if(res == 0){
        resString = "The congrugence has no solution.";
    }else{
        resString = "a = " + QString::number(res);
    }
    QMessageBox::information(this, "Warning",resString);
    return;

}


// ************************************ CAESAR CHIPER ******************************************************************************************************************


void MainWindow::on_btn_shift_clicked()
{
    if(ui->le_shift_k->text().isEmpty() || ui->le_shift_text->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
        return;
    }
    int K = ui->le_shift_k->text().toInt();
    QString text = ui->le_shift_text->text();

    QString res;
    if(ui->rb_shift_encrypt->isChecked()){
        res = encrypt_shift(K, text);
    }else{
        res = decrypt_shift(K, text);
    }

    QMessageBox::information(this, "Results", res);

}

// ************************************* AFFINE CIPHER *****************************************************************************************************************



void MainWindow::on_pushButton_affine_clicked()
{
    if(ui->lineEdit_affine_input->text().isEmpty() || ui->lineEdit_affine_k1->text().isEmpty() || ui->lineEdit_affine_k2->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter a number in all fields.");
        return;
    }

    QString input = ui->lineEdit_affine_input->text();
    int k1 = ui -> lineEdit_affine_k1->text().toInt();
    int k2 = ui -> lineEdit_affine_k2->text().toInt();

    if(k1 == 0){
        QMessageBox::warning(this, "Warning", "a can't be 0.");
        return;
    }

    if(findInverse(k1, 26) == -1){
        QMessageBox::warning(this, "Warning", QString::number(k1) + " doesn't have an inverse modulo 26, and can't be used.");
        return;
    }

    QString res;
    if(ui->radioButton_affine_krypter ->isChecked()){
        res = encrypt_affine(k1, k2, input);
    }else{
        res = decrypt_affine(k1, k2, input);
    }

    QMessageBox::information(this, "Result", res);
    return;

}

void MainWindow::on_btn_affine_num_clicked()
{

    if(ui->le_affine_a_num->text().isEmpty() || ui->le_affine_b_num->text().isEmpty() ||
            ui->le_affine_input_num->text().isEmpty() ||  ui->le_affine_n_num->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter a number in all fields.");
        return;
    }

    int input = ui->le_affine_input_num->text().toInt();
    int k1 = ui -> le_affine_a_num->text().toInt();
    int k2 = ui -> le_affine_b_num->text().toInt();
    int n = ui->le_affine_n_num->text().toInt();

    if(k1 == 0){
        QMessageBox::warning(this, "Warning", "a can't be 0.");
        return;
    }

    if(findInverse(k1, n) == -1){
        QMessageBox::warning(this, "Warning", QString::number(k1) + " doesn't have an inverse modulo " + QString::number(n) + ", and can't be used.");
        return;
    }

    QString resString;
    if(ui->rb_affine_encrypt_num ->isChecked()){
        resString = "Encrypted: " + QString::number(encrypt_affine_num(k1, k2, n, input));
    }else{
        resString = "Decrypted: " + QString::number(decrypt_affine_num(k1, k2, n, input));
    }

    QMessageBox::information(this, "Result", resString);
}



// ***************************************** VIGENERE CIPHER **********************************************************************************************************



void MainWindow::on_pushButton_vigenere_clicked()
{
    if(ui->lineEdit_vigenere_input->text().isEmpty() || ui->lineEdit_vigenere_keyword->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter input in all necessary fields.");
        return;
    }

    QString keyword = ui->lineEdit_vigenere_keyword->text();
    QString input = ui->lineEdit_vigenere_input->text();

    QString res;
    if(ui->radioButton_vigenere_krypter->isChecked()){
        res = encryptVigenere(keyword, input);
    }else{
        res = decryptVigenere(keyword, input);
    }

    QMessageBox::information(this, "Result", res);
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString text = item->text(column);
    int id = item->data(0, Qt::UserRole).toInt();
    change(id);
}


// ***************************************** HILL CIPHER ********************************************************************************************************************


void MainWindow::on_btnHill_clicked()
{

    if(ui->le_hill_a11->text().isEmpty() || ui->le_hill_a12->text().isEmpty() || ui->le_hill_a21->text().isEmpty() ||
            ui->le_hill_a22->text().isEmpty() || ui->le_hill_text->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter necessary input.");
        return;
    }

    int a11 = ui->le_hill_a11->text().toInt();
    int a12 = ui->le_hill_a12->text().toInt();
    int a21 = ui->le_hill_a21->text().toInt();
    int a22 = ui->le_hill_a22->text().toInt();
    QString text = ui->le_hill_text->text().toUpper();

    QString resString;
    if(text.length() % 2 != 0 || text.length() == 1){
        resString = "Your input string has to be dividable by 2.";
        QMessageBox::information(this, "Warning", resString);
        return;
    }

    int array[2][2] = {{a11, a12}, {a21, a22}};

    QVector<QVector<int>> res = findInverseMatrix(array, 26);


    resString += "det(A) = " + QString::number(res[2][0]) + "\r\n\r\n";
    if(res[2][1] == -1 || res[2][1] == 0){
        resString += "The matrix A doesn't have an inverse mod " + QString::number(26) + ".";
        QMessageBox::information(this, "Results", resString);
        return;
    }

    if(ui->rb_hill_encrypt->isChecked()){
        resString = encryptHill(text, array);
    }else{
        int inverseMatrix[2][2] = {{res[0][0], res[0][1]}, {res[1][0], res[1][1]}};
        resString = decryptHill(text, inverseMatrix);
    }

    QMessageBox::information(this, "Results", resString);

}

// ***************************************************** CBC MAC *********************************************************************************************************

void MainWindow::on_btnMac_clicked()
{
    if(ui->le_mac_IV->text().isEmpty() || ui->le_mac_a->text().isEmpty() || ui->le_mac_n->text().isEmpty() || ui->le_mac_x->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
        return;
    }

    QString binaryInput = ui->le_mac_x->text();
    QString resString;
    int n = ui->le_mac_n->text().toInt();
    QString IV = ui->le_mac_IV->text();

    if(binaryInput.length() % 4 != 0){
        QMessageBox::warning(this, "Warning", "Length of input has to be divisable by 4 (blocklength = 4)");
        return;
    }

    if(n == 0){
        QMessageBox::warning(this, "Warning", "n may not be 0.");
        return;
    }

    if(IV.length() != 4){
        QMessageBox::warning(this, "Warning", "Length of IV has to be 4.|");
        return;
    }

    QVector<int> binary;
    QVector<int> IV_binary;

    for(QChar &c : binaryInput){
        if(c == "1"){
            binary.append(1);
        }else{
            binary.append(0);
        }
    }
    for(QChar &c : IV){
        IV_binary.append(c.unicode()-48);
    }

    QVector<int> y_binary;
    if(ui->rb_mac_caesar->isChecked()){
        int K = ui->le_mac_a->text().toInt();
        y_binary = findCaesarMAC(binary, n, K, IV_binary);
    }

    if(ui->rb_mac_affine->isChecked()){

        if(ui->le_mac_b->text().isEmpty()){
            QMessageBox::warning(this, "Warning", "Please enter all necessary information.");
            return;
        }

        int A = ui->le_mac_a->text().toInt();

        if(findInverse(A, n) == -1){
            QMessageBox::warning(this, "Warning", "No inverse for " + QString::number(A) + " modulo " + QString::number(n));
            return;
        }

        int B = ui->le_mac_b->text().toInt();
        y_binary = findAffineMAC(binary, A, B, n, IV_binary);
    }

    for(int num : y_binary){
        resString += QString::number(num);
    }

    QMessageBox::information(this, "Results", "MAC: " + resString);
}




// ************************************ RSA *******************************************************************************************************************************



void MainWindow::on_btnRsa_clicked()
{
    int input = ui->le_rsa_input->text().toInt();
    int p = ui->le_rsa_p->text().toInt();
    int q = ui->le_rsa_q->text().toInt();
    int e = ui->le_rsa_e->text().toInt();
    int d = ui->le_rsa_d->text().toInt();
    int n = 0;

    if(!ui->le_rsa_n->text().isEmpty()){
        n = ui->le_rsa_n->text().toInt();
    }

    if(ui->le_rsa_n->text().isEmpty() && !(ui->le_rsa_p->text().isEmpty()) && !(ui->le_rsa_q->text().isEmpty())){
        n = p * q;
    }

    if(n == 0){
        QMessageBox::warning(this, "Warning", "n may not be 0.");
        return;
    }

    if(ui->rb_rsa_encrypt->isChecked()){
        if(ui->le_rsa_input->text().isEmpty() || ui->le_rsa_e->text().isEmpty() || n == 0){
            QMessageBox::warning(this, "Warning", "Please entery all necessary input.");
            return;
        }else{

            QRegExp re("([0-9]+)");
            if(!re.exactMatch(ui->le_rsa_input->text())){
                QMessageBox::warning(this, "Warning", "Enter input as a number.");
                return;
            }

            QMessageBox::information(this, "Results", "Encrypted: " + QString::number(encryptRSA(n, input, e)));
            return;
        }
    }else{
        if(ui->le_rsa_input->text().isEmpty() || ui->le_rsa_d->text().isEmpty() || n == 0){
            QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
            return;
        }else{
             QMessageBox::information(this, "Results", "Decrypted: " + QString::number(decryptRSA(n, input, d)));
        }
    }

}


// ********************************************** EL GAMAL **************************************************************************************************************


void MainWindow::on_btnGamal_clicked()
{

    if(ui->rb_gamal_encrypt->isChecked()){

        if(ui->le_gamal_alpha->text().isEmpty() || ui->le_gamal_beta->text().isEmpty() || ui->le_gamal_input->text().isEmpty()
                || ui->le_gamal_k->text().isEmpty() || ui->le_gamal_p->text().isEmpty()){
            QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
            return;
        }

        QString x = ui->le_gamal_input->text();

        QRegExp re("([0-9]+)");
        if(!re.exactMatch(x)){
            QMessageBox::warning(this, "Warning", "Enter input as a number.");
            return;
        }


        int p = ui->le_gamal_p->text().toInt();
        int alpha = ui->le_gamal_alpha->text().toInt();
        int beta = ui->le_gamal_beta->text().toInt();
        int k = ui->le_gamal_k->text().toInt();

        if(p == 0){
            QMessageBox::warning(this, "Warning", "p can't be 0.");
            return;
        }

        int inputToEncrypt = x.toInt();
        QVector<int> encryptedVec = encryptGamal(alpha, k, inputToEncrypt, beta, p);

        QMessageBox::information(this, "Results", "Encrypted: " + QString::number(encryptedVec[0]) + ", " + QString::number(encryptedVec[1]));
        return;

    }else{

        if(ui->le_gamal_a->text().isEmpty() || ui->le_gamal_p->text().isEmpty() || ui->le_gamal_input->text().isEmpty()){
            QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
            return;
        }

        QString x = ui->le_gamal_input->text();
        int p = ui->le_gamal_p->text().toInt();
        int a = ui->le_gamal_a->text().toInt();

        if(p == 0){
            QMessageBox::warning(this, "Warning", "p may not be 0.");
            return;
        }

        QRegExp re("([0-9]*[,])[0-9]+");
        if(!re.exactMatch(x)){
            QMessageBox::warning(this, "Warning", "Enter input to be validated on form (XX , XX)");
            return;
        }

        QVector<int> inputContainer;
        QString temp;
        for(QChar &c : x){
            if(c == ","){
                inputContainer.append(temp.toInt());
                temp.clear();
            }else{
                temp += c;
            }
        }
        inputContainer.append(temp.toInt());

        int res = decryptGamal(inputContainer[0], inputContainer[1], p, a);
        QMessageBox::information(this, "Results", "Decrypted:" + QString::number(res));
    }
}



// ************************************************************ EL GAMAL SIGNING ******************************************************************************************


void MainWindow::on_btnSignElg_clicked()
{
    if(ui->le_sign_elg_alpha->text().isEmpty() || ui->le_sign_elg_beta->text().isEmpty() || ui->le_sign_elg_p->text().isEmpty()
            || ui->le_sign_elg_input->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
        return;
    }

    QString x = ui->le_sign_elg_input->text();
    int alpha = ui->le_sign_elg_alpha->text().toInt();
    int beta = ui->le_sign_elg_beta->text().toInt();
    int p = ui->le_sign_elg_p->text().toInt();

    if(p == 0){
        QMessageBox::warning(this, "Warning", "p may not be 0.");
        return;
    }

    if(!isPrime(p)){
        QMessageBox::warning(this, "Warning", "p has to be a prime number.");
        return;
    }

    if(ui->rb_sign_elg_ver->isChecked()){

        QRegExp re("([0-9]+[(][0-9]+[,][0-9]+[)]+)");
        if(!re.exactMatch(x)){
            QMessageBox::warning(this, "Warning", "Enter input to be validated on form XX(XX,XX)");
            return;
        }

        QVector<int> resVector;
        QString tempString;
        for(QChar &c : x){
            if(c == "," || c == ")" || c == "("){
                resVector.append(tempString.toInt());
                tempString.clear();
            }else{
                tempString += c;
            }
        }

        QString resString;
        bool verified = verifyGamal(resVector[0], resVector[1], resVector[2], alpha, p, beta);
        if(verified){
            resString = "Verified!";
        }else{
            resString = "Not verified...";
        }
        QMessageBox::information(this, "Results", resString);
        return;
    }

    if(ui->rb_sign_elg_sign->isChecked()){

        QRegExp re("([0-9]+)");
        if(!re.exactMatch(x)){
            QMessageBox::warning(this, "Warning", "Enter input to be signed as a number.");
            return;
        }

        if(ui->le_sign_elg_a->text().isEmpty() || ui->le_sign_elg_k->text().isEmpty()){
            QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
            return;
        }

        int a = ui->le_sign_elg_a->text().toInt();
        int k = ui->le_sign_elg_k->text().toInt();

        if(findInverse(k, p-1) == -1){
            QMessageBox::warning(this, "Warning", "k has no inverse modulo p-1.");
            return;
        }

        QVector<int> res = signGamal(p,alpha,a,beta,k,x.toInt());
        QString resString = "sign(x,k) = (" + QString::number(res[0]) + ", " + QString::number(res[1]) + ")";
        QMessageBox::information(this, "Results", resString);
    }

}




// ******************************************** RSA SIGNING *****************************************************************************************************************




void MainWindow::on_btnSignRsa_clicked()
{
    if(ui->le_sign_rsa_a->text().isEmpty() || ui->le_sign_rsa_b->text().isEmpty() || ui->le_sign_rsa_input->text().isEmpty()
            || ui->le_sign_rsa_n->text().isEmpty() || ui->le_sign_rsa_n_public->text().isEmpty()){
        QMessageBox::warning(this, "Warning", "Please enter all necessary input.");
        return;
    }

    QString x = ui->le_sign_rsa_input->text();
    int a = ui->le_sign_rsa_a->text().toInt();
    int b = ui->le_sign_rsa_b->text().toInt();
    int n = ui->le_sign_rsa_n->text().toInt();
    int n_public = ui->le_sign_rsa_n_public->text().toInt();

    if(n == 0 || n_public == 0){
        QMessageBox::warning(this, "Warning", "n or n_public can not be 0.");
        return;
    }

    QString resString;
    if(ui->rb_sign_rsa_sign->isChecked()){
        QVector<int> vec = signRSA(n,b,x.toInt(),a,n_public);

        resString = "(";
        for(int num : vec){
            resString += QString::number(num) + " ";
        }
        resString += ")";
    }

    if(ui->rb_sign_rsa_verify->isChecked()){

        QRegExp re("([0-9]+[,])[0-9]+");

        if(!re.exactMatch(x)){
            QMessageBox::warning(this, "Warning", "Enter input to be validated on form (XX,XX)");
            return;
        }

        QVector<int> inputContainer;
        QString temp;
        for(QChar &c : x){
            if(c == ","){
                inputContainer.append(temp.toInt());
                temp.clear();
            }else{
                temp += c;
            }
        }

        inputContainer.append(temp.toInt());

        bool verified = verifyRSA(n,b,inputContainer[0], inputContainer[1], a, n_public);
        if(verified){
            resString += "Verified!";
        }else{
            resString += "Not verified...";
        }
    }

    QMessageBox::information(this, "Results", resString);

}

void MainWindow::on_rb_mac_affine_clicked()
{
    ui->gb_mac_affine->setVisible(true);
    ui->le_mac_b->setVisible(true);
    ui->label_mac_b->setVisible(true);
    ui->label_mac_k->setText("A");
}

void MainWindow::on_rb_mac_caesar_clicked()
{
    ui->gb_mac_affine->setVisible(true);
    ui->label_mac_k->setText("K");
    ui->le_mac_b->setVisible(false);
    ui->label_mac_b->setVisible(false);
}






