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
