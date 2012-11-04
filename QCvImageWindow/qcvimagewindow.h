/*
QCvImageWindow

Example:
QCvImageWindow* miniWindow = new QCvImageWindow();
miniWindow->setImageFromFilePath("***A.jpg");          // Optional, not depends on order of calling
miniWindow->setImageFromCvMat(cv::imread("***B.jpg")); // Optional, not depends on order of calling
miniWindow->setWindowTitle("Window title");            // Optional, not depends on order of calling (Default: "Image Window")
miniWindow->show();                                    // => Show the window of ***B.jpg (***A.jpg is not shown)
 */

#ifndef QCVIMAGEWINDOW_H
#define QCVIMAGEWINDOW_H

// When you build this without OpenCV, uncomment a line below:
//#define QCVIMAGEWINDOW_DONT_USE_OPENCV

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

#ifndef QCVIMAGEWINDOW_DONT_USE_OPENCV
    #include <opencv2/opencv.hpp>
#endif

class QCvImageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit QCvImageWindow(QWidget *parent = 0);
    ~QCvImageWindow();

    bool setImageFromFilePath(QString);
#ifndef QCVIMAGEWINDOW_DONT_USE_OPENCV
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
#ifndef QCVIMAGEWINDOW_DONT_USE_OPENCV
    cv::Mat _cvMatForQImage;
#endif

signals:
    
public slots:

private slots:
    void contextMenu(const QPoint& pos);
    void saveCurrentImage();
};

#endif // QCVIMAGEWINDOW_H
