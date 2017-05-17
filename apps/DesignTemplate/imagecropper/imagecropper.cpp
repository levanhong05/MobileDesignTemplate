#include "imagecropper.h"

#include <QMouseEvent>
#include <QPainter>

namespace {
    static const QSize WIDGET_MINIMUM_SIZE(128, 128);
}

ImageCropper::ImageCropper(QWidget* parent) :
    QWidget(parent),
    pimpl(new ImageCropperPrivate)
{
    setMinimumSize(WIDGET_MINIMUM_SIZE);
    setMouseTracking(true);
}

ImageCropper::~ImageCropper()
{
    delete pimpl;
}

void ImageCropper::setImage(const QPixmap& _image)
{
    pimpl->imageForCropping = _image;
    update();
}

void ImageCropper::setBackgroundColor(const QColor& _backgroundColor)
{
    pimpl->backgroundColor = _backgroundColor;
    update();
}

void ImageCropper::setCroppingRectBorderColor(const QColor& _borderColor)
{
    pimpl->croppingRectBorderColor = _borderColor;
    update();
}

void ImageCropper::setProportion(const QSizeF& _proportion)
{
    // Proportions are stored in the increment coefficients of the sides
    // So, if you change the size of the selection area,
    // the sizes of the sides change to a size depending on
    // increment coefficients.

    // Keep proportional dependence of the selection area in the increment coefficients of the sides
    if (pimpl->proportion != _proportion) {
        pimpl->proportion = _proportion;

        // Calculate the coefficients
        float heightDelta = (float)_proportion.height() / _proportion.width();
        float widthDelta = (float)_proportion.width() / _proportion.height();

        // We keep the coefficients
        pimpl->deltas.setHeight(heightDelta);
        pimpl->deltas.setWidth(widthDelta);
    }

    // Update the proportions of the selection area
    if ( pimpl->isProportionFixed ) {
        float croppintRectSideRelation = (float)pimpl->croppingRect.width() / pimpl->croppingRect.height();
        float proportionSideRelation = (float)pimpl->proportion.width() / pimpl->proportion.height();

        // If the selection area does not correspond to the required proportions, we will update it
        if (croppintRectSideRelation != proportionSideRelation) {
            bool widthShotrerThenHeight = pimpl->croppingRect.width() < pimpl->croppingRect.height();

            // Set the size of the side that is longer
            if (widthShotrerThenHeight) {
                pimpl->croppingRect.setHeight(pimpl->croppingRect.width() * pimpl->deltas.height());
            } else {
                pimpl->croppingRect.setWidth(pimpl->croppingRect.height() * pimpl->deltas.width());
            }

            // Redraw the widget
            update();
        }
    }
}

void ImageCropper::setProportionFixed(const bool _isFixed)
{
    if (pimpl->isProportionFixed != _isFixed) {
        pimpl->isProportionFixed = _isFixed;
        setProportion(pimpl->proportion);
    }
}

const QPixmap ImageCropper::cropImage()
{
    // Get the size of the displayed image
    QSize scaledImageSize =
            pimpl->imageForCropping.scaled(
                this->size(), Qt::KeepAspectRatio, Qt::FastTransformation
                ).size();

    // Define the distance from the left and top edges
    float leftDelta = 0;
    float topDelta = 0;
    const float HALF_COUNT = 2;

    if (this->size().height() == scaledImageSize.height()) {
        leftDelta = (this->width() - scaledImageSize.width()) / HALF_COUNT;
    } else {
        topDelta = (this->height() - scaledImageSize.height()) / HALF_COUNT;
    }

    // Define the proportion of the cropping area relative to the original image
    float xScale = (float)pimpl->imageForCropping.width()  / scaledImageSize.width();
    float yScale = (float)pimpl->imageForCropping.height() / scaledImageSize.height();

    // Calculate the area of the cropping taking into account the correction of the size of the original image
    QRectF realSizeRect(
                QPointF(pimpl->croppingRect.left() - leftDelta, pimpl->croppingRect.top() - topDelta),
                pimpl->croppingRect.size());

    // Adjust the left and upper edges
    realSizeRect.setLeft((pimpl->croppingRect.left() - leftDelta) * xScale);
    realSizeRect.setTop ((pimpl->croppingRect.top() - topDelta) * yScale);

    // Adjust the size
    realSizeRect.setWidth(pimpl->croppingRect.width() * xScale);
    realSizeRect.setHeight(pimpl->croppingRect.height() * yScale);

    // Get the cropped image
    return pimpl->imageForCropping.copy(realSizeRect.toRect());
}

