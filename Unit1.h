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
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TfmrPingPong : public TForm
{
__published:	// IDE-managed Components
        TShape *imgGround;
        TImage *imgLeftPaddle;
        TImage *imgRightPaddle;
        TImage *imgBall;
        TLabel *lblTitle;
        TButton *btnNewGame;
        TTimer *tmrLeftUp;
        TTimer *tmrLeftDown;
        TLabel *lblResult;
        TLabel *lblSprings;
        TButton *btnNextBound;
        TTimer *tmrRightUp;
        TTimer *tmrRightDown;
        TTimer *tmrBall;
        void __fastcall tmrLeftUpTimer(TObject *Sender);
        void __fastcall tmrLeftDownTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall btnNewGameClick(TObject *Sender);
        void __fastcall tmrBallTimer(TObject *Sender);
        void __fastcall tmrRightDownTimer(TObject *Sender);
        void __fastcall tmrRightUpTimer(TObject *Sender);
        void __fastcall btnNextBoundClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfmrPingPong(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmrPingPong *fmrPingPong;
//---------------------------------------------------------------------------
#endif
