/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWInterruptP.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

/*===========================================================================*/
/* WWInterruptVector クラスのもの                                            */
/*===========================================================================*/

static int WWInterruptVector_GetNumber(WWInterruptVector v)
{ return (v->number); }
static WWInterruptCallback WWInterruptVector_GetCallback(WWInterruptVector v)
{ return (v->callback); }
static int WWInterruptVector_GetCS(WWInterruptVector v)
{ return (v->cs); }
static int WWInterruptVector_GetDS(WWInterruptVector v)
{ return (v->ds); }

static int WWInterruptVector_SetNumber(WWInterruptVector v, int number)
{ return (v->number = number); }
static WWInterruptCallback WWInterruptVector_SetCallback(WWInterruptVector v,
							 WWInterruptCallback cb)
{ return (v->callback = cb); }
static int WWInterruptVector_SetCS(WWInterruptVector v, int cs)
{ return (v->cs = cs); }
static int WWInterruptVector_SetDS(WWInterruptVector v, int ds)
{ return (v->ds = ds); }

static int WWInterruptVector_ExecuteCallback(WWInterruptVector vector)
{
  if (vector->callback == NULL) return (1);
  (*(vector->callback))();
  return (0);
}

static WWInterruptVector WWInterruptVector_Create(int number)
{
  WWInterruptVector vector;

  vector = (WWInterruptVector)malloc(sizeof(_WWInterruptVector));
  if (vector == NULL)
    WonX_Error("WWInterruptVector_Create", "Cannot allocate memory.");

  WWInterruptVector_SetNumber(vector, number);
  WWInterruptVector_SetCallback(vector, NULL);
  WWInterruptVector_SetCS(vector, 0);
  WWInterruptVector_SetDS(vector, 0);

  return (vector);
}

static WWInterruptVector WWInterruptVector_Destroy(WWInterruptVector vector)
{
  if (vector == NULL)
    WonX_Error("WWInterruptVector_Destroy", "Object is not created.");
  free(vector);
  return (NULL);
}

/*===========================================================================*/
/* WWInterrupt クラスのもの                                                  */
/*===========================================================================*/

static WWInterruptVector WWInterrupt_GetVector(WWInterrupt interrupt,
					       int number)
{
  if ((number < 0) || (number > 7))
    WonX_Error("WWInterrupt_SetVector", "Invalid interrupt number.");
  return (interrupt->vector[number]);
}

static WWInterruptVector WWInterrupt_SetVector(WWInterrupt interrupt,
					       int number,
					       WWInterruptVector vector)
{
  if ((number < 0) || (number > 7))
    WonX_Error("WWInterrupt_SetVector", "Invalid interrupt number.");
  return (interrupt->vector[number] = vector);
}

int WWInterrupt_GetNumber(WWInterrupt interrupt, int num)
{
  return (WWInterruptVector_GetNumber(WWInterrupt_GetVector(interrupt, num)));
}

WWInterruptCallback WWInterrupt_GetCallback(WWInterrupt interrupt, int n)
{
  return (WWInterruptVector_GetCallback(WWInterrupt_GetVector(interrupt, n)));
}

int WWInterrupt_GetCS(WWInterrupt interrupt, int number)
{
  return (WWInterruptVector_GetCS(WWInterrupt_GetVector(interrupt, number)));
}

int WWInterrupt_GetDS(WWInterrupt interrupt, int number)
{
  return (WWInterruptVector_GetDS(WWInterrupt_GetVector(interrupt, number)));
}

WWInterruptCallback WWInterrupt_SetCallback(WWInterrupt interrupt, int num,
					    WWInterruptCallback callback)
{
  return (WWInterruptVector_SetCallback(WWInterrupt_GetVector(interrupt, num),
					callback));
}

int WWInterrupt_SetCS(WWInterrupt interrupt, int num, int cs)
{
  return (WWInterruptVector_SetCS(WWInterrupt_GetVector(interrupt, num), cs));
}

int WWInterrupt_SetDS(WWInterrupt interrupt, int num, int ds)
{
  return (WWInterruptVector_SetDS(WWInterrupt_GetVector(interrupt, num), ds));
}

int WWInterrupt_ExecuteCallback(WWInterrupt i, int n)
{
  return (WWInterruptVector_ExecuteCallback(WWInterrupt_GetVector(i, n)));
}

/*---------------------------------------------------------------------------*/
/* Number の取得                                                             */
/*---------------------------------------------------------------------------*/