// ********
// Protected section

void ImageCropper::paintEvent(QPaintEvent* _event)
{
    QWidget::paintEvent( _event );

    QPainter widgetPainter(this);
    // Draw an image in the center of the widget
    {
        // Customize the image to display by the size of the widget
        QPixmap scaledImage =
                pimpl->imageForCropping.scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation);

        // Fill in the background
        widgetPainter.fillRect( this->rect(), pimpl->backgroundColor );

        // We draw an image in the center of the widget
        if ( this->size().height() == scaledImage.height() ) {
            widgetPainter.drawPixmap( ( this->width() - scaledImage.width() ) / 2, 0, scaledImage );
        } else {
            widgetPainter.drawPixmap( 0, ( this->height() - scaledImage.height() ) / 2, scaledImage );
        }
    }
    // Draw a cropping area
    {
        // If this is the first mapping after the initiation, then center the trimming region
        if (pimpl->croppingRect.isNull()) {
            const int width = WIDGET_MINIMUM_SIZE.width()/2;
            const int height = WIDGET_MINIMUM_SIZE.height()/2;
            pimpl->croppingRect.setSize(QSize(width, height));
            float x = (this->width() - pimpl->croppingRect.width())/2;
            float y = (this->height() - pimpl->croppingRect.height())/2;
            pimpl->croppingRect.moveTo(x, y);
        }

        // Draw a darkened area
        QPainterPath p;
        p.addRect(pimpl->croppingRect);
        p.addRect(this->rect());
        widgetPainter.setBrush(QBrush(QColor(0,0,0,120)));
        widgetPainter.setPen(Qt::transparent);
        widgetPainter.drawPath(p);

        // Frame and control points
        widgetPainter.setPen(pimpl->croppingRectBorderColor);
        // Draw a rectangle of the trimming area
        {
            widgetPainter.setBrush(QBrush(Qt::transparent));
            widgetPainter.drawRect(pimpl->croppingRect);
        }
        // Draw checkpoints
        {
            widgetPainter.setBrush(QBrush(pimpl->croppingRectBorderColor));
            // Auxiliary X coordinates
            int leftXCoord   = pimpl->croppingRect.left() - 2;
            int centerXCoord = pimpl->croppingRect.center().x() - 3;
            int rightXCoord  = pimpl->croppingRect.right() - 2;

            // Auxiliary Y coordinates
            int topYCoord    = pimpl->croppingRect.top() - 2;
            int middleYCoord = pimpl->croppingRect.center().y() - 3;
            int bottomYCoord = pimpl->croppingRect.bottom() - 2;

            const QSize pointSize(6, 6);

            QVector<QRect> points;
            points
                    // left-hand side
                    << QRect( QPoint(leftXCoord, topYCoord), pointSize )
                    << QRect( QPoint(leftXCoord, middleYCoord), pointSize )
                    << QRect( QPoint(leftXCoord, bottomYCoord), pointSize )
                    // Center
                    << QRect( QPoint(centerXCoord, topYCoord), pointSize )
                    << QRect( QPoint(centerXCoord, middleYCoord), pointSize )
                    << QRect( QPoint(centerXCoord, bottomYCoord), pointSize )
                    // Right side
                    << QRect( QPoint(rightXCoord, topYCoord), pointSize )
                    << QRect( QPoint(rightXCoord, middleYCoord), pointSize )
                    << QRect( QPoint(rightXCoord, bottomYCoord), pointSize );

            widgetPainter.drawRects( points );
        }
        // Draw the dotted lines
        {
            QPen dashPen(pimpl->croppingRectBorderColor);
            dashPen.setStyle(Qt::DashLine);
            widgetPainter.setPen(dashPen);

            // Vertical
            widgetPainter.drawLine(
                        QPoint(pimpl->croppingRect.center().x(), pimpl->croppingRect.top()),
                        QPoint(pimpl->croppingRect.center().x(), pimpl->croppingRect.bottom()) );

            // Horizontal
            widgetPainter.drawLine(
                        QPoint(pimpl->croppingRect.left(), pimpl->croppingRect.center().y()),
                        QPoint(pimpl->croppingRect.right(), pimpl->croppingRect.center().y()) );
        }
    }

    widgetPainter.end();
}

