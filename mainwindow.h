#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <QLabel>
#include <QString>
#include <QSlider>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "saveformat.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_primaryradiobutton_toggled(bool checked);

    void on_secondaryradiobutton_toggled(bool checked);

    void on_tertiaryradiobutton_toggled(bool checked);

    void on_primarycolourcombobox_currentTextChanged(const QString &text);

    void on_secondarycolourcombobox_currentTextChanged(const QString &text);

    void on_tertiarycolourcombobox_currentTextChanged(const QString &text);

    void on_breedgraphicsview_mousePressEvent(QMouseEvent *);

    void on_pushButton_clicked();

    void on_primarycolouroffsetslider_valueChanged(int value);

    void on_primarycolourrangeslider_valueChanged(int value);

    void on_secondarycolourrangeslider_valueChanged(int value);

    void on_secondarycolouroffsetslider_valueChanged(int value);

    void on_tertiarycolourrangeslider_valueChanged(int value);

    void on_tertiarycolouroffsetslider_valueChanged(int value);

    void on_gendercheckbox_stateChanged(int arg1);

    void on_currencycheckbox_stateChanged(int arg1);

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

private:
    Ui::MainWindow *ui;
    std::string loadedFile = "";

    // morphology

    int geneSelected = 0;
    QPainter painter = QPainter();
    std::vector<QLabel*> colourLabels = decltype(colourLabels)();
    std::vector<QGraphicsView*> colourViews = decltype(colourViews)();
    QString imageLocation = QString("./assets/dragon-image-select.jpg");
    std::vector<std::shared_ptr<QGraphicsScene>> colourScenes = decltype(colourScenes)();

    QGraphicsScene dragonScene = decltype(dragonScene)();

    // search

    std::vector<std::string> genderButtonStrings = decltype(genderButtonStrings)({
        "Gender: Any",
        "Gender: Female",
        "Gender: Male"
    });

    std::vector<std::string> currencyButtonStrings = decltype(genderButtonStrings)({
        "Currency: Any",
        "Currency: Gems",
        "Currency: Treasure"
    });

    void updateColoursBasedOnGene(bool showDialogOnNoColour);

    void updateColours(int middleValue);

    void updateSearchColourLabel(QLabel* label, const std::string& name, QSlider* range, QSlider* offset);

    void loadImage();

    void loadDragon(const Dragon& dragon);

    void loadSearch(const SaveFormat& save);

    SaveFormat constructSave();

    Dragon constructMorphologyDragon();

};
#endif // MAINWINDOW_H
