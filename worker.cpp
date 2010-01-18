#include "worker.h"


#include <QMutexLocker>

const QMap<QString,QString> Worker::stations;


Worker::Worker()
{
	stations[QString("Lyon Part-Dieu")] = QString("OCE87723197");
	Worker::stations["Lyon Perrache"] = "OCE87722025";
	Worker::stations["Macon"] = "OCE87725689";
	Worker::stations["Ambérieu"] = "OCE87743716";
	Worker::stations["Villefranche"] = "OCE87721332";

}

Worker::~Worker()
{
}

void Worker::run()
{
}

Schedule Worker::getNextSchedule()
{
	Schedule ret;

	QMutexLocker locker(&m_mutex);

	ret = m_scheduleList.first();
	m_scheduleList.removeFirst();

	return ret;
}

QString Worker::getUrl(QTime start, QString stationId, int nb)
{
	return "";
}

