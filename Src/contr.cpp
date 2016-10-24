//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream.h>
#pragma hdrstop

#include "contr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
short v;
int pf;
float perc;
bool synch,shl,nshowz;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
MediaPlayer1->FileName="Windows XP - пуск.wav";
MediaPlayer1->Open();
MediaPlayer1->Play();
 Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
MediaPlayer1->FileName="Windows XP - пуск.wav";
MediaPlayer1->Open();
MediaPlayer1->Play();
 v=StrToInt(ComboBox1->Text);
 perc=TrackBar1->Position/8.0f;
 synch=CheckBox1->Checked;
 shl=CheckBox2->Checked;
 nshowz=CheckBox3->Checked;
 ofstream h;
 h.open("controls.cnt",ios_base::out|ios_base::binary|ios_base::beg);
 if(!h.is_open()) ShowMessage("Не вдалося відкрити файл");
h.write((char*)&pf,sizeof(int));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Запис не відбувся");h.close();}

h.write((char*)&nshowz,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Запис не відбувся");h.close();}

h.write((char*)&perc,sizeof(float));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Запис не відбувся");h.close();}

h.write((char*)&v,sizeof(short));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Запис не відбувся");h.close();}

h.write((char*)&shl,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Запис не відбувся");h.close();}


h.write((char*)&synch,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Запис не відбувся");h.close();}

h.close();

 ShowMessage("Зміни збережено");
 Form1->Close();
 
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
 ifstream h;
 h.open("controls.cnt",ios_base::in|ios_base::binary|ios_base::beg);
 if(h.is_open())
{
h.read((char*)&pf,sizeof(int));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Зчитування не відбулося");h.close();}

h.read((char*)&nshowz,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Зчитування не відбулося");h.close();}

h.read((char*)&perc,sizeof(float));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Зчитування не відбулося");h.close();}

h.read((char*)&v,sizeof(short));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Зчитування не відбулося");h.close();}

h.read((char*)&shl,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Зчитування не відбулося");h.close();}

h.read((char*)&synch,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Зчитування не відбулося");h.close();}
h.close();

TrackBar1->Position*=perc;
 CheckBox1->Checked=synch;
 CheckBox2->Checked=shl;
 CheckBox3->Checked=nshowz;
 ComboBox1->Text=IntToStr((int)v);
}        
else
ShowMessage("Не вдалося відкрити файл");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
MediaPlayer1->FileName="Windows XP - пуск.wav";
MediaPlayer1->Open();
MediaPlayer1->Play();
 TrackBar1->Position=8;
 CheckBox1->Checked=false;
 CheckBox2->Checked=false;
 CheckBox3->Checked=false;
 ComboBox1->Text="60";
}
//---------------------------------------------------------------------------


