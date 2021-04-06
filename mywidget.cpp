#include "mywidget.h"
#include "ui_mywidget.h"
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget),  _tab()
{
    ui->setupUi(this);

    _heighty = 0;
    _widthy = 0;
    _penLines.setColor(Qt::black);
    _penLines.setWidth(4);
    _penAxes.setColor(Qt::gray);
    _penAxes.setWidth(1);
    _dessiner = false;
    _dessinePoint = false;
    _dessineLigne = true;
    _save = false;

//    initDefaultPixMap();
//            //CELA NE FONCTIONNE PAS ET JE NE SAIS PAS DU TOUT POUR QUELLE RAISON
//    update();
}

MyWidget::~MyWidget()
{
    delete ui;
//    delete _pixmap;   //LIEU AU PIXMAP
}

QPen MyWidget::penAxes() const
{
    return _penAxes;
}

void MyWidget::setPenAxes(const QPen &penAxes)
{
    _penAxes = penAxes;
}

QPen MyWidget::penLines() const
{
    return _penLines;
}

void MyWidget::setPenLines(const QPen &penLines)
{
    _penLines = penLines;
}

QString MyWidget::filename() const
{
    return _filename;
}

void MyWidget::setFilename(const QString &filename)
{
    _filename = filename;
}

void MyWidget::setWidthy(int width)
{
    _widthy = width;
}

void MyWidget::setHeighty(int height)
{
    _heighty = height;
}

int MyWidget::widthy() const
{
    return _widthy;
}

int MyWidget::heighty() const
{
    return _heighty;
}

std::vector<float> MyWidget::tab() const
{
    return _tab;
}

void MyWidget::setTab(const std::vector<float> &tab)
{
    _tab = tab;
}

void MyWidget::ajouteDonnees(float data) {
    _tab.push_back(data);
}

void MyWidget::videDonnees() {
    if (! _tab.empty())
        _tab.clear();
}

void MyWidget::changeBackgroundColor(QColor color)
{
    this->setStyleSheet(this->styleSheet() + QString("background-color: %1").arg(color.name()) + ";");
}

void MyWidget::changeFont(QFont font)
{
    this->setFont(font);
}

void MyWidget::changePenColor(QColor color)
{
    this->setStyleSheet(this->styleSheet() + QString("color: %1").arg(color.name()) + ";");
    _penLines.setColor(color);
}

void MyWidget::changeAxeColor(QColor color)
{
    this->setStyleSheet(this->styleSheet() + QString("color: %1").arg(color.name()) + ";");
    _penAxes.setColor(color);
}

void MyWidget::sauvegarder()
{
    QPixmap pixmap (this->size());
    this->render(&pixmap);
    pixmap.save(_filename);
}

void MyWidget::paintEvent(QPaintEvent *) {
    if (_save) {
        qDebug() << tr("Sauvegardement effectué ! (^_^)");
        sauvegarder();
        _save = false;
        repaint();
    } else if (_dessiner) {
        dessinerLeGraphique();
        update();                       //APRES AVOIR DESSINER, JE RÉACTUALISE LE WIDGET
    } else {
        dessinerLesAxes();
        update();                       //APRES AVOIR DESSINER, JE RÉACTUALISE LE WIDGET
    }
}

bool MyWidget::save() const
{
    return _save;
}

void MyWidget::setSave(bool save)
{
    _save = save;
}

void MyWidget::dessinerLesAxes()
{
    //    QPainter painter (_pixmap);       //LIÉ AU PIXMAP
    QPainter painter (this);
    painter.setPen(_penAxes);

    //VU QUE LA TAILLE SE REDIMENSIONNE AUTOMATIQUEMENT LORSQU'ON REDIMENSIONNE LA FIGURE, CELA GACHE UN PETIT PEU MON CODE A CE NIVEAU
    unsigned int milieuY = height() / 2;
    painter.drawLine(_widthy, milieuY, width()-_widthy, milieuY);

    unsigned int milieuX = width() / 2;
    painter.drawLine(milieuX, _heighty, milieuX, height()-_heighty);
}

void MyWidget::evaluerALechelle(unsigned int echelle)
{
    for (std::size_t i(0); i<_tab.size(); ++i)
        _tab[i] *= echelle;
}

void MyWidget::dessinerLeGraphique()
{
    //    QPainter painter (_pixmap);       //LIÉ AU PIXMAP
    dessinerLesAxes();
    QPainter painter (this);
    painter.setPen(_penLines);
//    painter.drawPixmap(45, 45, 20, 20, *_pixmap); //LIÉ AU PIXMAP
    if (_dessineLigne) {
        for (std::size_t i(0); i<_tab.size()-2; i+=2) {
            float x1 = _tab.at(i) + (width()/2);
            float y1 = _tab.at(i+1) + (height()/2);
            float x2 = _tab.at(i+2) + (width()/2);
            float y2 = _tab.at(i+3) + (height()/2);
            painter.drawLine(x1, y1, x2, y2);   //POUR ECHELLE DE 10 cm
        }
    } else if (_dessinePoint) {
        for (std::size_t i(0); i<_tab.size()-1; i+=2) {
            float x1 = _tab.at(i) + (width()/2);
            float y1 = _tab.at(i+1) + (height()/2);
            painter.drawPoint(x1, y1);                      //POUR ECHELLE DE 10 cm
        }
    } else {
        qDebug() << tr("Action non prise en charge !");
    }
}

//        //LE CODE NE FONCTIONNE PAS QUAND JE DECIDE D'INCLURE UN PIXMAP ET JE NE SAIS PAS POURQUOI
//void MyWidget::initDefaultPixMap() {
//    setMinimumSize(400, 300);
//    if(_pixmap) {
//        delete _pixmap;
//    }
//    _pixmap = new QPixmap(this->size());

//    _pixmap->load("/home/etudiant/Bureau/InterfaceGraphique/projet_IG/moi.jpg");
//    setBackgroundRole(QPalette::Base);
//    setAutoFillBackground(true);

//    QPainter painter(_pixmap);
//    painter.setPen(Qt::black);
//    painter.fillRect(rect(), this->palette().background());
//    dessinerLesAxes();
//}


/*----PAS FINI PLUS HAUT----*/
