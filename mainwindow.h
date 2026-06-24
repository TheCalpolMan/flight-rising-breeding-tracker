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

private:
    Ui::MainWindow *ui;

    // morphology

    int geneSelected = 0;
    QPainter painter = QPainter();
    std::vector<QLabel*> colourLabels = decltype(colourLabels)();
    std::vector<QGraphicsView*> colourViews = decltype(colourViews)();
    std::vector<std::shared_ptr<QGraphicsScene>> colourScenes = decltype(colourScenes)();

    QGraphicsScene dragonScene = decltype(dragonScene)();

    // search

    void updateColoursBasedOnGene(bool showDialogOnNoColour);

    void updateColours(int middleValue);

    void updateSearchColourLabel(QLabel* label, QSlider* range, QSlider* offset);

};
#endif // MAINWINDOW_H
