#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "GuidGenv2.h"

int main(int argc, char* argv[])
{

	QApplication app(argc, argv);

	GuidGen window;

	window.resize(650, 400);

	window.setWindowTitle("GuidGen by Solovev");
	window.setWindowIcon(QIcon("icon.png"));

	window.show();

	return app.exec();
}