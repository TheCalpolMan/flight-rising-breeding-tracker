#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <QLabel>
#include <QString>
#include <QSlider>
#include <QPainter>
#include <QPointer>
#include <QComboBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QListWidgetItem>

#include "saveformat.h"
#include "lineageviewdialog.h"
#include "pairingresultsdialog.h"
#include "colourdistributiontool.h"

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

    void on_possibleparentlistwidget_itemDoubleClicked(QListWidgetItem *item);

    void on_addpairingpushbutton_clicked();

    void on_calculatepairingspushbutton_clicked();

    void on_possibleparentlistwidget_currentRowChanged(int currentRow);

    void on_namelineedit_returnPressed();

    void on_actionColour_Distribution_triggered();

    void on_pastedragonpushbutton_clicked();

    void on_childlistwidget_currentRowChanged(int currentRow);

    void on_removeRelationPushButton_clicked();

    void on_addRelationPushButton_clicked();

    void on_viewAllRelationsButton_clicked();

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

    // pairings

    QPointer<LineageViewDialog> lineageViewDialog;

    QPointer<PairingResultsDialog> pairingResultsDialog;

    std::vector<std::shared_ptr<Dragon>> possibleParentDragons = decltype(possibleParentDragons)();

    // tools

    QPointer<ColourDistributionTool> colourToolDialog;

    static std::string generateDragonTooltip(const Dragon& dragon);

    void updateColoursBasedOnGene(bool showDialogOnNoColour);

    void updateColours(int middleValue);

    void updateSearchColourLabel(QLabel* label, const std::string& name, QSlider* range, QSlider* offset);

    void loadImage();

    void loadMorphologyDragon(const Dragon& dragon);

    void loadPairingDragon(const Dragon& dragon);

    void loadSearch(const SaveFormat& save);

    bool checkEditableComboBox(const QComboBox* targetBox, bool createDialog, const std::string& dialogText = "");

    bool checkAllMorphologyInputs(bool createDialog);

    bool checkAllPairingInputs(bool createDialog);

    void updatePossibleParentDragons();

    void updateLineages(std::shared_ptr<Dragon> target);

    void pruneExpiredLineages();

    SaveFormat constructSave();

    Dragon constructMorphologyDragon();

    Dragon constructPairingDragon();

};
#endif // MAINWINDOW_H