int WWInterrupt_GetSendReadyNumber(WWInterrupt interrupt)
{ return (WWInterrupt_GetNumber(interrupt, SYS_INT_SENDREADY)); }
int WWInterrupt_GetKeyNumber(WWInterrupt interrupt)
{ return (WWInterrupt_GetNumber(interrupt, SYS_INT_KEY)); }
int WWInterrupt_GetCasetteNumber(WWInterrupt interrupt)
{ return (WWInterrupt_GetNumber(interrupt, SYS_INT_CASETTE)); }
int WWInterrupt_GetReceiveReadyNumber(WWInterrupt interrupt)
{ return (WWInterrupt_GetNumber(interrupt, SYS_INT_RECEIVEREADY)); }
int WWInterrupt_GetDisplineNumber(WWInterrupt interrupt)
{ return (WWInterrupt_GetNumber(interrupt, SYS_INT_DISPLINE)); }
int WWInterrupt_GetTimerCountUpNumber(WWInterrupt interrupt)
{ return (WWInterrupt_GetNumber(interrupt, SYS_INT_TIMER_COUNTUP)); }
int WWInterrupt_GetVBlankNumber(WWInterrupt interrupt)
{ return (WWInterrupt_GetNumber(interrupt, SYS_INT_VBLANK)); }
int WWInterrupt_GetHBlankCountUpNumber(WWInterrupt interrupt)
{ return (WWInterrupt_GetNumber(interrupt, SYS_INT_HBLANK_COUNTUP)); }

/*---------------------------------------------------------------------------*/
/* コールバック関数の取得                                                    */
/*---------------------------------------------------------------------------*/

WWInterruptCallback WWInterrupt_GetSendReadyCallback(WWInterrupt interrupt)
{ return (WWInterrupt_GetCallback(interrupt, SYS_INT_SENDREADY)); }
WWInterruptCallback WWInterrupt_GetKeyCallback(WWInterrupt interrupt)
{ return (WWInterrupt_GetCallback(interrupt, SYS_INT_KEY)); }
WWInterruptCallback WWInterrupt_GetCasetteCallback(WWInterrupt interrupt)
{ return (WWInterrupt_GetCallback(interrupt, SYS_INT_CASETTE)); }
WWInterruptCallback WWInterrupt_GetReceiveReadyCallback(WWInterrupt interrupt)
{ return (WWInterrupt_GetCallback(interrupt, SYS_INT_RECEIVEREADY)); }
WWInterruptCallback WWInterrupt_GetDisplineCallback(WWInterrupt interrupt)
{ return (WWInterrupt_GetCallback(interrupt, SYS_INT_DISPLINE)); }
WWInterruptCallback WWInterrupt_GetTimerCountUpCallback(WWInterrupt interrupt)
{ return (WWInterrupt_GetCallback(interrupt, SYS_INT_TIMER_COUNTUP)); }
WWInterruptCallback WWInterrupt_GetVBlankCallback(WWInterrupt interrupt)
{ return (WWInterrupt_GetCallback(interrupt, SYS_INT_VBLANK)); }
WWInterruptCallback WWInterrupt_GetHBlankCountUpCallback(WWInterrupt interrupt)
{ return (WWInterrupt_GetCallback(interrupt, SYS_INT_HBLANK_COUNTUP)); }

/*---------------------------------------------------------------------------*/
/* CS の取得                                                                 */
/*---------------------------------------------------------------------------*/

int WWInterrupt_GetSendReadyCS(WWInterrupt interrupt)
{ return (WWInterrupt_GetCS(interrupt, SYS_INT_SENDREADY)); }
int WWInterrupt_GetKeyCS(WWInterrupt interrupt)
{ return (WWInterrupt_GetCS(interrupt, SYS_INT_KEY)); }
int WWInterrupt_GetCasetteCS(WWInterrupt interrupt)
{ return (WWInterrupt_GetCS(interrupt, SYS_INT_CASETTE)); }
int WWInterrupt_GetReceiveReadyCS(WWInterrupt interrupt)
{ return (WWInterrupt_GetCS(interrupt, SYS_INT_RECEIVEREADY)); }
int WWInterrupt_GetDisplineCS(WWInterrupt interrupt)
{ return (WWInterrupt_GetCS(interrupt, SYS_INT_DISPLINE)); }
int WWInterrupt_GetTimerCountUpCS(WWInterrupt interrupt)
{ return (WWInterrupt_GetCS(interrupt, SYS_INT_TIMER_COUNTUP)); }
int WWInterrupt_GetVBlankCS(WWInterrupt interrupt)
{ return (WWInterrupt_GetCS(interrupt, SYS_INT_VBLANK)); }
int WWInterrupt_GetHBlankCountUpCS(WWInterrupt interrupt)
{ return (WWInterrupt_GetCS(interrupt, SYS_INT_HBLANK_COUNTUP)); }

/*---------------------------------------------------------------------------*/
/* DS の取得                                                                 */
/*---------------------------------------------------------------------------*/

