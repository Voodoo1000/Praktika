//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Printers.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "Unit1.h"
//---------------------------------------------------------------------------
/*
 \brief Функция сохранения
  Функция сохраняет данные StringGrid1 в папку с проектом.
  \param stringGrid - указатель на объект класса TStringGrid.
*/
void __fastcall SaveStringGridToTextFile2(TStringGrid* stringGrid)
{
	String fileName = "save_file.txt";

	TFileStream* fileStream = new TFileStream(fileName, fmCreate);
	TStreamWriter* streamWriter = new TStreamWriter(fileStream, TEncoding::UTF8, true);

	try
	{
		for (int row = 0; row < stringGrid->RowCount; row++)
		{
			String line = "";

			for (int col = 0; col < stringGrid->ColCount; col++)
			{
				String cellValue = stringGrid->Cells[col][row].Trim();
				line += cellValue + ",";
			}

			if (line.Length() > 0)
				line = line.SubString(1, line.Length() - 1);

			streamWriter->WriteLine(line);
		}
	}
	catch (const Exception& e)
	{
		ShowMessage("Ошибка при сохранении файла: " + e.Message);
	}

	delete streamWriter;
	delete fileStream;
}
class TForm2 : public TForm
{
__published:	// IDE-managed Components

	TStringGrid *StringGrid1;
	TLabel *Label1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TImageList *ImageList1;
	TSaveDialog *SaveDialog1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolBar *ToolBar2;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TMenuItem *N11;
	TMenuItem *N13;
	TMenuItem *N15;
	TPopupMenu *PopupMenu1;
	TMenuItem *N12;
	TMenuItem *N14;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *N19;
	TMenuItem *N20;
	TMenuItem *N21;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall ToolButton3Click(TObject *Sender);
	void __fastcall ToolButton4Click(TObject *Sender);
	void __fastcall ToolButton5Click(TObject *Sender);
	void __fastcall ToolButton6Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall N15Click(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall StringGrid1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall N18Click(TObject *Sender);
	void __fastcall N19Click(TObject *Sender);
	void __fastcall N20Click(TObject *Sender);
	void __fastcall N21Click(TObject *Sender);






private:    TForm1* Form1Instance;

public:   __fastcall TForm2(TComponent* Owner, TForm1* Form1);
   //	__fastcall TForm2(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif


