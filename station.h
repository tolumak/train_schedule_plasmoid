#ifndef STATION_H
#define STATION_H

#include <QString>
#include <QMap>

class Station
{
public:
	static QString stationId(QString name);
	static QString stationName(QString id);
	static const QMap<QString, QString> & map();

private:
	static QMap<QString, QString> stationIdMap;
	static bool initialized;
	static void populate();
};

#endif
