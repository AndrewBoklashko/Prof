//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

PFNWGLSWAPINTERVALEXTPROC wglSwapInterval=NULL;
VERT v;

GLMouse mouse;
ShapeContainer sc;
ShapeContainer* Shape::s=&sc;
ShapeContainer* Selector::s=&sc;

GLMouse* Selector::m=&mouse;

LPDIRECTINPUT       g_DI;
LPDIRECTINPUTDEVICE g_KDIDev;
GLCamera cam(Vector3(-7.0f,8.0f,27.0f));
Shape *New;
BYTE buffer[256];
Vector2 Coef,Pparam;
Selector Sel;
HANDLE hThreadHandle = NULL,hPrimHandle=NULL;
Vector3 vec1,vec2;
bool vud=false,text=false;
GLuint ActiveName=0,rmode=GL_RENDER,vis,primMode=GL_NULL_MODE;
float d=0;


HDC hDC=NULL;
HGLRC hRC=NULL;


ChangeMode(int Mode)
{
 mode=Mode;
 switch(mode)
 {
  case GL_NULL_MODE :
  Form1->Label2->Caption="������� �����";break;

  case GL_ROTATE :
  Form1->Label2->Caption="����� ��������� ��'����";break;

  case GL_MOVE :
  Form1->Label2->Caption="����� ���������� ��'����";break;

  case GL_MOVE_TO :
  Form1->Label2->Caption="����� ���������� ��'����";break;

  case GL_SCALE :
  Form1->Label2->Caption="����� ������������� ��'����";break;

  case GL_CAMERA_TRANSFORM :
  Form1->Label2->Caption="����� ��������� ������";break;

  case GL_CAMERA_ANGLE :
  Form1->Label2->Caption="����� ���� ���� ������ ������";break;

  case GL_DRAW :
  Form1->Label2->Caption="����� �������� ��'����";break;

  case GL_VUD_OBJ :
  Form1->Label2->Caption="����� �������� ��'����";break;

  default :  Form1->Label2->Caption="������� ������";
 }

}


int DI_Init()
{

  if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
    IID_IDirectInput8, (void**)&g_DI, NULL)))
  {
    return false;
  }
  
  if (FAILED(g_DI->CreateDevice(GUID_SysKeyboard, &g_KDIDev, NULL)))
    { return false; }


  if ( g_KDIDev->SetDataFormat(&c_dfDIKeyboard) )

    return false;


  DIPROPDWORD dipdw;

  ZeroMemory(&dipdw, sizeof(DIPROPDWORD));
   dipdw.diph.dwSize      = sizeof(DIPROPDWORD);
   dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
   dipdw.diph.dwObj       = 0;
   dipdw.diph.dwHow       = DIPH_DEVICE;
   dipdw.dwData           = 10;

   if(FAILED(g_KDIDev->SetProperty(
      DIPROP_BUFFERSIZE,
      &dipdw.diph)))
      return false;


  if(FAILED(g_KDIDev->SetDataFormat(&c_dfDIKeyboard)))
      return false;

  if (FAILED(g_KDIDev->SetCooperativeLevel(Form1->Handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) ))

    return false;


  if (g_KDIDev)

    g_KDIDev->Acquire();
  else

    return false;

  return true;
}


bool inline CheckMode(void)
{
 if(mode==GL_SPLINE||mode==GL_TRIANGLES||mode==GL_QUADS)
 return true;
 return false;
}


bool inline CheckRenderMode()
{
 if(rmode==GL_RENDER)return true;
 return false;
}

