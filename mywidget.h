#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include <QTableWidget>
#include <QLabel>
#include <vector>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    void initDefaultPixMap();
    QPen penLines() const;
    void setPenLines(const QPen &penLines);

    QPen penAxes() const;
    void setPenAxes(const QPen &penAxes);

    QString filename() const;
    void setFilename(const QString &filename);

    int heighty() const;
    void setHeighty(int height);

    int widthy() const;
    void setWidthy(int width);

    void setSave(bool save);
    bool save() const;

    std::vector<float> tab() const;
    void setTab(const std::vector<float> &tab);
    void ajouteDonnees(float data);
    void videDonnees();

    void sauvegarder();
    void changeBackgroundColor(QColor color);
    void changeFont(QFont font);
    void changePenColor(QColor color);
    void changeAxeColor(QColor color);
    void dessinerLeGraphique();
    void dessiner() { _dessiner = true; }   //DONNE L'AUTORISATION DE DESSINER
    void dessinerLigne() { _dessineLigne = true; _dessinePoint = false; }   //DONNE L'AUTORISATION DE DESSINER UNE LIGNE
    void dessinerPoint() { _dessinePoint = true; _dessineLigne = false; }   //DONNE L'AUTORISATION DE DESSINER UN POINT
    void evaluerALechelle(unsigned int echelle=25);
    void saved() { _save = true; }

protected:
    void dessinerLesAxes();
    void paintEvent(QPaintEvent * event) override;

private:
    Ui::MyWidget *ui;

    std::vector<float> _tab;
    int _heighty;
    int _widthy;
    QPen    _penLines;
    QPen    _penAxes;
    QString _filename;
    QPixmap *_pixmap;       //CECI DEVRAIT ME PERMETTRE DE FAIRE L'AFFICHAGE DU FOND, MAIS CA NE FONCTIONNE PAS ET JE NE SAIS PAS POURQUOI
    bool    _dessiner;      //PERMET DE SAVOIR SI ON DOIT DESSINER OU PAS
    bool    _dessinePoint;
    bool    _dessineLigne;
    bool    _save;
};

#endif // MYWIDGET_H
