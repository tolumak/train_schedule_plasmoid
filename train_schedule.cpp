#include "train_schedule.h"

#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsLinearLayout>

#include <plasma/svg.h>
#include <plasma/theme.h>

#include "schedule_item.h"
#include "worker.h"

PlasmaTrainSchedule::PlasmaTrainSchedule(QObject *parent, const QVariantList &args)
	: Plasma::PopupApplet(parent, args),
	  m_widget(0),
	  m_layout(0)
{
	m_widget = new QGraphicsWidget(this);
	m_layout = new QGraphicsLinearLayout(Qt::Vertical);

	if (!m_layout || !m_widget) {
		setFailedToLaunch(true, "unable to initialize");
		if (m_widget)
			delete(m_widget);
		if (m_layout)
			delete(m_layout);
		return;
	}

	Worker w;


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

	ScheduleItem * item;
	item = new ScheduleItem();
	item->setSchedule(m_schedule[0]);
	m_layout->addItem(item);

	item = new ScheduleItem();
	item->setSchedule(m_schedule[0]);
	m_layout->addItem(item);

	item = new ScheduleItem();
	item->setSchedule(m_schedule[0]);
	m_layout->addItem(item);

	m_widget->setLayout(m_layout);

#if 0
	destination = "Villefranche";
	QTime start2 = start.addSecs(3600);
	m_schedule << Schedule(destination, stations, start2, comment);
#endif
}


PlasmaTrainSchedule::~PlasmaTrainSchedule()
{
}

QGraphicsWidget * PlasmaTrainSchedule::graphicsWidget()
{
	return m_widget;
}



#include "train_schedule.moc"
