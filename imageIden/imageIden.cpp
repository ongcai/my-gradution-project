/****************************************************************************
 ** object : ImageIden 
 ** 毕业设计三级菜单　图像识别
 ** by luchaodong
 ** class Ui::ImageIden : public Ui_ImageIden {}
 ** ImageIden 
 ****************************************************************************/

#include <QtGui>
#include <QPixmap>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget> 
#include <QPalette>
#include <iostream>
#include "imageIden.h"

using namespace std;

ImageIden::ImageIden(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::ImageIden), //Ui namespace ,not this 
	m_getImg(new QImage)
{
	ui->setupUi(this);
	
	//设置背景图
	QRect screen_size = QApplication::desktop()->screenGeometry(); //get window size
	QPixmap pix("/opt/gb_ms/picture/background_1.jpg", 0, Qt::AutoColor);
	pix = pix.scaled(screen_size.width(), screen_size.height(), Qt::IgnoreAspectRatio); //photo size
	QPalette palette;
	palette.setBrush(backgroundRole(), QBrush(pix));
	setPalette(palette);

//按钮背景
	ui->buttonQuit->setText("");
	ui->buttonQuit->setFixedSize(81,32);
	ui->buttonQuit->setIconSize(QSize(81,32));
	pix.load("/opt/gb_ms/picture/return.png", 0, Qt::AutoColor);
	pix = pix.scaled(81, 32, Qt::IgnoreAspectRatio);
	ui->buttonQuit->setIcon(QIcon(pix));

/*
//set button font color
	palette.setColor(QPalette::ButtonText, Qt::black);
	ui->buttonQuit->setPalette(palette);
	ui->buttonQuit->setFlat(true);
*/

//signal and slots
	connect(ui->actionFromFile, SIGNAL(triggered()), this, SLOT(loadPicture()));
	connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(buttonQuit()));
	
	connect(ui->actionFace, SIGNAL(triggered()), this, SLOT(setModelFace()));
	connect(ui->actionDigit, SIGNAL(triggered()), this, SLOT(setModelDigit()));
	
	connect(ui->actionIden, SIGNAL(triggered()), this, SLOT(startIden()));
	connect(ui->actionCatch, SIGNAL(triggered()), this, SLOT(startCatch()));
	connect(ui->actionTrain, SIGNAL(triggered()), this, SLOT(startTrain()));

	connect(ui->buttonIden, SIGNAL(clicked()), this, SLOT(startIden()));
	connect(ui->buttonCatch, SIGNAL(clicked()), this, SLOT(startCatch()));
	connect(ui->buttonTrain, SIGNAL(clicked()), this, SLOT(startTrain()));
	
	connect(ui->buttonQuit, SIGNAL(clicked()), this, SLOT(buttonQuit()));
	
	connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteFaceID()));
	
	setModelFace();
	m_digit = 0;

	m_getImg->load("/opt/gb_ms/picture/melcd.jpg");
	*m_getImg = m_getImg->scaled(QSize(250,330), Qt::IgnoreAspectRatio); //photo size
	ui->labelPicture->setPixmap(QPixmap::fromImage(*m_getImg));
	
}

ImageIden::~ImageIden()
{
	delete ui;
	delete m_getImg;

}

void ImageIden::loadPicture()
{
	QString fileName;

	fileName = QFileDialog::getOpenFileName(this, trUtf8("选择图像"), "",
					tr("Images(*.png *.bmp *.jpg *.tif *.GIF)"));
	if (fileName.isEmpty())
		return;
	else
	{
		if ( !( m_getImg->load(fileName) ) )
		{
			QMessageBox::information(this,
					tr("Open img error"),
					tr("Open img error!"));
			return;
		}
		*m_getImg = m_getImg->scaled(QSize(250,330), Qt::IgnoreAspectRatio); //photo size
		ui->labelPicture->setPixmap(QPixmap::fromImage(*m_getImg));
	}
}

void ImageIden::buttonQuit()
{
	emit returned();
	close();
}

//设置为人脸识别模式
void ImageIden::setModelFace()
{
	if ( m_currentModel == FACEMODEL )
	{
		ui->actionFace->setChecked(true);
		return;
	}

	cout << "Set FaceIdent" << endl;
	//界面调整
	ui->actionDigit->setChecked(false);
	ui->lcdNumber->setVisible(false);

	ui->actionTrain->setEnabled(true);
	ui->buttonTrain->setVisible(true);
	ui->buttonTrain->setEnabled(true);
	ui->buttonDelete->setVisible(true);
	ui->buttonDelete->setEnabled(true);
	
	ui->labelInputID->setVisible(true);
	ui->labelIndentID->setVisible(true);
	ui->comboBoxID->setVisible(true);
	ui->lineEditShowIdentId->setVisible(true);
	
	m_currentModel = FACEMODEL;

	m_inputId = ui->comboBoxID->currentText();
	ui->lineEditShowIdentId->setText(m_inputId);		
}

//设置为数字识别模式
void ImageIden::setModelDigit()
{
	if (m_currentModel == DIGITMODEL)
	{
		ui->actionDigit->setChecked(true);
		return;
	}

	cout << "Set DigitIdent" << endl;
	//界面调整
	ui->actionFace->setChecked(false);
	ui->lcdNumber->setVisible(true);
	
	ui->actionTrain->setEnabled(false);
	ui->buttonTrain->setVisible(false);
	ui->buttonTrain->setEnabled(false);
	ui->buttonDelete->setVisible(false);
	ui->buttonDelete->setEnabled(false);
	
	ui->labelInputID->setVisible(false);
	ui->labelIndentID->setVisible(false);
	ui->comboBoxID->setVisible(false);
	ui->lineEditShowIdentId->setVisible(false);

	m_currentModel = DIGITMODEL;
	
	++m_digit;
	ui->lcdNumber->display(m_digit);
}

//开始识别
void ImageIden::startIden()
{
	cout << "StartIdent" << endl;

	m_inputId = ui->comboBoxID->currentText();
	ui->lineEditShowIdentId->setText(m_inputId);

}

//捕获图像
void ImageIden::startCatch()
{
	cout << "Catch img" << endl; 


}

//人脸识别训练
void ImageIden::startTrain()
{
	cout << "Start Train" << endl;


}

void ImageIden::deleteFaceID()
{
	m_inputId = ui->comboBoxID->currentText();
	qDebug() << m_inputId ;


}
