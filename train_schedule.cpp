#include "train_schedule.h"

#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsGridLayout>

#include <plasma/svg.h>
#include <plasma/theme.h>


PlasmaTrainSchedule::PlasmaTrainSchedule(QObject *parent, const QVariantList &args)
	: Plasma::PopupApplet(parent, args),
	  m_graphicsWidget(0),
	  m_layout(0),
	  m_scene(0),
	  m_view(0)
{


	m_scene = new QGraphicsScene();
	m_view = new QGraphicsView();

	if (!m_scene || !m_view) {
		setFailedToLaunch(true, "unable to initialize");
		if (m_scene)
			delete(m_scene);
		if (m_view)
			delete(m_view);
		return;
	}

	m_view->setScene(m_scene);












	QStringList stations;
	QString destination = "Amberieu";
	QString comment = "toto";
	QTime start = QTime::currentTime();

	setPopupIcon("application-rss+xml");

	stations << "Miribel";
	stations << "Beynost";
	stations << "St Maurice de Beynost";
	stations << "Montluel";
	stations << "La Valbonne";
	stations << "Meximieux-Perouge";
	stations << "Amberieu";

	m_schedule << Schedule(destination, stations, start, comment);

	destination = "Villefranche";
	QTime start2 = start.addSecs(3600);
	m_schedule << Schedule(destination, stations, start2, comment);

}


PlasmaTrainSchedule::~PlasmaTrainSchedule()
{
}

QGraphicsWidget * PlasmaTrainSchedule::graphicsWidget()
{
	if (m_graphicsWidget) {
		return m_graphicsWidget;
	}

	return m_graphicsWidget;
}



#include "train_schedule.moc"
