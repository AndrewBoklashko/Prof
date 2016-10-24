//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream.h>
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
if(int p=(UINT)ShellExecute(Form2->Handle,"open","help.chm",NULL,NULL,SW_SHOWMAXIMIZED)<32)
Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
ofstream h;
 int header=0;
 if(CheckBox1->Checked)header=1;
 h.open("hint.hnt",ios_base::out|ios_base::binary/*|ios_base::beg*/);

 if(h.is_open())
   {
     h.write((char*)&header,sizeof(int));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write");h.close();}
 h.close();
   }

}
//---------------------------------------------------------------------------
