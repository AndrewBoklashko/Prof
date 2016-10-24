//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <Mask.hpp>

#define GL_TEXTURING 0x00aa00

#define GL_VUD_OBJ 0x02080A
//#define GL_VUD_VERT 0x02080B
#define GL_ROTATE 0x070ab4
#define GL_MOVE 0xf4f5f6
#define GL_MOVE_TO 0xf4f5f7
#define GL_SCALE 0x1025f6
#define GL_NULL_MODE 0x0000
#define GL_CAMERA_TRANSFORM 0x0ca0
#define GL_CAMERA_ANGLE 0x0c47


#define GL_DRAW 0x0100
#define GL_BOX 0x0200
#define GL_SPHERE 0x0201
#define GL_CYLINDER 0x0202
#define GL_PYRAMID  0x0203
#define GL_DISC     0x0204
#define GL_PLANE 0x0206
#define GL_ROTATE_OBJ 0x0207
#define GL_VECTOR_OBJ 0x0208
#define GL_KONYS 0x0210
//-------------------------------------------------------------------------
#include<GL/gl.h>
#include<GL/glu.h>
#include "GLSpline.h"
#include "GLvector.h"
#include "GLCamera.h"
#include <process.h>
//#include"Unit2.h"
#include"GL\glext.h"
#include <GLUpdate.h>
#include "GLContainer.h"
#include"GL/wglext.h"
#include"figures.h"
#include "GLPrimitives.h"
#include "GLTimer.h"
//#include "GLTexProj.h"

#include <mmreg.h>
#include <dinput.h>
#include "GLSelector.h"
#pragma comment (lib, "dinput8.lib")

#pragma comment (lib, "dxguid.lib")
#include "GLMouse.h"


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TImage *Image6;
        TImage *Image7;
        TImage *Image8;
        TImage *Image9;
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
        TMenuItem *N11;
        TMenuItem *N12;
        TMenuItem *N13;
        TMenuItem *N14;
        TMenuItem *N15;
        TMenuItem *N16;
        TMenuItem *N17;
        TMenuItem *N18;
        TMenuItem *N19;
        TMenuItem *N20;
        TMenuItem *N21;
        TMenuItem *N22;
        TMenuItem *N23;
        TMenuItem *N24;
        TMenuItem *N25;
        TMenuItem *N26;
        TMenuItem *N27;
        TMenuItem *N28;
        TMenuItem *N29;
        TMenuItem *N30;
        TMenuItem *N31;
        TMenuItem *N32;
        TMenuItem *N33;
        TMenuItem *N34;
        TMenuItem *N35;
        TMenuItem *N36;
        TMenuItem *N37;
        TMenuItem *N38;
        TMenuItem *N39;
        TLabel *Label2;
        TColorDialog *ColorDialog1;
        TImage *Image10;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TMenuItem *N40;
        TMenuItem *N41;
        TMenuItem *N42;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TImage *Image11;
        TLabel *Label1;
        void __fastcall N8Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Image8Click(TObject *Sender);
        void __fastcall Panel3Click(TObject *Sender);
        void __fastcall N34Click(TObject *Sender);
        void __fastcall N35Click(TObject *Sender);
        void __fastcall N37Click(TObject *Sender);
        void __fastcall N36Click(TObject *Sender);
        void __fastcall Image6Click(TObject *Sender);
        void __fastcall Image2Click(TObject *Sender);
        void __fastcall Image5Click(TObject *Sender);
        void __fastcall Image4Click(TObject *Sender);
        void __fastcall Image3Click(TObject *Sender);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall N11Click(TObject *Sender);
        void __fastcall N12Click(TObject *Sender);
        void __fastcall N13Click(TObject *Sender);
        void __fastcall N14Click(TObject *Sender);
        void __fastcall N15Click(TObject *Sender);
        void __fastcall N16Click(TObject *Sender);
        void __fastcall N18Click(TObject *Sender);
        void __fastcall N19Click(TObject *Sender);
        void __fastcall N31Click(TObject *Sender);
        void __fastcall N32Click(TObject *Sender);
        void __fastcall Image10Click(TObject *Sender);
        void __fastcall N22Click(TObject *Sender);
        void __fastcall N23Click(TObject *Sender);
        void __fastcall N24Click(TObject *Sender);
        void __fastcall N25Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall N40Click(TObject *Sender);
        void __fastcall N41Click(TObject *Sender);
        void __fastcall N42Click(TObject *Sender);
        void __fastcall N27Click(TObject *Sender);
        void __fastcall Image9Click(TObject *Sender);
        void __fastcall Panel1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall N29Click(TObject *Sender);
        void __fastcall Panel1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall N30Click(TObject *Sender);
        void __fastcall N26Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall N39Click(TObject *Sender);
        void __fastcall N38Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Image7Click(TObject *Sender);

private:	// User declarations
public:		// User declarations

         bool done;
        __fastcall TForm1(TComponent* Owner);
       inline void __fastcall TForm1::formed();
     inline void __fastcall TForm1::myfunc(TObject*Sender,bool &don);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

bool m=false,pm=false,fone=false,Draw=false;
//int tex=0;
GLuint mode=0,/*VudMode=GL_NULL_MODE,*/viewMode;
int k=0,n=3;

//---------------------------------------------------------------------------
#endif

