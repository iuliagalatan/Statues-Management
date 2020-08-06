#include "MyListTableModel.h"


QVariant MyListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "PowerWordName" };
			case 1:
				return QString("Material");
			case 2:
				return QString("Age");
			case 3:
				return QString("CorporealForm");
			}
		}
	}
	return QVariant();
}

QVariant MyListTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();
	std::vector<Statue> saved = this->service.GetSavedElementsVector();
	Statue currentStatue = saved[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (col)
		{
		case 0:
			return QString::fromStdString(currentStatue.GetPowerWordName());
		case 1:
			return QString::fromStdString(currentStatue.GetMaterial());
		case 2:
			return QString::number(currentStatue.GetAge());
		case 3:
			return QString::fromStdString(currentStatue.GetCorporealForm());
		default:
			break;
		}
	}
	return QVariant();
}

int MyListTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

int MyListTableModel::rowCount(const QModelIndex& parent) const
{
	return service.GetSavedElementsVector().size();
}

bool MyListTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	
	//emit dataChanged(index, index);

	return false;
}

Qt::ItemFlags MyListTableModel::flags(const QModelIndex& index) const
{
	
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
