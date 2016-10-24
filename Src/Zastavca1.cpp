//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream.h>
#pragma hdrstop
#include <windows.h>

#include <gl/gl.h>

#include <gl/glu.h>
#include "gl/glext.h"
#include <gl/wglext.h>
#include "Zastavca1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//#define WGL_SAMPLE_BUFFERS_ARB  0x2041

//#define WGL_SAMPLES_ARB         0x2042

bool arbMultisampleSupported = false;

int  arbMultisampleFormat = -1;

HDC hDC=NULL;
HGLRC hRC=NULL;
short v;
float perc;
bool synch,shl,top;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

bool WGLisExtensionSupported(const char *extension)

{

  const size_t extlen = strlen(extension);

  const char *supported = NULL;

  PROC wglGetExtString = wglGetProcAddress("wglGetExtensionsStringARB");

  if (wglGetExtString)

    supported = ((char*(__stdcall*)(HDC))wglGetExtString)(wglGetCurrentDC());

  if (supported == NULL)

    supported = (char*)glGetString(GL_EXTENSIONS);

  if (supported == NULL)

    return false;

  for (const char* p = supported; ; p++)
  {

    p = strstr(p, extension);

    if (p == NULL)return false;


   for(int i=0;i<extlen;i++)
    if (extension[i]!=p[i])
    return false;

    if(p[extlen-1]=='\0'||p[extlen-1]==' ')
       return true;


  }

}

void KillWindow()
{
 if( hDC )

             { if( !wglMakeCurrent( hDC, NULL ) )

       {   MessageBox( NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK |
       MB_ICONINFORMATION );

       }
        if( !wglDeleteContext( hRC ) )

       {  MessageBox( NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK |
        MB_ICONINFORMATION );

       }

      hRC = NULL;

       }
       if( hDC && !ReleaseDC(Form1->Panel1->Handle, hDC ) )

     {

        MessageBox( NULL, "Release Device Context Failed.", "SHUTDOWN ERROR",
        MB_OK | MB_ICONINFORMATION );

        hDC=NULL;

     }
}


int Multisample()
{
bool valid;

  UINT numFormats;
int pixelFormat=-1;

  float fAttributes[] = {0,0};


  const PIXELFORMATDESCRIPTOR pfd=
  {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW |
    PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    16,0,0,0,0,0,0,0,0,0,16,0,0,PFD_MAIN_PLANE,0,0,0,0
  };
    hDC = GetDC(Form1->Panel1->Handle);
    //int pfC=ChoosePixelFormat (hDC, &pfd);
   if (SetPixelFormat (hDC,1, &pfd) == false)
       {
       MessageBox( NULL, "Cannot Set Pixel Format", "SHUTDOWN ERROR", MB_OK |
        MB_ICONINFORMATION );
        return -1;
       }
  hRC = wglCreateContext(hDC);
   if(hRC == NULL)
{ MessageBox( NULL, "NULL hRC", "SHUTDOWN ERROR", MB_OK |
        MB_ICONINFORMATION );
        return -1;
}
   if(wglMakeCurrent(hDC, hRC) == false)
     {MessageBox( NULL, "Error", "SHUTDOWN ERROR", MB_OK |
        MB_ICONINFORMATION );
        return -1;}

 if (!WGLisExtensionSupported("WGL_ARB_multisample "))

    return -1;

  else
  {
   PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB =

    (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

  int iAttributes[] = {

    WGL_DRAW_TO_WINDOW_ARB,GL_TRUE, // Истинна, если формат пикселя может быть использован в окне

    WGL_SUPPORT_OPENGL_ARB,GL_TRUE, // Истинна, если поддерживается OpenGL

    WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB, // Полная аппаратная поддержка

    WGL_COLOR_BITS_ARB,24,          // Цветность

    WGL_ALPHA_BITS_ARB,8,           // Размерность альфа-канала

    WGL_DEPTH_BITS_ARB,16,          // Глубина буфера глубины

    WGL_STENCIL_BITS_ARB,0,         // Глубина буфера шаблона

    WGL_DOUBLE_BUFFER_ARB,GL_TRUE,  // Истина, если используется двойная буферизация

    WGL_SAMPLE_BUFFERS_ARB,GL_TRUE, // Что мы и хотим

    WGL_SAMPLES_ARB, 8,            // проверка на 8x тип

    0,0};

 valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
  if (valid && numFormats >= 1)
    {
     KillWindow();
     return pixelFormat;
    }
  
  iAttributes[19] = 4;

  valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);

  if (valid && numFormats >= 1)

    {
     KillWindow();
     return pixelFormat;
    }


  iAttributes[19] = 2;

  valid = wglChoosePixelFormatARB(hDC,iAttributes,fAttributes,1,&pixelFormat,&numFormats);

  if (valid && numFormats >= 1)
    {
     KillWindow();
    return    pixelFormat;
    }

  }


KillWindow();
return -1;



}




