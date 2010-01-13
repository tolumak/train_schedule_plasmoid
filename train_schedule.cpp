#include "train_schedule.h"
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>

#include <plasma/svg.h>
#include <plasma/theme.h>


PlasmaTrainSchedule::PlasmaTrainSchedule(QObject *parent, const QVariantList &args)
    : Plasma::PopupApplet(parent, args)
{
}


PlasmaTrainSchedule::~PlasmaTrainSchedule()
{
}

QGraphicsWidget * PlasmaTrainSchedule::graphicsWidget()
{

	m_graphicswidget = new QGraphicsWidget();

	return m_graphicswidget;
}



#include "train_schedule.moc"
