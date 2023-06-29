//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------


class TForm1 : public TForm
{


__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TButton *Button1;
	TEdit *Edit4;
	TLabel *Label4;
	void __fastcall ButtonClick(TObject *Sender);
	void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit3KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit4KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit2Exit(TObject *Sender);
	void __fastcall Edit3Exit(TObject *Sender);
	void __fastcall Edit4Exit(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
private:   	// User declarations
public:	  void UndoLastAction(); void Counting();	// User declarations
	__fastcall TForm1(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
