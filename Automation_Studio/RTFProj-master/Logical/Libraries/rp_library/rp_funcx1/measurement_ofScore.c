#include <bur/plctypes.h>
#include <bur/plc.h>
#include <astime.h>
#include <string.h>
#include <math.h>

#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "rp_funcx1.h"
#ifdef __cplusplus
	};
#endif
void initialization(struct measurement_ofScore* m_oS);

void measurement_ofScore(struct measurement_ofScore* m_oS)
{
    
    if(!m_oS->Enable){
        initialization(m_oS);
    }
    
    switch(m_oS->Internal.state){
        case 0:
            {
                if(m_oS->Internal.counter <= 0){
                    m_oS->Internal.counter = 0;
                }
                
                m_oS->Internal.results[0]   = strcmp(m_oS->PLAYER1_NAME, "");
                m_oS->Internal.results[1]   = strcmp(m_oS->PLAYER2_NAME, "");
                
                if(m_oS->start_measurement == 1 && m_oS->Error == 0){
                    if(m_oS->Internal.results[0] == 0 && m_oS->Internal.results[1] == 0){
                        m_oS->Internal.auxiliary_str[5] = (UDINT) strcpy(m_oS->PLAYER1_NAME,"PLAYER 1");
                        m_oS->Internal.auxiliary_str[6] = (UDINT) strcpy(m_oS->PLAYER2_NAME,"PLAYER 2");
                    }
                    // CPU NAME
                    m_oS->Internal.auxiliary_str[7] = (UDINT) strcpy(m_oS->team_nameCPU,"B&R ROBOT");
                    // HUMAN NAME
                    strcpy(m_oS->Internal.string[5],m_oS->PLAYER1_NAME);
                    strcpy(m_oS->Internal.string[6]," \n \t& \n");
                    strcpy(m_oS->Internal.string[8], m_oS->PLAYER2_NAME);
                    m_oS->Internal.auxiliary_str[8] = (UDINT) strcat(m_oS->Internal.string[5], m_oS->Internal.string[6]);
                    strcpy(m_oS->Internal.string[7], m_oS->Internal.string[5]);
                    m_oS->Internal.auxiliary_str[9] = (UDINT) strcat(m_oS->Internal.string[7], m_oS->Internal.string[8]);
                    m_oS->Internal.auxiliary_str[10] = (UDINT) strcpy(m_oS->team_nameHUM,m_oS->Internal.auxiliary_str[9]);
                    // CHANGE STATE
                    m_oS->Internal.state = 1;
                }else if(m_oS->Error == 1){
                    m_oS->Internal.state = 5;
                }else if(m_oS->pause == 1){
                    m_oS->Internal.before_state = m_oS->Internal.state;
                    m_oS->Internal.state = 6;
                }else{
                    m_oS->Internal.state = 0;
                }
            }
            break;
        case 1:
            {
                if(m_oS->sens_wicket_CPU == 1){
                    m_oS->count_goals_CPU++;
                    m_oS->sens_wicket_CPU = 0;
                }
                
                if(m_oS->sens_wicket_HUM == 1){
                    m_oS->count_goals_HUM++;
                    m_oS->sens_wicket_HUM = 0;
                }
                
                if((m_oS->count_goals_HUM - m_oS->count_goals_CPU) == 0){
                    m_oS->probability_CPU = 50;
                    m_oS->probability_HUM = 50;
                }else if((m_oS->count_goals_HUM - m_oS->count_goals_CPU) < 0){
                    if(fabs((m_oS->count_goals_HUM - m_oS->count_goals_CPU)) <= 5){
                        m_oS->probability_CPU = 50 + fabs((m_oS->count_goals_HUM - m_oS->count_goals_CPU))*10;
                        m_oS->probability_HUM = 100 - m_oS->probability_CPU;
                    }else{
                        m_oS->probability_CPU = 100;
                        m_oS->probability_HUM = 0;
                    }
                }else{
                    if(fabs((m_oS->count_goals_HUM - m_oS->count_goals_CPU)) <= 5){
                        m_oS->probability_HUM = 50 + fabs((m_oS->count_goals_HUM - m_oS->count_goals_CPU))*10;
                        m_oS->probability_CPU = 100 - m_oS->probability_HUM;
                    }else{
                        m_oS->probability_HUM = 100;
                        m_oS->probability_CPU = 0;
                    }
                }
				if(((m_oS->count_goals_CPU + m_oS->count_goals_HUM) == 10) && m_oS->Error == 0){
					if(m_oS->count_goals_CPU > m_oS->count_goals_HUM){
						m_oS->Internal.WINNER++;
					}else if(m_oS->count_goals_CPU == m_oS->count_goals_HUM){
						m_oS->Internal.DRAW++;
					}else if(m_oS->count_goals_CPU < m_oS->count_goals_HUM){
						m_oS->Internal.LOSE++;
					}
					// change state
					m_oS->Internal.state             = 2;
					m_oS->Internal.write_matchInfo   = 1;
				}else if(m_oS->exit_game == 1 ){
                    m_oS->Internal.state = 3;
                }else if(m_oS->restart_measurement == 1){
                    m_oS->Internal.state = 4;
                }else if(m_oS->Error == 1){
                    m_oS->Internal.state = 5;
                }else if(m_oS->pause == 1){
                    m_oS->Internal.before_state = m_oS->Internal.state;
                    m_oS->Internal.state = 6;
                }else{
                    m_oS->Internal.state = 1;
                }
                
            }
            break;
        case 2:
            {
                if(m_oS->Internal.write_matchInfo == 1){                  
                    // call FB : Get time and date
                    m_oS->Internal.UtcDTStructureGetTime_1.enable = 1;
                    m_oS->Internal.UtcDTStructureGetTime_1.pDTStructure = (UDINT) &m_oS->Internal.DTStruct;
                    UtcDTStructureGetTime(&m_oS->Internal.UtcDTStructureGetTime_1);   
                    ascDTStructure((UDINT) &m_oS->Internal.DTStruct, (UDINT) &m_oS->Internal.string[0], m_oS->Internal.length);
                    // write time and date into the variable
                    m_oS->Internal.auxiliary_str[0] = (UDINT) strcpy(m_oS->match_informations.date[m_oS->Internal.counter],m_oS->Internal.string[0]);
                    // write score
                    m_oS->match_informations.score_CPU[m_oS->Internal.counter] = m_oS->count_goals_CPU;
                    m_oS->match_informations.score_HUM[m_oS->Internal.counter] = m_oS->count_goals_HUM;
                    // write name of B&R team
                    m_oS->Internal.auxiliary_str[1] = (UDINT) strcpy(m_oS->match_informations.team_name_CPU[m_oS->Internal.counter],"B&R ROBOT");
                    // write names of both players
                    strcpy(m_oS->Internal.string[1],m_oS->PLAYER1_NAME);
                    strcpy(m_oS->Internal.string[2]," & ");
                    strcpy(m_oS->Internal.string[4], m_oS->PLAYER2_NAME);
                    m_oS->Internal.auxiliary_str[2] = (UDINT) strcat(m_oS->Internal.string[1], m_oS->Internal.string[2]);
                    strcpy(m_oS->Internal.string[3], m_oS->Internal.string[1]);
                    m_oS->Internal.auxiliary_str[3] = (UDINT) strcat(m_oS->Internal.string[3], m_oS->Internal.string[4]);
                    m_oS->Internal.auxiliary_str[4] = (UDINT) strcpy(m_oS->match_informations.team_name_HUM[m_oS->Internal.counter],m_oS->Internal.auxiliary_str[3]);
                    
                    m_oS->Internal.counter++;
                    m_oS->Internal.write_matchInfo = 0;           
                }
                
                if(m_oS->exit_game == 1){
                    m_oS->Internal.state = 3;
                }else if(m_oS->restart_measurement == 1){
                    m_oS->Internal.state = 4;
                }else if(m_oS->Error == 1){
                    m_oS->Internal.state = 5;
                }else if(m_oS->pause == 1){
                    m_oS->Internal.before_state = m_oS->Internal.state;
                    m_oS->Internal.state = 6;
                }else{
                    m_oS->Internal.state = 2;
                }
            }
            break;
        case 3:
            {
                // exit game
                m_oS->start_measurement   = 0;
                m_oS->exit_game           = 0;
                m_oS->restart_measurement = 0;
                m_oS->count_goals_CPU     = 0;
                m_oS->count_goals_HUM     = 0;
            
                m_oS->Internal.e_r_str[0] = (UDINT) strcpy(m_oS->PLAYER1_NAME,"");
                m_oS->Internal.e_r_str[1] = (UDINT) strcpy(m_oS->PLAYER2_NAME,"");
                
                if(m_oS->Error == 1){
                    m_oS->Internal.state = 5;
                }else if(m_oS->pause == 1){
                    m_oS->Internal.before_state = m_oS->Internal.state;
                    m_oS->Internal.state = 6;
                }else{
                    m_oS->Internal.state = 0;
                }
            }
            break;
        case 4:
            {
                // restart game
                m_oS->start_measurement   = 0;
                m_oS->exit_game           = 0;
                m_oS->restart_measurement = 0;
                m_oS->count_goals_CPU     = 0;
                m_oS->count_goals_HUM     = 0;
            
                m_oS->Internal.e_r_str[2] = (UDINT) strcpy(m_oS->PLAYER1_NAME,m_oS->PLAYER1_NAME);
                m_oS->Internal.e_r_str[3] = (UDINT) strcpy(m_oS->PLAYER2_NAME,m_oS->PLAYER2_NAME);
                
                if(m_oS->Error == 1){
                    m_oS->Internal.state = 5;
                }else if(m_oS->pause == 1){
                    m_oS->Internal.before_state = m_oS->Internal.state;
                    m_oS->Internal.state = 6;
                }else{
                    m_oS->Internal.state = 1;
                }
            }
            break;
        case 5:
            {
                // error state
                if(m_oS->Error == 0){
                    m_oS->Internal.state = 3;
                }else if(m_oS->pause == 1){
                    m_oS->Internal.before_state = m_oS->Internal.state;
                    m_oS->Internal.state = 6;
                }
            }
            break;
        case 6:
            {
                // pause
                if(m_oS->Error == 1){
                    m_oS->Internal.state = 5;
                }else if(m_oS->pause == 0){
                    m_oS->Internal.state = m_oS->Internal.before_state;
                }
            }
            break;
    }// end switch
    
}// end fucntion

