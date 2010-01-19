#include "schedule.h"


Schedule::Schedule(QString type,
		   QString destination,
		   QStringList stations,
		   QTime start,
		   QString delay,
		   QString comment) :
	m_type(type),
	m_destination(destination),
	m_stations(stations),
	m_start(start),
	m_comment(comment),
	m_delay(delay)
{
}

QTime Schedule::start()
{
	return m_start;
}

QString Schedule::startStr()
{
	return m_start.toString("hh:mm");
}

QString Schedule::destination()
{
	return m_destination;
}

QStringList Schedule::stations()
{
	return m_stations;
}

QString Schedule::stationsStr()
{
	int i;
	QString str = "";
	for (i = 0 ; i < m_stations.length() - 1; i++) {
		str += m_stations[i];
		str += ", ";
	}
	str += m_stations[i];

	return str;
}

QString Schedule::comment()
{
	return m_comment;
}

QString Schedule::delay()
{
	return m_delay;
}

QString Schedule::type()
{
	return m_type;
}

void Schedule::setDestination(QString destination)
{
	m_destination = destination;
}

void Schedule::setStations(QStringList stations)
{
	m_stations = stations;
}

void Schedule::setComment(QString comment)
{
	m_comment = comment;
}

void Schedule::setStart(QTime start)
{
	m_start = start;
}

void Schedule::setDelay(QString delay)
{
	m_delay = delay;
}

void Schedule::setType(QString type)
{
	m_type = type;
}
