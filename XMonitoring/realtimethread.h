#ifndef REALTIMETHREAD_H
#define REALTIMETHREAD_H

#include <QThread>

class realtimethread : public QThread
{
	Q_OBJECT

public:
	realtimethread(QObject *parent);
	~realtimethread();

private:
	
};

#endif // REALTIMETHREAD_H
