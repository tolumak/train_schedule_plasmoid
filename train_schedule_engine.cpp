#include <qdebug.h>
#include <QDate>
#include <QTime>
#include <iostream>

#include <Plasma/DataContainer>

#include "train_schedule_engine.h"
#include "station.h"

const QString TrainScheduleEngine::DEFAULT_STATION = Station::stationId("Lyon Part-Dieu");
const QString TrainScheduleEngine::urlFormat = "http://aln.canaltp.fr/dev/index.php?gare=%1&nbredepart=%2&datedepart=%3&heuredep=%4&modedep=1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1&alea=1262617546333&numafficheur=0";


TrainScheduleEngine::TrainScheduleEngine(QObject* parent, const QVariantList& args)
	: Plasma::DataEngine(parent, args),
	m_start(DEFAULT_START),
	m_station(DEFAULT_STATION),
	m_nb(DEFAULT_NB),
	m_interval(DEFAULT_INTERVAL)
{
	Q_UNUSED(args);

	setMinimumPollingInterval(m_interval);

	m_manager = new QNetworkAccessManager(this);

	connect(m_manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(requestFinished(QNetworkReply*)));

}

TrainScheduleEngine::~TrainScheduleEngine()
{
	delete(m_manager);
	m_manager = 0;
}


bool TrainScheduleEngine::sourceRequestEvent(const QString& name)
{
	setData(name, DataEngine::Data());
	return updateSourceEvent(name);
}

bool TrainScheduleEngine::updateSourceEvent(const QString& name)
{
	QStringList list = name.split("-");
	QString newStation = list[1];
	int newNb = list[2].toInt();
	int newStart = list[3].toInt();

	setNb(newNb);
	setStart(newStart);
	setStation(newStation);

	request();

	return true;
}


void TrainScheduleEngine::setNb(int nb)
{
	if (nb > 0 && nb <= MAX_NB)
		m_nb = nb;
}

void TrainScheduleEngine::setInterval(int interval)
{
	m_interval = interval;
}

void TrainScheduleEngine::setStation(QString stationId)
{
	m_station = stationId;
}

void TrainScheduleEngine::setStart(int start)
{
	m_start = start;
}


QUrl TrainScheduleEngine::getUrl()
{
	QTime time = QTime::currentTime().addMSecs(m_start);

	return QUrl(urlFormat.arg(m_station).arg(m_nb)
		.arg(QDate::currentDate().toString("yyyy;MM;dd"))
		    .arg(time.toString("HH;mm")));
}


void TrainScheduleEngine::request()
{
	QNetworkReply * reply;

	reply = m_manager->get(QNetworkRequest(getUrl()));

	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
		this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void TrainScheduleEngine::requestFinished(QNetworkReply * reply)
{
	QString source = QString("schedule-%1-%2-%3").arg(m_station).arg(m_nb).arg(m_start);

	QString rep = QString::fromUtf8(reply->readAll());
	QStringList strings = rep.split(QRegExp("&ligne[0-9]="));
	if (!strings.isEmpty())
		strings.removeFirst();

	QVariantList * trainList = new QVariantList();
	for (int i = 0 ; i < strings.count() ; i++) {
		*trainList << parseLine(strings[i]);
	}

	setData(source, "items", *trainList);
	delete(trainList);

	reply->deleteLater();
}

QVariant TrainScheduleEngine::parseLine(QString &line)
{
	QMap<QString,QVariant> data;
	QTime start;
	QStringList cut = line.split(";");

	QStringList HourMinute = cut[2].split(":");
	start.setHMS(HourMinute[0].toInt(), HourMinute[1].toInt(), 0);

	QStringList stations = cut[4].trimmed().split(QRegExp("\\s*,\\s*"));


	data["type"] = cut[0].trimmed();
	data["stations"] = stations;
	data["start"] = start;
	data["destination"] = cut[3].trimmed();
	data["delay"] = cut[5].trimmed();
	data["comment"] = cut[6].trimmed();
	return data;
}

void TrainScheduleEngine::slotError(QNetworkReply::NetworkError error)
{
	qDebug() << "Network error " << error;
}

K_EXPORT_PLASMA_DATAENGINE(train_schedule, TrainScheduleEngine)

#include "train_schedule_engine.moc"
