#include <QString>
#include <QStringList>
#include <QTime>

class Schedule {

public:
	Schedule(QString & destination,
		 QStringList & stations,
		 QTime & start,
		 QString & comment);

	QString toStr();
	QString commaStations();
	QString comment();

private:
	QString m_destination;
	QStringList m_stations;
	QTime m_start;
	QString m_comment;
};
