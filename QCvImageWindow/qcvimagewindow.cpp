#include "qcvimagewindow.h"

QCvImageWindow::QCvImageWindow(QWidget *parent) :
    QWidget(parent, Qt::Window) // set Qt::Window
{
    if(! _init()){ qDebug() << "could not be initialized."; }
}


QCvImageWindow::~QCvImageWindow()
{
    if(_showImage){ delete _showImage; } // release QImage

    _imageLabel->deleteLater();
    _currentWindowLayout->deleteLater();

#ifndef QCVIMAGEWINDOW_DONT_USE_OPENCV
    _cvMatForQImage.release();
#endif
}

// Public methods
bool QCvImageWindow::setImageFromFilePath(QString filePath){
    _showImage = new QImage(filePath);
    if(_showImage->isNull()){ return false; }

    if(_update()){ return true; }
    else{ return false;}
}

#ifndef QCVIMAGEWINDOW_DONT_USE_OPENCV
// TODO: Support various type of images (cv::Mat)
bool QCvImageWindow::setImageFromCvMat(cv::Mat source){
    // do retain _cvMatForQImage(cv::Mat) !

    cv::cvtColor(source, _cvMatForQImage, CV_RGB2BGR);
    _showImage = new QImage(_cvMatForQImage.data, _cvMatForQImage.cols, _cvMatForQImage.rows, _cvMatForQImage.step, QImage::Format_RGB888);
    if(_showImage->isNull()){ return false; }

    if(_update()){ return true; }
    else{ return false;}
}
#endif

// Private methods

bool QCvImageWindow::_init(){
    _currentWindowLayout = new QVBoxLayout(this);
    if(! _currentWindowLayout){ return false; }
    setLayout(_currentWindowLayout);
    layout()->setContentsMargins(0, 0, 0, 0);

    _imageLabel = new QLabel(this);
    if(! _imageLabel){ return false; }
    _imageLabel->setText("Image not set.");
    layout()->addWidget(_imageLabel);

    setWindowTitle("Image window");

    setContextMenuPolicy(Qt::NoContextMenu);
    if(! connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(contextMenu(const QPoint&)))){ return false; }

    return true;
}

bool QCvImageWindow::_update(){
    if(! _updateImageLabel() ){ return false; }
    if(! _updateImageWindow()){ return false; }

    setContextMenuPolicy(Qt::CustomContextMenu);
    return true;
}

bool QCvImageWindow::_updateImageLabel(){
    if(! _imageLabel){ return false; }

    if(! _showImage->isNull()){
        if(_imageLabel){ delete _imageLabel; }
        _imageLabel = new QLabel(this);

        _imageLabel->setPixmap(QPixmap::fromImage(*_showImage));
        layout()->addWidget(_imageLabel);
    }

    return true;
}

bool QCvImageWindow::_updateImageWindow(){
    if(! _showImage->isNull()){
        setFixedSize(_showImage->width(), _showImage->height());
    }

    return true;
}

// Private slots

// from http://www.ffuts.org/blog/right-click-context-menus-with-qt/ and http://doc.qt.digia.com/qt/qmenu.html
void QCvImageWindow::contextMenu(const QPoint& pos)
{
    QPoint globalPos = mapToGlobal(pos);

    QMenu myMenu;
    QAction saveImage("Save", this);
    saveImage.setIconVisibleInMenu(false);
    connect(&saveImage, SIGNAL(triggered()), this, SLOT(saveCurrentImage()));

    myMenu.addAction(&saveImage);
    myMenu.exec(globalPos);
}

void QCvImageWindow::saveCurrentImage()
{
    if(! _showImage->isNull()){
        // TODO: How to ignore more than one parenthese in QFileDialog::getSaveFileName()?
        QString saveFilePath = QFileDialog::getSaveFileName(this, "Save image", "", "Images [*.jpg *.png *.tiff *.bmp] (*.jpg *.png *.tiff *.bmp))");

        // When saveFilePath is empty, QImage::save() is always failed.
        if(! saveFilePath.isEmpty()){
            // If a suffix of saveFilePath is empty, set ".jpg".
            // from  http://www.qtcentre.org/archive/index.php/t-8503.html
            QFileInfo saveFileInfo(saveFilePath);
            if(saveFileInfo.suffix().isEmpty()){ saveFilePath += ".jpg"; }

            if(_showImage->save(saveFilePath)){
                return;
            }else{
                QMessageBox saveFailedMsg(this);
                saveFailedMsg.setText("Failed to save image.");
                saveFailedMsg.exec();
            }
        }
    }
}
