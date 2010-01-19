#ifndef TrainSchedule_HEADER
#define TrainSchedule_HEADER

#include <KIcon>

#include <Plasma/PopupApplet>
#include <Plasma/Svg>
#include <Plasma/DataEngine>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLinearLayout>


#include "schedule.h"

class PlasmaTrainSchedule : public Plasma::PopupApplet
{

	Q_OBJECT
public:
        PlasmaTrainSchedule(QObject *parent, const QVariantList &args);
        ~PlasmaTrainSchedule();

	QGraphicsWidget * graphicsWidget();

public slots:
        void dataUpdated(const QString &name, const Plasma::DataEngine::Data &data);

private:
	void connectEngine();

private:
	QGraphicsWidget * m_widget;
	QGraphicsLinearLayout * m_layout;

	QList<Schedule> m_schedule;

	static const int DEFAULT_INTERVAL = 1000;
	int m_interval;
};


K_EXPORT_PLASMA_APPLET(train_schedule, PlasmaTrainSchedule)

#endif
