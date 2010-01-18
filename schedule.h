#ifndef SCHEDULE_H
#define SCHEDULE_H


#include <QString>
#include <QStringList>
#include <QTime>

class Schedule {

public:
	Schedule() {};
	Schedule(QString & destination,
		 QStringList & stations,
		 QTime & start,
		 QString & comment);

	QString destination();
	QString stations();
	QString comment();
	QString start();

private:
	QString m_destination;
	QStringList m_stations;
	QTime m_start;
	QString m_comment;

};

#endif
