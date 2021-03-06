#ifndef regionChoise_H 
#define regionChoise_H

#include "QvkRegionButtonArrow.h"
#include "ui_settings.h"

#include <QWidget>

class QvkRegionChoise : public QWidget
{ 
Q_OBJECT
public:
  QvkRegionChoise();
  virtual ~QvkRegionChoise();
  int getX();
  int getY();
  int getHeight();
  int getWidth();
  int getXRecordArea();
  int getYRecordArea();

  void recordMode(bool value);
  void areaSetResolution(int width, int height);


public slots:
  void slot_areaReset();


private slots:

    
protected:
  void paintEvent( QPaintEvent *event );
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent( QMouseEvent * event );


private:
  enum Handle { NoHandle, TopLeft, TopMiddle, TopRight, RightMiddle, BottomRight, BottomMiddle, BottomLeft, LeftMiddle, Middle, Settings };
  Handle handlePressed;
  Handle handleUnderMouse;

  QColor HandleColorBackground;
  QColor HandleColorBackgroundSize;
  QColor HandleColorByMousePressed;
  void setHandleColorBackground( QColor color );
  void setHandleColorByMousePressed( QColor color );
  void setHandleColorBackgroundSize( QColor color );

  int screenWidth = 400; //Must set a value. Under windows comes a QPainter message
  int screenHeight = 400;

  int mous_delta_X_to_blueline;
  int mous_delta_Y_to_blueline;

  int old_Mouse_X;
  int old_Mouse_Y;
  int old_Frame_Width;
  int old_Frame_Height;
  int old_Frame_X2;
  int old_Frame_Y2;

  int framePenWidth;
  int framePenHalf;
  int radius;
  int diameter;
  int penWidth;
  int penHalf;

  int frame_X;
  int frame_Y;
  int frame_Width;
  int frame_height;
  int frame_min_width;
  int frame_min_height;

  QRegion regionSet;

  int pixelWidth;
  int pixelHeight;

  void drawFrame( QPainter &painter );
  void printSize(QPainter &painter);
  void HandleRecord( QPainter &painter, int x, int y, int startAngle, int spanAngle );
  void HandleTopLeft(QPainter &painter );
  void HandleTopLeftSize(QPainter &painter);
  void HandleTopMiddle(QPainter &painter);
  void HandleTopMiddleSize(QPainter &painter);
  void HandleTopRight( QPainter &painter );
  void HandleTopRightSize(QPainter &painter);
  void HandleRightMiddle(QPainter &painter);
  void HandleRightMiddleSize(QPainter &painter);
  void HandleBottomRight(QPainter &painter);
  void HandleBottomRightSize(QPainter &painter);
  void HandleBottomMiddle(QPainter &painter);
  void HandleBottomMiddleSize( QPainter &painter );
  void HandleBottomLeft(QPainter &painter);
  void HandleBottomLeftSize( QPainter &painter );
  void HandleLeftMiddle(QPainter &painter);
  void HandleLeftMiddleSize( QPainter &painter );
  void HandleMiddle(QPainter &painter);

  void vk_setGeometry( int x, int y, int with, int height );

  enum vk_platform { x11, wayland, windows };
  vk_platform platform;

  bool recordemode = false;

  //Ui_AreaSettingsDialog myUiDialog;
  //QDialog *areaSettingDialog;

};
#endif