int WWInterrupt_GetSendReadyDS(WWInterrupt interrupt)
{ return (WWInterrupt_GetDS(interrupt, SYS_INT_SENDREADY)); }
int WWInterrupt_GetKeyDS(WWInterrupt interrupt)
{ return (WWInterrupt_GetDS(interrupt, SYS_INT_KEY)); }
int WWInterrupt_GetCasetteDS(WWInterrupt interrupt)
{ return (WWInterrupt_GetDS(interrupt, SYS_INT_CASETTE)); }
int WWInterrupt_GetReceiveReadyDS(WWInterrupt interrupt)
{ return (WWInterrupt_GetDS(interrupt, SYS_INT_RECEIVEREADY)); }
int WWInterrupt_GetDisplineDS(WWInterrupt interrupt)
{ return (WWInterrupt_GetDS(interrupt, SYS_INT_DISPLINE)); }
int WWInterrupt_GetTimerCountUpDS(WWInterrupt interrupt)
{ return (WWInterrupt_GetDS(interrupt, SYS_INT_TIMER_COUNTUP)); }
int WWInterrupt_GetVBlankDS(WWInterrupt interrupt)
{ return (WWInterrupt_GetDS(interrupt, SYS_INT_VBLANK)); }
int WWInterrupt_GetHBlankCountUpDS(WWInterrupt interrupt)
{ return (WWInterrupt_GetDS(interrupt, SYS_INT_HBLANK_COUNTUP)); }

/*---------------------------------------------------------------------------*/
/* コールバック関数の設定                                                    */
/*---------------------------------------------------------------------------*/

WWInterruptCallback WWInterrupt_SetSendReadyCallback(WWInterrupt interrupt,
						     WWInterruptCallback f)
{ return (WWInterrupt_SetCallback(interrupt, SYS_INT_SENDREADY, f)); }
WWInterruptCallback WWInterrupt_SetKeyCallback(WWInterrupt interrupt,
					       WWInterruptCallback f)
{ return (WWInterrupt_SetCallback(interrupt, SYS_INT_KEY, f)); }
WWInterruptCallback WWInterrupt_SetCasetteCallback(WWInterrupt interrupt,
						   WWInterruptCallback f)
{ return (WWInterrupt_SetCallback(interrupt, SYS_INT_CASETTE, f)); }
WWInterruptCallback WWInterrupt_SetReceiveReadyCallback(WWInterrupt interrupt,
							WWInterruptCallback f)
{ return (WWInterrupt_SetCallback(interrupt, SYS_INT_RECEIVEREADY, f)); }
WWInterruptCallback WWInterrupt_SetDisplineCallback(WWInterrupt interrupt,
						    WWInterruptCallback f)
{ return (WWInterrupt_SetCallback(interrupt, SYS_INT_DISPLINE, f)); }
WWInterruptCallback WWInterrupt_SetTimerCountUpCallback(WWInterrupt interrupt,
							WWInterruptCallback f)
{ return (WWInterrupt_SetCallback(interrupt, SYS_INT_TIMER_COUNTUP, f)); }
WWInterruptCallback WWInterrupt_SetVBlankCallback(WWInterrupt interrupt,
						  WWInterruptCallback f)
{ return (WWInterrupt_SetCallback(interrupt, SYS_INT_VBLANK, f)); }
WWInterruptCallback WWInterrupt_SetHBlankCountUpCallback(WWInterrupt interrupt,
							 WWInterruptCallback f)
{ return (WWInterrupt_SetCallback(interrupt, SYS_INT_HBLANK_COUNTUP, f)); }

/*---------------------------------------------------------------------------*/
/* CS の設定                                                                 */
/*---------------------------------------------------------------------------*/

int WWInterrupt_SetSendReadyCS(WWInterrupt interrupt, int cs)
{ return (WWInterrupt_SetCS(interrupt, SYS_INT_SENDREADY, cs)); }
int WWInterrupt_SetKeyCS(WWInterrupt interrupt, int cs)
{ return (WWInterrupt_SetCS(interrupt, SYS_INT_KEY, cs)); }
int WWInterrupt_SetCasetteCS(WWInterrupt interrupt, int cs)
{ return (WWInterrupt_SetCS(interrupt, SYS_INT_CASETTE, cs)); }
int WWInterrupt_SetReceiveReadyCS(WWInterrupt interrupt, int cs)
{ return (WWInterrupt_SetCS(interrupt, SYS_INT_RECEIVEREADY, cs)); }
int WWInterrupt_SetDisplineCS(WWInterrupt interrupt, int cs)
{ return (WWInterrupt_SetCS(interrupt, SYS_INT_DISPLINE, cs)); }
int WWInterrupt_SetTimerCountUpCS(WWInterrupt interrupt, int cs)
{ return (WWInterrupt_SetCS(interrupt, SYS_INT_TIMER_COUNTUP, cs)); }
int WWInterrupt_SetVBlankCS(WWInterrupt interrupt, int cs)
{ return (WWInterrupt_SetCS(interrupt, SYS_INT_VBLANK, cs)); }
int WWInterrupt_SetHBlankCountUpCS(WWInterrupt interrupt, int cs)
{ return (WWInterrupt_SetCS(interrupt, SYS_INT_HBLANK_COUNTUP, cs)); }

