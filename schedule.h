#ifndef SCHEDULE_H
#define SCHEDULE_H


#include <QString>
#include <QStringList>
#include <QTime>

class Schedule {

public:
	Schedule() {};
	Schedule(
		QString type,
		QString destination,
		QStringList stations,
		QTime start,
		QString delay,
		QString comment
		);

	QString destination();
	QStringList stations();
	QString stationsStr();
	QString comment();
	QTime   start();
	QString startStr();
	QString delay();
	QString type();

	void setDestination(QString destination);
	void setStations(QStringList stations);
	void setComment(QString comment);
	void setStart(QTime start);
	void setDelay(QString delay);
	void setType(QString type);


private:
	QString m_type;
	QString m_destination;
	QStringList m_stations;
	QTime m_start;
	QString m_comment;
	QString m_delay;

};

#endif
