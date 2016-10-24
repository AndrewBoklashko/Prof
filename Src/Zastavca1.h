//---------------------------------------------------------------------------

#ifndef Zastavca1H
#define Zastavca1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TImage *Image1;
        TLabel *Label5;
        TMediaPlayer *MediaPlayer1;
        TPanel *Panel1;
        void __fastcall Label4Click(TObject *Sender);
        void __fastcall Label1Click(TObject *Sender);
        void __fastcall Label2Click(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Label5Click(TObject *Sender);
        void __fastcall Label3Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
