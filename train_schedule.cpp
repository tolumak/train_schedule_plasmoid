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


#include "train_schedule.h"

#include <qdebug.h>
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsLinearLayout>

#include <plasma/svg.h>
#include <plasma/theme.h>
#include <KConfigDialog>

#include "schedule_item.h"
#include "station.h"

const QString PlasmaTrainSchedule::DEFAULT_STATION = Station::stationId("Lyon Part-Dieu");
const int PlasmaTrainSchedule::DEFAULT_INTERVAL = 60*1000;
const int PlasmaTrainSchedule::DEFAULT_NB = 6;
const int PlasmaTrainSchedule::DEFAULT_START = 30 * 60 * 1000;


PlasmaTrainSchedule::PlasmaTrainSchedule(QObject *parent, const QVariantList &args)
	: Plasma::PopupApplet(parent, args),
	  m_widget(0),
	  m_layout(0)
{
	m_widget = new QGraphicsWidget(this);
	m_layout = new QGraphicsLinearLayout(Qt::Vertical);

	if (!m_layout || !m_widget) {
		setFailedToLaunch(true, "unable to initialize");
		if (m_widget)
			delete(m_widget);
		if (m_layout)
			delete(m_layout);
		return;
	}

	m_widget->setLayout(m_layout);

	setAspectRatioMode(Plasma::FixedSize);
	setHasConfigurationInterface(true);
	setPopupIcon(icon());

}


PlasmaTrainSchedule::~PlasmaTrainSchedule()
{
}

void PlasmaTrainSchedule::init()
{
	KConfigGroup cg = config();
	m_interval = cg.readEntry("interval", DEFAULT_INTERVAL);
	m_start = cg.readEntry("start", DEFAULT_START);
	m_nb = cg.readEntry("nb", DEFAULT_NB);
	m_station = cg.readEntry("station", DEFAULT_STATION);

	connectToEngine();
}

void PlasmaTrainSchedule::connectToEngine()
{
	QString source = QString("schedule-%1-%2-%3").arg(m_station).arg(m_nb).arg(m_start);

        Plasma::DataEngine* engine = dataEngine("train_schedule");
	if (!engine) {
		qDebug() << "Unable to connect to train_schedule engine";
		return;
	}
	foreach(QString s, engine->sources()) {
		engine->disconnectSource(s, this);
	}

	engine->connectSource(source, this, m_interval);
}

QGraphicsWidget * PlasmaTrainSchedule::graphicsWidget()
{
	return m_widget;
}

void PlasmaTrainSchedule::createConfigurationInterface(KConfigDialog *parent)
{
	QWidget *widget = new QWidget();
	parent->addPage(widget, i18n("General"), icon());
	ui.setupUi(widget);

	ui.m_startSpinBox->setValue(m_start/60/1000);
	ui.m_nbSpinBox->setValue(m_nb);
	ui.m_intervalSpinBox->setValue(m_interval/60/1000);
	foreach (QString key, Station::map().keys()) {
		ui.m_stationComboBox->addItem(key, Station::map()[key]);
	}
	ui.m_stationComboBox->setCurrentIndex(ui.m_stationComboBox->findData(m_station));

	connect(parent, SIGNAL(accepted()), this, SLOT(configurationAccepted()));
}

void PlasmaTrainSchedule::configurationAccepted()
{
	m_start = ui.m_startSpinBox->value() * 60 * 1000;
	m_nb = ui.m_nbSpinBox->value();
	m_interval = ui.m_intervalSpinBox->value() * 60 * 1000;
	m_station = ui.m_stationComboBox->itemData(ui.m_stationComboBox->currentIndex()).toString();

	KConfigGroup cg = config();
	cg.writeEntry("interval", m_interval);
	cg.writeEntry("start", m_start);
	cg.writeEntry("nb", m_nb);
	cg.writeEntry("station", m_station);

	cg.config()->sync();

	connectToEngine();
}

void PlasmaTrainSchedule::dataUpdated(const QString &name, const Plasma::DataEngine::Data &data)
{
       	if (name == QString("schedule-%1-%2-%3").arg(m_station).arg(m_nb).arg(m_start)) {

		QVariantList items = data["items"].toList();
		while (items.count() > m_layout->count()) {
			ScheduleItem * schedItem = new ScheduleItem();
			m_layout->addItem(schedItem);
		}


		while (m_layout->count() > items.count()) {
			QGraphicsLayoutItem * layoutItem = m_layout->itemAt(0);
			m_layout->removeAt(0);
			delete(layoutItem);

		}


		for (int i = 0 ; i < items.count() ; i++) {
			QMap<QString,QVariant> item = items[i].toMap();
			Schedule sched(item["type"].toString(),
				       item["destination"].toString(),
				       item["stations"].toStringList(),
				       item["start"].toTime(),
				       item["delay"].toString(),
				       item["comment"].toString().mid(2));

			ScheduleItem * schedItem = dynamic_cast<ScheduleItem *>(m_layout->itemAt(i));
			schedItem->setSchedule(sched);
		}

		/* How to do this differently? */
		if (items.count() > 0 && layout()) {
			layout()->invalidate();
			layout()->activate();
			resize(maximumSize());
		}
	}
}


#include "train_schedule.moc"
