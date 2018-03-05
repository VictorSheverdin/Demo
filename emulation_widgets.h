/**
*
* \file
*
* \brief Виджеты, используемые для построения интерфейса редактирования сценариев эмуляционного моделирования
*
*/
#pragma once

#include "common/widgets.h"
#include "emulation_baseclasses.h"

#include "dictionary_models.h"
#include "dictionary_widgets.h"

namespace Emulation
{

	using emulation_dal::NotifyEvent;

	class WidgetBase;
	class ViewWidget;
	class EditWidget;
	class VariableTypesListComboBox;

	/**
	*
	* \brief Виджет формы для редактирования переменных сценария эмуляционного моделирования
	*
	*/
	class EditVariablesForm : public DialogFormBase
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param emulationData - данные из таблицы БД Emulation
		* \param parent - указатель на родительский виджет
		*
		*/
		EditVariablesForm(QWidget *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param data - данные из таблицы БД Emulation_variable
		* \param parent - указатель на родительский виджет
		*
		*/
		EditVariablesForm(const std::shared_ptr<emulation_dal::Emulation_variable> &data, QWidget *parent = nullptr);

		/**
		*
		* \brief Функция, служащая для загрузки данных переменной из таблицы БД Emulation_variable
		*
		* \param data - данные из таблицы БД Emulation_variable
		* \param parent - указатель на родительский виджет
		*
		*/
		void loadDBData(const std::shared_ptr<emulation_dal::Emulation_variable> &data);

		/// Функция возвращает наименование переменной сценария
		QString name() const;

		/**
		*
		* \brief Функция служит для установки наименования переменной сценария
		*
		* \param value - наименование переменной сценария
		*
		*/
		void name(const QString &value);

		/// Функция возвращает идентификационный номер типа переменной сценария
		int variableTypeId() const;

		/**
		*
		* \brief Функция служит для установки типа переменной
		*
		* \param value - идентификационный номер типа переменной из таблицы Emulation_variable_type
		*
		*/
		void variableTypeId(const int value) const;

		/**
		*
		* \brief Функция служит для установки типа переменной
		*
		* \param value - данные из таблицы БД Emulation_variable_type
		*
		*/
		void variableType(const std::shared_ptr<emulation_dal::Emulation_variable_type> &value);

		/// Функция возвращает длину переменной
		int lenght() const;

		/**
		*
		* \brief Функция служит для установки значений длины переменной
		*
		* \param value - устанавливаемое значение длины
		*
		*/
		void lenght(const int value);

		/// Функция возвращает флаг наличия у переменной значения по умолчанию
		bool defFlag() const;

		/**
		*
		* \brief Функция служит для установки флага наличия значения по умолчанию
		*
		* \param value - устанавливаемое значение наличия значения по умолчанию
		*
		*/
		void defFlag(const bool value);

		/// Функция возвращает флаг наличия у переменной значения по умолчанию
		bool arbitraryLenghtFlag() const;

		/**
		*
		* \brief Функция служит для установки флага наличия значения по умолчанию
		*
		* \param value - устанавливаемое значение наличия значения по умолчанию
		*
		*/
		void arbitraryLenghtFlag(const bool value);

		/// Функция возвращает описание переменной
		QString description() const;

		/**
		*
		* \brief Функция используется для установки значения по умолчанию
		*
		* \param value - устанавливаемое значение переменной по умолчанию
		*
		*/
		void description(const QString &value);

		/// Функция возвращает значение переменной
		QString value() const;

		/**
		*
		* \brief Функция используется для установки значения переменной
		*
		* \param value - устанавливаемое значение переменной
		*
		*/
		void value(const QString &newValue);

		/// Функция возвращает данные, хранящиеся в таблице БД Emulation_variable
		const std::shared_ptr<emulation_dal::Emulation_variable> &dbData() const;

	public slots:
		/// Функция служит для обновления данных, содержащихся в таблице БД Emulation_variable		
		void updateDBData();

		/// Функция служит для обновления доступности объектов-действий в зависимости от выбранного элемента отображения
		void updateAccesibility();

	protected:
		/// Функция инициализации базовых параметров формы
		void init();

		std::shared_ptr<emulation_dal::Emulation_variable> m_dbData; ///< Данные из таблицы БД Emulation_variable

		QLineEdit *m_variableNameLine; ///< Виджет для редактирования имени переменной
		VariableTypesListComboBox *m_variableTypeCombo; ///< Выпадающий список для выбора типа переменной
		SpinBox *m_lenghtSpin; ///< Виджет для редактирования длины переменной
		CheckBox *m_arbitraryLenghtCheck; ///< Виджет для задания флага произвольности длины
		CheckBox *m_defFlagCheck; ///< Виджет для задания флага наличия значения по умолчанию
		PlainTextEdit *m_descriptionEdit; ///< Виджет для редактирования описания переменной
		QLineEdit *m_valueLine; ///< Виджет для редактирования значения переменной
	};

	class FileTypesListComboBox;

