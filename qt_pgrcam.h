#ifndef _QT_PGRCAM_H
#define _QT_PGRCAM_H

#include <future>

#include <qmainwindow.h>

#include <FlyCapture2.h>

namespace Ui { class PGRCam; }

class PGRCam : public QMainWindow
{
	Q_OBJECT

public:
	explicit PGRCam(QWidget *parent = 0);
	~PGRCam();

private slots:
	// Controllers
	void on_connectButton_clicked();
	void on_startButton_clicked();
	void on_stopButton_clicked();

	// Camera
	void setCamera();
	void startCamera();
	void stopCamera();
	void capture();
	
private:
	Ui::PGRCam *ui;

	FlyCapture2::Camera camera;

	bool stopCapturing;

	std::thread capturer;

};

#endif //_QT_PGRCAM_H