#include "qt_pgrcam.h"
#include "ui_qt_pgrcam.h"

#include <QtWidgets>

PGRCam::PGRCam(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::PGRCam),
	stopCapturing(false)
{
	ui->setupUi(this);
}

PGRCam::~PGRCam()
{
}

void PGRCam::on_connectButton_clicked()
{
	setCamera();
}

void PGRCam::on_startButton_clicked()
{
	startCamera();
}

void PGRCam::on_stopButton_clicked()
{
	stopCamera();
}

void PGRCam::setCamera()
{
	using namespace FlyCapture2;

	BusManager busMan;

	// Find PGR cameras
	unsigned int numCams;
	busMan.GetNumOfCameras(&numCams);
	if (numCams == 0)
	{
		QMessageBox msgBox(this);
		msgBox.setText(tr("No camera is detected"));
		msgBox.exec();

		// Turn off the buttons
		ui->startButton->setEnabled(false);
		ui->stopButton->setEnabled(false);

		return;
	}

	// Connect the camera
	PGRGuid guid;
	busMan.GetCameraFromIndex(0, &guid);
	camera.Connect(&guid);

	// Turn on the button
	ui->startButton->setEnabled(true);
}

void PGRCam::startCamera()
{
	using namespace FlyCapture2;

	camera.StartCapture();

	// Dummy captures
	Image dummy;
	for (int i = 0; i < 10; i++)
	{
		camera.RetrieveBuffer(&dummy);
	}

	stopCapturing = false;
	capturer = std::thread([this] { capture(); });

	// Turn on/off the button
	ui->stopButton->setEnabled(true);
	ui->startButton->setEnabled(false);
}

void PGRCam::stopCamera()
{
	using namespace FlyCapture2;

	stopCapturing = true;
	capturer.join();

	camera.StopCapture();

	// Turn on/off the button
	ui->stopButton->setEnabled(false);
	ui->startButton->setEnabled(true);
}

void PGRCam::capture()
{
	using namespace FlyCapture2;

	Image raw, conv;
	unsigned int height, width;
	unsigned int view_height, view_width;
	bool first = true;
	while (!stopCapturing)
	{
		camera.RetrieveBuffer(&raw);
		raw.Convert(PIXEL_FORMAT_RGB, &conv);
		
		if (first)
		{
			height = conv.GetRows();
			width = conv.GetCols();

			view_height = ui->view->height();
			view_width = ui->view->width();

			first = false;
		}

		// Convert into QImage
		QImage img(conv.GetData(), width, height, QImage::Format_RGB888);
		ui->view->setPixmap(QPixmap::fromImage(img).scaled(view_width, view_height, Qt::KeepAspectRatio));
		ui->view->show();
	}

}
