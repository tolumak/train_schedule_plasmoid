#include "schedule_item.h"

QRectF ScheduleItem::boundingRect() const
{
	return QRectf(0, 0, SCHEDULE_ITEM_WIDTH, SCHEDULE_ITEM_HEIGHT);
}

vid paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	  QWidget *widget)
{
	p->save();
	p->setPen(Qt::White);
	p->drawText(boudingRect(), Qt::AlignTop | Qt::AlignHCenter, "Hello World!");
	p->restore();
}
