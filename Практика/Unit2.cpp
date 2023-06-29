//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <Vcl.Dialogs.hpp>
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Clipbrd.hpp>
#include <fstream>
#include <algorithm>
#include <System.SysUtils.hpp>
#include "Unit2.h"
#include "Unit1.h"
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

extern bool rad;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner, TForm1* Form1)
	: TForm(Owner)
{

	Form1Instance = Form1; //переменная для вызова функций с TForm1
}
/*
 \brief Функция для заполнения таблицы заголовками
  Функция позволяет заполнить заголовки таблицы StringGrid1
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::FormCreate(TObject *Sender)
{
	Form2->N3->Enabled = false;
	Form2->N4->Enabled = false;
	Form2->N9->Enabled = false;
	Form2->N10->Enabled = false;
	Form2->N11->Enabled = false;
	Form2->N12->Enabled = false;
	Form2->N14->Enabled = false;
	Form2->N16->Enabled = false;
	Form2->ToolButton1->Enabled = false;
	Form2->ToolButton2->Enabled = false;
	Form2->ToolButton3->Enabled = false;
	Form2->ToolButton5->Enabled = false;

	StringGrid1->Cells[0][0] = "№";
	StringGrid1->Cells[1][0] = "Фамилия";
	StringGrid1->Cells[2][0] = "Оценка 1";
	StringGrid1->Cells[3][0] = "Оценка 2";
	StringGrid1->Cells[4][0] = "Оценка 3";
	StringGrid1->Cells[5][0] = "Итог";
	StringGrid1->Cells[6][0] = "Успеваемость";
	StringGrid1->Cells[7][0] = "Автомат 5";
	StringGrid1->Cells[8][0] = "Допущен";
}
/*
 \brief Функция для добавления
  Функция позволяет добавить данные в таблицу StringGrid1
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N8Click(TObject *Sender)
{
	Form1->Button1->Caption="Добавление" ;
	Form1->Caption="Добавление" ;
	Form1->Show();
	Form1->Edit1->SetFocus();

	Form2->N3->Enabled = True;
	Form2->N4->Enabled = True;
	Form2->N9->Enabled = True;
	Form2->N10->Enabled = True;
	Form2->N11->Enabled = True;
	Form2->N12->Enabled = True;
	Form2->N14->Enabled = True;
	Form2->N16->Enabled = True;
	Form2->ToolButton1->Enabled = True;
	Form2->ToolButton2->Enabled = True;
	Form2->ToolButton3->Enabled = True;
	Form2->ToolButton5->Enabled = True;
}
/*
 \brief Функция для редактирования
  Функция позволяет отредактировать уже имеющиеся данные в таблице StringGrid1
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N9Click(TObject *Sender)
{
	int nm = StringGrid1->Selection.Top;//Определяем номер выделенной строки
	Form1->Button1->Caption="Редактирование" ;
	Form1->Caption="Редактирование" ;
	Form1->Edit1->Text= Form2->StringGrid1->Cells[1][nm];
	Form1->Edit2->Text= Form2->StringGrid1->Cells[2][nm];
	Form1->Edit3->Text= Form2->StringGrid1->Cells[3][nm];
	Form1->Edit4->Text= Form2->StringGrid1->Cells[4][nm];
	Form1->Show();
	SaveStringGridToTextFile2(StringGrid1);
}
/*
 \brief Функция для сохранения
  Функция с диалоговым окном позволяет сохранить данные StringGrid1 в тектовый документ.
  \param stringGrid - указатель на объект класса TStringGrid.
*/
void __fastcall SaveStringGridToTextFile(TStringGrid* stringGrid)
{
	TSaveDialog* saveDialog = new TSaveDialog(NULL);
	saveDialog->Title = "Сохранить как...";
	saveDialog->Filter = "Текстовые файлы (*.txt)|*.txt";
	saveDialog->DefaultExt = "txt";

	if (saveDialog->Execute())
	{
		String fileName = saveDialog->FileName;

		if (ExtractFileExt(fileName).IsEmpty())
			fileName += ".txt";

		if (FileExists(fileName))
		{
			int response = MessageBoxA(NULL, "Файл с таким именем уже существует. Заменить его?", "Подтверждение замены файла", MB_ICONQUESTION | MB_YESNO);
			if (response == IDNO)
			{
				delete saveDialog;
				return;
			}
		}

		TFileStream* fileStream = new TFileStream(fileName, fmCreate);
		TStreamWriter* streamWriter = new TStreamWriter(fileStream, TEncoding::UTF8, true);
		bool hasData = false;

		try
		{
			if (stringGrid->RowCount > 1 && stringGrid->ColCount > 1 && !stringGrid->Cells[1][1].Trim().IsEmpty())
			{
				for (int row = 0; row < stringGrid->RowCount; row++)
				{
					String line = "";

					for (int col = 0; col < stringGrid->ColCount; col++)
					{
						String cellValue = stringGrid->Cells[col][row].Trim();

						if (!cellValue.IsEmpty())
							hasData = true;

						line += cellValue + ",";
					}

					if (line.Length() > 0)
						line = line.SubString(1, line.Length() - 1);

					streamWriter->WriteLine(line);
				}

			if (!hasData)

				ShowMessage("Файл пуст");
			}
			else
			{
				ShowMessage("Нет введенных данных. Заполните таблицу");
			}
		}
		catch (const Exception& e)
		{
			ShowMessage("Ошибка при сохранении файла: " + e.Message);
		}

		delete streamWriter;
		delete fileStream;
	}

	delete saveDialog;
}
/*
 \brief Функция для сохранения
  Функция вызывает функцию сортировки.
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N4Click(TObject *Sender)
{
	SaveStringGridToTextFile(StringGrid1);
}
/*
 \brief Функция для сохранения
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::ToolButton1Click(TObject *Sender)
{
   N4Click(Sender);
}
/*
 \brief Функция для обработки
  Функция обрабатывает закрытие формы и вызывает функцию сохранения
  \param Sender указатель на объект, который используется на форме. CanClose ссылка, которая указывает, может ли форма быть закрыта.
*/
void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	int response = MessageDlg("Хотите сохранить файл?", mtConfirmation, mbYesNoCancel, 0);

	switch (response)
	{
		case mrYes:
		{
			SaveStringGridToTextFile2(StringGrid1);
			break;
		}
		case mrNo:
		{
			CanClose = true;
			break;
		}
	}
}
/*
 \brief Функция для Удаления
  Функция полностью удаляет строку
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N10Click(TObject *Sender)
{
	int nm= StringGrid1->Selection.Top;
	for(int i=nm; i < StringGrid1->RowCount-1; ++i)
	StringGrid1->Rows[i] = StringGrid1->Rows[i+1]; // Затереть текущую строку следующей
	StringGrid1->RowCount--;     //умеьшить кол-во строк
	ShowMessage("Удаление строки произошло успешно.");
	SaveStringGridToTextFile2(StringGrid1);
}
/*
 \brief Функция открытия
  Функция открывает текстовый документ с данными и заполняет StringGrid1
  \param stringGrid - указатель на объект класса TStringGrid.
*/
void __fastcall LoadTextFileToStringGrid(TStringGrid* stringGrid)
{
	TOpenDialog* openDialog = new TOpenDialog(NULL);
	openDialog->Title = "Выберите файл для открытия";
	openDialog->Filter = "Текстовые файлы (*.txt)|*.txt";

	if (openDialog->Execute())
	{
        try
		{
			TStreamReader* streamReader = new TStreamReader(openDialog->FileName, TEncoding::UTF8);
			try
			{
				// Проверка на пустой файл
				if (streamReader->EndOfStream)
				{
					ShowMessage("Выбранный файл пустой");
					return;
				}

				Form2->N3->Enabled = True;
				Form2->N4->Enabled = True;
				Form2->N9->Enabled = True;
				Form2->N10->Enabled = True;
				Form2->N11->Enabled = True;
				Form2->N12->Enabled = True;
				Form2->N14->Enabled = True;
				Form2->N16->Enabled = True;
				Form2->ToolButton1->Enabled = True;
				Form2->ToolButton2->Enabled = True;
				Form2->ToolButton3->Enabled = True;
				Form2->ToolButton5->Enabled = True;

				// Очистка StringGrid
				stringGrid->RowCount = 0;
				stringGrid->ColCount = 0;
				stringGrid->FixedCols = 0;
				stringGrid->FixedRows = 0;

				int maxCols = 0;
				int row = 0;
				while (!streamReader->EndOfStream)
                {
					String line = streamReader->ReadLine();

					TStringList* words = new TStringList;
					words->Delimiter = ',';
					words->StrictDelimiter = true;
					words->DelimitedText = line;

					if (words->Count > maxCols)
						maxCols = words->Count;

					stringGrid->RowCount = row + 1;
					for (int col = 0; col < words->Count; col++)
					{
						String cellValue = words->Strings[col].Trim();
						stringGrid->Cells[col][row] = cellValue;
					}

                    delete words;
					row++;
				}

				stringGrid->ColCount = maxCols;
			}
			__finally
			{
				delete streamReader;
			}
		}
		catch (const Exception& e)
		{
			ShowMessage("Ошибка при открытии файла: " + e.Message);
		}
	}

	delete openDialog;
}
/*
 \brief Функция открытия
  Функция вызывает функцию открытия текстового документа для заполнения StringGrid1
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N2Click(TObject *Sender)
{
	LoadTextFileToStringGrid(StringGrid1);
}
/*
 \brief Функция сохранения
  Функция вызывает функцию сохранения
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N3Click(TObject *Sender)
{
 SaveStringGridToTextFile2(StringGrid1);
}
void __fastcall TForm2::ToolButton2Click(TObject *Sender)
{
	N3Click(Sender);
}
void __fastcall TForm2::ToolButton3Click(TObject *Sender)
{
	N9Click(Sender);
}
void __fastcall TForm2::ToolButton4Click(TObject *Sender)
{
	N8Click(Sender);
}
void __fastcall TForm2::ToolButton5Click(TObject *Sender)
{
	 N10Click(Sender);
}
void __fastcall TForm2::ToolButton6Click(TObject *Sender)
{
	N2Click(Sender);
}
const int startRow = 1;
void __fastcall TForm2::N13Click(TObject *Sender)
{
	Form1Instance->Counting();
}
/*
 \brief Функция для подсчёта успеваемости
  Функция позволяет подсчитать процент успеваемости по условию, что максимальным числом становится, то которое больше 80% от 50
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N15Click(TObject *Sender)
{
	int numRows = StringGrid1->RowCount - 4; // Получаем количество строк из StringGrid1, за вычетом последних 4 строк
	int maxDivider = 0; // Переменная для хранения наибольшего делителя

	// Обход строк и вычисление результатов
	for (int i = startRow; i < numRows; i++)
	{
		int result = (StringGrid1->Cells[6][i] / 50) * 100;

		if (result > 40)
		{
			if (result > maxDivider)
			{
				maxDivider = result;
			}
		}

		StringGrid1->Cells[6][i] = result;
	}
	// Обновляем значения в зависимости от maxDivider
	for (int i = startRow; i < numRows; i++)
	{
		int result = (StringGrid1->Cells[6][i] / maxDivider) * 100;
		StringGrid1->Cells[6][i] = result;
	}

	int largestNumber = 0; // Переменная для хранения наибольшего числа
	int previousNumber = StrToIntDef(Form2->StringGrid1->Cells[6][Form2->StringGrid1->RowCount], 0);

	for (int row = 0; row < StringGrid1->RowCount; ++row)
	{
		int number = StrToIntDef(Form2->StringGrid1->Cells[6][row], 0);

		largestNumber = max(largestNumber, number);

		if (largestNumber > previousNumber)
		{
		StringGrid1->Cells[6][StringGrid1->RowCount - 2] = largestNumber;
		}
	}
		//Проверка автомата
		for (int i = startRow; i < numRows; i++)
		{
		int value = StrToFloat(Form2->StringGrid1->Cells[6][i]);
			if(value>80)
			{
			Form2->StringGrid1->Cells[7][i] ="+";
			}
			else
			{
					Form2->StringGrid1->Cells[7][i] ="";
			}
		}
		SaveStringGridToTextFile2(StringGrid1);
}
 /*
 \brief Функция копирования
  Функция позволяет скопировать данные из ячейки StrngGrid1
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N12Click(TObject *Sender)
{
	int col = StringGrid1->Col;
	int row = StringGrid1->Row;

	if (col >= 0 && row >= 0)
	{
		UnicodeString cellText = StringGrid1->Cells[col][row];
		Clipboard()->SetTextBuf(cellText.w_str());
	}
	ShowMessage("Данные были успешно скопированы.");
}
 /*
 \brief Функция вставления
  Функция позволяет вставить скопированные данные в ячейку StrngGrid1
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N14Click(TObject *Sender)
{
	int col = StringGrid1->Col;
	int row = StringGrid1->Row;

	if (col >= 0 && row >= 0)
	{
		UnicodeString clipboardText = Clipboard()->AsText;
		StringGrid1->Cells[col][row] = clipboardText;
	}
	ShowMessage("Данные вставлены!");
	SaveStringGridToTextFile2(StringGrid1);
}
/*
 \brief Функция удаления
  Функция позволяет удалить ячейку StrngGrid1
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N16Click(TObject *Sender)
{
	int col = StringGrid1->Col;
	int row = StringGrid1->Row;
	if (col >= 0 && row >= 0)
	{
		StringGrid1->Cells[col][row] = "";
	}
	ShowMessage("Удаление ячейки произошло успешно.");
	SaveStringGridToTextFile2(StringGrid1);
}
/*
 \brief Функция для контексного меню
  Функция определяет координаты появления меню
  \param Sender указатель на объект, который используется на форме, TMouseButton Button - передает код при нажатой кнопке мыши
*/
void __fastcall TForm2::StringGrid1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
		if (Button == mbRight)
	{
		StringGrid1->Col = StringGrid1->MouseCoord(X, Y).X;
		StringGrid1->Row = StringGrid1->MouseCoord(X, Y).Y;

		TPoint point = StringGrid1->ClientToScreen(Point(X, Y)); // Преобразование координат в экранные координаты

		PopupMenu1->Popup(point.X, point.Y); // Отображение контекстного меню в указанных экранных координатах
	}
}
 /*
 \brief Функция задания
  Функция позволяет пользователю узнать задание
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N18Click(TObject *Sender)
{
	String message =  "Скоро зима, приближается сессия, не все ее пройдут. Аршинский В.Л. хочет поставить экзамены автоматом студентам которые имеют отличную успеваемость. Успеваемость студентов Аршинский В.Л. высчитывает следующим образом: баллы, полученные студентом за каждую лабораторную работу, умножаются на её вес (трудоемкость), затем полученные для каждой лабы значения суммируются и вычисляется процент успеваемости для каждого студента от А) максимальной возможной суммы баллов (полегче) (50) Б) максимальной суммы баллов среди студентов сдавших все лабы, (если это значение больше 80% от максимально возможной суммы баллов) (посложнее Если успеваемость студента строго больше 80% - он получает 5 автоматом. Если сдал хоть одну лабу на 2 - то он не допущен к экзамену. Все остальные допускаются к экзамену.";
	ShowMessage(message);
}
/*
 \brief Функция о программе
  Функция позволяет пользователю узнать информацию о программе
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N19Click(TObject *Sender)
{
	String message =  "Название программного продукта: Rad Studio \n"
					  "Версия программного продукта:Embarcadero C++Builder 10.1\n"
					  "Дата последних изменений в программе: 29.06.23\n"
					  "Автор: Животов Сергей\n"
					  "E-mail: sergeyzhivotov01@mail.ru";

	// Выводим сообщение с объединенным текстом
	ShowMessage(message);
}
/*
 \brief Функция справки
  Функция позволяет пользователю получить справку о программе
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm2::N20Click(TObject *Sender)
{
	String message = "Если таблица не заполнена, то многие компоненты меню не доступны! \n "
		"1.Для ввода данных нужно в меню выбрать пункт правка -> добавить.\n"
		"1.1 Будьте внимательны при вводе неправильных данных программа будет выводить сообщения о совершенной ошибкой.\n"
		"2. Для редактирования или удаления данных нужно выбрать пункт правка -> редактировать или удалить.\n"
		"3. Для открытия или сохранения файла нужно нажать на пункт меню файл -> открыть, сохранить, сохранить как... \n"
		"4. Для выполнения задания нажмите на пункт меню задание -> и выберете нужный вариант. \n"
		"5. Узнать информацию можно в пункте меню о программе -> и далее выбрать нужный вариант.\n"
		"6. Так же в программе присутствует контекстное меню. Для его активации нажмите по таблице ПКМ и выберете действие.\n"
		"7. Для выхода из программы нажмите на пункт меню файл -> выход. Или нажмите на крестик в правом верхнем углу.\n";

	// Выводим сообщение с объединенным текстом
	ShowMessage(message);
}
/*
 \brief Функция возврата
  Функция позволяет вернуться на шаг назад
  \param Sender указатель на объект, который используется на форме
*/
 void __fastcall TForm2::N21Click(TObject *Sender)
{
	Form1Instance->UndoLastAction();
	Form1Instance->Counting();
	SaveStringGridToTextFile2(Form2->StringGrid1);
}


