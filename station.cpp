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

#include <KConfig>
#include <KConfigGroup>
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
	KConfig stationFile(QString("train_schedule/stations"), KConfig::FullConfig, "data");
	stationIdMap = stationFile.group("stations").entryMap();
}

const QMap<QString, QString> & Station::map() {
	if (!initialized) {
		populate();
		initialized = true;
	}

	return stationIdMap;
}
