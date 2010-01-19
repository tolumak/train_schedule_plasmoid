#include "schedule_item.h"

#include <QWidget>
#include <Plasma/Theme>

ScheduleItem::ScheduleItem()
{
	m_destination = new Plasma::Label();
	m_comment = new Plasma::Label();
	m_start = new Plasma::Label();
	m_stations = new Plasma::Label();
	m_delay = new Plasma::Label();
	m_layout = new QGraphicsGridLayout();

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

	m_layout->addItem(m_start, 0, 0);
	m_layout->addItem(m_destination, 0, 1);
	m_layout->addItem(m_stations, 1, 0, 1, 2);
	m_layout->addItem(m_delay, 2, 0);
	m_layout->addItem(m_comment, 2, 1);

	m_destination->setAlignment(Qt::AlignLeft);
	m_layout->setColumnAlignment(0, Qt::AlignLeft);
	m_layout->setColumnAlignment(1, Qt::AlignLeft);
	m_layout->setColumnFixedWidth(0, 75);

	m_comment->widget()->setStyleSheet("QLabel { color : red; }");
	m_delay->widget()->setStyleSheet("QLabel { color : red; }");


	QFont littleFont = Plasma::Theme::defaultTheme()->font(Plasma::Theme::DefaultFont);
	littleFont.setPointSize(littleFont.pointSize() - 2);
	m_stations->widget()->setFont(littleFont);

	setPreferredWidth(400);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed, QSizePolicy::GroupBox);

	setLayout(m_layout);
}

ScheduleItem::~ScheduleItem()
{
}

void ScheduleItem::setSchedule(Schedule & sched)
{
	m_destination->setText(sched.destination());
	m_start->setText(sched.startStr());
	m_stations->setText(sched.stationsStr());

	if (sched.comment().isEmpty()) {
		m_comment->hide();
	} else {
		m_comment->setText(sched.comment());
		m_comment->show();
	}

	if (sched.delay().isEmpty()) {
		m_delay->hide();
	} else {
		m_delay->setText(sched.delay());
		m_delay->show();
	}


}