	/**
	*
	* \brief Виджет формы для редактирования переменных сценария эмуляционного моделирования
	*
	*/
	class EditFilesForm : public DialogFormBase
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param emulationData - данные из таблицы БД Emulation
		* \param parent - указатель на родительский виджет
		*
		*/
		EditFilesForm(QWidget *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param data - данные из таблицы БД Emulation_variable
		* \param parent - указатель на родительский виджет
		*
		*/
		EditFilesForm(const std::shared_ptr<emulation_dal::Emulation_file> &data, QWidget *parent = nullptr);

		/**
		*
		* \brief Функция, служащая для загрузки данных переменной из таблицы БД Emulation_variable
		*
		* \param data - данные из таблицы БД Emulation_variable
		* \param parent - указатель на родительский виджет
		*
		*/
		void loadDBData(const std::shared_ptr<emulation_dal::Emulation_file> &data);

		/// Функция возвращает наименование переменной сценария
		QString name() const;

		/**
		*
		* \brief Функция служит для установки наименования переменной сценария
		*
		* \param value - наименование переменной сценария
		*
		*/
		void name(const QString &value);

		/// Функция возвращает идентификационный номер типа переменной сценария
		int fileTypeId() const;

		/**
		*
		* \brief Функция служит для установки типа переменной
		*
		* \param value - идентификационный номер типа переменной из таблицы Emulation_variable_type
		*
		*/
		void fileTypeId(const int value) const;

		/**
		*
		* \brief Функция служит для установки типа переменной
		*
		* \param value - данные из таблицы БД Emulation_variable_type
		*
		*/
		void fileType(const std::shared_ptr<emulation_dal::Emulation_file_type> &value);

		/// Функция возвращает флаг наличия у переменной значения по умолчанию
		bool useStoreFlag() const;

		/**
		*
		* \brief Функция служит для установки флага наличия значения по умолчанию
		*
		* \param value - устанавливаемое значение наличия значения по умолчанию
		*
		*/
		void useStoreFlag(const bool value);

		/// Функция возвращает описание переменной
		QString description() const;

		/**
		*
		* \brief Функция используется для установки значения по умолчанию
		*
		* \param value - устанавливаемое значение переменной по умолчанию
		*
		*/
		void description(const QString &value);

		/// Функция возвращает данные, хранящиеся в таблице БД Emulation_variable
		const std::shared_ptr<emulation_dal::Emulation_file> &dbData() const;

	public slots:
		/// Функция служит для обновления данных, содержащихся в таблице БД Emulation_variable		
		void updateDBData();

	protected:
		/// Функция инициализации базовых параметров формы
		void init();

		std::shared_ptr<emulation_dal::Emulation_file> m_dbData; ///< Данные из таблицы БД Emulation_variable

		QLineEdit *m_fileNameLine; ///< Виджет для редактирования имени переменной
		FileTypesListComboBox *m_fileTypeCombo; ///< Выпадающий список для выбора типа переменной
		CheckBox *m_useStoreCheck; ///< Виджет для задания флага произвольности длины
		PlainTextEdit *m_descriptionEdit; ///< Виджет для редактирования описания переменной
	};

	/**
	*
	* \brief Виджет диалога для редактирования переменных сценария эмуляционного моделирования
	*
	*/
	class EditVariablesDialog : public DialogBase
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param emulationData - данные из таблицы БД Emulation
		* \param parent - указатель на родительский виджет
		*
		*/
		EditVariablesDialog(QWidget *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param data - данные из таблицы БД Emulation_variable
		* \param parent - указатель на родительский виджет
		*
		*/
		EditVariablesDialog(const std::shared_ptr<emulation_dal::Emulation_variable> &data, QWidget *parent = nullptr);

		/// Функция возвращает данные, хранящиеся в таблице БД Emulation_variable
		std::shared_ptr<emulation_dal::Emulation_variable> dbData() const;

		EditVariablesForm *form() const;

	public slots:
		/// Слот, вызываемый при подтверждении пользователем сохранения изменений (нажатии кнопки Ok)
		virtual void accept();

	private:
		/// Функция инициализации базовых параметров формы
		void init();
	};

	/**
	*
	* \brief Виджет диалога для редактирования переменных сценария эмуляционного моделирования
	*
	*/
	class EditFilesDialog : public DialogBase
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param emulationData - данные из таблицы БД Emulation
		* \param parent - указатель на родительский виджет
		*
		*/
		EditFilesDialog(QWidget *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param data - данные из таблицы БД Emulation_variable
		* \param parent - указатель на родительский виджет
		*
		*/
		EditFilesDialog(const std::shared_ptr<emulation_dal::Emulation_file> &data, QWidget *parent = nullptr);

		/// Функция возвращает данные, хранящиеся в таблице БД Emulation_variable
		std::shared_ptr<emulation_dal::Emulation_file> dbData() const;

		EditFilesForm *form() const;

	public slots:
		/// Слот, вызываемый при подтверждении пользователем сохранения изменений (нажатии кнопки Ok)
		virtual void accept();

	private:
		/// Функция инициализации базовых параметров формы
		void init();
	};

