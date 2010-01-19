#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QList>
#include <QMutex>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>

#include "schedule.h"

class Worker: public QThread
{
	Q_OBJECT


public:
	Worker();
	~Worker();
	Schedule getNextSchedule();
	void setNb(int nb);
	void setInterval(int interval);
	void setStation(QString stationId);
	void setStart(QTime start);

protected:
	void run();

private:
	int request();
	QUrl getUrl();
	void requestFinished(QNetworkReply * reply);


private:
	const static QString urlFormat;
	const static QString host;

	QList<Schedule> m_scheduleList;
	QMutex m_mutex;
	QNetworkAccessManager m_manager;

	QTime m_start;
	QString m_station;
	int m_nb;
	int m_interval;

};

#endif
