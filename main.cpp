#include "qt_pgrcam.h"

#include <QtWidgets>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	PGRCam camera;
	camera.show();

	return app.exec();
}
