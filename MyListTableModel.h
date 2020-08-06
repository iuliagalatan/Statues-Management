#pragma once
#include "Service.h"
#include <qabstractitemmodel.h>
class MyListTableModel :
	public QAbstractTableModel
{
public:
	MyListTableModel(Service<BaseRepository>& servic) : service{ servic}
	{
	}


	QVariant headerData(int section, Qt::Orientation orientation, int role)const;


	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const;
	int columnCount(const QModelIndex& parent = QModelIndex())const;
	int rowCount(const QModelIndex& parent = QModelIndex())const;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex& index) const;
private:
	Service<BaseRepository>& service;

};

