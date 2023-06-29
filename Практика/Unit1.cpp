//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <System.SysUtils.hpp>
#include <System.Character.hpp>
#include "Unit1.h"
#include "Unit2.h"
#include <Vcl.Dialogs.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <regex>
#include <string>
#include <System.RegularExpressions.hpp>
 #include <System.SysUtils.hpp>
#include <System.DateUtils.hpp>
#include <stack>
 using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool rad = false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
int nrow;
 /*
 \brief Функция для добавления/редактирования
 Функция позволяет добавить/отредактировать данные
 \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm1::ButtonClick(TObject *Sender)
{
	  if (Form1->Caption =="Добавление")
	 {
		// Получение текущих координат фокуса
		int currentCol = Form2->StringGrid1->Col;
		int currentRow = Form2->StringGrid1->Row;
		// Переключение фокуса на следующую строку
		int newRow = currentRow + 1;
		// Проверка на превышение максимального значения строки
		if (newRow >= Form2->StringGrid1->RowCount) {
			// Сброс на первую строку
			newRow = 1;
		}
		// Установка новых координат фокуса и перевод фокуса на StringGrid
		Form2->StringGrid1->Row = newRow;
		Form2->StringGrid1->Col = 1; // Установка начальной колонки (например, 0)
		Form2->StringGrid1->SetFocus();
		nrow=Form2->StringGrid1->RowCount-4;
		Form2->StringGrid1->Cells[0][nrow]= IntToStr(Form2->StringGrid1->RowCount-4);

		++Form2->StringGrid1->RowCount;

		if(nrow>=1)
		 {
			Form2->StringGrid1->Cells[0][nrow+1] = "Вес лаб.";
			Form2->StringGrid1->Cells[2][nrow+1] = "2";
			Form2->StringGrid1->Cells[3][nrow+1] = "3";
			Form2->StringGrid1->Cells[4][nrow+1] = "5";
			Form2->StringGrid1->Cells[5][nrow+2] = "50";
			Form2->StringGrid1->Cells[0][nrow+2] = "Макс";
			Form2->StringGrid1->Cells[0][nrow+3] = "Лучшая усп.";
			Form2->StringGrid1->Cells[6][nrow+4] = "80";
			Form2->StringGrid1->Cells[0][nrow+4] = "Порог";
		}

		 if(nrow>=2)
		{
			Form2->StringGrid1->Cells[5][nrow+1] = "";
			Form2->StringGrid1->Cells[6][nrow+3] = "";
			Form2->StringGrid1->Cells[6][nrow+2] = "";
		}
	 }
	 else
	 {
		nrow = Form2->StringGrid1->Selection.Top;  // выделенная строка
	 }

	 Form2->StringGrid1->Cells[0][nrow]=nrow;
	 Form2->StringGrid1->Cells[1][nrow]=Edit1->Text;
	 Form2->StringGrid1->Cells[2][nrow]=Edit2->Text;
	 Form2->StringGrid1->Cells[3][nrow]=Edit3->Text;
	 Form2->StringGrid1->Cells[4][nrow]=Edit4->Text;
	 Form1->Edit1->Clear();
	 Form1->Edit2->Clear();
	 Form1->Edit3->Clear();
	 Form1->Edit4->Clear();
	 rad = true;

	 Form2->Show();
	 Form1->Close();

	 Counting();
	 SaveStringGridToTextFile2(Form2->StringGrid1);
}
/*
 \brief Функция для вычисления данных
  Функция позволяет вычислять данные, а именно итог, автомат, максимальный балл, допуск к экзамену
*/
void TForm1::Counting()
{
	 const int startRow = 1; // Начальная строка для умножения
	 double result;

	 //Итог
	 if(!Form2->StringGrid1->Cells[4][1].IsEmpty())
	 {

		 int numRows = Form2->StringGrid1->RowCount - 4; // Получаем количество строк из StringGrid1, за вычетом последних 4 строк
		 double sum = 0.0;

		for (int i = startRow; i < numRows; i++)
		{
			double grade = StrToFloat(Form2->StringGrid1->Cells[2][i]);    //StrToFloat - преобразование строки в float, grade хранит информацию об оценке
			double col2 = grade * 2;
			double	col3 = StrToFloat(Form2->StringGrid1->Cells[3][i]) * 3;
			double	col4 = StrToFloat(Form2->StringGrid1->Cells[4][i]) * 5;
			result = col2 + col3 + col4;

			Form2->StringGrid1->Cells[5][i] = FloatToStr(result);
			sum += result;
		}
	 }

	 // подсчёт максимального балла вывод напротив строк
	 if(!Form2->StringGrid1->Cells[4][1].IsEmpty())
	 {
		int numRows = Form2->StringGrid1->RowCount - 4; // Получаем количество строк из StringGrid1, за вычетом последних 4 строк

		for (int i = startRow; i < numRows; i++)
		{
			double result = (StrToFloat(Form2->StringGrid1->Cells[5][i]) / 50) * 100;
			Form2->StringGrid1->Cells[6][i] = FloatToStr(result);
		}
	 }

	 //Максимальный бал - вывод (1)
	 if(!Form2->StringGrid1->Cells[4][1].IsEmpty())
	 {
		int largestNumber = 0;
		int previousNumber = StrToIntDef(Form2->StringGrid1->Cells[6][Form2->StringGrid1->RowCount], 0);

		for (int row = 0; row < Form2->StringGrid1->RowCount-1; ++row) // Итерация только до предпоследней строки
		{
			// Получаем значение
			int number = StrToIntDef(Form2->StringGrid1->Cells[6][row], 0);

			// Обновляем наибольшее число, если текущее число больше
			largestNumber = std::max(largestNumber, number);

			if (largestNumber > previousNumber)
			{
				Form2->StringGrid1->Cells[6][Form2->StringGrid1->RowCount - 2] = IntToStr(largestNumber);
			}
		}
	 }

	 int Evaluation1;
	 int Evaluation2;
	 int Evaluation3;

	 //Проверка на допуск к экзамену
	 if(!Form2->StringGrid1->Cells[5][1].IsEmpty())
	 {
		int numRows = Form2->StringGrid1->RowCount - 4; // Получаем количество строк из StringGrid1, за вычетом последних 4 строк

		for (int i = startRow; i < numRows; i++)
		{
			Evaluation1 = StrToFloat(Form2->StringGrid1->Cells[2][i]);
			Evaluation2 = StrToFloat(Form2->StringGrid1->Cells[3][i]);
			Evaluation3 = StrToFloat(Form2->StringGrid1->Cells[4][i]);
			if(Evaluation1>2 && Evaluation2>2 && Evaluation3>2)
			{
				Form2->StringGrid1->Cells[8][i] ="+";
			}
			else
			{
				Form2->StringGrid1->Cells[8][i] ="";
			}
		}
	 }
	  //Проверка автомата
	if(!Form2->StringGrid1->Cells[5][1].IsEmpty())
	 {
		int numRows = Form2->StringGrid1->RowCount - 4; // Получаем количество строк из StringGrid1, за вычетом последних 4 строк

		for (int i = startRow; i < numRows; i++)
		{
		int value = StrToFloat(Form2->StringGrid1->Cells[6][i]);

			Evaluation1 = StrToFloat(Form2->StringGrid1->Cells[2][i]);
			Evaluation2 = StrToFloat(Form2->StringGrid1->Cells[3][i]);
			Evaluation3 = StrToFloat(Form2->StringGrid1->Cells[4][i]);

			if(value>80 && Evaluation1>2 && Evaluation2>2 && Evaluation3>2)
			{
				Form2->StringGrid1->Cells[7][i] ="+";
			}
			else
			{
				Form2->StringGrid1->Cells[7][i] ="";
			}
		}
	 }
}
/*
 \brief Функция для переставления фокуса мыши
  Функция позволяет переместить фокус мыши после нажатия пользователем клавиши Enter
  \param Sender указатель на объект, который используется на форме, WORD &Key передаёт код нажатой клавиши, Shift состояние клавиш-модификаторов
*/
void __fastcall TForm1::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN) Edit2->SetFocus();
}
/*
 \brief Функция для переставления фокуса мыши
  Функция позволяет переместить фокус мыши после нажатия пользователем клавиши Enter
  \param Sender указатель на объект, который используется на форме, WORD &Key передаёт код нажатой клавиши, Shift состояние клавиш-модификаторов
*/
void __fastcall TForm1::Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN) Edit3->SetFocus();
}
/*
 \brief Функция для переставления фокуса мыши
  Функция позволяет переместить фокус мыши после нажатия пользователем клавиши Enter
  \param Sender указатель на объект, который используется на форме, WORD &Key передаёт код нажатой клавиши, Shift состояние клавиш-модификаторов
*/
void __fastcall TForm1::Edit3KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN) Edit4->SetFocus();
}
/*
 \brief Функция для переставления фокуса мыши
  Функция позволяет переместить фокус мыши после нажатия пользователем клавиши Enter
  \param Sender указатель на объект, который используется на форме, WORD &Key передаёт код нажатой клавиши, Shift состояние клавиш-модификаторов
*/
void __fastcall TForm1::Edit4KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN) Button1->SetFocus();
}

