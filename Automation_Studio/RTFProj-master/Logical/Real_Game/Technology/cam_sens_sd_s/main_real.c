/*********************************************************************************************
* B&R Automation - Perfection in Automation (https://www.br-automation.com)
    ******************************************************************************************
    * Program 	    : Bachelor's Thesis
    * Author  	    : Lubomir Bubenik, Radek Otradovský
    * Created 	    : date ... 
	* University    : Brno University of Technology(BUT)
	* Faculty       : Faculty of Mechanical Engineering(FME), Faculty of Electrical Engineering and Communication(FEEC)
**********************************************************************************************
* Implementation OF PROGRAM cam_sens_sd_s(Real_Game/Technology/sim_cam_sens_sd_s/main_real.c)
**********************************************************************************************/

#include <bur/plctypes.h>
#include <AsMem.h>
#include <Camera.h>


#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif
#define Y_AXIS 
#define ABS_F(X) ((X) < (0) ? -(X) : (X)) 
struct Buffer{
	REAL X;
	REAL Y;
	REAL TimeDiff;
};

_GLOBAL FBCamera_typ FBCamera_0;
_GLOBAL Light_typ Light_0;
_GLOBAL GoalKeeper_typ GoalKeeper_0;
_LOCAL struct Buffer BufferRes[20];
_LOCAL INT i;
_LOCAL INT tmp;
_LOCAL INT Reset;

void _INIT ProgramInit(void)
{
	FBCamera_0.Enable = 1;
	i = 0;
	tmp = 0;
	Reset = 0;
}

void _CYCLIC ProgramCyclic(void)
{
	
	FBCamera(&FBCamera_0);
	Light(&Light_0);
	GoalKeeper(&GoalKeeper_0);
	
	if ((FBCamera_0.isBallFound) || (tmp)){
		if (((ABS_F(FBCamera_0.Results.AxisX-FBCamera_0.Results.AxisXOld)) > 100) && (!tmp)){
			BufferRes[0].X = FBCamera_0.Results.AxisXOld;
			BufferRes[0].Y = FBCamera_0.Results.AxisYOld;
			BufferRes[0].TimeDiff = 0;
			
			BufferRes[1].X = FBCamera_0.Results.AxisX;
			BufferRes[1].Y = FBCamera_0.Results.AxisY;
			BufferRes[1].TimeDiff = FBCamera_0.Results.TimeDiff_ms;
			tmp = 1;
			i = 2;
		}
		else if (tmp){
			if (i < 20){
				BufferRes[i].X = FBCamera_0.Results.AxisX;
				BufferRes[i].Y = FBCamera_0.Results.AxisX;
				BufferRes[i].TimeDiff = FBCamera_0.Results.TimeDiff_ms;
				i++;
			}
		}
	}
	
	if ((GoalKeeper_0.isGoal1) || (GoalKeeper_0.isGoal2))
		tmp = 0;
	if (Reset){
		memset(&BufferRes,0,sizeof(BufferRes));
		i = 0;
		Reset = 0;
	}
}



