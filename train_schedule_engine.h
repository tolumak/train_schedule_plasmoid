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


#ifndef TRAIN_SCHEDULE_ENGINE_H
#define TRAIN_SCHEDULE_ENGINE_H

#include <Plasma/DataEngine>

#include <QList>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>


class TrainScheduleEngine : public Plasma::DataEngine
{
	Q_OBJECT


public:
	const static int DEFAULT_NB = 6;
	const static int MAX_NB = 15;
	const static int DEFAULT_INTERVAL = 60*1000;
	const static int DEFAULT_START = 0;
	const static QString  DEFAULT_STATION;

public:
	TrainScheduleEngine(QObject* parent, const QVariantList& args);
	~TrainScheduleEngine();
	void setNb(int nb);
	void setInterval(int interval);
	void setStation(QString stationId);
	void setStart(int start);

protected:
	bool sourceRequestEvent(const QString& name);
	bool updateSourceEvent(const QString& name);

public slots:
	void requestFinished(QNetworkReply * reply);
	void slotError(QNetworkReply::NetworkError error);

private:
	QUrl getUrl();
	void request();
	QVariant parseLine(QString &line);

private:
	const static QString urlFormat;

	QNetworkAccessManager * m_manager;

	int m_start;
	QString m_station;
	int m_nb;
	int m_interval;

};

#endif
