#ifndef MAINWINDOW_H
#define MAINWINDOW_H


//#include "histogram/histogram.h"
//#include "histogram/imageanalyzer.h"



#include "camerathread.h"

#include <QOpenGLWindow>
#include <QMap>



#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-port-info-list.h>


using namespace hpis;

namespace Ui {
class MainWindow;
}

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    explicit MainWindow(CameraThread* camera);
    ~MainWindow();

protected:
    int findWidgets(CameraWidget* widget);

    // Events
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *ev) Q_DECL_OVERRIDE;
    void calcImageRect();

private:
    // Timers
    QTimer*                 m_lookupCameraTimer;
    QTimer*                 m_liveviewTimer;

    // Threads
    CameraThread* m_cameraThread;

    // Data
    int m_overscanLeft;
    int m_overscanRight;
    int m_overscanTop;
    int m_overscanBottom;

    QPixmap m_preview;
    QImage m_image;
    float m_fps;
    QRect m_imageRect;

    CameraStatus m_cameraStatus;

   // ImageAnalyzer* m_imageAnalyzer;
   // HistogramDisplay* m_histogramDisplay;

public slots:
    void showPreview(QPixmap preview);
    void showImage(QImage image);
    void cameraStatus(hpis::CameraStatus cameraStatus);
    //void lookupCamera();
};

#endif // MAINWINDOW_H
