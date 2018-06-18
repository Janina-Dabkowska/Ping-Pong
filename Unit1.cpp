//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfmrPingPong *fmrPingPong;
int x=8, y=8, leftPoints=0, rightPoints=0, springs=0, round=0;
AnsiString l="0", r="0", spr="0";

//---------------------------------------------------------------------------
__fastcall TfmrPingPong::TfmrPingPong(TComponent* Owner)
        : TForm(Owner)
{
	ShowMessage("Witaj w grze PingPong! \n"
	"Lewy gracz steruje wciskaj¹c klawisze A oraz Z \n"
	"Prawy gracz steruje wciskaj¹c strza³ki do góry lub w dó³ \n\n"
	"Jedna gra mo¿e mieæ maksymalnie 10 rund.\n"
        "Now¹ rundê mo¿esz uaktywniæ klawiszem spacji.\n\n"
	"Dla urozmaicenia zabawy: \n"
	"Kiedy odbijesz pi³kê na œrodku paletki wówczas zmienisz jej k¹t odbicia i pi³ka przyœpieszy. \n"
	"Mo¿esz dowolnie zmieniaæ pole gry.\n\n"
	" Mi³ej zabawy!\n");
}
//---------------------------------------------------------------------------

void __fastcall TfmrPingPong::tmrLeftUpTimer(TObject *Sender)
{   if(imgLeftPaddle->Top>10) imgLeftPaddle->Top-=10;

}
//---------------------------------------------------------------------------
void __fastcall TfmrPingPong::tmrLeftDownTimer(TObject *Sender)
{
    if(imgLeftPaddle->Top+imgLeftPaddle->Height<imgGround->Height-5) imgLeftPaddle->Top+=10;
}
//---------------------------------------------------------------------------
void __fastcall TfmrPingPong::tmrRightDownTimer(TObject *Sender)
{
    if(imgRightPaddle->Top+imgRightPaddle->Height<imgGround->Height-5) imgRightPaddle->Top+=10;
}
//---------------------------------------------------------------------------
void __fastcall TfmrPingPong::tmrRightUpTimer(TObject *Sender)
{
	if(imgRightPaddle->Top>10) imgRightPaddle->Top-=10;

}
//---------------------------------------------------------------------------
void __fastcall TfmrPingPong::FormKeyDown(TObject *Sender, WORD &Key,
    TShiftState Shift)
{
    if(Key==0x41) tmrLeftUp->Enabled=true;
    if(Key==0x5A) tmrLeftDown->Enabled=true;
    if(Key==VK_DOWN) tmrRightDown->Enabled=true;
    if(Key==VK_UP) tmrRightUp->Enabled=true;
    if(Key==VK_SPACE) btnNextBoundClick(Sender);

}
//---------------------------------------------------------------------------
void __fastcall TfmrPingPong::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key==0x41) tmrLeftUp->Enabled=false;
    if(Key==0x5A) tmrLeftDown->Enabled=false;
    if(Key==VK_DOWN) tmrRightDown->Enabled=false;
    if(Key==VK_UP) tmrRightUp->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TfmrPingPong::btnNewGameClick(TObject *Sender)
{       x=8; y=8;
        round=0;
        imgBall->Left=450;
	imgBall->Top=250;
	if (rightPoints!=0 || leftPoints!=0)
	{
		if(Application->MessageBox(
		"Czy na pewno zacz¹æ od nowa?","PotwierdŸ",
		MB_YESNO | MB_ICONQUESTION) == IDYES )
		{
			leftPoints=0; rightPoints=0; springs=0;
			l="0"; r="0"; spr="0";
			imgBall->Visible=true;
			tmrBall->Enabled=true;
			btnNewGame->Visible=false;
			lblTitle->Visible=false;
			lblResult->Visible=false;
			lblSprings->Visible=false;
			btnNextBound->Visible=false;
		}
	}
    else
	{
             imgBall->Visible=true;
             tmrBall->Enabled=true;
             btnNewGame->Visible=false;
             lblTitle->Visible=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfmrPingPong::btnNextBoundClick(TObject *Sender)
{
	if(round<10)
	{
        imgBall->Visible=true;
        imgBall->Left=450; imgBall->Top=250;
        tmrBall->Interval=20;
        tmrBall->Enabled=true;
        btnNewGame->Visible=false;
        lblTitle->Visible=false;
        lblResult->Visible=false;
        lblSprings->Visible=false;
        btnNextBound->Visible=false;
        springs=0; x=8;y=8;
	}
	else
	{  
		if(Application->MessageBox(
		"Gra nie mo¿e mieæ wiêcej ni¿ 10 rund, czy chcesz rozpocz¹æ nowa grê?","PotwierdŸ",
		MB_YESNO | MB_ICONQUESTION) == IDYES )
			{       round=0;
				imgBall->Left=450; imgBall->Top=250; x=8;y=8;
				leftPoints=0; rightPoints=0; springs=0;
				l="0"; r="0"; spr="0";
				imgBall->Visible=true;
				tmrBall->Enabled=true;
				btnNewGame->Visible=false;
				lblTitle->Visible=false;
				lblResult->Visible=false;
				lblSprings->Visible=false;
				btnNextBound->Visible=false;
			}
		else if(Application->MessageBox(
		"Zamkn¹æ grê?","PotwierdŸ",
		MB_YESNO | MB_ICONQUESTION) == IDYES )
			Application->Terminate();
	}
}
void __fastcall TfmrPingPong::tmrBallTimer(TObject *Sender)
{
    imgBall->Left+=x;
   imgBall->Top+=y;
    //odbij od górnej sciany
    if (imgBall->Top-2 <= imgGround->Top)
		 y=-y;

    //odbijaj od dolnej sciany
    if (imgBall->Top+imgBall->Height +2>= imgGround->Top+imgGround->Height)
		y=-y;

     //skucha z lewej
	if (imgBall->Left <=imgLeftPaddle->Left)
	{
		sndPlaySound("snd/miss.wav", SND_ASYNC);
		tmrBall->Enabled=false; rightPoints++; round++;
		imgBall->Visible=false;
		btnNewGame->Visible=true;
		btnNextBound->Visible=true;
		r=IntToStr(rightPoints);
		lblResult->Caption= l+":"+r;
		lblTitle->Caption="Punkt dla gracza prawego >";
		lblResult->Visible=true;
		lblTitle->Visible=true;
		spr= IntToStr(springs);
		lblSprings->Caption= "Iloœæ odbiæ:"+spr;
		lblSprings->Visible=true;
    }
    //odbicie od lewej paletki
    else  if ( imgBall->Left < imgLeftPaddle->Left+imgLeftPaddle->Width+10 &&
    imgBall->Top >= imgLeftPaddle->Top - imgBall->Height && imgBall->Top<=imgLeftPaddle->Top+imgLeftPaddle->Height-imgBall->Height )
    {
		if(x<0)
		{
			if(imgBall->Top > imgLeftPaddle->Top+imgLeftPaddle->Height/2-imgBall->Height/2 &&
			imgBall->Top < imgLeftPaddle->Top+imgLeftPaddle->Height/2+imgBall->Height/2)
				{
					x=-2*x; tmrBall->Interval=8;
				}
			else
				x=-x;
			sndPlaySound("snd/ping.wav", SND_ASYNC);
			springs++;
			if(tmrBall->Interval>5)
			tmrBall->Interval=tmrBall->Interval-2;
		}
    }
    //skucha z prawej
    else if (imgBall->Left+imgBall->Width >= imgRightPaddle->Left+imgRightPaddle->Width )
    {  
		sndPlaySound("snd/miss.wav", SND_ASYNC);
        tmrBall->Enabled=false; leftPoints++;   round++;
        imgBall->Visible=false;
        btnNewGame->Visible=true;
        btnNextBound->Visible=true;
        l=IntToStr(leftPoints);
        lblResult->Caption= l+":"+r;
        lblTitle->Caption="<Punkt dla gracza lewego ";
        lblResult->Visible=true;
        lblTitle->Visible=true;
		spr= IntToStr(springs);
		lblSprings->Caption= "Iloœæ odbiæ:"+spr;
		lblSprings->Visible=true;
    }


	//odbicie od prawej paletki
	else if (  imgBall->Left+imgBall->Width > imgRightPaddle->Left -10
	&& imgBall->Top >= imgRightPaddle->Top - imgBall->Height &&
	imgBall->Top < imgRightPaddle->Top +imgRightPaddle->Height-  imgBall->Height  )
	{
		if(x>0)
		{
			if(imgBall->Top >imgRightPaddle->Top+imgRightPaddle->Height/2-imgBall->Height/2 &&
			imgBall->Top < imgRightPaddle->Top+imgRightPaddle->Height/2+imgBall->Height/2)
				{
					x=-2*x; tmrBall->Interval=8;
				}
			else
				x=-x;
			sndPlaySound("snd/ping.wav", SND_ASYNC);
			springs++;
			if(tmrBall->Interval>5)
			tmrBall->Interval = tmrBall->Interval-2;
		}
	}
}

//---------------------------------------------------------------------------

void __fastcall TfmrPingPong::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(Application->MessageBox(
    "Czy na pewno zakoñczyæ program?","PotwierdŸ",
    MB_YESNO | MB_ICONQUESTION) == IDNO )
		{
			Action=caNone;
		}
}
//---------------------------------------------------------------------------

void __fastcall TfmrPingPong::FormResize(TObject *Sender)
{
   imgRightPaddle->Left=imgGround->Width-110;
   btnNewGame->Left=imgGround->Width/2-btnNewGame->Width/2;
   btnNextBound->Left=imgGround->Width/2-btnNextBound->Width/2;
   lblResult->Left=imgGround->Width/2-lblResult->Width/2;
   lblSprings->Left=imgGround->Width/2-lblSprings->Width/2;
   lblTitle->Left=imgGround->Width/2-lblTitle->Width/2;
}
//---------------------------------------------------------------------------

