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

	Form1Instance = Form1; //���������� ��� ������ ������� � TForm1
}
/*
 \brief ������� ��� ���������� ������� �����������
  ������� ��������� ��������� ��������� ������� StringGrid1
  \param Sender ��������� �� ������, ������� ������������ �� �����
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

	StringGrid1->Cells[0][0] = "�";
	StringGrid1->Cells[1][0] = "�������";
	StringGrid1->Cells[2][0] = "������ 1";
	StringGrid1->Cells[3][0] = "������ 2";
	StringGrid1->Cells[4][0] = "������ 3";
	StringGrid1->Cells[5][0] = "����";
	StringGrid1->Cells[6][0] = "������������";
	StringGrid1->Cells[7][0] = "������� 5";
	StringGrid1->Cells[8][0] = "�������";
}
/*
 \brief ������� ��� ����������
  ������� ��������� �������� ������ � ������� StringGrid1
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N8Click(TObject *Sender)
{
	Form1->Button1->Caption="����������" ;
	Form1->Caption="����������" ;
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
 \brief ������� ��� ��������������
  ������� ��������� ��������������� ��� ��������� ������ � ������� StringGrid1
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N9Click(TObject *Sender)
{
	int nm = StringGrid1->Selection.Top;//���������� ����� ���������� ������
	Form1->Button1->Caption="��������������" ;
	Form1->Caption="��������������" ;
	Form1->Edit1->Text= Form2->StringGrid1->Cells[1][nm];
	Form1->Edit2->Text= Form2->StringGrid1->Cells[2][nm];
	Form1->Edit3->Text= Form2->StringGrid1->Cells[3][nm];
	Form1->Edit4->Text= Form2->StringGrid1->Cells[4][nm];
	Form1->Show();
	SaveStringGridToTextFile2(StringGrid1);
}
/*
 \brief ������� ��� ����������
  ������� � ���������� ����� ��������� ��������� ������ StringGrid1 � �������� ��������.
  \param stringGrid - ��������� �� ������ ������ TStringGrid.
*/
void __fastcall SaveStringGridToTextFile(TStringGrid* stringGrid)
{
	TSaveDialog* saveDialog = new TSaveDialog(NULL);
	saveDialog->Title = "��������� ���...";
	saveDialog->Filter = "��������� ����� (*.txt)|*.txt";
	saveDialog->DefaultExt = "txt";

	if (saveDialog->Execute())
	{
		String fileName = saveDialog->FileName;

		if (ExtractFileExt(fileName).IsEmpty())
			fileName += ".txt";

		if (FileExists(fileName))
		{
			int response = MessageBoxA(NULL, "���� � ����� ������ ��� ����������. �������� ���?", "������������� ������ �����", MB_ICONQUESTION | MB_YESNO);
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

				ShowMessage("���� ����");
			}
			else
			{
				ShowMessage("��� ��������� ������. ��������� �������");
			}
		}
		catch (const Exception& e)
		{
			ShowMessage("������ ��� ���������� �����: " + e.Message);
		}

		delete streamWriter;
		delete fileStream;
	}

	delete saveDialog;
}
/*
 \brief ������� ��� ����������
  ������� �������� ������� ����������.
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N4Click(TObject *Sender)
{
	SaveStringGridToTextFile(StringGrid1);
}
/*
 \brief ������� ��� ����������
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::ToolButton1Click(TObject *Sender)
{
   N4Click(Sender);
}
/*
 \brief ������� ��� ���������
  ������� ������������ �������� ����� � �������� ������� ����������
  \param Sender ��������� �� ������, ������� ������������ �� �����. CanClose ������, ������� ���������, ����� �� ����� ���� �������.
*/
void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	int response = MessageDlg("������ ��������� ����?", mtConfirmation, mbYesNoCancel, 0);

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
 \brief ������� ��� ��������
  ������� ��������� ������� ������
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N10Click(TObject *Sender)
{
	int nm= StringGrid1->Selection.Top;
	for(int i=nm; i < StringGrid1->RowCount-1; ++i)
	StringGrid1->Rows[i] = StringGrid1->Rows[i+1]; // �������� ������� ������ ���������
	StringGrid1->RowCount--;     //�������� ���-�� �����
	ShowMessage("�������� ������ ��������� �������.");
	SaveStringGridToTextFile2(StringGrid1);
}
/*
 \brief ������� ��������
  ������� ��������� ��������� �������� � ������� � ��������� StringGrid1
  \param stringGrid - ��������� �� ������ ������ TStringGrid.
*/
void __fastcall LoadTextFileToStringGrid(TStringGrid* stringGrid)
{
	TOpenDialog* openDialog = new TOpenDialog(NULL);
	openDialog->Title = "�������� ���� ��� ��������";
	openDialog->Filter = "��������� ����� (*.txt)|*.txt";

	if (openDialog->Execute())
	{
        try
		{
			TStreamReader* streamReader = new TStreamReader(openDialog->FileName, TEncoding::UTF8);
			try
			{
				// �������� �� ������ ����
				if (streamReader->EndOfStream)
				{
					ShowMessage("��������� ���� ������");
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

				// ������� StringGrid
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
			ShowMessage("������ ��� �������� �����: " + e.Message);
		}
	}

	delete openDialog;
}
/*
 \brief ������� ��������
  ������� �������� ������� �������� ���������� ��������� ��� ���������� StringGrid1
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N2Click(TObject *Sender)
{
	LoadTextFileToStringGrid(StringGrid1);
}
/*
 \brief ������� ����������
  ������� �������� ������� ����������
  \param Sender ��������� �� ������, ������� ������������ �� �����
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
 \brief ������� ��� �������� ������������
  ������� ��������� ���������� ������� ������������ �� �������, ��� ������������ ������ ����������, �� ������� ������ 80% �� 50
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N15Click(TObject *Sender)
{
	int numRows = StringGrid1->RowCount - 4; // �������� ���������� ����� �� StringGrid1, �� ������� ��������� 4 �����
	int maxDivider = 0; // ���������� ��� �������� ����������� ��������

	// ����� ����� � ���������� �����������
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
	// ��������� �������� � ����������� �� maxDivider
	for (int i = startRow; i < numRows; i++)
	{
		int result = (StringGrid1->Cells[6][i] / maxDivider) * 100;
		StringGrid1->Cells[6][i] = result;
	}

	int largestNumber = 0; // ���������� ��� �������� ����������� �����
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
		//�������� ��������
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
 \brief ������� �����������
  ������� ��������� ����������� ������ �� ������ StrngGrid1
  \param Sender ��������� �� ������, ������� ������������ �� �����
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
	ShowMessage("������ ���� ������� �����������.");
}
 /*
 \brief ������� ����������
  ������� ��������� �������� ������������� ������ � ������ StrngGrid1
  \param Sender ��������� �� ������, ������� ������������ �� �����
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
	ShowMessage("������ ���������!");
	SaveStringGridToTextFile2(StringGrid1);
}
/*
 \brief ������� ��������
  ������� ��������� ������� ������ StrngGrid1
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N16Click(TObject *Sender)
{
	int col = StringGrid1->Col;
	int row = StringGrid1->Row;
	if (col >= 0 && row >= 0)
	{
		StringGrid1->Cells[col][row] = "";
	}
	ShowMessage("�������� ������ ��������� �������.");
	SaveStringGridToTextFile2(StringGrid1);
}
/*
 \brief ������� ��� ����������� ����
  ������� ���������� ���������� ��������� ����
  \param Sender ��������� �� ������, ������� ������������ �� �����, TMouseButton Button - �������� ��� ��� ������� ������ ����
*/
void __fastcall TForm2::StringGrid1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
		if (Button == mbRight)
	{
		StringGrid1->Col = StringGrid1->MouseCoord(X, Y).X;
		StringGrid1->Row = StringGrid1->MouseCoord(X, Y).Y;

		TPoint point = StringGrid1->ClientToScreen(Point(X, Y)); // �������������� ��������� � �������� ����������

		PopupMenu1->Popup(point.X, point.Y); // ����������� ������������ ���� � ��������� �������� �����������
	}
}
 /*
 \brief ������� �������
  ������� ��������� ������������ ������ �������
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N18Click(TObject *Sender)
{
	String message =  "����� ����, ������������ ������, �� ��� �� �������. ��������� �.�. ����� ��������� �������� ��������� ��������� ������� ����� �������� ������������. ������������ ��������� ��������� �.�. ����������� ��������� �������: �����, ���������� ��������� �� ������ ������������ ������, ���������� �� � ��� (������������), ����� ���������� ��� ������ ���� �������� ����������� � ����������� ������� ������������ ��� ������� �������� �� �) ������������ ��������� ����� ������ (�������) (50) �) ������������ ����� ������ ����� ��������� ������� ��� ����, (���� ��� �������� ������ 80% �� ����������� ��������� ����� ������) (��������� ���� ������������ �������� ������ ������ 80% - �� �������� 5 ���������. ���� ���� ���� ���� ���� �� 2 - �� �� �� ������� � ��������. ��� ��������� ����������� � ��������.";
	ShowMessage(message);
}
/*
 \brief ������� � ���������
  ������� ��������� ������������ ������ ���������� � ���������
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N19Click(TObject *Sender)
{
	String message =  "�������� ������������ ��������: Rad Studio \n"
					  "������ ������������ ��������:Embarcadero C++Builder 10.1\n"
					  "���� ��������� ��������� � ���������: 29.06.23\n"
					  "�����: ������� ������\n"
					  "E-mail: sergeyzhivotov01@mail.ru";

	// ������� ��������� � ������������ �������
	ShowMessage(message);
}
/*
 \brief ������� �������
  ������� ��������� ������������ �������� ������� � ���������
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
void __fastcall TForm2::N20Click(TObject *Sender)
{
	String message = "���� ������� �� ���������, �� ������ ���������� ���� �� ��������! \n "
		"1.��� ����� ������ ����� � ���� ������� ����� ������ -> ��������.\n"
		"1.1 ������ ����������� ��� ����� ������������ ������ ��������� ����� �������� ��������� � ����������� �������.\n"
		"2. ��� �������������� ��� �������� ������ ����� ������� ����� ������ -> ������������� ��� �������.\n"
		"3. ��� �������� ��� ���������� ����� ����� ������ �� ����� ���� ���� -> �������, ���������, ��������� ���... \n"
		"4. ��� ���������� ������� ������� �� ����� ���� ������� -> � �������� ������ �������. \n"
		"5. ������ ���������� ����� � ������ ���� � ��������� -> � ����� ������� ������ �������.\n"
		"6. ��� �� � ��������� ������������ ����������� ����. ��� ��� ��������� ������� �� ������� ��� � �������� ��������.\n"
		"7. ��� ������ �� ��������� ������� �� ����� ���� ���� -> �����. ��� ������� �� ������� � ������ ������� ����.\n";

	// ������� ��������� � ������������ �������
	ShowMessage(message);
}
/*
 \brief ������� ��������
  ������� ��������� ��������� �� ��� �����
  \param Sender ��������� �� ������, ������� ������������ �� �����
*/
 void __fastcall TForm2::N21Click(TObject *Sender)
{
	Form1Instance->UndoLastAction();
	Form1Instance->Counting();
	SaveStringGridToTextFile2(Form2->StringGrid1);
}


