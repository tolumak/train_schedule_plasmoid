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

#include "schedule_item.h"

#include <QWidget>
#include <QLabel>
#include <Plasma/Theme>
#include <QGraphicsSceneResizeEvent>


ScheduleItem::ScheduleItem(QGraphicsItem * parent, Qt::WindowFlags wFlags):
	QGraphicsWidget(parent, wFlags)
{
	QFont defaultFont = Plasma::Theme::defaultTheme()->font(Plasma::Theme::DefaultFont);

	m_destination = new Plasma::Label(this);
	m_comment = new Plasma::Label(this);
	m_start = new Plasma::Label(this);
	m_stations = new Plasma::Label(this);
	m_delay = new Plasma::Label(this);
	m_layout = new QGraphicsGridLayout(this);

	if (!m_destination ||
	    !m_comment ||
	    !m_start ||
	    !m_stations ||
	    !m_layout) {
		if (m_destination)
			delete(m_destination);
		if (m_comment)
			delete(m_comment);
		if (m_start)
			delete(m_start);
		if (m_stations)
			delete(m_stations);
		if (m_layout)
			delete(m_layout);
		return;
	}

	m_destination->nativeWidget()->setWordWrap(false);
	m_comment->nativeWidget()->setWordWrap(false);
	m_start->nativeWidget()->setWordWrap(false);
	m_delay->nativeWidget()->setWordWrap(false);

	m_layout->addItem(m_start, 0, 0);
	m_layout->addItem(m_destination, 0, 1);
	m_layout->addItem(m_stations, 1, 0, 1, 2);
	m_layout->addItem(m_delay, 2, 0);
	m_layout->addItem(m_comment, 2, 1);

	m_layout->setColumnFixedWidth(0, 65);

	m_comment->setStyleSheet("QLabel { color : red; }");
	m_delay->setStyleSheet("QLabel { color : red; }");
//	m_stations->setStyleSheet("QLabel { border : 1px solid white; }");


	QFont littleFont = defaultFont;
	littleFont.setPointSize(littleFont.pointSize() - 2);
	m_stations->widget()->setFont(littleFont);

	setPreferredWidth(400);

	setLayout(m_layout);
}

ScheduleItem::~ScheduleItem()
{
}

void ScheduleItem::setSchedule(Schedule & sched)
{
	int h;
	QFont defaultFont = Plasma::Theme::defaultTheme()->font(Plasma::Theme::DefaultFont);
	m_destination->setText(QString("%1 (%2)").
			       arg(sched.destination()).
			       arg(sched.type()));

	m_start->setText(sched.startStr());
	m_stations->setText(sched.stationsStr());
	h = m_stations->nativeWidget()->heightForWidth(size().width());
	m_stations->setMinimumHeight(h);
	m_stations->setPreferredHeight(h);

	m_comment->setText(sched.comment());
	m_delay->setText(sched.delay());

	while (m_layout->count() > 3)
		m_layout->removeAt(3);

	if (!sched.delay().isEmpty()) {
		m_layout->addItem(m_delay, 2, 0);
	}

	if  (!sched.comment().isEmpty()) {
		m_layout->addItem(m_comment, 2, 1);
	}

	adjustSize();
}

void ScheduleItem::resizeEvent(QGraphicsSceneResizeEvent * event)
{
	int h;
	h = m_stations->nativeWidget()->heightForWidth(event->newSize().width());
	m_stations->setMinimumHeight(h);
	m_stations->setPreferredHeight(h);

}
