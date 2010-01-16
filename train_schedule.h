#ifndef TrainSchedule_HEADER
#define TrainSchedule_HEADER

#include <KIcon>

#include <Plasma/PopupApplet>
#include <Plasma/Svg>
#include <Plasma/Label>

#include "schedule.h"

namespace Plasma {
  class Label;
}
class QGraphicsGridLayout;


class PlasmaTrainSchedule : public Plasma::PopupApplet
{

	Q_OBJECT
public:
        // Basic Create/Destroy
        PlasmaTrainSchedule(QObject *parent, const QVariantList &args);
        ~PlasmaTrainSchedule();

	QGraphicsWidget * graphicsWidget();

private:
	QGraphicsWidget * m_graphicsWidget;
	QGraphicsGridLayout * m_layout;

	QList<Schedule> m_schedule;
};

K_EXPORT_PLASMA_APPLET(train_schedule, PlasmaTrainSchedule)

#endif
