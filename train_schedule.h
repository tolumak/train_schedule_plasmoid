#ifndef TrainSchedule_HEADER
#define TrainSchedule_HEADER

#include <KIcon>

#include <Plasma/PopupApplet>
#include <Plasma/Svg>


class PlasmaTrainSchedule : public Plasma::PopupApplet
{

	Q_OBJECT
public:
        // Basic Create/Destroy
        PlasmaTrainSchedule(QObject *parent, const QVariantList &args);
        ~PlasmaTrainSchedule();

	QGraphicsWidget * graphicsWidget();

private:
	QGraphicsWidget * m_graphicswidget;
};

K_EXPORT_PLASMA_APPLET(train_schedule, PlasmaTrainSchedule)

#endif
