#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QList>
#include <QMutex>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>

#include "schedule.h"

class Worker : public QObject
{
	Q_OBJECT


public:
	const static int DEFAULT_NB = 4;
	const static int DEFAULT_INTERVAL = 5;
	const static QString  DEFAULT_STATION;

public:
	Worker();
	~Worker();
	Schedule getNextSchedule();
	void setNb(int nb);
	void setInterval(int interval);
	void setStation(QString stationId);
	void setStart(QTime start);

	void request();
protected:
	void run();

public slots:
	void requestFinished(QNetworkReply * reply);
	void slotError(QNetworkReply::NetworkError error);

private:
	QUrl getUrl();

private:
	const static QString urlFormat;

	QList<Schedule> m_scheduleList;
	QMutex m_mutex;
	QNetworkAccessManager * m_manager;

	QTime m_start;
	QString m_station;
	int m_nb;
	int m_interval;

};

#endif
