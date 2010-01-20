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

#ifndef SCHEDULE_ITEM_H
#define SCHEDULE_ITEM_H

#include <QGraphicsWidget>
#include <QPainter>
#include <Plasma/Label>
#include <QGraphicsGridLayout>

#include "schedule.h"

class ScheduleItem: public QGraphicsWidget
{
public:
	ScheduleItem();
	~ScheduleItem();

	void setSchedule(Schedule & sched);

private:
	Plasma::Label * m_destination;
	Plasma::Label * m_comment;
	Plasma::Label * m_start;
	Plasma::Label * m_stations;
	Plasma::Label * m_delay;
	QGraphicsGridLayout * m_layout;
};

#endif
