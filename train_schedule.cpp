#include "train_schedule.h"

#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsGridLayout>

#include <plasma/svg.h>
#include <plasma/theme.h>


PlasmaTrainSchedule::PlasmaTrainSchedule(QObject *parent, const QVariantList &args)
	: Plasma::PopupApplet(parent, args),
	  m_graphicsWidget(0)
{
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

	Plasma::Label * m_label;
	QGraphicsLinearLayout * layout;

	m_layout = new QGraphicsGridLayout();

	for (int i = 0 ; i < m_schedule.length() ; i++) {


		m_label = new Plasma::Label;
		m_label->setText(m_schedule[i].toStr());
		m_layout->addItem(m_label, i * 2, 0);
		m_label = new Plasma::Label;
		m_label->setText(m_schedule[i].comment());
		m_layout->addItem(m_label, i * 2, 1);
		m_label = new Plasma::Label;
		m_label->setText(m_schedule[i].commaStations());
		m_layout->addItem(m_label, i * 2 + 1, 0, 1, 2);
	}

	m_graphicsWidget = new QGraphicsWidget(this);
	m_graphicsWidget->setLayout(m_layout);


	return m_graphicsWidget;
}



#include "train_schedule.moc"
