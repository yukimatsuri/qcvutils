/*
QCvImageWindow
Supported: OpenCV 2.4.3, Qt 4.8.0

Example:
QCvImageWindow* miniWindow = new QCvImageWindow();
miniWindow->setImageFromFilePath("***A.jpg");          // Optional, not depends on order of calling
miniWindow->setImageFromCvMat(cv::imread("***B.jpg")); // Optional, not depends on order of calling
miniWindow->setWindowTitle("Window title");            // Optional, not depends on order of calling (Default: "Image Window")
miniWindow->show();                                    // => Show the window of ***B.jpg (***A.jpg is not shown)
 */

#ifndef QCVIMAGEWINDOW_H
#define QCVIMAGEWINDOW_H

// When you build this without OpenCV, comment a line below:
#define QCVIMAGEWINDOW_USE_OPENCV

#include <QWidget>
// For image window.
#include <QLabel>
#include <QLayout>
// For image saving method.
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
// For Debug
#include <QDebug>

#ifdef QCVIMAGEWINDOW_USE_OPENCV
    #include <opencv2/opencv.hpp>
#endif

class QCvImageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit QCvImageWindow(QWidget *parent = 0);
    ~QCvImageWindow();

    bool setImageFromFilePath(QString);
#ifdef QCVIMAGEWINDOW_USE_OPENCV
    bool setImageFromCvMat(cv::Mat);
#endif

private:
    bool _init(void);
    bool _update(void);

    bool _updateImageLabel(void);
    bool _updateImageWindow(void);

    QVBoxLayout* _currentWindowLayout;
    QImage* _showImage;
    QLabel* _imageLabel;
#ifdef QCVIMAGEWINDOW_USE_OPENCV
    cv::Mat _cvMatForQImage;
#endif

signals:
    
public slots:

private slots:
    void contextMenu(const QPoint& pos);
    void saveCurrentImage(void);
};

#endif // QCVIMAGEWINDOW_H