void ImageCropper::mousePressEvent(QMouseEvent* _event)
{
    if (_event->button() == Qt::LeftButton) {
        pimpl->isMousePressed = true;
        pimpl->startMousePos = _event->pos();
        pimpl->lastStaticCroppingRect = pimpl->croppingRect;
    }

    updateCursorIcon(_event->pos());
}

void ImageCropper::mouseMoveEvent(QMouseEvent* _event)
{
    QPointF mousePos = _event->pos(); // About itself (widget)

    if (!pimpl->isMousePressed) {
        // Handle the normal state, i.e. The size does not change
        // the trimming area, and it does not move on the widget
        pimpl->cursorPosition = cursorPosition(pimpl->croppingRect, mousePos);
        updateCursorIcon(mousePos);
    } else if (pimpl->cursorPosition != CursorPositionUndefined) {
        // Process actions above the cropping area define the mouse cursor shift
        QPointF mouseDelta;
        mouseDelta.setX( mousePos.x() - pimpl->startMousePos.x() );
        mouseDelta.setY( mousePos.y() - pimpl->startMousePos.y() );

        if (pimpl->cursorPosition != CursorPositionMiddle) {
            // Change the size of the cropping area
            QRectF newGeometry =
                    calculateGeometry(
                        pimpl->lastStaticCroppingRect,
                        pimpl->cursorPosition,
                        mouseDelta);

            // The user tries to rotate the cropping area inside out
            if (!newGeometry.isNull()) {
                pimpl->croppingRect = newGeometry;
            }
        } else {
            // Move the cropping area
            pimpl->croppingRect.moveTo( pimpl->lastStaticCroppingRect.topLeft() + mouseDelta );
        }

        // Redraw the widget
        update();
    }
}

void ImageCropper::mouseReleaseEvent(QMouseEvent* _event)
{
    pimpl->isMousePressed = false;
    updateCursorIcon(_event->pos());
}

// ********
// Private section

namespace {
    // Is the point next to the coordinate of the side
    static bool isPointNearSide (const int _sideCoordinate, const int _pointCoordinate)
    {
        static const int indent = 10;
        return (_sideCoordinate - indent) < _pointCoordinate && _pointCoordinate < (_sideCoordinate + indent);
    }
}

