#include "TextEdit.h"
#include <QDebug>
#include <QPainter>  

CTextEdit::CTextEdit(QWidget *parent)
	: QTextEdit(parent)
{

	this->hide();
	this->setGeometry(0,0,60, 40);
	

	//设置textedit背景透明
	QPalette pl = this->palette();
	pl.setBrush(QPalette::Base, QBrush(QColor(0, 0, 0,0)));
	pl.setColor(QPalette::Text, QColor("red"));
	this->setPalette(pl);

	//输入框大小随文字多少而变化
	connect(this, SIGNAL(textChanged()), this, SLOT(slot_textChanged()));
	
	this->setStyleSheet(
		"QTextEdit{ border:1px solid #dadada; }"
	);

	// 初始字体的设置
	m_font.setFamily("Microsoft YaHei");
	m_font.setPointSize(12);
	this->setFont(m_font);

	this->setAlignment(Qt::AlignJustify);
	this->setWordWrapMode(QTextOption::WordWrap);
}


CTextEdit::~CTextEdit()
{
}

void CTextEdit::setDrawFont(QFont font)
{
	m_font = font;
	this->setFont(m_font);
}

void CTextEdit::paintEvent(QPaintEvent *pEvent)
{
	return QTextEdit::paintEvent(pEvent);


	//QPainter paint(this->viewport());
	//paint.drawText(this->rect(), Qt::AlignJustify, this->toPlainText());
}
void CTextEdit::focusInEvent(QFocusEvent *pEvent)
{
	QTextEdit::focusInEvent(pEvent);
	return;
}

void CTextEdit::focusOutEvent(QFocusEvent *pEvent)
{
	//qDebug() << "focusOutEvent";
	//QRect rect;
	//QString strText;
	//rect = QRect(QPoint(this->x(), this->y()), QSize(this->width(), this->height()));
	//strText = this->toPlainText();
	//emit sig_draw_text(rect, strText);
	//this->hide();
	//this->clear();
	QTextEdit::focusOutEvent(pEvent);
}

void CTextEdit::slot_textChanged()
{
	if (this->toPlainText().size() < 5)
	{
		this->resize(this->toPlainText().size() * 10 + 50, 40);
	}
	else
	{

		this->resize(this->toPlainText().size() * 15 + 30, this->document()->size().rheight() + 10);
	}
}