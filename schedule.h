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

#ifndef SCHEDULE_H
#define SCHEDULE_H


#include <QString>
#include <QStringList>
#include <QTime>

class Schedule {

public:
	Schedule() {};
	Schedule(
		QString type,
		QString destination,
		QStringList stations,
		QTime start,
		QString delay,
		QString comment
		);

	QString destination();
	QStringList stations();
	QString stationsStr();
	QString comment();
	QTime   start();
	QString startStr();
	QString delay();
	QString type();

	void setDestination(QString destination);
	void setStations(QStringList stations);
	void setComment(QString comment);
	void setStart(QTime start);
	void setDelay(QString delay);
	void setType(QString type);


private:
	QString m_type;
	QString m_destination;
	QStringList m_stations;
	QTime m_start;
	QString m_comment;
	QString m_delay;

};

#endif