void initialization(struct measurement_ofScore* m_oS){
    m_oS->Internal.state             = 0;
    m_oS->Internal.e_r_str[0]        = 0;
    m_oS->Internal.e_r_str[1]        = 0;
    m_oS->Internal.e_r_str[2]        = 0;
    m_oS->Internal.e_r_str[3]        = 0;
    m_oS->Internal.auxiliary_str[0]  = 0;
    m_oS->Internal.auxiliary_str[1]  = 0;
    m_oS->Internal.auxiliary_str[2]  = 0;
    m_oS->Internal.auxiliary_str[3]  = 0;
    m_oS->Internal.auxiliary_str[4]  = 0;
    m_oS->Internal.auxiliary_str[5]  = 0;
    m_oS->Internal.auxiliary_str[6]  = 0;
    m_oS->Internal.auxiliary_str[7]  = 0;
    m_oS->Internal.auxiliary_str[8]  = 0;
    m_oS->Internal.auxiliary_str[9]  = 0;
    m_oS->Internal.auxiliary_str[10] = 0;
    m_oS->Internal.counter           = 0;
    m_oS->Internal.length            = 25;
    m_oS->Internal.write_matchInfo   = 0;
    m_oS->Internal.results[0]        = 0;
    m_oS->Internal.results[1]        = 0;
	m_oS->Internal.before_state      = 0;
	m_oS->Internal.WINNER			 = 0;
	m_oS->Internal.DRAW			     = 0;
	m_oS->Internal.LOSE				 = 0;
    m_oS->count_goals_CPU            = 0;
    m_oS->count_goals_HUM            = 0;
    m_oS->sens_wicket_HUM            = 0;
    m_oS->restart_measurement        = 0;
    m_oS->pause                      = 0;
    m_oS->exit_game                  = 0;
    m_oS->start_measurement          = 0;
    m_oS->probability_CPU            = 50;
    m_oS->probability_HUM            = 50;
}// end function