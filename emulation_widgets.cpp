#include "stdafx.h"

#include "emulation_widgets.h"

#include "emulation_supportwidgets.h"
#include "emulation_scenery.h"

#include "emulation_functions.h"

#include "dictionaries/dictionary_widgets.h"
#include "emulation_delegates.h"
#include "topology2d/topology2d_host.h"

namespace Emulation
{

	// EditVariablesForm
	EditVariablesForm::EditVariablesForm(QWidget *parent)
		: DialogFormBase(parent), m_dbData(std::shared_ptr<emulation_dal::Emulation_variable>(new emulation_dal::Emulation_variable))
	{
		init();
	}

	EditVariablesForm::EditVariablesForm(const std::shared_ptr<emulation_dal::Emulation_variable> &data, QWidget *parent)
		: DialogFormBase(parent)
	{
		init();

		loadDBData(data);
	}

	void EditVariablesForm::init()
	{
		QGridLayout *mainLayout = new QGridLayout(this);

		QLabel *variableNameLabel = new QLabel(tr("Variable name"), this);
		m_variableNameLine = new QLineEdit(this);

		mainLayout->addWidget(variableNameLabel, 0, 0);
		mainLayout->addWidget(m_variableNameLine, 0, 1);

		QLabel *variableTypeLabel = new QLabel(tr("Variable type"), this);
		m_variableTypeCombo = new VariableTypesListComboBox(this);

		mainLayout->addWidget(variableTypeLabel, 2, 0);
		mainLayout->addWidget(m_variableTypeCombo, 2, 1);

		QLabel *lenghtLabel = new QLabel(tr("Lenght"), this);
		m_lenghtSpin = new SpinBox(this);
		m_lenghtSpin->setRange(-1, 255);

		mainLayout->addWidget(lenghtLabel, 3, 0);
		mainLayout->addWidget(m_lenghtSpin, 3, 1);

		m_arbitraryLenghtCheck = new CheckBox(tr("Arbitrary lenght"), this);

		mainLayout->addWidget(m_arbitraryLenghtCheck, 4, 0, 1, 2);

		QLabel *valueLabel = new QLabel(tr("Value"), this);
		m_valueLine = new QLineEdit(this);

		mainLayout->addWidget(valueLabel, 5, 0);
		mainLayout->addWidget(m_valueLine, 5, 1);

		m_defFlagCheck = new CheckBox(tr("Default value flag"), this);

		mainLayout->addWidget(m_defFlagCheck, 6, 0, 1, 2);

		QLabel *descriptionLabel = new QLabel(tr("Description"), this);
		m_descriptionEdit = new PlainTextEdit(this);

		mainLayout->addWidget(descriptionLabel, 7, 0);
		mainLayout->addWidget(m_descriptionEdit, 7, 1);

		connect(m_arbitraryLenghtCheck, SIGNAL(stateChanged(int)), SLOT(updateAccesibility()));
		connect(m_defFlagCheck, SIGNAL(stateChanged(int)), SLOT(updateAccesibility()));

		updateAccesibility();
	}

	void EditVariablesForm::loadDBData(const std::shared_ptr<emulation_dal::Emulation_variable> &data)
	{
		m_dbData = data;

		if (data) {

			name(data->ev_name());
			variableType(data->evt());

			if (!data->ev_length().null()) {
				lenght(data->ev_length().get());
				arbitraryLenghtFlag(false);
			}
			else {
				arbitraryLenghtFlag(true);
			}

			defFlag(data->ev_data_ready());
			description(data->ev_description());
			value(data->ev_data());

		}
	}

	QString EditVariablesForm::name() const
	{
		return m_variableNameLine->text();
	}

	void EditVariablesForm::name(const QString &value)
	{
		m_variableNameLine->setText(value);
	}

	int EditVariablesForm::variableTypeId() const
	{
		return m_variableTypeCombo->currentId();
	}

	void EditVariablesForm::variableTypeId(const int value) const
	{
		m_variableTypeCombo->currentById(value);
	}

	void EditVariablesForm::variableType(const std::shared_ptr<emulation_dal::Emulation_variable_type> &value)
	{
		if (value)
			variableTypeId(value->id());
	}

	int EditVariablesForm::lenght() const
	{
		return m_lenghtSpin->value();
	}

	void EditVariablesForm::lenght(const int value)
	{
		m_lenghtSpin->setValue(value);
	}

	bool EditVariablesForm::defFlag() const
	{
		return m_defFlagCheck->isChecked();
	}

	void EditVariablesForm::defFlag(const bool value)
	{
		m_defFlagCheck->setChecked(value);
	}

	bool EditVariablesForm::arbitraryLenghtFlag() const
	{
		return m_arbitraryLenghtCheck->isChecked();
	}

	void EditVariablesForm::arbitraryLenghtFlag(const bool value)
	{
		m_arbitraryLenghtCheck->setChecked(value);
	}

	QString EditVariablesForm::description() const
	{
		return m_descriptionEdit->toPlainText();
	}

	void EditVariablesForm::description(const QString &value)
	{
		m_descriptionEdit->setPlainText(value);
	}

	QString EditVariablesForm::value() const
	{
		return m_valueLine->text();
	}

	void EditVariablesForm::value(const QString &newValue)
	{
		m_valueLine->setText(newValue);
	}

	const std::shared_ptr<emulation_dal::Emulation_variable> &EditVariablesForm::dbData() const
	{
		return m_dbData;
	}

	void EditVariablesForm::updateDBData()
	{
		if (m_dbData) {
			m_dbData->ev_name(name());
			m_dbData->evt_id(variableTypeId());

			if (arbitraryLenghtFlag())
				m_dbData->ev_length().reset();
			else
				m_dbData->ev_length(odb::nullable<__int64>(lenght()));

			m_dbData->ev_data_ready(defFlag());
			m_dbData->ev_description(description());
			m_dbData->ev_data(QByteArray(value().toStdString().c_str()));
		}

	}

	void EditVariablesForm::updateAccesibility()
	{
		m_lenghtSpin->setEnabled(!m_arbitraryLenghtCheck->isChecked());
		m_valueLine->setEnabled(m_defFlagCheck->isChecked());
	}


	// EditFilesForm
	EditFilesForm::EditFilesForm(QWidget *parent)
		: DialogFormBase(parent), m_dbData(std::shared_ptr<emulation_dal::Emulation_file>(new emulation_dal::Emulation_file))
	{
		init();
	}

	EditFilesForm::EditFilesForm(const std::shared_ptr<emulation_dal::Emulation_file> &data, QWidget *parent)
		: DialogFormBase(parent), m_dbData(std::shared_ptr<emulation_dal::Emulation_file>(new emulation_dal::Emulation_file))
	{
		init();

		loadDBData(data);
	}

	void EditFilesForm::init()
	{
		QGridLayout *mainLayout = new QGridLayout(this);

		QLabel *fileNameLabel = new QLabel(tr("File name"), this);
		m_fileNameLine = new QLineEdit(this);

		mainLayout->addWidget(fileNameLabel, 0, 0);
		mainLayout->addWidget(m_fileNameLine, 0, 1);

		QLabel *fileTypeLabel = new QLabel(tr("File type"), this);
		m_fileTypeCombo = new FileTypesListComboBox(this);

		mainLayout->addWidget(fileTypeLabel, 2, 0);
		mainLayout->addWidget(m_fileTypeCombo, 2, 1);

		m_useStoreCheck = new CheckBox(tr("Use store"), this);

		mainLayout->addWidget(m_useStoreCheck, 3, 0, 1, 2);

		QLabel *descriptionLabel = new QLabel(tr("Description"), this);
		m_descriptionEdit = new PlainTextEdit(this);

		mainLayout->addWidget(descriptionLabel, 5, 0);
		mainLayout->addWidget(m_descriptionEdit, 5, 1);

	}

	void EditFilesForm::loadDBData(const std::shared_ptr<emulation_dal::Emulation_file> &data)
	{
		if (data) {

			m_dbData = data;

			name(data->ef_name());
			fileType(data->eft());

			useStoreFlag(data->ef_use_file_store());
			description(data->ef_description());

		}
	}

	QString EditFilesForm::name() const
	{
		return m_fileNameLine->text();
	}

	void EditFilesForm::name(const QString &value)
	{
		m_fileNameLine->setText(value);
	}

	int EditFilesForm::fileTypeId() const
	{
		return m_fileTypeCombo->currentId();
	}

	void EditFilesForm::fileTypeId(const int value) const
	{
		m_fileTypeCombo->currentById(value);
	}

	void EditFilesForm::fileType(const std::shared_ptr<emulation_dal::Emulation_file_type> &value)
	{
		if (value)
			fileTypeId(value->id());
	}

	bool EditFilesForm::useStoreFlag() const
	{
		return m_useStoreCheck->isChecked();
	}

	void EditFilesForm::useStoreFlag(const bool value)
	{
		m_useStoreCheck->setChecked(value);
	}

	QString EditFilesForm::description() const
	{
		return m_descriptionEdit->toPlainText();
	}

	void EditFilesForm::description(const QString &value)
	{
		m_descriptionEdit->setPlainText(value);
	}

