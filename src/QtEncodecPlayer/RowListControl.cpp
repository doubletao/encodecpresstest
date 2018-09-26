#include "RowListControl.h"
#include <QComboBox>
#include <QLineEdit>
#include <QHeaderView>
#include <QLabel>
#include <QPainter>
#include <QBuffer>

/////////////////////////////////RowListDelegate//////////////////////////////////////////////////////////////////////////////////////////////////////////
RowListDelegate::RowListDelegate(QWidget * parent, int nWidth/* = 0*/, int nHeight/* = 0*/)
	: QStyledItemDelegate(parent)
	, m_nWidth(nWidth)
	, m_nHeight(nHeight)
{
}

void RowListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	//高度不变，在矩形中居中
	QRect rtEditor = option.rect;
	if (m_nHeight > 0)
	{
		rtEditor.setTop(rtEditor.top() + (rtEditor.height() - m_nHeight) / 2);
		rtEditor.setBottom(rtEditor.top() + m_nHeight);
	}
	if (m_nWidth > 0)
	{
		rtEditor.setLeft(rtEditor.left() + (rtEditor.width() - m_nWidth) / 2);
		rtEditor.setRight(rtEditor.left() + m_nWidth);
	}
	editor->setGeometry(rtEditor);
}

void RowListDelegate::SetWidth(int nWidth)
{
	m_nWidth = nWidth;
}

void RowListDelegate::SetHeight(int nHeight)
{
	m_nHeight = nHeight;
}

/////////////////////////////////RowListTextDelegate//////////////////////////////////////////////////////////////////////////////////////////////////////////
RowListTextDelegate::RowListTextDelegate(QWidget *parent, bool bReadonly/* = false*/, int nWidth/* = 0*/, int nHeight/* = 30*/)
	: RowListDelegate(parent, nWidth, nHeight)
	, m_bReadonly(bReadonly)
{
}

QWidget * RowListTextDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (m_bReadonly)
	{
		return nullptr;
	}
	else
	{
		QLineEdit * pEditor = new QLineEdit(parent);
		return pEditor;
	}
}

void RowListTextDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::DisplayRole).toString();
	QLineEdit * pEditor = static_cast<QLineEdit *>(editor);
	if (pEditor)
	{
		pEditor->setText(value);
	}
}

void RowListTextDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QString value = "";
	QLineEdit * pEditor = static_cast<QLineEdit *>(editor);
	if (pEditor)
	{
		value = pEditor->text();
	}
	model->setData(index, value);
}

/////////////////////////////////RowListComboboxDelegate//////////////////////////////////////////////////////////////////////////////////////////////////////////
RowListComboboxDelegate::RowListComboboxDelegate(QWidget * parent, int nWidth/* = 0*/, int nHeight/* = 30*/)
	: RowListDelegate(parent, nWidth, nHeight)
{
}

QWidget * RowListComboboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QComboBox * pEditor = new QComboBox(parent);
	pEditor->setEditable(false);
	for (auto it : m_lstStrValue)
	{
		pEditor->addItem(it);
	}
	return pEditor;
}

void RowListComboboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::DisplayRole).toString();
	QComboBox * pEditor = static_cast<QComboBox *>(editor);
	if (pEditor)
	{
		pEditor->setCurrentText(value);
	}
}

void RowListComboboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QString value = "";
	QComboBox * pEditor = static_cast<QComboBox *>(editor);
	if (pEditor)
	{
		value = pEditor->currentText();
	}
	model->setData(index, value);
}

void RowListComboboxDelegate::SetListValue(QStringList lstStrValue)
{
	m_lstStrValue = lstStrValue;
}

/////////////////////////////////RowListIconDelegate//////////////////////////////////////////////////////////////////////////////////////////////////////////
RowListIconDelegate::RowListIconDelegate(QWidget *parent, int nWidth/* = 0*/, int nHeight/* = 0*/)
	: RowListDelegate(parent, nWidth, nHeight)
{
}

QWidget * RowListIconDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	return nullptr;
}

void RowListIconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QByteArray value = index.model()->data(index, Qt::DisplayRole).toByteArray();
	QPixmap pixIcon;
	if (pixIcon.loadFromData(value))
	{
		QRect rtIcon = option.rect;
		QRect rtImg = pixIcon.rect();
		rtIcon.setTop(rtIcon.top() + (rtIcon.height() - rtImg.height()) / 2);
		rtIcon.setBottom(rtIcon.top() + rtImg.height());
		rtIcon.setLeft(rtIcon.left() + (rtIcon.width() - rtImg.width()) / 2);
		rtIcon.setRight(rtIcon.left() + rtImg.width());
		if (false)
		{
			pixIcon.save("d:\\a.bmp");
		}
		if (painter)
		{
			painter->drawPixmap(rtIcon, pixIcon);
		}
	}
}

/////////////////////////////////RowListControl//////////////////////////////////////////////////////////////////////////////////////////////////////////
RowListControl::RowListControl(QWidget *parent)
	: QTableView(parent)
{
}

RowListControl::~RowListControl()
{
}

void RowListControl::SetColumnType(int nColumn, EmRowListColumnType emType)
{
	switch (emType)
	{
	case EmRowListColumnType::ReadonlyText:
		setItemDelegateForColumn(nColumn, new RowListTextDelegate(this, true));
		break;
	case EmRowListColumnType::Text:
		setItemDelegateForColumn(nColumn, new RowListTextDelegate(this));
		break;
	case EmRowListColumnType::Combobox:
		setItemDelegateForColumn(nColumn, new RowListComboboxDelegate(this));
		break;
	case EmRowListColumnType::Icon:
		setItemDelegateForColumn(nColumn, new RowListIconDelegate(this));
		horizontalHeader()->setSectionResizeMode(nColumn, QHeaderView::Fixed);
		break;
	default:
		break;
	}
}

void RowListControl::SetColumnType(int nColumn, EmRowListColumnType emType, QStringList lstStrValue)
{
	switch (emType)
	{
	case EmRowListColumnType::Combobox:
	{
		RowListComboboxDelegate * pComboboxDelegate = new RowListComboboxDelegate(this);
		pComboboxDelegate->SetListValue(lstStrValue);
		setItemDelegateForColumn(nColumn, pComboboxDelegate);
	}
		break;
	default:
		SetColumnType(nColumn, emType);
		break;
	}
}

void RowListControl::SetRowHeight(int nHeight)
{
	verticalHeader()->setDefaultSectionSize(nHeight);
}

bool RowListControl::SetIcon(int nRow, int nColumn, const QPixmap & img)
{
	QByteArray bytearray;
	QBuffer buffer(&bytearray);
	buffer.open(QIODevice::WriteOnly);
	if (img.save(&buffer, "PNG"))
	{
		model()->setData(model()->index(nRow, nColumn), bytearray);
		return true;
	}
	return false;
}

