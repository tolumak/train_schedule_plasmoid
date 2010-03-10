/***************************************************************************
 *
 * Train Schedule plasmoid - show SNCF (french trains company) schedule
 *
 *    Copyright (C) 2010  Michel Lafon-Puyo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************/

#include <kdebug.h>
#include <QDate>
#include <QTime>

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
}

TrainScheduleEngine::~TrainScheduleEngine()
{
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


KUrl TrainScheduleEngine::getUrl()
{
	QTime time = QTime::currentTime().addMSecs(m_start);

	return KUrl(urlFormat.arg(m_station).arg(m_nb)
		.arg(QDate::currentDate().toString("yyyy;MM;dd"))
		    .arg(time.toString("HH;mm")));
}


void TrainScheduleEngine::request()
{
	KIO::TransferJob *job;
	job = KIO::get(getUrl(), KIO::Reload, KIO::HideProgressInfo);
	connect(job, SIGNAL(result(KJob *)),
		this, SLOT(resultReceived(KJob *)));
	connect(job, SIGNAL(data(KIO::Job *, const QByteArray &)),
		this, SLOT(dataReceived(KIO::Job *, const QByteArray &)));
}

void TrainScheduleEngine::resultReceived(KJob *job)
{
	if (job->error()) {
		kDebug() << job->errorString();
	}
}

void TrainScheduleEngine::dataReceived(KIO::Job *job, const QByteArray &data)
{
	Q_UNUSED(job);

	QString source = QString("schedule-%1-%2-%3").arg(m_station).arg(m_nb).arg(m_start);

	QString rep = QString::fromUtf8(data);

	QStringList strings = rep.split(QRegExp("&ligne[0-9]="));

	// Remove blabla...
	if (!strings.isEmpty())
		strings.removeFirst();

	// If there is something left in the list it deserves
	// to be treated!
	if (!strings.isEmpty()) {
		QVariantList * trainList = new QVariantList();
		for (int i = 0 ; i < strings.count() ; i++) {
			*trainList << parseLine(strings[i]);
		}

		setData(source, "items", *trainList);
		delete(trainList);
	}
}


QVariant  TrainScheduleEngine::parseLine(QString &line)
{
	QMap<QString,QVariant> data;
	QTime start;
	QStringList cut = line.split(";");

	if (cut.count() >= 5) {
		QStringList HourMinute = cut[2].split(":");
		start.setHMS(HourMinute[0].toInt(), HourMinute[1].toInt(), 0);

		QStringList stations = cut[4].trimmed().split(QRegExp("\\s*,\\s*"));

		data["type"] = cut[0].trimmed();
		data["stations"] = stations;
		data["start"] = start;
		data["destination"] = cut[3].trimmed();

		if (cut.count() >= 6) {
			data["delay"] = cut[5].trimmed();
		}
		else {
			data["delay"] = "";
		}

		if (cut.count() >= 7) {
			// the data are a mix of Utf8 and Latin-1 characters
			// so the following lines are ugly but... it works
			if (cut[6][0] == 65533) {
				cut[6].remove(0, 1);
			}
			data["comment"] = cut[6].trimmed();
		} else {
			data["comment"] = "";
		}
	}
	else {
		data["type"] = "Unknown";
		data["start"] = start.setHMS(0,0,0);
		data["destination"] = "Unknown";
		data["stations"] = QStringList();
		data["comment"] = "";
		data["delay"] = "";
	}
	return data;
}

K_EXPORT_PLASMA_DATAENGINE(train_schedule, TrainScheduleEngine)

#include "train_schedule_engine.moc"
