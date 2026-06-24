#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <QLabel>
#include <QString>
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

    void on_colouroffsetslider_valueChanged(int value);

    void on_colourrangeslider_valueChanged(int value);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    // morphology

    int geneSelected = 0;
    QPainter painter = QPainter();
    std::vector<QLabel*> colourLabels = decltype(colourLabels)();
    std::vector<QGraphicsView*> colourViews = decltype(colourViews)();
    std::vector<std::unique_ptr<QGraphicsScene>> colourScenes = decltype(colourScenes)();

    QGraphicsScene dragonScene = decltype(dragonScene)();

    // search

    QString colourRange = "<html><head/><body><p><span style=\" font-weight:700;\">Colour Range:</span> 5</p></body></html>";
    QString colourOffset = "<html><head/><body><p><span style=\" font-weight:700;\">Colour Offset:</span> 0</p></body></html>";;

    void updateColoursBasedOnGene(bool showDialogOnNoColour);

    void updateColours(int middleValue);

};
#endif // MAINWINDOW_H