/*---------------------------------------------------------------------------*/
/* DS の設定                                                                 */
/*---------------------------------------------------------------------------*/

int WWInterrupt_SetSendReadyDS(WWInterrupt interrupt, int ds)
{ return (WWInterrupt_SetDS(interrupt, SYS_INT_SENDREADY, ds)); }
int WWInterrupt_SetKeyDS(WWInterrupt interrupt, int ds)
{ return (WWInterrupt_SetDS(interrupt, SYS_INT_KEY, ds)); }
int WWInterrupt_SetCasetteDS(WWInterrupt interrupt, int ds)
{ return (WWInterrupt_SetDS(interrupt, SYS_INT_CASETTE, ds)); }
int WWInterrupt_SetReceiveReadyDS(WWInterrupt interrupt, int ds)
{ return (WWInterrupt_SetDS(interrupt, SYS_INT_RECEIVEREADY, ds)); }
int WWInterrupt_SetDisplineDS(WWInterrupt interrupt, int ds)
{ return (WWInterrupt_SetDS(interrupt, SYS_INT_DISPLINE, ds)); }
int WWInterrupt_SetTimerCountUpDS(WWInterrupt interrupt, int ds)
{ return (WWInterrupt_SetDS(interrupt, SYS_INT_TIMER_COUNTUP, ds)); }
int WWInterrupt_SetVBlankDS(WWInterrupt interrupt, int ds)
{ return (WWInterrupt_SetDS(interrupt, SYS_INT_VBLANK, ds)); }
int WWInterrupt_SetHBlankCountUpDS(WWInterrupt interrupt, int ds)
{ return (WWInterrupt_SetDS(interrupt, SYS_INT_HBLANK_COUNTUP, ds)); }

/*---------------------------------------------------------------------------*/
/* コールバック関数の実行                                                    */
/*---------------------------------------------------------------------------*/

int WWInterrupt_ExecuteSendReadyCallback(WWInterrupt interrupt)
{ return (WWInterrupt_ExecuteCallback(interrupt, SYS_INT_SENDREADY)); }
int WWInterrupt_ExecuteKeyCallback(WWInterrupt interrupt)
{ return (WWInterrupt_ExecuteCallback(interrupt, SYS_INT_KEY)); }
int WWInterrupt_ExecuteCasetteCallback(WWInterrupt interrupt)
{ return (WWInterrupt_ExecuteCallback(interrupt, SYS_INT_CASETTE)); }
int WWInterrupt_ExecuteReceiveReadyCallback(WWInterrupt interrupt)
{ return (WWInterrupt_ExecuteCallback(interrupt, SYS_INT_RECEIVEREADY)); }
int WWInterrupt_ExecuteDisplineCallback(WWInterrupt interrupt)
{ return (WWInterrupt_ExecuteCallback(interrupt, SYS_INT_DISPLINE)); }
int WWInterrupt_ExecuteTimerCountUpCallback(WWInterrupt interrupt)
{ return (WWInterrupt_ExecuteCallback(interrupt, SYS_INT_TIMER_COUNTUP)); }
int WWInterrupt_ExecuteVBlankCallback(WWInterrupt interrupt)
{ return (WWInterrupt_ExecuteCallback(interrupt, SYS_INT_VBLANK)); }
int WWInterrupt_ExecuteHBlankCountUpCallback(WWInterrupt interrupt)
{ return (WWInterrupt_ExecuteCallback(interrupt, SYS_INT_HBLANK_COUNTUP)); }

/*---------------------------------------------------------------------------*/
/* オブジェクトの作成                                                        */
/*---------------------------------------------------------------------------*/

WWInterrupt WWInterrupt_Create()
{
  WWInterrupt interrupt;
  int i;

  interrupt = (WWInterrupt)malloc(sizeof(_WWInterrupt));
  if (interrupt == NULL)
    WonX_Error("WWInterrupt_Create", "Cannot allocate memory.");

  for (i = 0; i < 8; i++)
    WWInterrupt_SetVector(interrupt, i, WWInterruptVector_Create(i));

  return (interrupt);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

WWInterrupt WWInterrupt_Destroy(WWInterrupt interrupt)
{
  int i;
  WWInterruptVector vector;

  if (interrupt == NULL)
    WonX_Error("WWInterrupt_Destroy", "Object is not created.");

  for (i = 0; i < 8; i++) {
    vector = WWInterrupt_GetVector(interrupt, i);
    if (vector != NULL)
      WWInterrupt_SetVector(interrupt, i, WWInterruptVector_Destroy(vector));
  }

  free(interrupt);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