bool InitGL(void)
{
ifstream h;
 int header=0;
 h.open("hint.hnt",ios_base::out|ios_base::binary/*|ios_base::beg*/);

 if(h.is_open())

   {
     h.read((char*)&header,sizeof(int));
     if(h.rdstate()!=ios::goodbit)
     {ShowMessage("Can`t Write");h.close();return false;}
     h.close();
   }


if(header==0)Form2->Show();
wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
if(wglSwapInterval)
wglSwapInterval(1);
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f},
lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f },
lightDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f },
lightSpecular[] = { 0.7f, 0.7f, 0.7f },
lightpos[] = { -10.0f, 30.0f, 20.0f, 0.0f };
v.v.Color=Vector3(1.0f,1.0f,1.0f);
 VBOActivate();
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );      // �������� ����� � ����� �������

          glLoadIdentity();              // �������� ������� �������
 glShadeModel(GL_SMOOTH);
 glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
 glEnable(GL_DEPTH_TEST);
 glClearDepth(1.0f);
 glDepthFunc(GL_LEQUAL);
 cam.SetCamera();
 glLoadIdentity();
 glEnable(GL_COLOR_MATERIAL);
 glDisable(GL_MULTISAMPLE_ARB);
 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
 glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
 glEnable(GL_POLYGON_OFFSET_FILL);
 glPolygonOffset(1.0f,1.0f);
 glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
 glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
 glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
 glLightfv(GL_LIGHT0,GL_POSITION, lightpos);
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,lightSpecular);
 //glMateriali(GL_FRONT_AND_BACK, GL_SHININESS,60);
 glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
 glBlendFunc(GL_SRC_ALPHA,GL_ONE);
 //gfBox(Vector3(-3.5f,-4.5f,-8.5f),Vector3(-1.0f,-1.5f,-4.5f),&sc);
 //gfPyramid(Vector3 (-0.8f,-0.5f,-0.6f),Vector3(0.8f,-0.5f,0.6f),Vector3(0.0f,0.5f,0.0f),&sc);
 //gfDisc(Vector3(3.0f,3.0f,-6.0f),3.0f,0.8f,32,360.0f,&sc);
 //gfPlane(Vector3(-5.0f,5.0f,-5.0f),Vector3(-2.0f,5.0f,-2.0f),3,3,&sc);
 //gfCylinder(Vector3(-6.5f,0.2f,-1.0f),0.5f,2.0f,24,360.0f,3.0f,&sc);
 //gfSphere(Vector3(-3.0f,0.0f,6.0f),1.0f,16,16,&sc);
 //glReadBuffer(GL_BACK);
 sc.Init();
 vis=glGenLists(2);
 glNewList(vis,GL_COMPILE);
 glLineWidth(1.5f);
 glBegin(GL_LINES);
glNormal3f(0.0f,1.0f,0.0f);
glColor3f(0.7f,0.0f,0.0f);
glVertex3f(0.0f,0.0f,0.0f);
glVertex4f(1.0f,0.0f,0.0f,0.0f);
glVertex3f(0.0f,0.0f,0.0f);
glVertex4f(0.0f,1.0f,0.0f,0.0f);
glVertex3f(0.0f,0.0f,0.0f);
glVertex4f(0.0f,0.0f,1.0f,0.0f);
glColor3f(0.0,0.7,0.0);
glVertex3f(0.0f,0.0f,0.0f);
glVertex4f(-1.0f,0.0f,0.0f,0.0f);
glColor3f(0.0,0.0,0.7);
glVertex3f(0.0f,0.0f,0.0f);
glVertex4f(0.0f,0.0f,-1.0f,0.0f);
glColor3f(0.4,0.0,0.4);
glVertex3f(0.0f,0.0f,0.0f);
glVertex4f(0.0f,-1.0f,0.0f,0.0f);
glEnd();
glColor3f(0.4f,0.4f,0.4f);
glLineWidth(1.0f);
glBegin(GL_LINES);
for(float i=-9.0f;i<10.0f;i++)
{
 glVertex3f(i,0.0f,-10.0f);
 glVertex3f(i,0.0f,10.0f);
}

for(float i=-9.0f;i<10.0f;i++)
{
 glVertex3f(-10.0f,0.0f,i);
 glVertex3f(10.0f,0.0f,i);
}
glEnd();

glEndList();

cam.LRrotate(16.0f);
cam.UDrotate(-14.0f);
cam.Go(-35.0f);
  return true;
   }

