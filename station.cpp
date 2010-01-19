#include "station.h"

QMap<QString,QString> Station::stationIdMap;
bool Station::initialized = false;


QString Station::stationId(QString name) {
	if (!initialized) {
		populate();
		initialized = true;
	}
	return stationIdMap[name];
}

QString Station::stationName(QString id) {
	if (!initialized) {
		populate();
		initialized = true;
	}

	return stationIdMap.key(id);
}

void Station::populate() {
	stationIdMap["Lyon Part-Dieu"] = QString("OCE87723197");
	stationIdMap["Lyon Perrache"] = "OCE87722025";
	stationIdMap["Macon"] = "OCE87725689";
	stationIdMap["Ambérieu"] = "OCE87743716";
	stationIdMap["Villefranche"] = "OCE87721332";
}
