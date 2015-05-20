#ifndef PHOTOWINDOW_H
#define PHOTOWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFileInfo>

namespace Ui {
class PhotoWindow;
}

class PhotoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PhotoWindow(QWidget *parent = 0);
    ~PhotoWindow();

    QPixmap PhotoSave,pi;
    QTimer *Slideshow = new QTimer();
    QFileInfo fi;

private slots:

    void showEvent(QShowEvent *);

    void resizeEvent (QResizeEvent *);

    void on_actionToolBarMoved_triggered();

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

    void on_actionOpen_triggered();

    void ActionEnabler();

    void PhotoSelecter();

    void ProcessingPhoto();

    void SavePhoto();

    void on_actionZoomIN_triggered();

    void on_actionZoom1_1_triggered();

    void on_actionZoomOut_triggered();

    void on_actionFitWindow_triggered();

    void on_actionRotateLaft_triggered();

    void on_actionRotateRight_triggered();

    void on_actionFlip_Horizontal_triggered();

    void on_actionFlip_Vertical_triggered();

    void on_actionResize_triggered();

    void on_actionPrevious_Photo_triggered();

    void on_actionSlideshow_triggered();

    void on_actionNext_Photo_triggered();

    void on_actionPhotoInfo_triggered();

    void on_actionFullscreen_triggered();

    void on_actionOption_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionPrint_triggered();

    void on_actionQuit_triggered();

    void on_actionHome_Page_triggered();

    void on_actionAbout_triggered();

    void closeEvent (QCloseEvent *event);

private:
    Ui::PhotoWindow *ui;
};

#endif // PHOTOWINDOW_H