void __fastcall TForm1::Label4Click(TObject *Sender)
{
MediaPlayer1->FileName="Windows XP - пуск.wav";
MediaPlayer1->Open();
MediaPlayer1->Play();

Form1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Label1Click(TObject *Sender)
{
MediaPlayer1->FileName="Windows XP - пуск.wav";
MediaPlayer1->Open();
MediaPlayer1->Play();
AnsiString T="Editor.exe";
WinExec(T.c_str(),SW_SHOWNORMAL);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Label2Click(TObject *Sender)
{
MediaPlayer1->FileName="Windows XP - пуск.wav";
MediaPlayer1->Open();
MediaPlayer1->Play();
AnsiString T="controls.exe";
WinExec(T.c_str(),SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::FormPaint(TObject *Sender)
{
if(top)
Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
 int pixelFormat=-1;

 ifstream h;
 h.open("controls.cnt",ios_base::in|ios_base::binary|ios_base::beg);
 if(h.is_open())
{
 h.read((char*)&pixelFormat,sizeof(int));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read"); h.close();}

h.read((char*)&top,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}

h.read((char*)&perc,sizeof(float));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}

h.read((char*)&v,sizeof(short));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}

h.read((char*)&shl,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}

h.read((char*)&synch,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}
h.close();                   
}
 if(top)
 {
  AnsiString T="Editor.exe";
  WinExec(T.c_str(),SW_SHOWNORMAL);
 }
Image1->Width=Form1->Width;
Image1->Height=Form1->Height;

arbMultisampleFormat=Multisample();
if(arbMultisampleFormat!=-1)pixelFormat=arbMultisampleFormat;

ofstream H;
 H.open("controls.cnt",ios_base::out|ios_base::binary|ios_base::beg);
 if(!H.is_open()) ShowMessage("Can`t Open ");
H.write((char*)&pixelFormat,sizeof(int));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}

H.write((char*)&top,sizeof(bool));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}

H.write((char*)&perc,sizeof(float));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}

H.write((char*)&v,sizeof(short));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}

H.write((char*)&shl,sizeof(bool));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}


H.write((char*)&synch,sizeof(bool));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}
H.close();


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label5Click(TObject *Sender)
{
MediaPlayer1->FileName="Windows XP - пуск.wav";
MediaPlayer1->Open();
MediaPlayer1->Play();
AnsiString T="about2.exe";
WinExec(T.c_str(),SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label3Click(TObject *Sender)
{
MediaPlayer1->FileName="Windows XP - пуск.wav";
MediaPlayer1->Open();
MediaPlayer1->Play();
ShellExecute(Form1->Handle,"open","help.chm",NULL,NULL,SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
Image1->Width=Form1->Width;
Image1->Height=Form1->Height;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 int pixelFormat=-1;

 ifstream h;
 h.open("controls.cnt",ios_base::in|ios_base::binary|ios_base::beg);
 if(h.is_open())
{
 h.read((char*)&pixelFormat,sizeof(int));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read"); h.close();}

h.read((char*)&top,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}

h.read((char*)&perc,sizeof(float));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}

h.read((char*)&v,sizeof(short));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}

h.read((char*)&shl,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}

h.read((char*)&synch,sizeof(bool));
 if(h.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Read");h.close();}
h.close();                   
}
 if(top)
 {
  AnsiString T="Editor.exe";
  WinExec(T.c_str(),SW_SHOWNORMAL);
 }
Image1->Width=Form1->Width;
Image1->Height=Form1->Height;

arbMultisampleFormat=Multisample();
if(arbMultisampleFormat!=-1)pixelFormat=arbMultisampleFormat;

ofstream H;
 H.open("controls.cnt",ios_base::out|ios_base::binary|ios_base::beg);
 if(!H.is_open()) ShowMessage("Can`t Open ");
H.write((char*)&pixelFormat,sizeof(int));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}

H.write((char*)&top,sizeof(bool));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}

H.write((char*)&perc,sizeof(float));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}

H.write((char*)&v,sizeof(short));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}

H.write((char*)&shl,sizeof(bool));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}


H.write((char*)&synch,sizeof(bool));
 if(H.rdstate()!=ios::goodbit)
 {ShowMessage("Can`t Write In ");h.close();}
H.close();
}
//---------------------------------------------------------------------------

