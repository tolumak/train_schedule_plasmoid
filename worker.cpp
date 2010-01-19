#include <qdebug.h>
#include <QMutexLocker>
#include <QDate>
#include <QTime>
#include <iostream>

#include "worker.h"
#include "station.h"

const QString Worker::DEFAULT_STATION = Station::stationId("Lyon Part-Dieu");
const QString Worker::urlFormat = "http://aln.canaltp.fr/dev/index.php?gare=%1&nbredepart=%2&datedepart=%3&heuredep=%4&modedep=1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1&alea=1262617546333&numafficheur=0";


Worker::Worker()/*:
	m_start(QTime::currentTime()),
	m_station(DEFAULT_STATION),
	m_nb(DEFAULT_NB),
	m_interval(DEFAULT_INTERVAL)*/
{
	m_manager = new QNetworkAccessManager(this);

	connect(m_manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(requestFinished(QNetworkReply*)));

	qDebug() << "toto";
}

Worker::~Worker()
{
	delete(m_manager);
	m_manager = 0;
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


void Worker::request()
{
	QNetworkReply * reply;

	reply = m_manager->get(QNetworkRequest(QUrl("http://qt.nokia.com/index.html")));

/*	if (reply->error() != QNetworkReply::NoError)
 		qDebug() << "request error: " << getUrl().toString();
*/
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
		this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void Worker::requestFinished(QNetworkReply * reply)
{
	qDebug() << "tata";
	QString str;
	do {
		str = reply->readLine();
	}while(!str.isEmpty());
	std::cout << qPrintable(str) << std::endl;

	reply->deleteLater();
}

void Worker::slotError(QNetworkReply::NetworkError error)
{
	qDebug() << error;
}

