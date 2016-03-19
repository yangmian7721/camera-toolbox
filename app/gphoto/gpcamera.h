#ifndef GPCAMERA_H
#define GPCAMERA_H

#include "../camera.h"


#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>

#include <QMap>
#include <QList>

namespace hpis {

class GPCamera : public Camera
{
    Q_OBJECT
public:
    enum RecordingMedia {
        RecordingMediaCard = 0,
        RecordingMediaSDRAM,
        RecordingMediaBoth
    };

    enum CaptureTarget {
        CaptureTargetSDRAM = 0,
        CaptureTargetCard
    };


    explicit GPCamera(QString cameraModel, QString cameraPort, QObject *parent = 0);
    ~GPCamera();

    bool init();
    void shutdown();
    bool capturePreview(CameraPreview** cameraPreview);
    bool capturePhoto();
    bool readCameraSettings();
    bool applyCameraSettings();


    bool setCaptureMode(CaptureMode captureMode);
    CaptureMode captureMode();

    QString aperture();
    QString shutterSpeed();
    QString exposureMode();
    QString lvZoomRatio();

    bool setRecordingMedia(RecordingMedia recordingMedia);
    QString recordingMedia();

    bool setCaptureTarget(CaptureTarget captureTarget);
    QString captureTarget();


    bool increaseAperture();
    bool decreaseAperture();

    bool increaseShutterSpeed();
    bool decreaseShutterSpeed();

    bool exposureModePlus();
    bool exposureModeMinus();

    bool increaseLvZoomRatio();
    bool decreaseLvZoomRatio();

    bool changeAfArea(int x, int y);

protected:
    void reportError(QString error);
    QString errorCodeToString(int errorCode);

    bool lookupWidgets(CameraWidget* widget, QString path);
    bool refreshCameraSettings();

    bool refreshWidget(const QString& widgetName);


    bool extractWidgetChoices(CameraWidget* widget, QList<QString>& choice);


    // get widget value
    QString getRadioWidgetValue(QString widgetName);
    float getRangeWidgetValue(QString widgetName);

    // set widget
    bool setToggleWidget(QString widgetName, int toggleValue);
    bool setRangeWidget(QString widgetName, float rangeValue);
    bool setRadioWidget(QString widgetName, QString radioValue);
    bool setTextWidget(QString widgetName, QString textValue);

    // widget names
    virtual QString captureModeWidgetName();

    virtual QString apertureWidgetName();
    virtual QString shutterSpeedWidgetName();

    virtual QString liveviewSelectorWidgetName();
    virtual QString afModeWidgetName();
    virtual QString lvZoomRatioWidgetName();

    virtual QString exposureModeWidgetName();

    virtual QString afAreaWidgetName();
    virtual QString afAtWidgetName();
    virtual QString afDriveWidgetName();

    virtual QString recordingMediaWidgetName();
    virtual QString captureTargetWidgetName();


private:

    int m_cameraNumber;


    // GPhoto context
    ::GPContext*              m_context;
    ::CameraAbilitiesList*    m_abilitiesList;
    ::GPPortInfoList*         m_portInfoList;
    ::Camera*                 m_camera;
    ::CameraWidget*           m_cameraWindow;

    // Camera state
    bool m_configChanged;

    // Camera widgets
    QMap<QString, CameraWidget*> m_widgets;

    // Camera infos
    CameraAbilities m_cameraAbilities;
    QString m_cameraModel;
    QString m_cameraPort;

    // Camera settings
    CaptureMode m_captureMode;

    QList<QString> m_cameraApertures;
    int m_cameraAperture;

    QList<QString> m_cameraShutterSpeeds;
    int m_cameraShutterSpeed;

    QList<QString> m_exposureModes;
    int m_exposureMode;

    QList<QString> m_lvZoomRatios;
    int m_lvZoomRatio;

    QList<QString> m_recordingMedias;
    int m_recordingMedia;

    QList<QString> m_captureTargets;
    int m_captureTarget;

signals:

public slots:
};

}

#endif // GPCAMERA_H