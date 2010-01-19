#include "train_schedule.h"

#include <qdebug.h>
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsLinearLayout>

#include <plasma/svg.h>
#include <plasma/theme.h>

#include "schedule_item.h"

PlasmaTrainSchedule::PlasmaTrainSchedule(QObject *parent, const QVariantList &args)
	: Plasma::PopupApplet(parent, args),
	  m_widget(0),
	  m_layout(0),
	  m_interval(DEFAULT_INTERVAL)
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

	m_widget->setLayout(m_layout);

	setPopupIcon("application-rss+xml");

	connectEngine();
}


PlasmaTrainSchedule::~PlasmaTrainSchedule()
{
}

void PlasmaTrainSchedule::connectEngine()
{
	QString source = "schedule";

        Plasma::DataEngine* engine = dataEngine("train_schedule");
	if (!engine) {
		qDebug() << "Unable to connect to train_schedule engine";
		return;
	}
	engine->connectSource(source, this, m_interval);
}

QGraphicsWidget * PlasmaTrainSchedule::graphicsWidget()
{
	return m_widget;
}

void PlasmaTrainSchedule::dataUpdated(const QString &name, const Plasma::DataEngine::Data &data)
{
       	if (name == "schedule") {

		QVariantList items = data["items"].toList();

		while (items.count() > m_layout->count()) {
			ScheduleItem * schedItem = new ScheduleItem();
			m_layout->addItem(schedItem);
		}
		while (items.count() < m_layout->count()) {
			m_layout->removeAt(0);
		}


		for (int i = 0 ; i < items.count() ; i++) {
			QMap<QString,QVariant> item = items[i].toMap();
			qDebug() << item["comment"].toString().mid(1);
			Schedule sched(item["type"].toString(),
				       item["destination"].toString(),
				       item["stations"].toStringList(),
				       item["start"].toTime(),
				       item["delay"].toString(),
				       item["comment"].toString().mid(1));

			ScheduleItem * schedItem = dynamic_cast<ScheduleItem *>(m_layout->itemAt(i));
			schedItem->setSchedule(sched);
		}
	}

}


#include "train_schedule.moc"