bool CreateContext()
{
  const PIXELFORMATDESCRIPTOR pfd=
  {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW |
    PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    32,0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0
  };
   hDC = GetDC(Form1->Panel1->Handle);
   if (SetPixelFormat (hDC,ChoosePixelFormat (hDC, &pfd), &pfd) == false)
      Application->Terminate ();
   hRC = wglCreateContext(hDC);
   if(hRC == NULL) Application->Terminate ();
   if(wglMakeCurrent(hDC, hRC) == false) Application->Terminate ();

  InitGL();
  DI_Init();
 mouse.Init(g_DI,Form1->Handle);
 return true;
}

inline void __fastcall TForm1::formed()
{
if (mouse.Is3D)
{
Edit1->Text= FloatToStrF(mouse.Locate.x,ffNumber,50,2);
Edit2->Text= FloatToStrF(mouse.Locate.y,ffNumber,50,2);
Edit3->Text= FloatToStrF(mouse.Locate.z,ffNumber,50,2);
}
}

void DrawScene()
{
sc.DrawFigures();

if(mode==GL_VUD_OBJ)
{
 if(vud)
 {
  vec2=mouse.Locate;
  sc.SetBuffer(0);
  Sel.Update();
  Par(vec1,vec2,&cam);
  sc.SetBuffer(sc.VB);
  sc.CheckVertexs(&cam,vec1,vec2,buffer[DIK_LCONTROL]&0x80||buffer[DIK_RCONTROL]&0x80);
  sc.CheckFigures(&cam,vec1,vec2);
 }
}

 /*if(mouse.CheckRight())
  {


  }
    */
}
//tp.Draw();


void Vis()
{
Form1->formed();
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
cam.LookAt();

glCallList(vis);


mouse.CursorDraw();
glColor3f(0.0f,0.0f,0.0f);
glBegin(GL_LINES);
glVertex3f(mouse.Locate.x,0.0f,0.0f);
glVertex3fv(&mouse.Locate.x);
glVertex3f(0.0f,mouse.Locate.y,0.0f);
glVertex3fv(&mouse.Locate.x);
glVertex3f(0.0f,0.0f,mouse.Locate.z);
glVertex3fv(&mouse.Locate.x);

if(mode==GL_DRAW&&(primMode==GL_ROTATE_OBJ||primMode==GL_VECTOR_OBJ)&&Draw)
    {
     glColor3f(1.0f,0.0f,1.0f);
     glVertex3fv(&New->s->Vlist[New->Indexs[New->NumOfVerts-1]].Vert.x);
     glVertex3fv(&mouse.Locate.x);
    }
glEnd();



if(mouse.Is3D&&mode==GL_DRAW)
    {
      switch(primMode)
      {
       case GL_NULL_MODE :break;
       case GL_PLANE :
       {
        if(Draw)
        gfPlaneDraw(mouse.LDownPos,mouse.Locate,&sc);
        break;
       }
      }
    }


    if(mode==GL_CAMERA_ANGLE)
    {
     if(mouse.KeepLeft())
     {
      cam.Angle+=0.1f;
     }

     if(mouse.KeepRight())
     {
      cam.Angle-=0.1f;
     }   
     cam.SetPerspective();
    }

/*if(spl&&spldr)
 {
  New->ShapeExtrude(spl);
  spldr=false;
 }
 */
/*sc.SetBuffer(0);
glDisableClientState(GL_COLOR_ARRAY);

glEnableClientState(GL_COLOR_ARRAY);
sc.SetBuffer(sc.VB);  */

}



