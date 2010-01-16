#include "schedule.h"


Schedule::Schedule(QString & destination,
		   QStringList & stations,
		   QTime & start,
		   QString & comment) :
	m_destination(destination),
	m_stations(stations),
	m_start(start),
	m_comment(comment)
{
}

QString Schedule::toStr()
{
	QString str = "";
	str += m_start.toString("hh:mm");
	str += " ";
	str += m_destination;
	return str;
}

QString Schedule::commaStations()
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
