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
	const static int DEFAULT_INTERVAL = 60*1000;
	const static QString  DEFAULT_STATION;

public:
	TrainScheduleEngine(QObject* parent, const QVariantList& args);
	~TrainScheduleEngine();
	void setNb(int nb);
	void setInterval(int interval);
	void setStation(QString stationId);
	void setStart(QTime start);

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

	QTime m_start;
	QString m_station;
	int m_nb;
	int m_interval;

};

#endif
