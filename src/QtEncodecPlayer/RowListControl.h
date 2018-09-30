#pragma once
#include <QStyledItemDelegate>
#include <QTableView>
enum class EmRowListColumnType
{
	ReadonlyText = 0,
	Text,
	Combobox,
	Icon,
	FrameTime,
};

class RowListDelegate : public QStyledItemDelegate
{
protected:
	int m_nWidth;
	int m_nHeight;
public:
	RowListDelegate(QWidget *parent, int nWidth = 0, int nHeight = 0);
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);
};

class RowListTextDelegate : public RowListDelegate
{
private:
	bool m_bReadonly;
public:
	RowListTextDelegate(QWidget *parent, bool bReadonly = false, int nWidth = 0, int nHeight = 30);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

class RowListComboboxDelegate : public RowListDelegate
{
private:
	QStringList m_lstStrValue;
public:
	RowListComboboxDelegate(QWidget *parent, int nWidth = 0, int nHeight = 30);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
public:
	void SetListValue(QStringList lstStrValue);
};

class RowFrameTimeEditDelegate : public RowListDelegate
{
private:
	QString m_strDispFormat;
public:
	RowFrameTimeEditDelegate(QWidget *parent, QString strDispFormat = "hh:mm:ss:yy", int nWidth = 0, int nHeight = 30);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

class RowListIconDelegate : public RowListDelegate
{
public:
	RowListIconDelegate(QWidget *parent, int nWidth = 0, int nHeight = 0);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

class RowListControl : public QTableView
{
public:
	RowListControl(QWidget *parent);
	virtual ~RowListControl();
	void SetColumnType(int nColumn, EmRowListColumnType emType);
	void SetColumnType(int nColumn, EmRowListColumnType emType, QStringList lstStrValue);//用来给例如下拉选类型填充数据
	void SetRowHeight(int nHeight);
	bool SetIcon(int nRow, int nColumn, const QPixmap & img);
};

