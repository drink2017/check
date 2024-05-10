#include "screenshotlabel.h"
#include "commandmanager.h"

#include <QWheelEvent>
#include <QDebug>
#include <QVBoxLayout>

screenshotLabel::screenshotLabel(QWidget* parent) : QLabel(parent)
{

}


void screenshotLabel::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15;

    // 根据滚轮滚动方向更新当前显示的图片索引
    int currentImageIndex = verticalScrollBar->value();
    currentImageIndex -= numSteps;

    // 处理边界情况，确保图片索引在合法范围内
    if (currentImageIndex < 0)
        currentImageIndex = 0;
    else if (currentImageIndex >= commandManager::getInstance()->screenshots.size())
        currentImageIndex = commandManager::getInstance()->screenshots.size() - 1;

    verticalScrollBar->setValue(currentImageIndex);

    // 在label中显示对应索引的图片
    changeScreenshot(currentImageIndex);

    event->accept();
}

void screenshotLabel::changeScreenshot(int value){
    if(commandManager::getInstance()->screenshots.size() > 0){
        QPixmap screenshot;
        screenshot = commandManager::getInstance()->screenshots.at(value).scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        setPixmap(screenshot);
        label_headline->setText(commandManager::getInstance()->headlines.at(value));
    }
}


void screenshotLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(pixmap()){
        QWidget* originalWidget = new QWidget;
        originalWidget->setWindowTitle("Original Pixmap");
        QVBoxLayout* layout = new QVBoxLayout(originalWidget);
        QLabel* originalLabel = new QLabel;
        int value = verticalScrollBar->value();
        originalLabel->setPixmap(commandManager::getInstance()->screenshots.at(value));
        originalLabel->setScaledContents(true);
        layout->addWidget(originalLabel);

        originalWidget->resize(pixmap()->copy().size());
        originalWidget->setStyleSheet("background-color: gray;");
        originalWidget->setGeometry(0,0,originalWidget->width(),originalWidget->height());
        originalWidget->show();
    }
}