	/**
	*
	* \brief Модель для просмотра списка переменных сценария.
	*
	*/
	class ViewVariablesTableModel : public DBTableModel<emulation_dal::Emulation_variable>
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский объект
		*
		*/		
		ViewVariablesTableModel(QObject *parent = nullptr);
		
		/**
		*
		* \brief Конструктор
		*
		* \param value - список переменных для отображения
		* \param parent - указатель на родительский объект
		*
		*/
		ViewVariablesTableModel(const emulation_dal::Emulation_variable_store &value, QObject *parent = nullptr);

		/// Функция возвращает заголовки столбцов модели
		QVariant headerData(int section, Qt::Orientation orientation, int role) const;

		/// Функция возвращает данные, содержащиеся в таблице
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

		/// Функция возвращает количество строк в модели
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

		/// Функция возвращает количество столбцов в модели
		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

	private slots:
		DB_EVENT_FUNCTIONS(emulation_dal::DB::notifier()->Emulation_variable_notify())

	protected:
		/// Функция инициализации базовых параметров модели
		void init();

		READONLY_FLAGS_FUNCTION

	};
	
	class ViewFilesTableModel : public DBTableModel<emulation_dal::Emulation_file>
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский объект
		*
		*/
		ViewFilesTableModel(QObject *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param value - список переменных для отображения
		* \param parent - указатель на родительский объект
		*
		*/
		ViewFilesTableModel(const emulation_dal::Emulation_file_store &value, QObject *parent = nullptr);

		/// Функция возвращает заголовки столбцов модели
		QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

		/// Функция возвращает данные, содержащиеся в таблице
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

		/// Функция возвращает количество столбцов в модели
		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	private slots:
		DB_EVENT_FUNCTIONS(emulation_dal::DB::notifier()->Emulation_file_notify())

	protected:
		/// Функция инициализации базовых параметров модели
		void init();

		READONLY_FLAGS_FUNCTION

	};

	/**
	*
	* \brief Модель для редактирования списка переменных сценария.
	*
	*/
	class EditVariablesTableModel : public DBTableModel<emulation_dal::Emulation_variable>
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский объект
		*
		*/
		EditVariablesTableModel(QObject *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param value - список переменных для редактирования
		* \param parent - указатель на родительский объект
		*
		*/
		EditVariablesTableModel(emulation_dal::Emulation_variable_store &value, QObject *parent = nullptr);

		/// Функция возвращает заголовки столбцов модели
		QVariant headerData(int section, Qt::Orientation orientation, int role) const;

		/// Функция возвращает данные, содержащиеся в таблице
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

		/// Функция возвращает количество строк в модели
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

		/// Функция возвращает количество столбцов в модели
		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

	protected:
		/// Функция инициализации базовых параметров модели
		void init();

		EDITABLE_FLAGS_FUNCTION
	};

	/**
	*
	* \brief Модель для редактирования списка переменных сценария.
	*
	*/
	class EditFilesTableModel : public DBTableModel<emulation_dal::Emulation_file>
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский объект
		*
		*/
		EditFilesTableModel(QObject *parent);

		/**
		*
		* \brief Конструктор
		*
		* \param value - список переменных для редактирования
		* \param parent - указатель на родительский объект
		*
		*/
		EditFilesTableModel(emulation_dal::Emulation_file_store &value, QObject *parent = nullptr);

		/// Функция возвращает заголовки столбцов модели
		QVariant headerData(int section, Qt::Orientation orientation, int role) const;

		/// Функция возвращает данные, содержащиеся в таблице
		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

		/// Функция возвращает количество строк в модели
		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

		/// Функция возвращает количество столбцов в модели
		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

	protected:
		/// Функция инициализации базовых параметров модели
		void init();

		EDITABLE_FLAGS_FUNCTION
	};

	/**
	*
	* \brief Виджет просмотра справочника переменных.
	*
	*/
	class ViewVariablesTableWidget : public DBTableViewBase, public GlobalActions
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		ViewVariablesTableWidget(QWidget *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param value - список переменных для редактирования
		* \param parent - указатель на родительский виджет
		*
		*/
		ViewVariablesTableWidget(const emulation_dal::Emulation_variable_store &value, QWidget *parent = nullptr);

		/**
		*
		* \brief Функция для установки данных в модель
		*
		* \param value - массив значений переменных, устанавливаемых для отображения
		*
		*/
		void setDataVector(const emulation_dal::Emulation_variable_store &value);

		MODEL_FUNCTIONS(ViewVariablesTableModel)

	public slots:
		/// Функция для очистки модели
		void clearDataVector();

		TABLE_COLUMN_WIDTH_SETTINGS(ViewVariablesTableWidget);

	protected:
		/// Функция инициализации базовых параметров виджета
		void init();
	};

	class ViewVariablesWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit ViewVariablesWidget(QWidget* parent = nullptr);
		explicit ViewVariablesWidget(const emulation_dal::Emulation_variable_store &value, QWidget *parent = nullptr);

		void tableData(const emulation_dal::Emulation_variable_store &value);

		ViewVariablesTableModel *tableModel() const;

		/**
		*
		* \brief Функция служит для добавления строки в модель из базы с заданным индексом
		*
		* \param id - индекс БД.
		*
		*/
		bool appendById(const long id);

		/**
		*
		* \brief Функция служит для обновления строки в модели с заданным индексом
		*
		* \param id - индекс БД.
		*
		*/
		bool updateById(const long id);

		/**
		*
		* \brief Функция служит для удаления строки из модели и БД с заданным индексом
		*
		* \param id - индекс БД.
		*
		*/
		bool removeById(const long id);

	public slots:
		void clear();

	protected:
		QLabel *m_label;
		ViewVariablesTableWidget *m_table; ///< Таблица переменных
		QVBoxLayout *m_layout;

	private:
		void init();

	};

	class ViewFilesTableWidget : public DBTableViewBase, public GlobalActions
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		ViewFilesTableWidget(QWidget *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param value - список переменных для редактирования
		* \param parent - указатель на родительский виджет
		*
		*/
		ViewFilesTableWidget(const emulation_dal::Emulation_file_store &value, QWidget *parent = nullptr);

		/**
		*
		* \brief Функция для установки данных в модель
		*
		* \param value - массив значений переменных, устанавливаемых для отображения
		*
		*/
		void setDataVector(const emulation_dal::Emulation_file_store &value);

		MODEL_FUNCTIONS(ViewFilesTableModel)

	public slots:
		/// Функция для очистки модели
		void clearDataVector();

		TABLE_COLUMN_WIDTH_SETTINGS(ViewFilesTableWidget);

	protected:
		/// Функция инициализации базовых параметров виджета
		void init();
	};

	class ViewFilesWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit ViewFilesWidget(QWidget *parent = nullptr);
		explicit ViewFilesWidget(const emulation_dal::Emulation_file_store &value, QWidget *parent = nullptr);

		void tableData(const emulation_dal::Emulation_file_store &value);

		ViewFilesTableModel *tableModel() const;

		void useFileStore(const bool value, const QString path);

		/**
		*
		* \brief Функция служит для добавления строки в модель из базы с заданным индексом
		*
		* \param id - индекс БД.
		*
		*/
		bool appendById(const long id);

		/**
		*
		* \brief Функция служит для обновления строки в модели с заданным индексом
		*
		* \param id - индекс БД.
		*
		*/
		bool updateById(const long id);

		/**
		*
		* \brief Функция служит для удаления строки из модели и БД с заданным индексом
		*
		* \param id - индекс БД.
		*
		*/
		bool removeById(const long id);

	public slots:
		void clear();

	protected:
		QLabel *m_label;
		QLabel *m_useFileStoreLabel;
		ViewFilesTableWidget *m_table; ///< Таблица переменных
		QVBoxLayout *m_layout;

	private:
		void init();

	};

	class EditFilesVariablesTableWidgetBase : public DBTableViewBase, public GlobalActions
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		explicit EditFilesVariablesTableWidgetBase(QWidget *parent = nullptr);

	public slots:
		/// Функция для разрешения глобальный объектов-действий
		virtual void enableGlobalActions();

	private:
		void init();
	};

	class EditFilesVariablesWidgetBase : public QWidget, public GlobalActions
	{
		Q_OBJECT

	public:
		/// Конструктор
		explicit EditFilesVariablesWidgetBase(QWidget* parent = nullptr);

		EditFilesVariablesTableWidgetBase *tableWidget() const; 

	public slots:
		void updateControlsAccesibility();

	protected:
		NERToolbar *m_toolbar;

		QLabel *m_label;
		QVBoxLayout *m_layout;

		void setTableWidget(EditFilesVariablesTableWidgetBase *value);

	private:
		void init();

		SimplyPointer<EditFilesVariablesTableWidgetBase> m_table; ///< Таблица переменных
	};

	/**
	*
	* \brief Виджет редактирования справочника переменных.
	*
	*/
	class EditVariablesTableWidget : public EditFilesVariablesTableWidgetBase
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		EditVariablesTableWidget(QWidget *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param value - список переменных для редактирования
		* \param parent - указатель на родительский виджет
		*
		*/
		EditVariablesTableWidget(const std::shared_ptr<emulation_dal::Emulation> emulationData, QWidget *parent = nullptr);

		/**
		*
		* \brief Функция для установки данных в модель
		*
		* \param value - массив значений переменных, устанавливаемых в модели
		*
		*/
		void setDataVector(const emulation_dal::Emulation_variable_store &value);
		const emulation_dal::Emulation_variable_store &dataVector() const;

		MODEL_FUNCTIONS(EditVariablesTableModel)

	signals:
		void addVariableSignal(const QString &name);
		void editVariableSignal(const QString &lastName, const QString &newName);
		void deleteVariableSignal(const QString &name);

	public slots:
		/// Функция для очистки модели
		void clearDataVector();

		void newVariableDialog();
		void editVariableDialog(const QString &value);
		void removeVariable(const QString &value);

		/// Слот, вызываемй глобальным объектом-действием создания нового документа newAction.
		virtual void onNewAction() override;
		/// Слот, вызываемй глобальным объектом-действием создания открытия документа openAction.
		virtual void onOpenAction() override;
		/// Слот, вызываемй глобальным объектом-действием создания удаления документа deleteAction.
		virtual void onDeleteAction() override;

	private slots:
		TABLE_COLUMN_WIDTH_SETTINGS(EditVariablesTableWidget);

	protected:
		/// Функция инициализации базовых параметров виджета
		void init();

		/// Функция обработки события вызова контекстного меню
		void contextMenuEvent(QContextMenuEvent *e);

	};

	class EditVariablesWidget : public EditFilesVariablesWidgetBase
	{
		Q_OBJECT

	public:
		explicit EditVariablesWidget(QWidget* parent = nullptr);

		explicit EditVariablesWidget(const std::shared_ptr<emulation_dal::Emulation> data, QWidget* parent = nullptr);

		void tableData(const emulation_dal::Emulation_variable_store &value);
		const emulation_dal::Emulation_variable_store &tableData() const;

		EditVariablesTableModel *tableModel() const;

		void loadDBData(const std::shared_ptr<emulation_dal::Emulation> data);

		EditVariablesTableWidget *table() const;

	signals:
		void addVariableSignal(const QString &name);
		void editVariableSignal(const QString &lastName, const QString &newName);
		void deleteVariableSignal(const QString &name);

	public slots:
		void newVariableDialog();
		void editVariableDialog(const QString &value);
		void removeVariable(const QString &value);

		void clear();

		/// Слот, вызываемй глобальным объектом-действием создания нового документа newAction.
		virtual void onNewAction();
		/// Слот, вызываемй глобальным объектом-действием создания открытия документа openAction.
		virtual void onOpenAction();
		/// Слот, вызываемй глобальным объектом-действием создания удаления документа deleteAction.
		virtual void onDeleteAction();

	protected:

	private:
		void init();

	};

	/**
	*
	* \brief Виджет редактирования справочника файлов.
	*
	*/
	class EditFilesTableWidget : public EditFilesVariablesTableWidgetBase
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		EditFilesTableWidget(QWidget *parent = nullptr);

		/**
		*
		* \brief Конструктор
		*
		* \param value - список переменных для редактирования
		* \param parent - указатель на родительский виджет
		*
		*/
		EditFilesTableWidget(const std::shared_ptr<emulation_dal::Emulation> emulationData, QWidget *parent = nullptr);

		/**
		*
		* \brief Функция для установки данных в модель
		*
		* \param value - массив значений переменных, устанавливаемых в модели
		*
		*/
		void setDataVector(const emulation_dal::Emulation_file_store &value);
		const emulation_dal::Emulation_file_store &dataVector() const;

		MODEL_FUNCTIONS(EditFilesTableModel)

	signals:
		void addFileSignal(const QString &name);
		void editFileSignal(const QString &lastName, const QString &newName);
		void deleteFileSignal(const QString &name);

	public slots:
		/// Функция для очистки модели
		void clearDataVector();

		void newFileDialog();
		void editFileDialog(const QString &value);
		void removeFile(const QString &value);

		/// Слот, вызываемй глобальным объектом-действием создания нового документа newAction.
		virtual void onNewAction() override;
		/// Слот, вызываемй глобальным объектом-действием создания открытия документа openAction.
		virtual void onOpenAction() override;
		/// Слот, вызываемй глобальным объектом-действием создания удаления документа deleteAction.
		virtual void onDeleteAction() override;

	private slots:
		TABLE_COLUMN_WIDTH_SETTINGS(EditFilesTableWidget);

	protected:
		/// Функция инициализации базовых параметров виджета
		void init();

		/// Функция обработки события вызова контекстного меню
		void contextMenuEvent(QContextMenuEvent *e);
	};

	class EditFilesWidget : public EditFilesVariablesWidgetBase
	{
		Q_OBJECT

	public:
		explicit EditFilesWidget(QWidget* parent = nullptr);

		explicit EditFilesWidget(const std::shared_ptr<emulation_dal::Emulation> data, QWidget* parent = nullptr);

		void tableData(const emulation_dal::Emulation_file_store &value);
		const emulation_dal::Emulation_file_store &tableData() const;

		EditFilesTableModel *tableModel() const;

		void loadDBData(const std::shared_ptr<emulation_dal::Emulation> data);

		EditFilesTableWidget *table() const;

		bool useFileStore() const;
		void useFileStore(const bool value);

		QString fileStorePath() const;
		void fileStorePath(const QString &value);

	signals:
		void addFileSignal(const QString &name);
		void editFileSignal(const QString &lastName, const QString &newName);
		void deleteFileSignal(const QString &name);

	public slots:
		void newVariableDialog();
		void editVariableDialog(const QString &value);
		void removeVariable(const QString &value);

		void clear();

		/// Слот, вызываемй глобальным объектом-действием создания нового документа newAction.
		virtual void onNewAction();
		/// Слот, вызываемй глобальным объектом-действием создания открытия документа openAction.
		virtual void onOpenAction();
		/// Слот, вызываемй глобальным объектом-действием создания удаления документа deleteAction.
		virtual void onDeleteAction();

		void updateFileStoreAccesibility();

	protected:
		CheckBox *m_useFileStoreCheckBox;
		QLineEdit *m_fileStorePath;

	private:
		void init();

	};

	/**
	*
	* \brief Базовый класс для реализации комбинированного виджета, состоящего из двух: виджета описания и виджета списка переменных.
	*
	*/
	class DVFSplitterBase : public QSplitter, public ParentWidget
	{
		Q_OBJECT
	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		explicit DVFSplitterBase(WidgetBase* parent);

		/**
		*
		* \brief Функция установки описания
		*
		* \param value - устанавливаемое значчение
		*
		*/
		void description(const QString& value);

		/// Функция возвращает описание
		QString description() const;

		/// Функция, служащая для очистки описания
		void clear();

		void loadDBData();
		void updateDBData();

	private slots:
		void update(const NotifyEvent &ev);

	protected:
		PlainTextEdit *m_descriptionEdit; ///< Виджет редактирования описания

	private:
		/// Функция инициализации базовых параметров виджета
		void init();

	};

	/**
	*
	* \brief Виджет, включающий в себя два виджета: редактирования описания и просмотра списка переменных.
	*
	*/
	class ViewDVFSplitter : public DVFSplitterBase
	{
		Q_OBJECT
	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		explicit ViewDVFSplitter(WidgetBase* parent);

		/**
		*
		* \brief Функция, используемая для установки списка переменных
		*
		* \param value - массив, содержащий список переменных
		*
		*/
		void variablesData(const emulation_dal::Emulation_variable_store &value);

		void filesData(const emulation_dal::Emulation_file_store &value);

		/// Функция возвращает модель для отображения списка переменных сценария
		ViewVariablesTableModel *model() const;

		/// Функция служит для установки возможности редактирования описания
		void setEditable(const bool flag);

		void loadDBData();

	public slots:
		/// Функция для очистки виджетов
		void clear();

	private slots:
		// Сохранение настроек
		SPLITTER_SETTINGS(ViewDVFSplitter)

		void appendVariable(const NotifyEvent &ev);
		void updateVariable(const NotifyEvent &ev);
		void removeVariable(const NotifyEvent &ev);

		void appendFile(const NotifyEvent &ev);
		void updateFile(const NotifyEvent &ev);
		void removeFile(const NotifyEvent &ev);


	protected:
		ViewVariablesWidget *m_variablesWidget; ///< Виджет отображения переменных сценария
		ViewFilesWidget *m_filesWidget; ///< Виджет отображения переменных сценария

	private:
		/// Функция инициализации базовых параметров виджета
		void init();

	};

	/**
	*
	* \brief Виджет, включающий в себя два виджета: редактирования описания и редактирования списка переменных.
	*
	*/
	class EditDVFSplitter : public DVFSplitterBase
	{
		Q_OBJECT
	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		explicit EditDVFSplitter(WidgetBase *parent);

		/**
		*
		* \brief Функция, используемая для установки списка переменных
		*
		* \param value - массив, содержащий список переменных
		*
		*/
		void variablesData(const emulation_dal::Emulation_variable_store &value);

		void filesData(const emulation_dal::Emulation_file_store &value);

		/// Функция возвращает модель для отображения списка переменных сценария
		EditVariablesTableModel *variablesModel() const;

		EditFilesTableModel *filesModel() const;

		/// Функция возвращает виджет редактирования перерменных сценария
		EditVariablesWidget *variablesWidget() const;

		EditFilesWidget *filesWidget() const;

		void loadDBData();
		void updateDBData();

	public slots:
		/// Функция для очистки виджетов
		void clear();

	private slots:
		// Сохранение настроек
		SPLITTER_SETTINGS(EditDVFSplitter)

	protected:
		EditVariablesWidget *m_variablesWidget; ///< Виджет редактирования переменных
		EditFilesWidget *m_filesWidget; ///< Виджет редактирования переменных

	private:
		/// Функция инициализации базовых параметров виджета
		void init();

	};

	/**
	*
	* \brief Модель справочника запросов, принадлежащих некоторому сценарию
	*
	*/
	class EmulationRuntimeRequestsModel : public Dictionary::RuntimeRequestsModelBase, public ParentWidget
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский объект
		*
		*/
		EmulationRuntimeRequestsModel(WidgetBase *parent);

		/**
		*
		* \brief Конструктор
		*
		* \param emulationDataPtr - сценарий, запросы которого отображаются в модели
		* \param parent - указатель на родительский объект
		*
		*/
		void loadDBData();

		/// Функция возвращает сценарий, которому принадлежат отображаемые запросы
		const std::shared_ptr<emulation_dal::Emulation> emulation() const;

	private slots:
		/**
		*
		* \brief Функция добаления виртуальной записи, используемая для отбработки уведомлений от БД
		*
		* \param ev - описание события
		*
		*/
		void append(const NotifyEvent &ev);

		/**
		*
		* \brief Слот обновления записи в таблице, вызываемый в ответ на событие, получаемое от БД
		*
		* \param ev - описание события
		*
		*/
		void update(const NotifyEvent &ev);

		/**
		*
		* \brief Слот удаления записи в таблице, вызываемый в ответ на событие, получаемое от БД
		*
		* \param ev - описание события
		*
		*/
		void remove(const NotifyEvent &ev);

	protected:

		/// Функция для создания сингально-слотовых соединений, используемых для обновления состояния модели на основании уведомлений от БД
		void createUpdateConnections();

		/// Функция инициализации базовых параметров модели
		void init();
	};

	/**
	*
	* \brief Виджет просмотра запросов сценария моделирования
	*
	*/
	class RuntimeRequestsWidget : public Dictionary::RuntimeRequestsWidgetBase, public ParentWidget
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		RuntimeRequestsWidget(WidgetBase *parent);

		/// Функция возвращает модель, установленную в виджете
		EmulationRuntimeRequestsModel *model() const;

		/**
		*
		* \brief Функция для установки данных в модель
		*
		* \param value - массив значений переменных, устанавливаемых для отображения
		*
		*/
		void setDataVector(const emulation_dal::Emulation_runtime_request_store value);

		/**
		*
		* \brief Функция для текущего сценария моделирования
		*
		* \param value - данные, идентифицирующие сценарий моделирования
		*
		*/
		void loadDBData();

	public slots:
		/// Функция для разрешения глобальный объектов-действий
		virtual void enableGlobalActions();

		/**
		*
		* \brief Функция для разрешения глобальный объектов-действий в зависимости от выбранного в текущий момент элемента
		*
		* \param idx - индекс модели, в зависимости от значения корого принимается решение о разрешении глобальных действий
		*
		*/
		void enableActions(const QModelIndex idx);

		/// Функция используется для очистки таблицы
		void clear();

		/// Функция, служащая для запроса запуска текущего сценария
		void runCurrentScenery();

		/// Функция, служащая для запроса постановки текущего сценария на паузу
		void pauseCurrentScenery();

		/// Функция, служащая для запроса продолжения текущего сценария после постановки его на паузу
		void continueCurrentScenery();

		/// Функция, служащая для запроса остановки текущего сценария
		void stopCurrentScenery();

		private slots:
		TABLE_COLUMN_WIDTH_SETTINGS(RuntimeRequestsWidget)

	protected:
		/// Функция инициализации базовых параметров виджета
		void init();

		/// Функция обработки события контекстного меню
		virtual void contextMenuEvent(QContextMenuEvent *event);
	};

	/**
	*
	* \brief Базовый класс, служащий для описания основных параметров проекта эмуляционного моделирования
	*
	*/
	class BasicsWidgetBase : public QWidget, public ParentWidget
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		BasicsWidgetBase(WidgetBase *containerWidget);

		/// Функция для загрузки данных из БД
		void loadDBData();

		// Функция для обновления данных из БД
		void updateDBData();

		/**
		*
		* \brief Функция, используется для задания даты создания проекта
		*
		* \param value - устанавливаемое значение даты создания
		*
		*/
		void creationDate(const QDateTime& value);

		/**
		*
		* \brief Функция, используется для задания даты создания проекта
		*
		* \param value - устанавливаемое значение даты создания в виде строки
		*
		*/
		void creationDate(const QString& value);

		/// Функция возвращает дату создания проекта эмуляционного моделирования
		QString creationDate() const;

		/**
		*
		* \brief Функция, используется для задания даты изменения проекта
		*
		* \param value - устанавливаемое значение даты изменения
		*
		*/
		void editingDate(const QDateTime& value);
		
		/**
		*
		* \brief Функция, используется для задания даты изменения проекта
		*
		* \param value - устанавливаемое значение даты изменения в виде строки
		*
		*/
		void editingDate(const QString& value);

		/// Функция возвращает дату изменения проекта эмуляционного моделирования
		QString editingDate() const;

	public slots:
		void clear();

	private slots:
		void updateDates(const NotifyEvent &ev);

	protected:
		/// Функция инициализации базовых параметров виджета
		void init();

		QVBoxLayout *m_mainLayout; ///< Главный компоновщик виджета
		QGridLayout *m_dateLayout; ///< Компоновщик виджетов отображения даты

		QLabel *m_creationDateTimeValueLabel; ///< Виджет отображения даты создания документа

		QLabel *m_editingDateTimeValueLabel; ///< Виджет отображения даты изменения документа

	};

	/**
	*
	* \brief Виджет, служащий для просмотра основных параметров проекта эмуляционного моделирования
	*
	*/
	class ViewBasicsWidget : public BasicsWidgetBase
	{
		Q_OBJECT

	public:
		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		ViewBasicsWidget(ViewWidget *viewWidget);

		/**
		*
		* \brief Функция задает количество хостов, используемое для отображения пользователю
		*
		* \param value - значение количества хостов, устанавливаемое для отображения
		*
		*/
		void hostsCount(const unsigned int value);

		/**
		*
		* \brief Функция задает количество хостов, используемое для отображения пользователю
		*
		* \param value - значение количества хостов в виде строки, устанавливаемое для отображения
		*
		*/
		void hostsCount(const QString &value);

		/// Функция возвращает строку, содержащую количество хостов в проекте, служащее для отображения для пользователя
		QString hostsCount() const;

		// Функция для очистки значений всех полей виджета
		void clear();

		/// Функция для чтения данных из таблицы БД Emulation
		void loadDBData();

		ViewWidget *parentContainerWidget() const;

	private slots:
		void updateHostsCount();

	protected:
		/// Функция инициализации базовых параметров виджета
		void init();

		QLabel *m_hostsCountValueLabel; ///< Виджет, служащий для отображения количества хостов в проекте

		ViewDVFSplitter *m_dvfWidget; ///< Комбинированный виджет для отображения описания и переменных
	};

	class StandListComboBox;
	class GroupListComboBox;

	/**
	*
	* \brief Виджет, служащий для просмотра основных параметров проекта эмуляционного моделирования
	*
	*/
	class EditBasicWidget : public BasicsWidgetBase
	{
		Q_OBJECT

	public:

		/**
		*
		* \brief Конструктор
		*
		* \param parent - указатель на родительский виджет
		*
		*/
		EditBasicWidget(EditWidget *editWidget);

		/**
		*
		* \brief Функция устанавливает идентификатор группы, которой принадлежит сценарий
		*
		* \param value - значение идентификатора группы
		*
		*/
		void groupId(const int value);

		void standId(const int value);

		/// Функция возвращает идентификатор группы, которой принадлежит сценарий
		int groupId() const;

		/**
		*
		* \brief Функция устанавливает группу, которой принадлежит сценарий посредством передачи значений из БД
		*
		* \param value - запись из таблицы БД Emulation_group
		*
		*/
		void group(const std::shared_ptr<emulation_dal::Emulation_group> value);

		void stand(const std::shared_ptr<emulation_dal::Emulation_stand> value);

		/// Функция возвращает наименование группы, которой принадлежит сценарий
		QString group() const;

		/**
		*
		* \brief Функция служит для установки наименования сценария эмуляционного моделирования
		*
		* \param value - наименование сценария
		*
		*/
		void name(const QString& value);

		/// Функция возвращает наименование сценария эмуляционного моделирования
		QString name() const;

		/**
		*
		* \brief Функция служит для установки описания сценария эмуляционного моделирования
		*
		* \param value - описание сценария
		*
		*/
		void description(const QString& value);

		/// Функция возвращает описание сценария эмуляционного моделирования
		QString description() const;

		QString standName() const;
		QString groupName() const;

		/// Функция для чтения данных из таблицы БД Emulation
		void loadDBData();

		/// Функция для обновления данных из БД
		void updateDBData();

		/**
		*
		* \brief Функция, используемая для установки списка переменных
		*
		* \param value - массив, содержащий список переменных
		*
		*/
		void variablesData(const emulation_dal::Emulation_variable_store &value);

		/// Функция для очистки виджетов
		void clear();

		/// Функция возвращает виджет, служащий для выбора стенда, на котором работают машины
		StandListComboBox *standListComboBox() const;

		/// Функция возвращает виджет, служащий для выбора группы, которой принадлежит сценарий
		GroupListComboBox *groupListComboBox() const;

		// Виджет редактирования перерменнных сценария
		EditVariablesWidget *variablesWidget() const;

		EditFilesWidget *filesWidget() const;

		/// Функция возвращает виджет, служащий для ввода наименования сценария эмуляционного моделирования
		QLineEdit *nameLineEdit() const;

		/// Функция возвращает текущий стенд, на котором выполняется сценарий
		std::shared_ptr<emulation_dal::Emulation_stand> currentStand() const;

		std::shared_ptr<emulation_dal::Emulation_group> currentGroup() const;

		EditWidget *parentContainerWidget() const;

	protected:
		/// Функция инициализации базовых параметров виджета
		void init();

		StandListComboBox *m_standList; ///< Выпадающий список стендов проекта

		GroupListComboBox *m_groupList; ///< Выпадающий список групп сценариев

		QLineEdit *m_nameLine; /// Виджет ввода наименования сценария эмуляционного моделирования

		EditDVFSplitter *m_dvfWidget; ///< Комбинированный виджет для редактирования описания и переменных

	};

	class ReplaceVmsTableModel : public TableModelBase
	{
		Q_OBJECT

	public:
		ReplaceVmsTableModel(QObject *parent = nullptr);

		QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

		virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

		virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	private:
		/// Функция инициализации базовых параметров модели
		void init();

	};

	class ReplaceVmsTableWidget : public TableViewBase
	{
		Q_OBJECT

	public:
		ReplaceVmsTableWidget(QWidget *parent = nullptr);

	private:
		void init();
	};

	class ReplaceVmsDialogForm : public DialogFormBase
	{
		Q_OBJECT

	public:
		ReplaceVmsDialogForm(QWidget* parent = nullptr);

	protected:
		QVBoxLayout *m_layout;

		ReplaceVmsTableWidget *m_widget;

	private:
		void init();
	};

	class ReplaceVmsDialog : public DialogBase
	{
		Q_OBJECT

	public:
		ReplaceVmsDialog(QWidget *parent = nullptr);

	};

}