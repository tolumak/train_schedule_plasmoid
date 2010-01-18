#ifndef TrainSchedule_HEADER
#define TrainSchedule_HEADER

#include <KIcon>

#include <Plasma/PopupApplet>
#include <Plasma/Svg>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLinearLayout>


#include "schedule.h"
#include "worker.h"

class PlasmaTrainSchedule : public Plasma::PopupApplet
{

	Q_OBJECT
public:
        // Basic Create/Destroy
        PlasmaTrainSchedule(QObject *parent, const QVariantList &args);
        ~PlasmaTrainSchedule();

	QGraphicsWidget * graphicsWidget();

private:
	QGraphicsWidget * m_widget;
	QGraphicsLinearLayout * m_layout;

	QList<Schedule> m_schedule;
};


K_EXPORT_PLASMA_APPLET(train_schedule, PlasmaTrainSchedule)

#endif