// Объявление стека для хранения состояний данных ячеек
std::stack<std::pair<int, std::pair<int, UnicodeString>>> cellStack;
/*
 \brief Функция для сохранения
  Функция для сохранения состояния ячейки перед изменением
  \param Acol - индекс столбца ячейки, ARow - индекс строки ячейки, UnicodeString& Value - значение ячейки
*/
void SaveCellState(int ACol, int ARow, const UnicodeString& Value)
{
	cellStack.push(std::make_pair(ACol, std::make_pair(ARow, Value)));
}
/*
 \brief Функция для возврата
  Функция для возврата на одно действие назад
*/
void TForm1::UndoLastAction()
{
	if (!cellStack.empty())
	{
		std::pair<int, std::pair<int, UnicodeString>> cellState = cellStack.top();
		cellStack.pop();

		int ACol = cellState.first;
		int ARow = cellState.second.first;
		UnicodeString Value = cellState.second.second;

		Form2->StringGrid1->Cells[ACol][ARow] = Value;
	}
}
/*
 \brief Функция для проверки
  Функция проверяет данные на ввод
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm1::Edit1Exit(TObject *Sender)
{
	TEdit *edit = dynamic_cast<TEdit *>(Sender);

    // Проверяем, что поле ввода не пустое
	if (edit->Text.IsEmpty()) {
        edit->SetFocus();
        ShowMessage("Введите данные");
        return;
    }

    // Проверка на количество символов
    if (edit->Text.Length() > 1612) {
		edit->SetFocus();
		ShowMessage("Превышено ограничение по количеству символов (максимум 1612): " + edit->Text);
		edit->Text = "";
        return;
    }

    UnicodeString input = edit->Text.Trim(); // Удаляем лишние пробелы в начале и конце строки

	// Проверка на наличие тире (минуса)
    int dashIndex = input.Pos('-');

    // Если есть тире, проверяем наличие заглавной буквы после тире
    if (dashIndex > 0) {
        // Проверка на корректность разделения слов тире (минусом) и наличие заглавной буквы после тире
        if (dashIndex == 1 || dashIndex == input.Length() || input[dashIndex - 1] == '-' || input[dashIndex + 1] == '-') {
            edit->SetFocus();
			ShowMessage("Некорректное разделение слов тире (минусом)");
            edit->Text = "";
            return;
        }

        // Проверка на наличие заглавной буквы после тире
        if (!iswupper(input[dashIndex + 1]) && !iswspace(input[dashIndex + 1])) {
            edit->SetFocus();
			ShowMessage("После тире должна быть заглавная буква или пробел");
            edit->Text = "";
            return;
        }

        // Проверка на окончание данных символом, отличным от букв
        if (!iswalpha(input[input.Length()])) {
            edit->SetFocus();
			ShowMessage("Данные не могут оканчиваться символом, отличным от букв: " + edit->Text);
            edit->Text = "";
            return;
        }
    }
    // Если нет тире, проверяем наличие заглавной буквы в начале строки
    else {
        if (!iswupper(input[1])) {
			edit->SetFocus();
			ShowMessage("Первая буква должна быть заглавной");
			edit->Text = "";
			return;
		}

		// Проверка на окончание данных символом, отличным от букв
		if (!iswalpha(input[input.Length()])) {
			edit->SetFocus();
			ShowMessage("Данные не могут иметь символы, отличным от букв: " + edit->Text);
			edit->Text = "";
			return;
		}
	}

	// Проверка на наличие цифр
	for (int i = 1; i <= input.Length(); ++i) {
		if (isdigit(input[i])) {
			edit->SetFocus();
			ShowMessage("Нельзя вводить цифры");
			edit->Text = "";
			return;
		}
	}
	int column = 1;  // Индекс колонки для редактирования
	int row = Form2->StringGrid1->Row;  // Индекс строки для редактирования

	UnicodeString value1 = Form2->StringGrid1->Cells[column][row];
	SaveCellState(column, row, value1);
	Form2->StringGrid1->Cells[column][row] = edit->Text;
}
/*
 \brief Функция для проверки
  Функция проверяет данные на ввод
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm1::Edit2Exit(TObject *Sender)
{
TEdit *edit = dynamic_cast<TEdit *>(Sender);

	if (edit->Text.IsEmpty()) {
		edit->SetFocus();
		ShowMessage("Введите данные");
		return;
	}

	// Проверка на количество символов
	if (edit->Text.Length() > 3) {
		edit->SetFocus();
		ShowMessage("Превышено ограничение по количеству символов (максимум 3): " + edit->Text);
		edit->Text = "";
		return;
	}

	bool containsLetters = false;
	for (int i = 1; i <= edit->Text.Length(); ++i) {
		if (iswalpha(edit->Text[i])) {
			containsLetters = true;
			break;
		}
	}

	if (containsLetters) {
		edit->SetFocus();
		ShowMessage("Не допускается ввод букв");
		edit->Text = "";
		return;
	}

	// Проверка на ввод чисел от 2 до 5
	float value = StrToFloatDef(edit->Text, -1);
	if (value < 2 || value > 5) {
		edit->SetFocus();
		ShowMessage("Допустимый диапазон значений: от 2 до 5. Запрешено использовать точки.");
		edit->Text = "";
		return;
	}


	int column = 2;  // Индекс колонки для редактирования
	int row = Form2->StringGrid1->Row;  // Индекс строки для редактирования

	UnicodeString value2 = Form2->StringGrid1->Cells[column][row];
	SaveCellState(column, row, value2);
	Form2->StringGrid1->Cells[column][row] = edit->Text;
}
/*
 \brief Функция для проверки
  Функция проверяет данные на ввод
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm1::Edit3Exit(TObject *Sender)
{
	TEdit *edit = dynamic_cast<TEdit *>(Sender);

	if (edit->Text.IsEmpty()) {
		edit->SetFocus();
		ShowMessage("Введите данные");
		return;
	}

	// Проверка на количество символов
	if (edit->Text.Length() > 3) {
		edit->SetFocus();
		ShowMessage("Превышено ограничение по количеству символов (максимум 3): " + edit->Text);
		edit->Text = "";
		return;
	}

	bool containsLetters = false;
	for (int i = 1; i <= edit->Text.Length(); ++i) {
		if (iswalpha(edit->Text[i])) {
			containsLetters = true;
			break;
		}
	}

	if (containsLetters) {
		edit->SetFocus();
		ShowMessage("Не допускается ввод букв");
		edit->Text = "";
		return;
	}

	// Проверка на ввод чисел от 2 до 5
	float value = StrToFloatDef(edit->Text, -1);
	if (value < 2 || value > 5) {
		edit->SetFocus();
		ShowMessage("Допустимый диапазон значений: от 2 до 5. Запрешено использовать точки.");
		edit->Text = "";
		return;
	}
	int column = 3;  // Индекс колонки для редактирования
	int row = Form2->StringGrid1->Row;  // Индекс строки для редактирования

	UnicodeString value3 = Form2->StringGrid1->Cells[column][row];
	SaveCellState(column, row, value3);
	Form2->StringGrid1->Cells[column][row] = edit->Text;
}
/*
 \brief Функция для проверки
  Функция проверяет данные на ввод
  \param Sender указатель на объект, который используется на форме
*/
void __fastcall TForm1::Edit4Exit(TObject *Sender)
{
	TEdit *edit = dynamic_cast<TEdit *>(Sender);

	if (edit->Text.IsEmpty()) {
		edit->SetFocus();
		ShowMessage("Введите данные");
		return;
	}

	// Проверка на количество символов
	if (edit->Text.Length() > 3) {
		edit->SetFocus();
		ShowMessage("Превышено ограничение по количеству символов (максимум 3): " + edit->Text);
		edit->Text = "";
		return;
	}

	bool containsLetters = false;
	for (int i = 1; i <= edit->Text.Length(); ++i) {
		if (iswalpha(edit->Text[i])) {
			containsLetters = true;
			break;
		}
	}

	if (containsLetters) {
		edit->SetFocus();
		ShowMessage("Не допускается ввод букв");
		edit->Text = "";
		return;
	}

	// Проверка на ввод чисел от 2 до 5
	float value = StrToFloatDef(edit->Text, -1);
	if (value < 2 || value > 5) {
		edit->SetFocus();
		ShowMessage("Допустимый диапазон значений: от 2 до 5. Запрешено использовать точки.");
		edit->Text = "";
		return;
	}

	int column = 4;  // Индекс колонки для редактирования
	int row = Form2->StringGrid1->Row;  // Индекс строки для редактирования

	UnicodeString value4 = Form2->StringGrid1->Cells[column][row];
	SaveCellState(column, row, value4);
	Form2->StringGrid1->Cells[column][row] = edit->Text;
}
