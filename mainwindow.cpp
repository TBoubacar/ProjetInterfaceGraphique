#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuitter_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCharger_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrez le fichier"), QString(), tr("Fichiers (*.csv)"));
    chargerFichierCSV(fileName);
}

void MainWindow::on_action_propos_de_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action_propos_de_Graphiques_triggered()
{
    QString msg  = tr("Je me nomme TOURE Boubacar, étudiant en Licence 3 Informatique à la faculté de sciences d'Angers. \n"
                   "À la suite d'un projet visant à me faire valider une de mes unités de formations (Interface Graphique). \n"
                   "J'ai dû mettre en place cette magnifique Interface Graphique (^_^).");
    QMessageBox::information(this, tr("À propos de Graphiques"), msg);
}

void MainWindow::chargerFichierCSV(const QString &filename) {
    QFile file (filename);              //On recupère le fichier .csv contenant les données du graphique
    file.open(QIODevice::ReadOnly);     //Ouverture du fichier en mode lecture uniquement

    if (file.exists()) {
        unsigned int ligne (0);         //Pour la gestion du nombre de ligne (Le nombre de ligne au demarrage est égale à 0)
        bool titreAfficher(false);      //Pour gerer l'affichage de l'en-tête (utile pour empecher que l'on recalcule à chaque fois le nombre de colonnes)
        QFileInfo fileInfo (file.fileName());
        this->setWindowTitle("Graphiques[" + fileInfo.fileName() + "]");    //Modification du nom de l'Application
        ui->widget->setFilename("Graphiques[" + fileInfo.fileName() + "].png"); //Pour avoir le nom dans lequel on enregistrera le fichier lors du sauvegardement

        while(! file.atEnd()) {
            QString fileLine = file.readLine();                                     //Lecture ligne par ligne du fichier
            QStringList tabCSV = fileLine.split(',', QString::SkipEmptyParts);      //On recupère les cellules en decoupant la ligne à l'aide du delimiter ',' et on met le contenu dans un tableau (On fait attention au cas où le fichier .csv est mal formé)
            ui->tableWidget->setRowCount((ligne+1));                                //On modifie le nombre de lignes de manière dynamique (ceci doit être fait obligatoirement avant l'insertion)
            if (! titreAfficher) {
                ui->tableWidget->setColumnCount(tabCSV.size());                     //On modifie le nombre de colonnes une et une seule fois, car elle ne varie pas
                ui->tableWidget->setHorizontalHeaderLabels(fileLine.split(","));
                titreAfficher = true;
            } else {
                for (auto colonne(0); colonne<tabCSV.length(); ++colonne) {
                    QTableWidgetItem *cellule = new QTableWidgetItem;               //On crée une nouvelle cellule contenant les données du fichier .csv
                    cellule->setText(tabCSV.at(colonne));
                    ui->tableWidget->setItem(ligne, colonne, cellule);              //On insert les données dans la QTableWidget
                }
                ++ligne;                                                            //On incremente le nombre de ligne
            }
        }
        ui->actionDessiner_un_graphique->setEnabled(true);          //ON PEUT DONNER LA POSSIBILITÉ D'EFFECTUER LE DESSIN
        ui->actionSauvegarder_le_graphique_sous->setEnabled(true);  //ON PEUT DONNER LA POSSIBILITÉ DE SAUVEGARDER LE DESSIN
        chargerDonnees();
    } else {
        qDebug() << tr("Fichier non rétrouver");
    }
    file.close();                                                                   //Fermeture du fichier lu
}

void MainWindow::on_pushButton_6_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choisissez une couleur de fond"));
    ui->pushButton_6->setStyleSheet(QString("background-color: %1").arg(color.name()));
    ui->widget->changeBackgroundColor(color);
}

void MainWindow::on_pushButton_4_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->label_4->setFont(font);
        ui->widget->changeFont(font);
        ui->pushButton_4->setText(font.family() + "," + font.styleName());
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red, this, tr("Choisissez une couleur de crayon"));
    ui->pushButton_3->setStyleSheet(QString("background-color: %1").arg(color.name()));
    ui->widget->changePenColor(color);
}

void MainWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::green, this, tr("Choisissez une couleur de crayon"));
    ui->pushButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
    ui->widget->changePenColor(color);
}

void MainWindow::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::blue, this, tr("Choisissez une couleur de crayon"));
    ui->pushButton_2->setStyleSheet(QString("background-color: %1").arg(color.name()));
    ui->widget->changePenColor(color);
}

void MainWindow::on_pushButton_5_clicked()
{
    QColor color = QColorDialog::getColor(Qt::gray, this, tr("Choisissez une couleur de crayon"));
    ui->pushButton_5->setStyleSheet(QString("background-color: %1").arg(color.name()));
    ui->widget->changeAxeColor(color);
}

void MainWindow::on_actionDessiner_un_graphique_triggered()
{
    chargerDonnees();       //ON CHARGE LES DONNÉES, PUIS ON DESSINE (UTILE LORS DE LA MODIFICATION DES CHAMPS MANUELLEMENT DE DONNÉES)
    ui->widget->dessiner();
}

void MainWindow::on_actionSauvegarder_le_graphique_sous_triggered()
{
    //Sauvegardement de l'image
    ui->widget->saved();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->widget->setWidthy(ui->widget->width() - arg1);
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    ui->widget->setHeighty(ui->widget->height() - arg1);
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    ui->widget->setWidthy(ui->widget->widthy()+arg1);
}

void MainWindow::on_spinBox_5_valueChanged(int arg1)
{
    ui->widget->setHeighty(ui->widget->heighty()+arg1);
}

void MainWindow::chargerDonnees()
{
    ui->widget->videDonnees();  //ON S'ASSURE QUE NOTRE TABLE EST VIDE

    for (int i (0); i<ui->tableWidget->rowCount(); ++i) {
        for (int j (0); j<ui->tableWidget->columnCount(); ++j) {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            QString val = item->text();
            ui->widget->ajouteDonnees(val.toFloat());           //ON INSERT LES VALEURS FLOATANTES DANS NOTRE VECTOR
        }
    }
    ui->widget->evaluerALechelle(30);
}


void MainWindow::on_comboBox_activated(int index)
{
    chargerDonnees();
    if (index == 0) {
        ui->widget->dessinerLigne();
    }
    else if (index == 1) {
        ui->widget->dessinerPoint();
    }
    else
        qDebug() << tr("Action non prise en compte !");
}

void MainWindow::on_checkBox_clicked()
{
    qDebug() << tr("Action non prise en compte !");
}

void MainWindow::on_spinBox_6_valueChanged(int)
{
    qDebug() << tr("Action non prise en compte !");
}

void MainWindow::on_spinBox_2_valueChanged(int)
{
    qDebug() << tr("Action non prise en compte !");
}
