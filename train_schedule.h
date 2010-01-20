#ifndef TrainSchedule_HEADER
#define TrainSchedule_HEADER

#include <KIcon>

#include <Plasma/PopupApplet>
#include <Plasma/Svg>
#include <Plasma/DataEngine>
#include <QGraphicsLinearLayout>

#include "ui_config.h"

class PlasmaTrainSchedule : public Plasma::PopupApplet
{

	Q_OBJECT
public:
        PlasmaTrainSchedule(QObject *parent, const QVariantList &args);
        ~PlasmaTrainSchedule();

	QGraphicsWidget * graphicsWidget();

public slots:
        void dataUpdated(const QString &name, const Plasma::DataEngine::Data &data);
        void createConfigurationInterface(KConfigDialog *parent);
	void configurationAccepted();

private:
	void connectToEngine();

private:
	QGraphicsWidget * m_widget;
	QGraphicsLinearLayout * m_layout;

	static const int DEFAULT_INTERVAL;
	int m_interval;
	static const int DEFAULT_NB;
	int m_nb;
	static const int DEFAULT_START;
	int m_start;
	static const QString DEFAULT_STATION;
	QString m_station;
	Ui::Config ui;
};


K_EXPORT_PLASMA_APPLET(train_schedule, PlasmaTrainSchedule)

#endif
