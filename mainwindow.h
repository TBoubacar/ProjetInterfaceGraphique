#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QStandardItem>
#include <QDebug>
#include <QPixmap>
#include <sstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_checkBox_clicked();

    void on_actionQuitter_triggered();

    void on_actionCharger_triggered();

    void on_action_propos_de_Qt_triggered();

    void on_action_propos_de_Graphiques_triggered();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_actionDessiner_un_graphique_triggered();

    void on_actionSauvegarder_le_graphique_sous_triggered();

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_5_valueChanged(int arg1);

    void on_comboBox_activated(int index);

    void on_checkBox_clicked();

    void on_spinBox_6_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

protected:
    void chargerFichierCSV(const QString & filename);
    void chargerDonnees();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