CursorPosition ImageCropper::cursorPosition(const QRectF& _cropRect, const QPointF& _mousePosition)
{
    CursorPosition cursorPosition = CursorPositionUndefined;

    if ( _cropRect.contains( _mousePosition ) ) {
        // Two-way direction
        if (isPointNearSide(_cropRect.top(), _mousePosition.y()) &&
            isPointNearSide(_cropRect.left(), _mousePosition.x())) {
            cursorPosition = CursorPositionTopLeft;
        } else if (isPointNearSide(_cropRect.bottom(), _mousePosition.y()) &&
                   isPointNearSide(_cropRect.left(), _mousePosition.x())) {
            cursorPosition = CursorPositionBottomLeft;
        } else if (isPointNearSide(_cropRect.top(), _mousePosition.y()) &&
                   isPointNearSide(_cropRect.right(), _mousePosition.x())) {
            cursorPosition = CursorPositionTopRight;
        } else if (isPointNearSide(_cropRect.bottom(), _mousePosition.y()) &&
                   isPointNearSide(_cropRect.right(), _mousePosition.x())) {
            cursorPosition = CursorPositionBottomRight;
        // One-way direction
        } else if (isPointNearSide(_cropRect.left(), _mousePosition.x())) {
            cursorPosition = CursorPositionLeft;
        } else if (isPointNearSide(_cropRect.right(), _mousePosition.x())) {
            cursorPosition = CursorPositionRight;
        } else if (isPointNearSide(_cropRect.top(), _mousePosition.y())) {
            cursorPosition = CursorPositionTop;
        } else if (isPointNearSide(_cropRect.bottom(), _mousePosition.y())) {
            cursorPosition = CursorPositionBottom;
        // Without direction
        } else {
            cursorPosition = CursorPositionMiddle;
        }
    }

    return cursorPosition;
}

void ImageCropper::updateCursorIcon(const QPointF& _mousePosition)
{
    QCursor cursorIcon;

    switch (cursorPosition(pimpl->croppingRect, _mousePosition))
    {
        case CursorPositionTopRight:
        case CursorPositionBottomLeft:
            cursorIcon = QCursor(Qt::SizeBDiagCursor);
            break;
        case CursorPositionTopLeft:
        case CursorPositionBottomRight:
            cursorIcon = QCursor(Qt::SizeFDiagCursor);
            break;
        case CursorPositionTop:
        case CursorPositionBottom:
            cursorIcon = QCursor(Qt::SizeVerCursor);
            break;
        case CursorPositionLeft:
        case CursorPositionRight:
            cursorIcon = QCursor(Qt::SizeHorCursor);
            break;
        case CursorPositionMiddle:
            cursorIcon = pimpl->isMousePressed ?
                        QCursor(Qt::ClosedHandCursor) :
                        QCursor(Qt::OpenHandCursor);
            break;
        case CursorPositionUndefined:
        default:
            cursorIcon = QCursor(Qt::ArrowCursor);
            break;
    }

    this->setCursor(cursorIcon);
}

const QRectF ImageCropper::calculateGeometry(
        const QRectF& _sourceGeometry,
        const CursorPosition _cursorPosition,
        const QPointF& _mouseDelta
        )
{
    QRectF resultGeometry;

    if ( pimpl->isProportionFixed ) {
        resultGeometry =
                calculateGeometryWithFixedProportions(
                    _sourceGeometry, _cursorPosition, _mouseDelta, pimpl->deltas);
    } else {
        resultGeometry =
                calculateGeometryWithCustomProportions(
                    _sourceGeometry, _cursorPosition, _mouseDelta);
    }

    // If the user tries to turn the cropping area inside out, return null-rectangle
    if ((resultGeometry.left() >= resultGeometry.right()) ||
        (resultGeometry.top() >= resultGeometry.bottom())) {
        resultGeometry = QRect();
    }

    return resultGeometry;
}