inline void KillGLWindow( void )
{
   ShowCursor( true );

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


inline void keyboard(void*)
{
register PerfTimer kTimer;
Vector3 scale(1.0f,1.0f,1.0f),ang;
bool secDraw=false;
kTimer.Start();
while(Form1->done)
{
  if(kTimer.GetRealTime()>16.6f)
  {
  kTimer.Restart();
  //EnterCriticalSection(&Form1->CS);
   mouse.Update();
  //KeyBoard

 HRESULT hr = g_KDIDev->GetDeviceState(sizeof(buffer), &buffer);
  if(FAILED(hr))g_KDIDev->Acquire();
  /*MessageBox( NULL,"������� DirectX",
    "RUNTIME ERROR", MB_OK |MB_ICONINFORMATION );
   /* HRESULT hr=0;
     while (!hr) hr= g_KDIDev->Acquire();    */
  if((buffer[DIK_M]&0x80)&&!pm)
    {
     pm=true;
     m=!m;
     if(m)
     mouse.Set3DMode();
     else
     mouse.Set2DMode();
    }
 if(mouse.Is3D)
  {
  if(mode==GL_DRAW)
    {
      switch(primMode)
      {
       case GL_NULL_MODE :break;
       case GL_PLANE :
       {
       if(mouse.CheckLeft())
       {
       Draw=true;
       }
       if(!mouse.KeepLeft()&&Draw)
        {
        gfPlane(mouse.LDownPos,mouse.Locate,2,2,&sc);
        Draw=false;
        }
        else if(Draw)
         gfPlaneDraw(mouse.LDownPos,mouse.Locate,&sc);
        break;
       }

       case GL_SPHERE :
       {
       if(mouse.CheckLeft())
       Draw=true;
       if(!mouse.KeepLeft()&&Draw)
        {
        gfSphere(mouse.LDownPos,mouse.DeltaLPos().Abs(),18,18,&sc);
        Draw=false;
        }
        break;
       }

       case GL_BOX :
       {
       if(mouse.CheckLeft())
       Draw=true;
       if(!mouse.KeepLeft()&&Draw)
        {
        gfBox(mouse.LDownPos,mouse.Locate,&sc);
        Draw=false;
        }
        break;
       }

       case GL_PYRAMID :
       {
       static Vector3 Vert1,Vert2;
        if(mouse.CheckLeft())
        if(!secDraw)
        Draw=true;
        else
        {
         gfPyramid(Vert1,Vert2,mouse.Locate,&sc);
         Draw=false;
         secDraw=false;
         Vert1=Vert2=nil3;
        }
       if(!mouse.KeepLeft()&&Draw)
        {
        Vert1=mouse.LDownPos;
        Vert2=mouse.Locate;
        secDraw=true;
        Draw=false;
        }
        break;
       }

       case GL_KONYS :
       {
       static Vector3 Vert1,Vert2,Vert3,Vert4;
       static short TwoDraw=0;
        if(mouse.CheckLeft())
        if(!secDraw)
        {
        if(TwoDraw!=1)
        Draw=true;
        else
        TwoDraw=2;
        }

       if(!mouse.KeepLeft()&&Draw)
        {
        Vert1=mouse.LDownPos;
        Vert2=mouse.Locate;
        Draw=false;
        TwoDraw=1;
        }

       if(!mouse.KeepLeft()&&TwoDraw==2)
        {
        Vert3=mouse.LDownPos;
        Vert4=mouse.Locate;
         gfKonys(Vector3(Vert1.x,(Vert1.y+Vert3.y)/2,Vert1.z),
                            Vert1.ZXDistance(Vert2),Vert3.ZXDistance(Vert4),
                            64,360.0f,fabs((Vert3.y-Vert1.y)/2.0f),&sc);
         Draw=false;
         secDraw=false;
         TwoDraw=0;
         Vert1=Vert2=Vert3=Vert4=nil3;
        }
        break;
       }


       case GL_CYLINDER :
       {
       static Vector3 Vert1,Vert2,Vert3,Vert4;
       static short TwoDraw=0;
        if(mouse.CheckLeft())
        if(!secDraw)
        {
        if(TwoDraw!=1)
        Draw=true;
        else
        TwoDraw=2;
        }

       if(!mouse.KeepLeft()&&Draw)
        {
        Vert1=mouse.LDownPos;
        Vert2=mouse.Locate;
        Draw=false;
        TwoDraw=1;
        }

       if(!mouse.KeepLeft()&&TwoDraw==2)
        {
        Vert3=mouse.LDownPos;
        Vert4=mouse.Locate;
         gfCylinder(Vector3(Vert1.x,(Vert1.y+Vert3.y)/2,Vert1.z),
                            Vert1.ZXDistance(Vert2),64,360.0f,
                            fabs((Vert3.y-Vert1.y)/2.0f),&sc);
         Draw=false;
         secDraw=false;
         TwoDraw=0;
         Vert1=Vert2=Vert3=Vert4=nil3;
        }
        break;
       }

       case GL_ROTATE_OBJ :
       {
       if(mouse.CheckLeft())
        if(!Draw)
        {
          v.v.Vert=mouse.Locate;
          v.v.Color=Vector3(0.0f,0.0f,0.0f);
          sc.AddVertex(&v);
          New=new Spline(1);
          New->Indexs[0]=sc.VertCount-1;
          sc.AddEnd(New);
         Draw=true;
        }
        else
        {
         v.v.Vert=mouse.Locate;
         v.v.Color=Vector3(0.0f,0.0f,0.0f);
         sc.AddVertex(&v);
         New->AddIndex(sc.VertCount-1);
        }
        if(mouse.CheckRight()&&Draw)
         {
           v.v.Vert=mouse.Locate;
           v.v.Color=Vector3(0.0f,0.0f,0.0f);
           sc.AddVertex(&v);
           New->AddIndex(sc.VertCount-1);
           New->CreateRotateShape(20);
           Draw=false;
           sc.RemoveShape(New);
           New=NULL;
         }
        break;
       }

       case GL_VECTOR_OBJ :
       {
       static Shape* Spl;
       if(mouse.CheckLeft())
        if(!Draw)
        {
          v.v.Vert=mouse.Locate;
          v.v.Color=Vector3(0.0f,0.0f,0.0f);
          sc.AddVertex(&v);
          New=new Spline(1);
          New->Indexs[0]=sc.VertCount-1;
          sc.AddEnd(New);
         Draw=true;
        }
        else
        {
         v.v.Vert=mouse.Locate;
         v.v.Color=Vector3(0.0f,0.0f,0.0f);
         sc.AddVertex(&v);
         New->AddIndex(sc.VertCount-1);
        }
        if(mouse.CheckRight())
         {
           if(!secDraw)
           {
           if(Draw)
           {
           v.v.Vert=mouse.Locate;
           v.v.Color=Vector3(0.0f,0.0f,0.0f);
           sc.AddVertex(&v);
           New->AddIndex(sc.VertCount-1);
           Spl=New;
           Draw=false;
           secDraw=true;
           }
           }
           else
           {
           v.v.Vert=mouse.Locate;
           v.v.Color=Vector3(0.0f,0.0f,0.0f);
           sc.AddVertex(&v);
           New->AddIndex(sc.VertCount-1);
           Draw=secDraw=false;
           New->ShapeExtrude(Spl);
           sc.RemoveShape(New);
           New=NULL;
           sc.RemoveShape(Spl);
           Spl=NULL;
           }
         }
        break;
       }


        case GL_DISC :
       {
       static Vector3 Vert1,Vert2;
        if(mouse.CheckLeft())
        if(!secDraw)
        Draw=true;
        else
        {
         Vector3 v=Vert2-Vert1,v1=mouse.Locate-Vert1;
         v.y=v1.y=0.0f;
         gfDisc(Vert1,v1.Abs(),v.Abs(),64,360.0f,&sc);
         Draw=false;
         secDraw=false;
         Vert1=Vert2=nil3;
        }
       if(!mouse.KeepLeft()&&Draw)
        {
        Vert1=mouse.LDownPos;
        Vert2=mouse.Locate;
        secDraw=true;
        Draw=false;
        }
        break;
       }
      }


    }

    if (buffer[DIK_S]&0x80)
    {
    cam.UDrotate(-0.8f);
    }
    if (buffer[DIK_W]&0x80)
    {
    cam.UDrotate(0.8f);
    }
    if (buffer[DIK_A]&0x80)
    {
    cam.LRrotate(-0.8f);
    }
    if (buffer[DIK_D]&0x80)
    {
    cam.LRrotate(0.8f);
    }
    if (buffer[DIK_Z]&0x80)
    {
    cam.CWrotate(1.0f);
    }
    if (buffer[DIK_X]&0x80)
    {
    cam.CWrotate(-1.0f);
    }
    if (buffer[DIK_R]&0x80)
    {
    cam.Go(0.25f);
    }
    if (buffer[DIK_F]&0x80)
    {
    cam.Go(-0.25f);
    }
    if (buffer[DIK_C]&0x80)
    {
     mouse.ObNull();
    }

    

  //Mouse

   if(mouse.KeepLeft())
   {
  
     if(mode==GL_CAMERA_TRANSFORM)
    {
     cam.Translate(mouse.NDeltaLPos());
    }
   }

   if(mouse.CheckLeft())
   {
     if(mode==GL_VUD_OBJ&&!vud)
      {
       vec1=mouse.Locate;
       vud=true;
      }


     if(CheckMode()&&CheckRenderMode())
     {
      v.v.Vert=mouse.Locate;
      sc.AddVertex(&v);
      k++;


     }

   }

   if(mouse.CheckRight())
   {

     if(mode==GL_MOVE_TO)
      {
       sc.MoveTo(mouse.Locate);
      }

    if((mode==GL_ROTATE||mode==GL_MOVE)&&!fone)
     {
      fone=true;
     }

   }


    if(mouse.KeepRight())
    {
    if(fone)
    {
     if(mode==GL_MOVE)
      {
       sc.Move(mouse.NDeltaRPos());
      }


      if(mode==GL_ROTATE)
      {
       ang=mouse.NDeltaRPos()*50.0f;
       sc.Rotate(ang);
      }
     }
      if(mode==GL_CAMERA_TRANSFORM)
    {
     cam.Rotate(mouse.NDeltaRPos()*10.0f);
    }
    }
     if(mode==GL_SCALE&&d)
      {
        scale+=Vector3(d/5000.0f*mouse.bAxis.x,
                       d/5000.0f*mouse.bAxis.y,
                       d/5000.0f*mouse.bAxis.z);
        sc.Scale(scale);
        scale=Vector3(1.0f,1.0f,1.0f);

      }

     if(mode==GL_CAMERA_TRANSFORM&&!mouse.KeepLeft()&&!mouse.KeepRight())
    {
     cam.Go((float)d/60.0f);
    }
  mouse.Locate.y+=mouse.bAxis.y*(float)(d/700.0f);
  d=0;
 }
if(!(buffer[DIK_M]&0x80)&&pm)pm=false;
}

}
_endthread();
}





inline void __fastcall TForm1::myfunc(TObject*Sender,bool &don)
{
static PerfTimer Timer;
if(!hThreadHandle)
{
  done=true;
  if(!CreateContext())
    {
     MessageBox( NULL, "������� ������������",
     "SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION );
     Form1->Close();
    }
  ColorDialog1->Color=0x19CC66;
  for(int i=0;i<Image1->Width;i++)
  for(int j=0;j<Image1->Height;j++)
  Image10->Canvas->Pixels[i][j]=0x19CC66;//0.098f,0.8f,0.4f;
  hThreadHandle =(HANDLE) _beginthread(keyboard,0,NULL);
//hPrimHandle=(HANDLE) _beginthread(DrawPrimitives,0,NULL);
  Timer.Start();
}

if(Timer.GetRealTime()>16.6f)
  {
         Timer.Restart();
         Vis();
         DrawScene();
         SwapBuffers( hDC );
  }
}




//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------



void __fastcall TForm1::N8Click(TObject *Sender)
{

Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
Application->OnIdle=myfunc;
Form1->Caption="Prof - ���� ����� 1";
Form1->Top=0;
Form1->Left=0;
Form1->Width=Screen->Width;
Form1->Height=Screen->Height-40;


}
//---------------------------------------------------------------------------




void __fastcall TForm1::Image8Click(TObject *Sender)
{
primMode=GL_ROTATE_OBJ;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel3Click(TObject *Sender)
{
primMode=GL_VECTOR_OBJ;
mode=GL_DRAW;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N34Click(TObject *Sender)
{
cam.Pos=Vector3(-7.0f,8.0f,27.0f);
cam.Eye=Vector3(0.0f,0.0f,-1.0f);
cam.Up=Vector3(0.0f,1.0f,0.0f);
cam.LRrotate(16.0f);
cam.UDrotate(-14.0f);
cam.Go(-35.0f);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N35Click(TObject *Sender)
{
cam.Pos=Vector3(0.0f,60.0f,-3.5f);
cam.Eye=Vector3(0.0f,-1.0f,0.0f);
cam.Up=Vector3(0.0f,0.0f,-1.0f);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N37Click(TObject *Sender)
{
cam.Pos=Vector3(60.0f,0.0f,0.0f);
cam.Eye=Vector3(-1.0f,0.0f,0.0f);
cam.Up=Vector3(0.0f,1.0f,0.0f);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N36Click(TObject *Sender)
{
cam.Pos=Vector3(0.0f,0.0f,60.0f);
cam.Eye=Vector3(0.0f,0.0f,-1.0f);
cam.Up=Vector3(0.0f,1.0f,0.0f);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image6Click(TObject *Sender)
{
primMode=GL_CYLINDER;
ChangeMode(GL_DRAW);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2Click(TObject *Sender)
{
primMode=GL_DISC;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image5Click(TObject *Sender)
{
primMode=GL_PYRAMID;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4Click(TObject *Sender)
{
primMode=GL_BOX;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3Click(TObject *Sender)
{
primMode=GL_SPHERE;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
primMode=GL_PLANE;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)
{
primMode=GL_PLANE;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N12Click(TObject *Sender)
{
primMode=GL_SPHERE;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{
primMode=GL_BOX;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N14Click(TObject *Sender)
{
primMode=GL_PYRAMID;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N15Click(TObject *Sender)
{
primMode=GL_DISC;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N16Click(TObject *Sender)
{
primMode=GL_CYLINDER;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N18Click(TObject *Sender)
{
primMode=GL_ROTATE_OBJ;
ChangeMode(GL_DRAW);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N19Click(TObject *Sender)
{
primMode=GL_VECTOR_OBJ;
mode=GL_DRAW;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N31Click(TObject *Sender)
{

ChangeMode(GL_CAMERA_TRANSFORM);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N32Click(TObject *Sender)
{

ChangeMode(GL_CAMERA_ANGLE);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image10Click(TObject *Sender)
{
TColor color;
ColorDialog1->Execute();
color=ColorDialog1->Color;

 v.v.Color=Vector3((GLfloat)((GLfloat)(GetRValue(color))/255.0f),
 (GLfloat)((GLfloat)(GetGValue(color))/255.0f),
 (GLfloat)((GLfloat)(GetBValue(color))/255.0f));
 sc.ActiveColor=v.v.Color;
  g_KDIDev->Acquire();
for(int i=0;i<Image1->Width;i++)
for(int j=0;j<Image1->Height;j++)
Image10->Canvas->Pixels[i][j]=color;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N22Click(TObject *Sender)
{
 ChangeMode(GL_ROTATE);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N23Click(TObject *Sender)
{
ChangeMode(GL_SCALE);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N24Click(TObject *Sender)
{
 ChangeMode(GL_MOVE);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N25Click(TObject *Sender)
{
 ChangeMode(GL_MOVE_TO);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
 done=false;
   WaitForSingleObject(hThreadHandle, 500);
   WaitForSingleObject(hPrimHandle, 500);
 //  if(hThreadHandle)   CloseHandle( hThreadHandle );
  // KillGLWindow();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{
d=WheelDelta;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
 if(!BitBtn1->Tag)
{
BitBtn1->Tag=1;
mouse.bAxis.x=0.0f;
BitBtn1->Font->Color=clRed;
}
else
{
BitBtn1->Tag=0;
mouse.bAxis.x=1.0f;
BitBtn1->Font->Color=clLime;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
 if(!BitBtn2->Tag)
{
BitBtn2->Tag=1;
mouse.bAxis.y=0.0f;
BitBtn2->Font->Color=clRed;
}
else
{
BitBtn2->Tag=0;
mouse.bAxis.y=1.0f;
BitBtn2->Font->Color=clLime;
}        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
if(!BitBtn3->Tag)
{
BitBtn3->Tag=1;
mouse.bAxis.z=0.0f;
BitBtn3->Font->Color=clRed;
}
else
{
BitBtn3->Tag=0;
mouse.bAxis.z=1.0f;
BitBtn3->Font->Color=clLime;
}
        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N40Click(TObject *Sender)
{
sc.Hide();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N41Click(TObject *Sender)
{
sc.HideAll();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N42Click(TObject *Sender)
{
sc.UnHide();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N27Click(TObject *Sender)
{
sc.FlipNormals();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image9Click(TObject *Sender)
{
primMode=GL_VECTOR_OBJ;
ChangeMode(GL_DRAW);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Panel1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(Button==mbRight&&mode==GL_VUD_OBJ&&mode!=GL_ROTATE&&mode!=GL_SCALE
                                         &&mode!=GL_MOVE&&mode!=GL_MOVE_TO)
   {
   static GLuint buffer[64];
   register GLint hits,viewport[]={0,0,1024,768};
   glSelectBuffer(64,buffer);


   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glRenderMode(GL_SELECT);
   glLoadIdentity();

   gluPickMatrix(X,768-Y,2.0f,2.0f,viewport);
   gluPerspective(cam.Angle,1024.0f/768.0f, 0.1f, 1000.0f );
   sc.DrawFiguresForSelect();

   hits=glRenderMode(GL_RENDER);
   if(hits>0&&buffer[3])
   {
    sc.Activate(buffer[3],::buffer[DIK_LCONTROL]&0x80||::buffer[DIK_RCONTROL]&0x80);
   }

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   }
        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N29Click(TObject *Sender)
{
//VudMode=GL_VUD_OBJ;

rmode=GL_NULL_MODE;
ChangeMode(GL_VUD_OBJ);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(mode==GL_VUD_OBJ)vud=false;
//if(tp.IsEnable)text=false;
if(mode==GL_ROTATE||mode==GL_MOVE)fone=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N30Click(TObject *Sender)
{
sc.SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N26Click(TObject *Sender)
{
sc.Remove();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
if(OpenDialog1->Execute())
{
if(!sc.ReadFromFile(OpenDialog1->FileName))
ShowMessage("Can`t Read");
else
Form1->Caption="Prof - "+OpenDialog1->FileName;
}
g_KDIDev->Acquire();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
if(SaveDialog1->Execute())
{
if(!sc.WriteToFile(SaveDialog1->FileName+".raw"))
ShowMessage("Can`t Write");
}
g_KDIDev->Acquire();

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit2Change(TObject *Sender)
{
mouse.Locate.y=StrToFloat(Edit2->Text);
}
//---------------------------------------------------------------------------






void __fastcall TForm1::N5Click(TObject *Sender)
{
sc.RemoveAll();
Form1->Caption="Prof - ���� ����� 1";
}
//---------------------------------------------------------------------------








void __fastcall TForm1::N39Click(TObject *Sender)
{
AnsiString T="about2.exe";
WinExec(T.c_str(),SW_SHOWMAXIMIZED);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N38Click(TObject *Sender)
{
if(int p=(UINT)ShellExecute(Form1->Handle,"open","help.chm",NULL,NULL,SW_SHOWMAXIMIZED)<32)
Application->Terminate();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button4Click(TObject *Sender)
{
cam.Pos=Vector3(-7.0f,8.0f,27.0f);
cam.Eye=Vector3(0.0f,0.0f,-1.0f);
cam.Up=Vector3(0.0f,1.0f,0.0f);
cam.LRrotate(16.0f);
cam.UDrotate(-14.0f);
cam.Go(-35.0f);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
cam.Pos=Vector3(60.0f,0.0f,0.0f);
cam.Eye=Vector3(-1.0f,0.0f,0.0f);
cam.Up=Vector3(0.0f,1.0f,0.0f);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
cam.Pos=Vector3(0.0f,60.0f,-3.5f);
cam.Eye=Vector3(0.0f,-1.0f,0.0f);
cam.Up=Vector3(0.0f,0.0f,-1.0f);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
cam.Pos=Vector3(0.0f,0.0f,60.0f);
cam.Eye=Vector3(0.0f,0.0f,-1.0f);
cam.Up=Vector3(0.0f,1.0f,0.0f);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image7Click(TObject *Sender)
{
primMode=GL_KONYS;
ChangeMode(GL_DRAW);
}
//---------------------------------------------------------------------------

