/***************************************************************************
 *
 * Train Schedule plasmoid - show SNCF (french trains company) schedule
 *
 *    Copyright (C) 2010  Michel Lafon-Puyo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************/

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
	void init();
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