const QRectF ImageCropper::calculateGeometryWithCustomProportions(
        const QRectF& _sourceGeometry,
        const CursorPosition _cursorPosition,
        const QPointF& _mouseDelta
        )
{
    QRectF resultGeometry = _sourceGeometry;

    switch ( _cursorPosition ) {
        case CursorPositionTopLeft:
            resultGeometry.setLeft( _sourceGeometry.left() + _mouseDelta.x() );
            resultGeometry.setTop ( _sourceGeometry.top()  + _mouseDelta.y() );
            break;
        case CursorPositionTopRight:
            resultGeometry.setTop  ( _sourceGeometry.top()   + _mouseDelta.y() );
            resultGeometry.setRight( _sourceGeometry.right() + _mouseDelta.x() );
            break;
        case CursorPositionBottomLeft:
            resultGeometry.setBottom( _sourceGeometry.bottom() + _mouseDelta.y() );
            resultGeometry.setLeft  ( _sourceGeometry.left()   + _mouseDelta.x() );
            break;
        case CursorPositionBottomRight:
            resultGeometry.setBottom( _sourceGeometry.bottom() + _mouseDelta.y() );
            resultGeometry.setRight ( _sourceGeometry.right()  + _mouseDelta.x() );
            break;
        case CursorPositionTop:
            resultGeometry.setTop( _sourceGeometry.top() + _mouseDelta.y() );
            break;
        case CursorPositionBottom:
            resultGeometry.setBottom( _sourceGeometry.bottom() + _mouseDelta.y() );
            break;
        case CursorPositionLeft:
            resultGeometry.setLeft( _sourceGeometry.left() + _mouseDelta.x() );
            break;
        case CursorPositionRight:
            resultGeometry.setRight( _sourceGeometry.right() + _mouseDelta.x() );
            break;
        default:
            break;
    }

    return resultGeometry;
}

const QRectF ImageCropper::calculateGeometryWithFixedProportions(
        const QRectF& _sourceGeometry,
        const CursorPosition _cursorPosition,
        const QPointF& _mouseDelta,
        const QSizeF& _deltas
        )
{
    QRectF resultGeometry = _sourceGeometry;

    switch (_cursorPosition) {
        case CursorPositionLeft:
            resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.x() * _deltas.height());
            resultGeometry.setLeft(_sourceGeometry.left() + _mouseDelta.x());
            break;
        case CursorPositionRight:
            resultGeometry.setTop(_sourceGeometry.top() - _mouseDelta.x() * _deltas.height());
            resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.x());
            break;
        case CursorPositionTop:
            resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.y());
            resultGeometry.setRight(_sourceGeometry.right() - _mouseDelta.y() * _deltas.width());
            break;
        case CursorPositionBottom:
            resultGeometry.setBottom(_sourceGeometry.bottom() + _mouseDelta.y());
            resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.y() * _deltas.width());
            break;
        case CursorPositionTopLeft:
            if ((_mouseDelta.x() * _deltas.height()) < (_mouseDelta.y())) {
                resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.x() * _deltas.height());
                resultGeometry.setLeft(_sourceGeometry.left() + _mouseDelta.x());
            } else {
                resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.y());
                resultGeometry.setLeft(_sourceGeometry.left() + _mouseDelta.y() * _deltas.width());
            }
            break;
        case CursorPositionTopRight:
            if ((_mouseDelta.x() * _deltas.height() * -1) < (_mouseDelta.y())) {
                resultGeometry.setTop(_sourceGeometry.top() - _mouseDelta.x() * _deltas.height());
                resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.x() );
            } else {
                resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.y());
                resultGeometry.setRight(_sourceGeometry.right() - _mouseDelta.y() * _deltas.width());
            }
            break;
        case CursorPositionBottomLeft:
            if ((_mouseDelta.x() * _deltas.height()) < (_mouseDelta.y() * -1)) {
                resultGeometry.setBottom(_sourceGeometry.bottom() - _mouseDelta.x() * _deltas.height());
                resultGeometry.setLeft(_sourceGeometry.left() + _mouseDelta.x());
            } else {
                resultGeometry.setBottom(_sourceGeometry.bottom() + _mouseDelta.y());
                resultGeometry.setLeft(_sourceGeometry.left() - _mouseDelta.y() * _deltas.width());
            }
            break;
        case CursorPositionBottomRight:
            if ((_mouseDelta.x() * _deltas.height()) > (_mouseDelta.y())) {
                resultGeometry.setBottom(_sourceGeometry.bottom() + _mouseDelta.x() * _deltas.height());
                resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.x());
            } else {
                resultGeometry.setBottom(_sourceGeometry.bottom() + _mouseDelta.y());
                resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.y() * _deltas.width());
            }
            break;
        default:
            break;
    }

    return resultGeometry;
}

