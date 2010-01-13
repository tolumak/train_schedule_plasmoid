#ifndef TrainSchedule_HEADER
#define TrainSchedule_HEADER

#include <KIcon>

#include <Plasma/PopupApplet>
#include <Plasma/Svg>
#include <Plasma/Label>

namespace Plasma {
  class Label;
}
class QGraphicsLinearLayout;


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
	Plasma::Label * m_label;
	QGraphicsLinearLayout * m_layout;
};

K_EXPORT_PLASMA_APPLET(train_schedule, PlasmaTrainSchedule)

#endif
