#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QList>
#include <QMap>
#include <QMutex>

#include "schedule.h"

class Worker: public QThread
{
	Q_OBJECT

public:
	static const QMap<QString,QString> stations;

public:
	Worker();
	~Worker();
	Schedule getNextSchedule();

protected:
	void run();

private:
	QString getUrl(QTime start, QString station, int nb);
	QString getStationId(QString station);

private:
	QList<Schedule> m_scheduleList;
	QMutex m_mutex;



};

#endif
