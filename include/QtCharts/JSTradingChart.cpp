#include"JSTradingChart.h"
#include<qdir.h>
#include<qtextstream.h>
#include <qlayout.h>
#include <qprogressbar.h>
JSTradingChart::JSTradingChart()
{
	mainchart = new JSMainChart("rb1710");
	this->setCentralWidget(mainchart);
	indicatorchart = new JSINDICATOR;
	QDockWidget *indicatordock = new QDockWidget;
	QDockWidget *top = new QDockWidget;
	indicatordock->setWidget(indicatorchart);

	QGridLayout *layout = new QGridLayout;
	QProgressBar *bar = new QProgressBar;
	layout->addWidget(bar);
	top->setLayout(layout);
	
	this->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, top);
	this->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, indicatordock);

	mainchart->createLineSeries("test",QPen(Qt::red,10));

	indicatorchart->createLineSeries("indicator", QPen(Qt::yellow, 3));
	//qRegisterMetaType<QKeyEvent>("QKeyEvent");//ע�ᵽԪϵͳ��
	connect(mainchart, SIGNAL(sendKey(QKeyEvent *)), indicatorchart, SLOT(keyPressEvent(QKeyEvent *)));
	connect(indicatorchart, SIGNAL(sendKey(QKeyEvent *)), mainchart, SLOT(keyPressEvent(QKeyEvent *)));

	this->showMaximized();

	QString fileName = "H:/rb1710.csv";
	QDir dir = QDir::current();
	QFile file(dir.filePath(fileName));
	if (!file.open(QIODevice::ReadOnly))
	{

	}
	QTextStream * out = new QTextStream(&file);//�ı���  
	QStringList tempOption = out->readAll().split("\n");//ÿ����\n����  
	bar->setMinimum(0);  // ��Сֵ
	bar->setMaximum(tempOption.size());  // ���ֵ
	for (int i = 0; i < tempOption.count(); i++)
	{
		bar->setValue(i);
		QStringList tempbar = tempOption.at(i).split(",");//һ���еĵ�Ԫ���ԣ�����  
		if (tempbar.size()>5)
		{
			QString datetime = tempbar[0]+":00";
			double open = tempbar[1].toDouble();
			double high = tempbar[2].toDouble();
			double low = tempbar[3].toDouble();
			double close = tempbar[4].toDouble();
			double timestamp = QDateTime::fromString(datetime, "yyyy/MM/dd hh:mm:ss").toMSecsSinceEpoch();
			this->mainchart->addCandleStickSet(open, high, low, close,timestamp );
		}
	}
	file.close();//������ɺ�ǵùر��ļ�  
}

JSTradingChart::~JSTradingChart()
{

}

void JSTradingChart::generateset()
{
	

}