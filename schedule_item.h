#include <QGraphicsItem>


ScheduleItem:QGraphicsItem
{
	Q_OBJECT

public:

	const int SCHEDULE_ITEM_WIDTH =150;
	const int SCHEDULE_ITEM_HEIGHT = 50;


	QRectF boundingRect() const;
	vid paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		  QWidget *widget);
};
