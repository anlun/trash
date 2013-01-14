#include <QtCore>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	QGraphicsScene scene;

    QGraphicsView view(&scene);
    view.show();

    return app.exec();
}