	const std::shared_ptr<emulation_dal::Emulation_file> &EditFilesForm::dbData() const
	{
		return m_dbData;
	}

	void EditFilesForm::updateDBData()
	{
		m_dbData->ef_name(name());
		m_dbData->eft_id(fileTypeId());

		m_dbData->ef_use_file_store(useStoreFlag());
		m_dbData->ef_description(description());

	}

	// EditVariablesDialog
	EditVariablesDialog::EditVariablesDialog(QWidget *parent)
		: DialogBase(parent)
	{
		init();

		DialogBase::form(new EditVariablesForm(this));
	}

	EditVariablesDialog::EditVariablesDialog(const std::shared_ptr<emulation_dal::Emulation_variable> &data, QWidget *parent)
		: DialogBase(parent)
	{
		init();

		DialogBase::form(new EditVariablesForm(data, this));
	}

	void EditVariablesDialog::accept()
	{
		EditVariablesForm *dlgForm = form();

		if (dlgForm)
			dlgForm->updateDBData();

		DialogBase::accept();
	}

	void EditVariablesDialog::init()
	{
		setWindowTitle(tr("Edit Variables Reference Book"));
	}

	std::shared_ptr<emulation_dal::Emulation_variable> EditVariablesDialog::dbData() const
	{
		EditVariablesForm *dlgForm = form();

		if (dlgForm)
			return dlgForm->dbData();
		else 
			return std::shared_ptr<emulation_dal::Emulation_variable>();
	}

	EditVariablesForm *EditVariablesDialog::form() const
	{
		return dynamic_cast<EditVariablesForm *>(DialogBase::form());
	}

	// EditFilesDialog
	EditFilesDialog::EditFilesDialog(QWidget *parent)
		: DialogBase(parent)
	{
		init();

		DialogBase::form(new EditFilesForm(this));

	}

	EditFilesDialog::EditFilesDialog(const std::shared_ptr<emulation_dal::Emulation_file> &data, QWidget *parent)
		: DialogBase(parent)
	{
		init();

		DialogBase::form(new EditFilesForm(data, this));

	}

	void EditFilesDialog::accept()
	{
		EditFilesForm *dlgForm = form();

		if (dlgForm)
			dlgForm->updateDBData();

		DialogBase::accept();
	}

	void EditFilesDialog::init()
	{
		setWindowTitle(tr("Edit Files Reference Book"));
	}

	std::shared_ptr<emulation_dal::Emulation_file> EditFilesDialog::dbData() const
	{
		EditFilesForm *dlgForm = form();

		if (dlgForm)
			return dlgForm->dbData();
		else
			return std::shared_ptr<emulation_dal::Emulation_file>();
	}

	EditFilesForm *EditFilesDialog::form() const
	{
		return dynamic_cast<EditFilesForm *>(DialogBase::form());
	}

	// ViewVariablesTableModel
	ViewVariablesTableModel::ViewVariablesTableModel(QObject *parent)
		: DBTableModel<emulation_dal::Emulation_variable>(DoNotAutoLoad, parent)
	{
		init();
	}

	ViewVariablesTableModel::ViewVariablesTableModel(const Emulation_variable_store &value, QObject *parent)
		: DBTableModel<emulation_dal::Emulation_variable>(DoNotAutoLoad, parent)
	{
		set(value);

		init();
	}

	void ViewVariablesTableModel::init()
	{
	}

