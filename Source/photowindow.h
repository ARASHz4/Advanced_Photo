#ifndef PHOTOWINDOW_H
#define PHOTOWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFileInfo>
#include <QSystemTrayIcon>

namespace Ui {
class PhotoWindow;
}

class PhotoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PhotoWindow(QWidget *parent = 0);
    ~PhotoWindow();

    static void setPhotoAddress(const QStringList &value);
    static QStringList PhotoAddress();

    static void setPs(int value);
    static int Ps();

private:
    Ui::PhotoWindow *ui;

    QPixmap PhotoSave, pi;
    QTimer Slideshow, ScreenshotTimer, ScreenshotIconSec;
    #if defined(Q_OS_MAC)
    QTimer LoadOtherPhotosDelay;
    #endif

    static QStringList photoAddress;
    static int ps;

    QFileInfo fi;
    QSystemTrayIcon *tray;

    QString ScreenshotFile, PSize;
    int pw, ph, ww, wh, j, mbh, tbh, pw2, ph2, SaveAnswer, pst, psb, pwz, phz, rd, zoomp, IconTrayNum;
    float zw, zh;
    bool zoom, sls, pe, sph, ssh, iif, wasMax, samt;

private slots:
    void Retranslate();

    void resizeEvent(QResizeEvent *);

    void on_actionToolBarMoved_triggered();

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

    void LoadOtherPhotos();

    void ActionEnabler();

    void PhotoSelecter();

    void ProcessingPhoto();

    void SavePhoto();

    void Screenshot();

    void ScreenshotIcon();

    void Close_Photo();

    void Restore();

    void CancelScreenshot();

    void closeEvent (QCloseEvent *event);

    void on_actionOpen_Photo_triggered();

    void on_actionClose_Photo_triggered();

    void on_actionClose_All_Photos_triggered();

    void on_actionGo_to_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionOption_triggered();

    void on_actionPrint_triggered();

    void on_actionQuit_triggered();

    void on_actionScreenshot_triggered();

    void on_actionResize_triggered();

    void on_actionRotateLeft_triggered();

    void on_actionRotateRight_triggered();

    void on_actionFlip_Horizontal_triggered();

    void on_actionFlip_Vertical_triggered();

    void on_actionHome_Page_triggered();

    void on_actionAbout_triggered();

    void on_actionZoomIN_triggered();

    void on_actionZoom1_1_triggered();

    void on_actionZoomOut_triggered();

    void on_actionFitWindow_triggered();

    void on_actionPrevious_Photo_triggered();

    void on_actionSlideshow_triggered();

    void on_actionNext_Photo_triggered();

    void on_actionPhotoInfo_triggered();

    void on_actionFullscreen_triggered();

public slots:
    void Start();

    void OpenArguments(QStringList Arguments);
};

#endif // PHOTOWINDOW_H
