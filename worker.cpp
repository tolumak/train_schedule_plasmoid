#include <QMutexLocker>
#include <QDate>
#include <QTime>
#include <iostream>

#include "worker.h"


const QString Worker::urlFormat = "http://aln.canaltp.fr/dev/index.php?gare=%1&nbredepart=%2&datedepart=%3&heuredep=%4&modedep=1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1&alea=1262617546333&numafficheur=0";
const QString Worker::host = "aln.canaltp.fr";


Worker::Worker()
{
	connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(requestFinished(QNetworkReply*)));
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

void Worker::setNb(int nb)
{
	m_nb = nb;
}

void Worker::setInterval(int interval)
{
	m_interval = interval;
}

void Worker::setStation(QString stationId)
{
	m_station = stationId;
}

void Worker::setStart(QTime start)
{
	m_start = start;
}


QUrl Worker::getUrl()
{
	return QUrl(urlFormat.arg(m_station).arg(m_nb)
		.arg(QDate::currentDate().toString("yyyy;MM;dd"))
		    .arg(m_start.toString("HH;mm")));
}


int Worker::request()
{
	QNetworkReply * reply;
	QNetworkRequest request(getUrl());

	reply = m_manager.get(request);

	if (reply->error() == QNetworkReply::NoError)
		return 0;
	else
		return -1;
}

void Worker::requestFinished(QNetworkReply * reply)
{
	QString str;
	do {
		str = reply->readLine();
	}while(!str.isEmpty());
	std::cout << qPrintable(str) << std::endl;

	reply->deleteLater();
}