	QVariant ViewVariablesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
			switch (section) {
			case 0:
				return QObject::tr("Variable name");
			case 1:
				return QObject::tr("Variable type");
			case 2:
				return QObject::tr("Lenght");
			case 3:
				return QObject::tr("Default value");
			case 4:
				return QObject::tr("Description");
			case 5:
				return QObject::tr("Value");
			}
		}

		return QVariant();
	}

	QVariant ViewVariablesTableModel::data(const QModelIndex &index, int role) const
	{
		std::shared_ptr<emulation_dal::Emulation> curEmulation;
		std::shared_ptr<emulation_dal::Emulation_variable_type> curVariableType;
		odb::nullable<__int64> curLenght;

		if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
			if (index.row() >= 0 && index.row() < size()) {
				switch (index.column()) {
				case 0:
					return at(index.row())->ev_name();

				case 1:
					curVariableType = at(index.row())->evt();
					if (curVariableType)
						return curVariableType->evt_name();
					break;

				case 2:
					curLenght = at(index.row())->ev_length();

					if (curLenght.null() || curLenght.get() == -1)
						return QObject::tr("Arbitrary lenght");
					else
						return curLenght.get();

					break;

				case 3:
					if (at(index.row())->ev_data_ready())
						return at(index.row())->ev_data();
					else
						return "-";
				case 4:
					return at(index.row())->ev_description();
				case 5:
					return at(index.row())->ev_data();
				}
			}
		}

		return QVariant();
	}

	int ViewVariablesTableModel::rowCount(const QModelIndex &parent) const
	{
		return size();
	}

	int ViewVariablesTableModel::columnCount(const QModelIndex &parent) const
	{
		return 6;
	}

	// ViewFilesTableModel
	ViewFilesTableModel::ViewFilesTableModel(QObject *parent)
		: DBTableModel<emulation_dal::Emulation_file>(DoNotAutoLoad, parent)
	{
		init();
	}

	ViewFilesTableModel::ViewFilesTableModel(const emulation_dal::Emulation_file_store &value, QObject *parent)
		: DBTableModel<emulation_dal::Emulation_file>(DoNotAutoLoad, parent)
	{
		set(value);

		init();
	}

	void ViewFilesTableModel::init()
	{

	}

	QVariant ViewFilesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
			switch (section) {
			case 0:
				return QObject::tr("File name");
			case 1:
				return QObject::tr("File type");
			case 2:
				return QObject::tr("Data flag");
			case 3:
				return QObject::tr("Data");
			case 4:
				return QObject::tr("Use store");
			case 5:
				return QObject::tr("Description");
			}
		}

		return QVariant();

	}

	QVariant ViewFilesTableModel::data(const QModelIndex &index, int role) const
	{
		std::shared_ptr<emulation_dal::Emulation> curEmulation;
		std::shared_ptr<emulation_dal::Emulation_file_type> curFileType;
		odb::nullable<__int64> curLenght;

		if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
			if (index.row() >= 0 && index.row() < size()) {
				switch (index.column()) {
				case 0:
					return at(index.row())->ef_name();

				case 1:
					curFileType = at(index.row())->eft();
					if (curFileType)
						return curFileType->eft_name();
					break;

				case 2:
					return at(index.row())->ef_data_ready();
				case 3:
					return at(index.row())->ef_data();
				case 4:
					return at(index.row())->ef_use_file_store();
				case 5:
					return at(index.row())->ef_description();
				}
			}
		}

		return QVariant();
	}

	int ViewFilesTableModel::columnCount(const QModelIndex &parent) const
	{
		return 6;
	}

	// EditVariablesTableModel
	EditVariablesTableModel::EditVariablesTableModel(QObject *parent)
		: DBTableModel<emulation_dal::Emulation_variable>(DoNotAutoLoad, parent)
	{
		init();
	}

	EditVariablesTableModel::EditVariablesTableModel(emulation_dal::Emulation_variable_store &value, QObject *parent)
		: DBTableModel<emulation_dal::Emulation_variable>(value, parent)
	{
		init();
	}

	void EditVariablesTableModel::init()
	{
	}

	QVariant EditVariablesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
			switch (section) {
			case 0:
				return QObject::tr("Variable name");
			case 1:
				return QObject::tr("Variable type");
			case 2:
				return QObject::tr("Lenght");
			case 3:
				return QObject::tr("Default value");
			case 4:
				return QObject::tr("Description");
			case 5:
				return QObject::tr("Value");
			}
		}

		return QVariant();
	}

	QVariant EditVariablesTableModel::data(const QModelIndex &index, int role) const
	{
		std::shared_ptr<emulation_dal::Emulation> curEmulation;
		std::shared_ptr<emulation_dal::Emulation_variable_type> curVariableType;
		odb::nullable<__int64> curLenght;

		if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
			if (index.row() >= 0 && index.row() < size()) {
				switch (index.column()) {
				case 0:
					return at(index.row())->ev_name();

				case 1:
					curVariableType = at(index.row())->evt();
					if (curVariableType)
						return curVariableType->evt_name();
					break;

				case 2:
					curLenght = at(index.row())->ev_length();

					if (curLenght.null() || curLenght.get() == -1)
						return QObject::tr("Arbitrary lenght");
					else
						return curLenght.get();

					break;

				case 3:
					if (at(index.row())->ev_data_ready())
						return at(index.row())->ev_data();
					else
						return "-";
				case 4:
					return at(index.row())->ev_description();
				case 5:
					return at(index.row())->ev_data();
				}
			}
		}

		return QVariant();
	}

	int EditVariablesTableModel::rowCount(const QModelIndex &parent) const
	{
		return size();
	}

	int EditVariablesTableModel::columnCount(const QModelIndex &parent) const
	{
		return 6;
	}

	// EditVariablesTableModel
	EditFilesTableModel::EditFilesTableModel(QObject *parent)
		: DBTableModel<emulation_dal::Emulation_file>(DoNotAutoLoad, parent)
	{
		init();
	}

	EditFilesTableModel::EditFilesTableModel(emulation_dal::Emulation_file_store &value, QObject *parent)
		: DBTableModel<emulation_dal::Emulation_file>(value, parent)
	{
		init();
	}

	void EditFilesTableModel::init()
	{
	}

	QVariant EditFilesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
			switch (section) {
			case 0:
				return QObject::tr("File name");
			case 1:
				return QObject::tr("File type");
			case 2:
				return QObject::tr("Data flag");
			case 3:
				return QObject::tr("Data");
			case 4:
				return QObject::tr("Use store");
			case 5:
				return QObject::tr("Description");
			}
		}

		return QVariant();
	}

	QVariant EditFilesTableModel::data(const QModelIndex &index, int role) const
	{
		std::shared_ptr<emulation_dal::Emulation> curEmulation;
		std::shared_ptr<emulation_dal::Emulation_file_type> curFileType;
		odb::nullable<__int64> curLenght;

		if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
			if (index.row() >= 0 && index.row() < size()) {
				switch (index.column()) {
				case 0:
					return at(index.row())->ef_name();

				case 1:
					curFileType = at(index.row())->eft();
					if (curFileType)
						return curFileType->eft_name();
					break;

				case 2:
					return at(index.row())->ef_data_ready();
				case 3:
					return at(index.row())->ef_data();
				case 4:
					return at(index.row())->ef_use_file_store();
				case 5:
					return at(index.row())->ef_description();
				}
			}
		}

		return QVariant();
	}

	int EditFilesTableModel::rowCount(const QModelIndex &parent) const
	{
		return size();
	}

	int EditFilesTableModel::columnCount(const QModelIndex &parent) const
	{
		return 6;
	}

	// ViewVariablesTableWidget
	ViewVariablesTableWidget::ViewVariablesTableWidget(QWidget *parent)
		: DBTableViewBase(parent)
	{
		setModel(new ViewVariablesTableModel(this));

		init();
	}

	ViewVariablesTableWidget::ViewVariablesTableWidget(const emulation_dal::Emulation_variable_store &value, QWidget *parent)
		: DBTableViewBase(parent)
	{
		setModel(new ViewVariablesTableModel(value, this));

		init();
	}

	void ViewVariablesTableWidget::init()
	{
		setSelectionBehavior(SelectRows);

		if (isSettingsExist())
			loadSettings();

		connect(horizontalHeader(), SIGNAL(geometriesChanged()), SLOT(saveSettings()));

		enableGlobalActions();

	}

	void ViewVariablesTableWidget::setDataVector(const emulation_dal::Emulation_variable_store &value)
	{
		auto variablesModel = model();

		if (variablesModel)
			variablesModel->setDataVector(value);
	}

	void ViewVariablesTableWidget::clearDataVector()
	{
		auto variablesModel = model();

		if (variablesModel)
			variablesModel->clearDataVector();
	}

	// ViewVariablesWidget
	ViewVariablesWidget::ViewVariablesWidget(QWidget* parent)
		: QWidget(parent)
	{
		m_table = new ViewVariablesTableWidget(this);

		init();
	}

	ViewVariablesWidget::ViewVariablesWidget(const emulation_dal::Emulation_variable_store &value, QWidget *parent)
		: QWidget(parent)
	{
		m_table = new ViewVariablesTableWidget(value, this);

		init();
	}

	void ViewVariablesWidget::init()
	{
		m_label = new QLabel(tr("Scenery variables: "));

		m_layout = new QVBoxLayout();
		m_layout->setContentsMargins(0, 0, 0, 0);
		setLayout(m_layout);

		m_layout->addWidget(m_label);
		m_layout->addWidget(m_table);

	}

	void ViewVariablesWidget::tableData(const emulation_dal::Emulation_variable_store &value)
	{
		m_table->setDataVector(value);
	}

	ViewVariablesTableModel *ViewVariablesWidget::tableModel() const
	{
		return m_table->model();
	}

	void ViewVariablesWidget::clear()
	{
		m_table->clearDataVector();
	}

	bool ViewVariablesWidget::appendById(const long id)
	{
		return tableModel()->appendById(id);
	}

	bool ViewVariablesWidget::updateById(const long id)
	{
		return tableModel()->updateById(id);
	}

	bool ViewVariablesWidget::removeById(const long id)
	{
		return tableModel()->removeById(id);
	}

	// ViewFilesTableWidget
	ViewFilesTableWidget::ViewFilesTableWidget(QWidget *parent)
		: DBTableViewBase(parent)
	{
		setModel(new ViewFilesTableModel(this));

		init();
	}

	ViewFilesTableWidget::ViewFilesTableWidget(const emulation_dal::Emulation_file_store &value, QWidget *parent)
		: DBTableViewBase(parent)
	{
		setModel(new ViewFilesTableModel(value, this));

		init();
	}

	void ViewFilesTableWidget::init()
	{
		setSelectionBehavior(SelectRows);

		if (isSettingsExist())
			loadSettings();

		connect(horizontalHeader(), SIGNAL(geometriesChanged()), SLOT(saveSettings()));

		enableGlobalActions();

	}

	void ViewFilesTableWidget::setDataVector(const emulation_dal::Emulation_file_store &value)
	{
		auto filesModel = model();

		if (filesModel)
			filesModel->setDataVector(value);
	}

	void ViewFilesTableWidget::clearDataVector()
	{
		auto filesModel = model();

		if (filesModel)
			filesModel->clearDataVector();
	}

	// ViewFilesWidget
	ViewFilesWidget::ViewFilesWidget(QWidget* parent)
		: QWidget(parent)
	{
		m_table = new ViewFilesTableWidget(this);

		init();
	}

	ViewFilesWidget::ViewFilesWidget(const emulation_dal::Emulation_file_store &value, QWidget *parent)
		: QWidget(parent)
	{
		m_table = new ViewFilesTableWidget(value, this);

		init();
	}

	void ViewFilesWidget::init()
	{
		m_label = new QLabel(tr("Scenery files: "));

		m_useFileStoreLabel = new QLabel();

		m_layout = new QVBoxLayout();
		m_layout->setContentsMargins(0, 0, 0, 0);
		setLayout(m_layout);

		m_layout->addWidget(m_label);
		m_layout->addWidget(m_useFileStoreLabel);
		m_layout->addWidget(m_table);

	}

	void ViewFilesWidget::tableData(const emulation_dal::Emulation_file_store &value)
	{
		m_table->setDataVector(value);
	}

	ViewFilesTableModel *ViewFilesWidget::tableModel() const
	{
		return m_table->model();
	}

	void ViewFilesWidget::clear()
	{
		m_table->clearDataVector();
	}

	void ViewFilesWidget::useFileStore(const bool value, const QString path)
	{
		if (value) {
			auto trimmedPath = path.trimmed();

			if (trimmedPath.isEmpty()) {
				m_useFileStoreLabel->setText(tr("Use file store"));

			}
			else {
				m_useFileStoreLabel->setText(tr("Use file store, path: ") + trimmedPath);

			}

		}
		else
			m_useFileStoreLabel->setText(tr("Dont use file store"));

	}

	bool ViewFilesWidget::appendById(const long id)
	{
		return tableModel()->appendById(id);
	}

	bool ViewFilesWidget::updateById(const long id)
	{
		return tableModel()->updateById(id);
	}

	bool ViewFilesWidget::removeById(const long id)
	{
		return tableModel()->removeById(id);
	}

	// EditFilesVariablesTableWidgetBase
	EditFilesVariablesTableWidgetBase::EditFilesVariablesTableWidgetBase(QWidget *parent)
		: DBTableViewBase(parent)
	{
		init();
	}

	void EditFilesVariablesTableWidgetBase::init()
	{
		connect(this, SIGNAL(selectionChanged(const QModelIndex)), SLOT(enableGlobalActions()));
	}

	void EditFilesVariablesTableWidgetBase::enableGlobalActions()
	{
		enableNewAction();

		if (currentIndex().isValid()) {
			enableOpenAction();
			enableDeleteAction();
		}
	}

	// EditFilesVariablesWidgetBase
	EditFilesVariablesWidgetBase::EditFilesVariablesWidgetBase(QWidget* parent)
		: QWidget(parent)
	{
		init();
	}

	void EditFilesVariablesWidgetBase::init()
	{
		m_toolbar = new NERToolbar(tr("Edit variables toolbar"));

		m_label = new QLabel();

		m_layout = new QVBoxLayout();
		m_layout->setContentsMargins(0, 0, 0, 0);
		setLayout(m_layout);

		QHBoxLayout *labelLayout = new QHBoxLayout();

		labelLayout->addWidget(m_label);
		labelLayout->addStretch();
		labelLayout->addWidget(m_toolbar);

		m_layout->addLayout(labelLayout);

		int buttonsHeight = m_label->fontMetrics().height();

		if (buttonsHeight > 0)
			m_toolbar->setIconSize(QSize(buttonsHeight, buttonsHeight));

	}

	void EditFilesVariablesWidgetBase::updateControlsAccesibility()
	{
		if (m_table) {
			if (m_table->currentIndex().isValid())
			{
				m_toolbar->editAction()->setEnabled(true);
				m_toolbar->removeAction()->setEnabled(true);

			}
			else {
				m_toolbar->editAction()->setEnabled(false);
				m_toolbar->removeAction()->setEnabled(false);

			}
		}
		else
			m_toolbar->disableAllActions();

	}

	EditFilesVariablesTableWidgetBase *EditFilesVariablesWidgetBase::tableWidget() const
	{
		return m_table;

	}

	void EditFilesVariablesWidgetBase::setTableWidget(EditFilesVariablesTableWidgetBase *value)
	{
		if (!m_table) {
			m_table = value;

			m_layout->addWidget(m_table);

			connect(m_table, SIGNAL(selectionChanged(const QModelIndex)), SLOT(updateControlsAccesibility()));

			updateControlsAccesibility();
		}
		else
			throw std::exception();

	}

	// EditVariablesTableWidget
	EditVariablesTableWidget::EditVariablesTableWidget(QWidget *parent)
		: EditFilesVariablesTableWidgetBase(parent)
	{
		init();
	}

	EditVariablesTableWidget::EditVariablesTableWidget(const std::shared_ptr<emulation_dal::Emulation> emulationData, QWidget *parent)
		: EditFilesVariablesTableWidgetBase(parent)
	{
		init();

		if (emulationData)
			setDataVector(*emulationData->emulation_variables());

	}

	void EditVariablesTableWidget::init()
	{
		setModel(new EditVariablesTableModel(this));

		setItemDelegateForColumn(1, new VariableTypesListDelegate(this));
		setItemDelegateForColumn(2, new VariableLenghtDelegate(this));

		setSelectionBehavior(SelectRows);

		if (isSettingsExist())
			loadSettings();

		connect(horizontalHeader(), SIGNAL(geometriesChanged()), SLOT(saveSettings()));

		enableGlobalActions();

	}

	void EditVariablesTableWidget::setDataVector(const emulation_dal::Emulation_variable_store &value)
	{
		auto variablesModel = model();

		if (variablesModel)
			variablesModel->setDataVector(value);
	}

	const emulation_dal::Emulation_variable_store &EditVariablesTableWidget::dataVector() const
	{
		return *model();
	}

	void EditVariablesTableWidget::clearDataVector()
	{
		auto variablesModel = model();

		if (variablesModel)
			variablesModel->clearDataVector();
	}

	void EditVariablesTableWidget::newVariableDialog()
	{
		EditVariablesDialog *dialog = new EditVariablesDialog(this);

		if (dialog->exec() == QDialog::Accepted) {
			auto data = dialog->dbData();

			if (data) {

				auto variablesModel = model();

				if (variablesModel) {
					for (auto i : *variablesModel) {
						if (i && i->ev_name().trimmed() == data->ev_name().trimmed()) {
							Global::Messages::ErrorMessage(tr("Variable name ") + data->ev_name().trimmed() + tr(" is already exist!"));
							return;
						}

					}

					variablesModel->push_back(data);
					emit addVariableSignal(data->ev_name());

				}

			}

		}

	}

	void EditVariablesTableWidget::editVariableDialog(const QString &value)
	{
		auto it = model()->find_by_attribute(emulation_dal::Emulation_variable::Attributes::EV_NAME, value);

		if (it != model()->end()) {
			auto lastData = *it;

			if (lastData) {
				QString lastName = lastData->ev_name();

				EditVariablesDialog *dialog = new EditVariablesDialog(lastData, this);

				if (dialog->exec() == QDialog::Accepted) {

					auto newData = dialog->dbData();

					if (newData) {

						auto variablesModel = model();

						auto newName = newData->ev_name();

						if (variablesModel) {
							for (auto i : *variablesModel) {
								if (i && i != newData && i->ev_name().trimmed() == newData->ev_name().trimmed()) {
									newData->ev_name(lastName);
									Global::Messages::ErrorMessage(tr("Variable name ") + newName.trimmed() + tr(" is already exist!"));
									return;
								}
							}

							variablesModel->at(it, newData);
							emit editVariableSignal(lastName, newName);

						}

					}

				}

			}

		}

	}

	void EditVariablesTableWidget::removeVariable(const QString &value)
	{		
		auto it = model()->find_by_attribute(emulation_dal::Emulation_variable::Attributes::EV_NAME, value);

		if (it != model()->end() && *it) {
			if (Global::Messages::YesNoMessage(tr("Delete current record?"), tr("Deleting record")) == QMessageBox::Yes) {

				auto deletedName = (*it)->ev_name();

				model()->removeRow(it);

				emit deleteVariableSignal(deletedName);
			}

		}
		
	}

	
	void EditVariablesTableWidget::onNewAction()
	{
		newVariableDialog();
	}

	void EditVariablesTableWidget::onOpenAction()
	{
		QModelIndex idx = currentIndex();

		if (idx.isValid()) {

			auto lastData = model()->at(idx.row());

			if (lastData) {

				QString lastName = lastData->ev_name();

				EditVariablesDialog *dialog = new EditVariablesDialog(lastData, this);

				if (dialog->exec() == QDialog::Accepted) {

					auto newData = dialog->dbData();

					if (newData) {

						auto variablesModel = model();

						auto newName = newData->ev_name();

						if (variablesModel) {
							for (auto i : *variablesModel) {
								if (i && i != newData && i->ev_name().trimmed() == newData->ev_name().trimmed()) {
									newData->ev_name(lastName);
									Global::Messages::ErrorMessage(tr("Variable name ") + newName.trimmed() + tr(" is already exist!"));
									return;
								}
							}

							variablesModel->at(idx.row(), newData);
							emit editVariableSignal(lastName, newName);

						}

					}

				}

			}

		}

	}

	void EditVariablesTableWidget::onDeleteAction()
	{
		QModelIndex idx = currentIndex();

		if (idx.isValid()) {

			if (Global::Messages::YesNoMessage(tr("Delete current record?"), tr("Deleting record")) == QMessageBox::Yes) {
				auto variablesModel = model();

				if (variablesModel) {

					auto deletedRec = variablesModel->at(idx.row());

					variablesModel->removeRow(idx.row());

					if (deletedRec) {

						emit deleteVariableSignal(deletedRec->ev_name());

					}

				}

			}

		}

	}

	void EditVariablesTableWidget::contextMenuEvent(QContextMenuEvent *e)
	{
		QTableView::contextMenuEvent(e);

		QModelIndex cur = currentIndex();

		QMenu contextMenu(tr("Context Menu"));

		QAction *createAction = contextMenu.addAction(tr("New"));
		QAction *editAction = contextMenu.addAction(tr("Edit"));
		contextMenu.addSeparator();
		QAction *deleteAction = contextMenu.addAction(tr("Delete"));

		if (!cur.isValid()) {
			editAction->setDisabled(true);
			deleteAction->setDisabled(true);
		}

		QAction *selectedAction = contextMenu.exec(e->globalPos());

		if (selectedAction == createAction)
			onNewAction();
		else if (selectedAction == editAction)
			onOpenAction();
		else if (selectedAction == deleteAction)
			onDeleteAction();

	}

	// EditVariablesWidget
	EditVariablesWidget::EditVariablesWidget(QWidget* parent)
		: EditFilesVariablesWidgetBase(parent)
	{
		init();
	}

	EditVariablesWidget::EditVariablesWidget(const std::shared_ptr<emulation_dal::Emulation> data, QWidget* parent)
		: EditFilesVariablesWidgetBase(parent)
	{
		init();

		loadDBData(data);
	}

	void EditVariablesWidget::init()
	{
		EditFilesVariablesWidgetBase::setTableWidget(new EditVariablesTableWidget(this));

		m_label->setText(tr("Scenery variables: "));

		connect(m_toolbar->newAction(), SIGNAL(triggered(bool)), SLOT(onNewAction()));
		connect(m_toolbar->editAction(), SIGNAL(triggered(bool)), SLOT(onOpenAction()));
		connect(m_toolbar->removeAction(), SIGNAL(triggered(bool)), SLOT(onDeleteAction()));

		connect(table(), SIGNAL(addVariableSignal(const QString &)), SIGNAL(addVariableSignal(const QString &)));
		connect(table(), SIGNAL(editVariableSignal(const QString &, const QString &)), SIGNAL(editVariableSignal(const QString &, const QString &)));
		connect(table(), SIGNAL(deleteVariableSignal(const QString &)), SIGNAL(deleteVariableSignal(const QString &)));
	}

	EditVariablesTableWidget *EditVariablesWidget::table() const
	{
		return dynamic_cast<EditVariablesTableWidget *>(EditFilesVariablesWidgetBase::tableWidget());
	}

	void EditVariablesWidget::tableData(const emulation_dal::Emulation_variable_store &value)
	{
		table()->setDataVector(value);
	}

	const emulation_dal::Emulation_variable_store &EditVariablesWidget::tableData() const
	{
		return table()->dataVector();
	}

	EditVariablesTableModel *EditVariablesWidget::tableModel() const
	{
		return table()->model();
	}

	void EditVariablesWidget::clear()
	{
		table()->clearDataVector();
	}

	void EditVariablesWidget::onNewAction()
	{
		table()->onNewAction();
	}

	void EditVariablesWidget::onOpenAction()
	{
		table()->onOpenAction();
	}

	void EditVariablesWidget::onDeleteAction()
	{
		table()->onDeleteAction();
	}

	void EditVariablesWidget::newVariableDialog()
	{
		table()->newVariableDialog();
	}

	void EditVariablesWidget::editVariableDialog(const QString &value)
	{
		table()->editVariableDialog(value);
	}

	void EditVariablesWidget::removeVariable(const QString &value)
	{
		table()->removeVariable(value);
	}

	void EditVariablesWidget::loadDBData(const std::shared_ptr<emulation_dal::Emulation> data)
	{
		if (data)
			tableData(*data->emulation_variables());
	}

	// EditFilesTableWidget
	EditFilesTableWidget::EditFilesTableWidget(QWidget *parent)
		: EditFilesVariablesTableWidgetBase(parent)
	{
		init();
	}

	EditFilesTableWidget::EditFilesTableWidget(const std::shared_ptr<emulation_dal::Emulation> emulationData, QWidget *parent)
		: EditFilesVariablesTableWidgetBase(parent)
	{
		init();

		if (emulationData)
			setDataVector(*emulationData->emulation_files());
	}

	void EditFilesTableWidget::init()
	{
		setModel(new EditFilesTableModel(this));

		setItemDelegateForColumn(1, new VariableTypesListDelegate(this));
		setItemDelegateForColumn(2, new VariableLenghtDelegate(this));

		setSelectionBehavior(SelectRows);

		if (isSettingsExist())
			loadSettings();

		connect(horizontalHeader(), SIGNAL(geometriesChanged()), SLOT(saveSettings()));

		enableGlobalActions();

	}

	void EditFilesTableWidget::setDataVector(const emulation_dal::Emulation_file_store &value)
	{
		auto filesModel = model();

		if (filesModel)
			filesModel->setDataVector(value);
	}

	const emulation_dal::Emulation_file_store &EditFilesTableWidget::dataVector() const
	{
		return *model();
	}

	void EditFilesTableWidget::clearDataVector()
	{
		auto filesModel = model();

		if (filesModel)
			model()->clearDataVector();
	}

	void EditFilesTableWidget::newFileDialog()
	{
		EditFilesDialog *dialog = new EditFilesDialog(this);

		if (dialog->exec() == QDialog::Accepted) {
			auto data = dialog->dbData();

			if (data) {
				auto filesModel = model();

				if (filesModel) {
					for (auto i : *filesModel) {
						if (i && i->ef_name().trimmed() == data->ef_name().trimmed()) {
							Global::Messages::ErrorMessage(tr("File name ") + data->ef_name().trimmed() + tr(" is already exist!"));
							return;
						}
					}

					filesModel->push_back(data);
					emit addFileSignal(data->ef_name());

				}

			}

		}

	}

	void EditFilesTableWidget::editFileDialog(const QString &value)
	{
		auto it = model()->find_by_attribute(emulation_dal::Emulation_file::Attributes::EF_NAME, value);

		if (it != model()->end()) {

			auto lastData = *it;

			if (lastData) {
				QString lastName = lastData->ef_name();

				EditFilesDialog *dialog = new EditFilesDialog(lastData, this);

				if (dialog->exec() == QDialog::Accepted) {
					auto newData = dialog->dbData();

					if (newData) {
						auto filesModel = model();

						auto newName = newData->ef_name();

						if (filesModel) {
							for (auto i : *filesModel) {
								if (i && i != newData && i->ef_name().trimmed() == newData->ef_name().trimmed()) {
									newData->ef_name(lastName);
									Global::Messages::ErrorMessage(tr("File name ") + newName.trimmed() + tr(" is already exist!"));
									return;
								}
							}

							filesModel->at(it, newData);
							emit editFileSignal(lastName, newName);

						}

					}

				}

			}

		}

	}

	void EditFilesTableWidget::removeFile(const QString &value)
	{
		auto it = model()->find_by_attribute(emulation_dal::Emulation_file::Attributes::EF_NAME, value);

		if (it != model()->end() && *it) {
			if (Global::Messages::YesNoMessage(tr("Delete current record?"), tr("Deleting record")) == QMessageBox::Yes) {
				auto deletedName = (*it)->ef_name();
				model()->removeRow(it);
				emit deleteFileSignal(deletedName);

			}

		}

	}

	void EditFilesTableWidget::onNewAction()
	{
		newFileDialog();
	}

	void EditFilesTableWidget::onOpenAction()
	{
		QModelIndex idx = currentIndex();

		if (idx.isValid()) {

			auto lastData = model()->at(idx.row());

			if (lastData) {

				QString lastName = lastData->ef_name();

				EditFilesDialog *dialog = new EditFilesDialog(lastData, this);

				if (dialog->exec() == QDialog::Accepted) {

					auto newData = dialog->dbData();

					if (newData) {

						auto filesModel = model();

						auto newName = newData->ef_name();

						if (filesModel) {
							for (auto i : *filesModel) {
								if (i && i != newData && i->ef_name().trimmed() == newData->ef_name().trimmed()) {
									newData->ef_name(lastName);
									Global::Messages::ErrorMessage(tr("File name ") + newName.trimmed() + tr(" is already exist!"));
									return;
								}
							}

							filesModel->at(idx.row(), newData);
							emit editFileSignal(lastName, newName);

						}

					}

				}

			}

		}

	}

	void EditFilesTableWidget::onDeleteAction()
	{
		QModelIndex idx = currentIndex();

		if (idx.isValid()) {

			if (Global::Messages::YesNoMessage(tr("Delete current record?"), tr("Deleting record")) == QMessageBox::Yes) {
				auto filesModel = model();

				if (filesModel) {
					auto deletedRec = filesModel->at(idx.row());

					filesModel->removeRow(idx.row());

					emit deleteFileSignal(deletedRec->ef_name());

				}

			}

		}

	}

	void EditFilesTableWidget::contextMenuEvent(QContextMenuEvent *e)
	{
		QTableView::contextMenuEvent(e);

		QModelIndex cur = currentIndex();

		QMenu contextMenu(tr("Context Menu"));

		QAction *createAction = contextMenu.addAction(tr("New"));
		QAction *editAction = contextMenu.addAction(tr("Edit"));
		contextMenu.addSeparator();
		QAction *deleteAction = contextMenu.addAction(tr("Delete"));

		if (!cur.isValid()) {
			editAction->setDisabled(true);
			deleteAction->setDisabled(true);
		}

		QAction *selectedAction = contextMenu.exec(e->globalPos());

		if (selectedAction == createAction)
			onNewAction();
		else if (selectedAction == editAction)
			onOpenAction();
		else if (selectedAction == deleteAction)
			onDeleteAction();
	}

	// EditFilesWidget
	EditFilesWidget::EditFilesWidget(QWidget* parent)
		: EditFilesVariablesWidgetBase(parent)
	{
		init();

	}

	EditFilesWidget::EditFilesWidget(const std::shared_ptr<emulation_dal::Emulation> data, QWidget* parent)
		: EditFilesVariablesWidgetBase(parent)
	{
		init();

		loadDBData(data);

	}

	void EditFilesWidget::init()
	{
		QHBoxLayout *fileStoreLayout = new QHBoxLayout();

		m_useFileStoreCheckBox = new CheckBox(tr("Use file store"));
		m_layout->addWidget(m_useFileStoreCheckBox);

		m_fileStorePath = new QLineEdit();

		fileStoreLayout->addWidget(m_useFileStoreCheckBox);
		fileStoreLayout->addWidget(m_fileStorePath);

		m_layout->addLayout(fileStoreLayout);

		EditFilesVariablesWidgetBase::setTableWidget(new EditFilesTableWidget(this));

		m_label->setText(tr("Scenery files: "));

		connect(m_toolbar->newAction(), SIGNAL(triggered(bool)), SLOT(onNewAction()));
		connect(m_toolbar->editAction(), SIGNAL(triggered(bool)), SLOT(onOpenAction()));
		connect(m_toolbar->removeAction(), SIGNAL(triggered(bool)), SLOT(onDeleteAction()));

		connect(table(), SIGNAL(addFileSignal(const QString &)), SIGNAL(addFileSignal(const QString &)));
		connect(table(), SIGNAL(editFileSignal(const QString &, const QString &)), SIGNAL(editFileSignal(const QString &, const QString &)));
		connect(table(), SIGNAL(deleteFileSignal(const QString &)), SIGNAL(deleteFileSignal(const QString &)));

		connect(m_useFileStoreCheckBox, SIGNAL(stateChanged(int)), SLOT(updateFileStoreAccesibility()));

		updateFileStoreAccesibility();

	}

	EditFilesTableWidget *EditFilesWidget::table() const
	{
		return dynamic_cast<EditFilesTableWidget *>(EditFilesVariablesWidgetBase::tableWidget());
	}

	bool EditFilesWidget::useFileStore() const
	{
		return m_useFileStoreCheckBox->isChecked();
	}

	void EditFilesWidget::useFileStore(const bool value)
	{
		m_useFileStoreCheckBox->setChecked(value);
	}

	QString EditFilesWidget::fileStorePath() const
	{
		return m_fileStorePath->text();
	}

	void EditFilesWidget::fileStorePath(const QString &value)
	{
		m_fileStorePath->setText(value);
	}

	void EditFilesWidget::tableData(const emulation_dal::Emulation_file_store &value)
	{
		table()->setDataVector(value);
	}

	const emulation_dal::Emulation_file_store &EditFilesWidget::tableData() const
	{
		return table()->dataVector();
	}

	EditFilesTableModel *EditFilesWidget::tableModel() const
	{
		return table()->model();
	}

	void EditFilesWidget::newVariableDialog()
	{
		table()->newFileDialog();
	}

	void EditFilesWidget::editVariableDialog(const QString &value)
	{
		table()->editFileDialog(value);
	}

	void EditFilesWidget::removeVariable(const QString &value)
	{
		table()->removeFile(value);
	}

	void EditFilesWidget::clear()
	{
		table()->clearDataVector();
	}

	void EditFilesWidget::onNewAction()
	{
		table()->onNewAction();
	}

	void EditFilesWidget::onOpenAction()
	{
		table()->onOpenAction();
	}

	void EditFilesWidget::onDeleteAction()
	{
		table()->onDeleteAction();
	}

	void EditFilesWidget::updateFileStoreAccesibility()
	{
		m_fileStorePath->setEnabled(useFileStore());
	}

	void EditFilesWidget::loadDBData(const std::shared_ptr<emulation_dal::Emulation> data)
	{
		if (data) {
			tableData(*data->emulation_files());
			useFileStore(data->emulation_use_file_store());
			fileStorePath(data->emulation_file_store_path());
			
			updateFileStoreAccesibility();
		}

	}

	// DVFSplitterBase
	DVFSplitterBase::DVFSplitterBase(WidgetBase* parent)
		: QSplitter(parent), ParentWidget(parent)
	{
		init();
	}

	void DVFSplitterBase::init()
	{
		QLabel *descriptionLabel = new QLabel(tr("Description:"));
		m_descriptionEdit = new PlainTextEdit();

		QWidget *descriptionWidget = new QWidget();
		QVBoxLayout *descriptionLayout = new QVBoxLayout();
		descriptionLayout->setContentsMargins(0, 0, 0, 0);
		descriptionWidget->setLayout(descriptionLayout);

		descriptionLayout->addWidget(descriptionLabel);
		descriptionLayout->addWidget(m_descriptionEdit);

		setOrientation(Qt::Vertical);
		setContentsMargins(0, 0, 0, 0);

		addWidget(descriptionWidget);

		connect(emulation_dal::DB::notifier()->Emulation_notify(), SIGNAL(updated(const NotifyEvent &)), SLOT(update(const NotifyEvent &)));

	}

	void DVFSplitterBase::description(const QString& value)
	{
		m_descriptionEdit->setPlainText(value);
	}

	QString DVFSplitterBase::description() const
	{
		return m_descriptionEdit->toPlainText();
	}

	void DVFSplitterBase::clear()
	{
		m_descriptionEdit->clear();
	}

	void DVFSplitterBase::loadDBData()
	{
		clear();

		auto data = dbData();

		if (data) {
			description(data->emulation_description());
		}

	}

	void DVFSplitterBase::updateDBData()
	{
		auto data = dbData();

		if (data)
			data->emulation_description(description());
	}

	void DVFSplitterBase::update(const NotifyEvent &ev)
	{
		auto emulation = emulation_dal::Emulation_store::query_one_by_id(ev.objectId());

		auto data = dbData();

		if (emulation && data && *data == *emulation)
			description(emulation->emulation_description());

	}

	// ViewDVFSplitter
	ViewDVFSplitter::ViewDVFSplitter(WidgetBase* parent)
		: DVFSplitterBase(parent)
	{
		init();
	}

	void ViewDVFSplitter::init()
	{
		// Окно просмотра переменных
		m_variablesWidget = new ViewVariablesWidget(this);
		addWidget(m_variablesWidget);

		// Окно просмотра файлов
		m_filesWidget = new ViewFilesWidget(this);
		addWidget(m_filesWidget);

		m_descriptionEdit->setReadOnly(true);

		if (isSettingsExist())
			loadSettings();

		connect(this, SIGNAL(splitterMoved(int, int)), SLOT(saveSettings()));

		connect(emulation_dal::DB::notifier()->Emulation_variable_notify(), SIGNAL(added(const NotifyEvent &)), SLOT(appendVariable(const NotifyEvent &)));
		connect(emulation_dal::DB::notifier()->Emulation_variable_notify(), SIGNAL(updated(const NotifyEvent &)), SLOT(updateVariable(const NotifyEvent &)));
		connect(emulation_dal::DB::notifier()->Emulation_variable_notify(), SIGNAL(removed(const NotifyEvent &)), SLOT(removeVariable(const NotifyEvent &)));

		connect(emulation_dal::DB::notifier()->Emulation_file_notify(), SIGNAL(added(const NotifyEvent &)), SLOT(appendFile(const NotifyEvent &)));
		connect(emulation_dal::DB::notifier()->Emulation_file_notify(), SIGNAL(updated(const NotifyEvent &)), SLOT(updateFile(const NotifyEvent &)));
		connect(emulation_dal::DB::notifier()->Emulation_file_notify(), SIGNAL(removed(const NotifyEvent &)), SLOT(removeFile(const NotifyEvent &)));

	}

	void ViewDVFSplitter::clear()
	{
		DVFSplitterBase::clear();

		m_variablesWidget->clear();
		m_filesWidget->clear();
	}

	void ViewDVFSplitter::variablesData(const emulation_dal::Emulation_variable_store &value)
	{
		m_variablesWidget->tableData(value);
	}

	void ViewDVFSplitter::filesData(const emulation_dal::Emulation_file_store &value)
	{
		m_filesWidget->tableData(value);
	}

	ViewVariablesTableModel *ViewDVFSplitter::model() const
	{
		return m_variablesWidget->tableModel();
	}

	void ViewDVFSplitter::setEditable(const bool flag)
	{
		m_descriptionEdit->setEnabled(flag);
	}

	void ViewDVFSplitter::loadDBData()
	{
		clear();

		DVFSplitterBase::loadDBData();

		auto data = dbData();

		if (data) {
			variablesData(*data->emulation_variables());
			filesData(*data->emulation_files());
			m_filesWidget->useFileStore(data->emulation_use_file_store(), data->emulation_file_store_path());
		}

	}

	void ViewDVFSplitter::appendVariable(const NotifyEvent &ev)
	{
		auto variable = emulation_dal::Emulation_variable_store::query_one_by_id(ev.objectId());

		auto data = dbData();

		if (variable && data) {
			if (*variable->emulation() == *data)
				m_variablesWidget->appendById(ev.objectId());
		}
	}

	void ViewDVFSplitter::updateVariable(const NotifyEvent &ev)
	{
		auto data = dbData();

		if (data) {
				m_variablesWidget->updateById(ev.objectId());
		}

	}

	void ViewDVFSplitter::removeVariable(const NotifyEvent &ev)
	{
		auto data = dbData();

		if (data) {
			m_variablesWidget->removeById(ev.objectId());
		}

	}

	void ViewDVFSplitter::appendFile(const NotifyEvent &ev)
	{
		auto file = emulation_dal::Emulation_file_store::query_one_by_id(ev.objectId());

		auto data = dbData();

		if (file && data) {
			if (*file->emulation() == *data)
				m_filesWidget->appendById(ev.objectId());
		}

	}

	void ViewDVFSplitter::updateFile(const NotifyEvent &ev)
	{
		auto data = dbData();

		if (& data) {
			m_filesWidget->updateById(ev.objectId());
		}

	}
	
	void ViewDVFSplitter::removeFile(const NotifyEvent &ev)
	{
		auto data = dbData();

		if (data) {
			m_filesWidget->removeById(ev.objectId());
		}

	}

	// EditDVFSplitter
	EditDVFSplitter::EditDVFSplitter(WidgetBase *parent)
		: DVFSplitterBase(parent)
	{
		init();
	}

	void EditDVFSplitter::init()
	{
		// Окно просмотра переменных
		m_variablesWidget = new EditVariablesWidget(this);
		addWidget(m_variablesWidget);

		m_filesWidget = new EditFilesWidget(this);
		addWidget(m_filesWidget);

		if (isSettingsExist())
			loadSettings();

		connect(this, SIGNAL(splitterMoved(int, int)), SLOT(saveSettings()));
	}

	void EditDVFSplitter::clear()
	{
		DVFSplitterBase::clear();

		m_variablesWidget->clear();
		m_filesWidget->clear();
	}

	void EditDVFSplitter::variablesData(const emulation_dal::Emulation_variable_store &value)
	{
		m_variablesWidget->tableData(value);
	}

	void EditDVFSplitter::filesData(const emulation_dal::Emulation_file_store &value)
	{
		m_filesWidget->tableData(value);
	}

	EditVariablesTableModel *EditDVFSplitter::variablesModel() const
	{
		return m_variablesWidget->tableModel();
	}

	EditFilesTableModel *EditDVFSplitter::filesModel() const
	{
		return m_filesWidget->tableModel();
	}

	EditVariablesWidget *EditDVFSplitter::variablesWidget() const
	{
		return m_variablesWidget;
	}

	EditFilesWidget *EditDVFSplitter::filesWidget() const
	{
		return m_filesWidget;
	}

	void EditDVFSplitter::loadDBData()
	{
		clear();

		DVFSplitterBase::loadDBData();

		auto data = dbData();

		if (data) {
			variablesData(*data->emulation_variables());
			filesData(*data->emulation_files());

			m_filesWidget->useFileStore(data->emulation_use_file_store());
			m_filesWidget->fileStorePath(data->emulation_file_store_path());
		}

	}

	void EditDVFSplitter::updateDBData()
	{
		DVFSplitterBase::updateDBData();

		auto data = dbData();

		if (data) {
			data->emulation_variables(*variablesModel());
			data->emulation_files(*filesModel());

			data->emulation_use_file_store(m_filesWidget->useFileStore());
			data->emulation_file_store_path(m_filesWidget->fileStorePath());

		}

	}

	// EmulationRuntimeRequestsModel
	EmulationRuntimeRequestsModel::EmulationRuntimeRequestsModel(WidgetBase *parent)
		: RuntimeRequestsModelBase(DoNotAutoLoad, parent), ParentWidget(parent)
	{
		init();

		loadDBData();
	}

	void EmulationRuntimeRequestsModel::init()
	{
		createUpdateConnections();
	}

	void EmulationRuntimeRequestsModel::loadDBData()
	{
		auto data = emulation();

		if (data)
			setDataVector(*data->emulation_runtime_requests());
	}
	
	const std::shared_ptr<emulation_dal::Emulation> EmulationRuntimeRequestsModel::emulation() const
	{
		if (m_parentContainerWidget)
			return m_parentContainerWidget->dbData();

		return std::shared_ptr<emulation_dal::Emulation>();
	}
	
	void EmulationRuntimeRequestsModel::append(const NotifyEvent &ev)
	{
		std::shared_ptr<emulation_dal::Emulation_runtime_request> newRecord = Emulation_runtime_request_store::query_one_by_id(ev.objectId());

		auto data = emulation();

		if (newRecord && newRecord->emulation() && data && newRecord->emulation_id() == data->id())
			appendById(ev.objectId());
	}

	void EmulationRuntimeRequestsModel::update(const NotifyEvent &ev)
	{
		updateById(ev.objectId());
	}

	void EmulationRuntimeRequestsModel::remove(const NotifyEvent &ev)
	{
		removeById(ev.objectId());
	}

	void EmulationRuntimeRequestsModel::createUpdateConnections()
	{
		connect(emulation_dal::DB::notifier()->Emulation_runtime_request_notify(), SIGNAL(added(const NotifyEvent &)), SLOT(append(const NotifyEvent &)));
		connect(emulation_dal::DB::notifier()->Emulation_runtime_request_notify(), SIGNAL(updated(const NotifyEvent &)), SLOT(update(const NotifyEvent &)));
		connect(emulation_dal::DB::notifier()->Emulation_runtime_request_notify(), SIGNAL(removed(const NotifyEvent &)), SLOT(remove(const NotifyEvent &)));
	}

	// RuntimeRequestsWidget
	RuntimeRequestsWidget::RuntimeRequestsWidget(WidgetBase *parent)
		: RuntimeRequestsWidgetBase(parent), ParentWidget(parent)
	{
		init();
	}

	EmulationRuntimeRequestsModel *RuntimeRequestsWidget::model() const
	{
		return dynamic_cast<EmulationRuntimeRequestsModel *>(QTableView::model());
	}

	void RuntimeRequestsWidget::init()
	{
		setModel(new EmulationRuntimeRequestsModel(m_parentContainerWidget));

		if (isSettingsExist())
			loadSettings();

		connect(horizontalHeader(), SIGNAL(geometriesChanged()), SLOT(saveSettings()));

		connect(this, SIGNAL(selectionChanged(const QModelIndex)), SLOT(enableActions(const QModelIndex)));

		enableGlobalActions();
	}

	void RuntimeRequestsWidget::contextMenuEvent(QContextMenuEvent *event)
	{
		QModelIndex cur = currentIndex();

		QMenu contextMenu(QObject::tr("Runtime Requests Context Menu"));

		QAction *showResultsAction = contextMenu.addAction(tr("Show results"));
		contextMenu.addSeparator();

		QAction *pauseAction = contextMenu.addAction(tr("Pause scenery"));
		QAction *continueAction = contextMenu.addAction(tr("Continue scenery"));
		QAction *stopAction = contextMenu.addAction(tr("Stop scenery"));
		contextMenu.addSeparator();

		QAction *deleteAction = contextMenu.addAction(tr("Delete"));

		QAction *selectedAction = contextMenu.exec(event->globalPos());

		if (selectedAction == showResultsAction)
			showCurrentResults();
		else if (selectedAction == pauseAction)
			pauseCurrentScenery();
		else if (selectedAction == continueAction)
			continueCurrentScenery();
		else if (selectedAction == stopAction)
			stopCurrentScenery();
		else if (selectedAction == deleteAction)
			removeCurrentRequest();
	}

	void RuntimeRequestsWidget::setDataVector(const emulation_dal::Emulation_runtime_request_store value)
	{
		if (model())
			model()->setDataVector(value);
	}

	void RuntimeRequestsWidget::loadDBData()
	{
		model()->loadDBData();
	}

	void RuntimeRequestsWidget::enableGlobalActions()
	{
		enableRunAction(true);

		enableActions(currentIndex());
	}

	void RuntimeRequestsWidget::enableActions(const QModelIndex idx)
	{
		if (idx.isValid()) {
			enableDeleteAction(true);
			enablePauseAction(true);
			enableStopAction(true);
			enableShowResultsAction(true);
			enableShowArchieveAction(true);
			enableFindAction(true);
		}
	}

	void RuntimeRequestsWidget::clear()
	{
		if (model())
			model()->clearDataVector();
	}


	void RuntimeRequestsWidget::runCurrentScenery()
	{
		if (model() && model()->emulation()) {

			Emulation::runScenery(model()->emulation());

		}

	}

	void RuntimeRequestsWidget::pauseCurrentScenery()
	{
		QModelIndex idx = currentIndex();

		if (idx.isValid()) {

			Emulation::pauseScenery(model()->at(idx.row()));

		}

	}

	void RuntimeRequestsWidget::continueCurrentScenery()
	{
		QModelIndex idx = currentIndex();

		if (idx.isValid()) {

			Emulation::continueScenery(model()->at(idx.row()));

		}

	}

	void RuntimeRequestsWidget::stopCurrentScenery()
	{
		QModelIndex idx = currentIndex();

		if (idx.isValid()) {

			Emulation::stopScenery(model()->at(idx.row()));

		}

	}

	// BasicsWidgetBase
	BasicsWidgetBase::BasicsWidgetBase(WidgetBase *containerWidget)
		: QWidget(containerWidget), ParentWidget(containerWidget)
	{
		init();

		loadDBData();
	}

	void BasicsWidgetBase::init()
	{
		m_mainLayout = new QVBoxLayout(this);

		m_dateLayout = new QGridLayout();

		m_dateLayout->addWidget(new QLabel(tr("Creation date:"), this), 0, 0);
		m_dateLayout->addWidget(m_creationDateTimeValueLabel = new QLabel("-", this), 0, 1);

		m_dateLayout->addWidget(new QLabel(tr("Editing date:"), this), 0, 2);
		m_dateLayout->addWidget(m_editingDateTimeValueLabel = new QLabel("-", this), 0, 3);

		connect(emulation_dal::DB::notifier()->Emulation_notify(), SIGNAL(updated(const NotifyEvent &)), SLOT(updateDates(const NotifyEvent &)));
	}

	void BasicsWidgetBase::loadDBData()
	{
		clear();

		auto data = dbData();
		
		if (data) {
			creationDate(data->emulation_creation_time());
			editingDate(data->emulation_update_time());

		}

	}

	void BasicsWidgetBase::updateDBData()
	{
		auto data = dbData();

		if (data) {
			if (data->emulation_creation_time().isNull())
				data->emulation_creation_time(QDateTime::currentDateTime());

			data->emulation_update_time(QDateTime::currentDateTime());

		}

	}

	void BasicsWidgetBase::creationDate(const QDateTime& value)
	{
		m_creationDateTimeValueLabel->setText(value.toString());
	}

	void BasicsWidgetBase::creationDate(const QString& value)
	{
		m_creationDateTimeValueLabel->setText(value);
	}

	QString BasicsWidgetBase::creationDate() const
	{
		return m_creationDateTimeValueLabel->text();
	}

	void BasicsWidgetBase::editingDate(const QDateTime& value)
	{
		m_editingDateTimeValueLabel->setText(value.toString());
	}

	void BasicsWidgetBase::editingDate(const QString& value)
	{
		m_editingDateTimeValueLabel->setText(value);
	}

	QString BasicsWidgetBase::editingDate() const
	{
		return m_editingDateTimeValueLabel->text();
	}

	void BasicsWidgetBase::clear()
	{
		creationDate("-");
		editingDate("-");

	}

	void BasicsWidgetBase::updateDates(const NotifyEvent &ev)
	{
		auto data = dbData();
		if (data) {
			auto emulation = emulation_dal::Emulation_store::query_one_by_id(ev.objectId());

			if (emulation && *data == *emulation) {
				loadDBData();
			}

		}

	}

	// ViewBasicsWidget
	ViewBasicsWidget::ViewBasicsWidget(ViewWidget *viewWidget)
		: BasicsWidgetBase(viewWidget)
	{
		// Окно просмотра переменных
		init();

		loadDBData();
	}

	void ViewBasicsWidget::init()
	{
		m_dvfWidget = new ViewDVFSplitter(m_parentContainerWidget);

		QLabel *hostsCountLabel = new QLabel(tr("Hosts count:"), this);
		m_hostsCountValueLabel = new QLabel("-", this);

		m_mainLayout->addWidget(m_dvfWidget);

		QHBoxLayout *hostCountLayout = new QHBoxLayout();

		hostCountLayout->addWidget(hostsCountLabel);
		hostCountLayout->addWidget(m_hostsCountValueLabel);
		hostCountLayout->addStretch();

		m_mainLayout->addLayout(hostCountLayout);

		m_mainLayout->addLayout(m_dateLayout);

		connect(emulation_dal::DB::notifier()->Emulation_topology_host_notify(), SIGNAL(added(const NotifyEvent &)), SLOT(updateHostsCount()));
		connect(emulation_dal::DB::notifier()->Emulation_topology_host_notify(), SIGNAL(removed(const NotifyEvent &)), SLOT(updateHostsCount()));

	}

	void ViewBasicsWidget::hostsCount(const unsigned int value)
	{
		hostsCount(QString::number(value));
	}

	void ViewBasicsWidget::hostsCount(const QString &value)
	{
		m_hostsCountValueLabel->setText(value);
	}

	QString ViewBasicsWidget::hostsCount() const
	{
		return m_hostsCountValueLabel->text();
	}

	void ViewBasicsWidget::clear()
	{
		BasicsWidgetBase::clear();

		m_dvfWidget->clear();

		hostsCount("-");

	}

	void ViewBasicsWidget::updateHostsCount()
	{
		hostsCount("-");

		auto data = dbData();

		if (data) {
			auto canvas = data->etc();

			if (canvas) {
				auto hosts = canvas->emulation_topology_hosts();

				if (hosts) {
					int counter = 0;

					for (auto i : *hosts) {
						if (i->eht() && i->eht()->eht_code() == Topology2D::VirtualHostObject::typeCode())
							counter++;
					}

					hostsCount(counter);

				}

			}

		}

	}

	void ViewBasicsWidget::loadDBData()
	{
		clear();

		BasicsWidgetBase::loadDBData();

		auto data = dbData();

		if (data) {

			m_dvfWidget->loadDBData();

			updateHostsCount();

		}

	}

	ViewWidget *ViewBasicsWidget::parentContainerWidget() const
	{
		return dynamic_cast<ViewWidget *>(BasicsWidgetBase::parentContainerWidget());
	}

	// EditBasicWidget
	EditBasicWidget::EditBasicWidget(EditWidget *editWidget)
		: BasicsWidgetBase(editWidget)
	{
		init();
	}

	void EditBasicWidget::init()
	{
		QLabel *standLabel = new QLabel(tr("Stand:"), this);
		m_standList = new StandListComboBox(this);

		QLabel *groupLabel = new QLabel(tr("Group:"), this);
		m_groupList = new GroupListComboBox(this);

		QLabel *nameLabel = new QLabel(tr("Name:"), this);
		m_nameLine = new QLineEdit(this);

		QGridLayout *basicLayout = new QGridLayout();

		basicLayout->addWidget(nameLabel, 0, 0);
		basicLayout->addWidget(m_nameLine, 0, 1, 1, 3);

		basicLayout->addWidget(standLabel, 1, 0);
		basicLayout->addWidget(m_standList, 1, 1);
		basicLayout->addWidget(groupLabel, 1, 2);
		basicLayout->addWidget(m_groupList, 1, 3);

		m_standList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		m_groupList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

		m_mainLayout->addLayout(basicLayout);

		m_dvfWidget = new EditDVFSplitter(m_parentContainerWidget);

		m_mainLayout->addWidget(m_dvfWidget);

		m_mainLayout->addLayout(m_dateLayout);
	}

	int EditBasicWidget::groupId() const
	{
		return m_groupList->currentData().toInt();
	}

	void EditBasicWidget::groupId(const int value)
	{
		for (int i = 0; i < m_groupList->count(); ++i) {
			if (m_groupList->itemData(i).toInt() == value)
				m_groupList->setCurrentIndex(i);
		}
	}

	void EditBasicWidget::standId(const int value)
	{
		for (int i = 0; i < m_standList->count(); ++i) {
			if (m_standList->itemData(i).toInt() == value)
				m_standList->setCurrentIndex(i);
		}
	}

	void EditBasicWidget::group(const std::shared_ptr<emulation_dal::Emulation_group> value)
	{
		if (value)
			groupId(value->id());
	}

	QString EditBasicWidget::group() const
	{
		return m_groupList->currentText();
	}

	void EditBasicWidget::stand(const std::shared_ptr<emulation_dal::Emulation_stand> value)
	{
		if (value)
			standId(value->id());
	}

	void EditBasicWidget::name(const QString& value)
	{
		m_nameLine->setText(value);
	}

	QString EditBasicWidget::name() const
	{
		return m_nameLine->text();
	}

	void EditBasicWidget::description(const QString& value)
	{
		m_dvfWidget->description(value);
	}

	QString EditBasicWidget::description() const
	{
		return m_dvfWidget->description();
	}

	QString EditBasicWidget::standName() const
	{
		return m_standList->currentText();
	}

	QString EditBasicWidget::groupName() const
	{
		return m_groupList->currentText();
	}

	void EditBasicWidget::clear()
	{
		BasicsWidgetBase::clear();

		m_dvfWidget->clear();

		name(QString());
	}

	StandListComboBox *EditBasicWidget::standListComboBox() const
	{
		return m_standList;
	}

	GroupListComboBox *EditBasicWidget::groupListComboBox() const
	{
		return m_groupList;
	}

	EditVariablesWidget *EditBasicWidget::variablesWidget() const
	{
		return m_dvfWidget->variablesWidget();
	}

	EditFilesWidget *EditBasicWidget::filesWidget() const
	{
		return m_dvfWidget->filesWidget();
	}

	QLineEdit *EditBasicWidget::nameLineEdit() const
	{
		return m_nameLine;
	}

	std::shared_ptr<emulation_dal::Emulation_stand> EditBasicWidget::currentStand() const
	{
		return m_standList->currentStand();
	}

	std::shared_ptr<emulation_dal::Emulation_group> EditBasicWidget::currentGroup() const
	{
		return m_groupList->currentGroup();
	}

	void EditBasicWidget::loadDBData()
	{
		clear();

		BasicsWidgetBase::loadDBData();

		auto data = dbData();

		if (data) {
			group(data->eg());
			stand(data->es());
			name(data->emulation_name());
		}

		m_dvfWidget->loadDBData();

	}

	void EditBasicWidget::updateDBData()
	{
		BasicsWidgetBase::updateDBData();

		auto data = dbData();

		if (data) {
			data->eg(currentGroup());
			data->es(currentStand());
			data->emulation_name(m_nameLine->text());
		}

		m_dvfWidget->updateDBData();
	}

	void EditBasicWidget::variablesData(const emulation_dal::Emulation_variable_store &value)
	{
		m_dvfWidget->variablesData(value);
	}

	EditWidget *EditBasicWidget::parentContainerWidget() const
	{
		return dynamic_cast<EditWidget *>(BasicsWidgetBase::parentContainerWidget());
	}


	// ReplaceVmsTableModel
	ReplaceVmsTableModel::ReplaceVmsTableModel(QObject *parent)
		: TableModelBase(parent)
	{
		init();
	}

	void ReplaceVmsTableModel::init()
	{
	}

	QVariant ReplaceVmsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		return QVariant();
	}

	QVariant ReplaceVmsTableModel::data(const QModelIndex &index, int role) const
	{
		return QVariant();
	}

	int ReplaceVmsTableModel::rowCount(const QModelIndex &parent) const
	{
		return 0;
	}

	int ReplaceVmsTableModel::columnCount(const QModelIndex &parent) const
	{
		return 0;
	}

	// ReplaceVmsTableView
	ReplaceVmsTableWidget::ReplaceVmsTableWidget(QWidget *parent)
		: TableViewBase(parent)
	{
		init();
	}

	void ReplaceVmsTableWidget::init()
	{
		setModel(new ReplaceVmsTableModel(this));
	}

	// ReplaceVmsDialogForm
	ReplaceVmsDialogForm::ReplaceVmsDialogForm(QWidget* parent)
		: DialogFormBase(parent)
	{
		init();
	}

	void ReplaceVmsDialogForm::init()
	{
		m_layout = new QVBoxLayout(this);

		setLayout(m_layout);

		m_widget = new ReplaceVmsTableWidget(this);

	}

	// ReplaceVmsDialog
	ReplaceVmsDialog::ReplaceVmsDialog(QWidget *parent)
		: DialogBase(parent)
	{
		form(new DialogFormBase(this));
	}

}