#include "train_schedule.h"

#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsLinearLayout>

#include <plasma/svg.h>
#include <plasma/theme.h>


PlasmaTrainSchedule::PlasmaTrainSchedule(QObject *parent, const QVariantList &args)
	: Plasma::PopupApplet(parent, args),
	  m_graphicsWidget(0)
{
	setPopupIcon("application-rss+xml");
}


PlasmaTrainSchedule::~PlasmaTrainSchedule()
{
}

QGraphicsWidget * PlasmaTrainSchedule::graphicsWidget()
{
	if (m_graphicsWidget) {
		return m_graphicsWidget;
	}

	m_label = new Plasma::Label;
	m_label->setText("Hello world!");
	m_layout = new QGraphicsLinearLayout(Qt::Vertical);
	m_layout->addItem(m_label);
	m_graphicsWidget = new QGraphicsWidget(this);
	m_graphicsWidget->setLayout(m_layout);

	m_graphicsWidget->setPreferredSize(370,440);
	//a tiny minimum size, a panel 48px high is enough to display the whole applet
	m_graphicsWidget->setMinimumSize(150, 48);


	return m_graphicsWidget;
}



#include "train_schedule.moc"
