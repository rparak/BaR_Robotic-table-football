%% Matlab simulation
% Author Name  : Roman Parak 
% University   : Brno University of Technology
% Faculty      : Faculty of Mechanical Engineering
% Institute    : Institute of Automation and Computer Science
% Project Name : Master's Thesis - Robotic table football - game strategy

clc
clear
close all

%% Rectangles
% main - play ground
rectangle('Position',[0 -3515 12100 7030],'EdgeColor','k',...
    'LineWidth',0.1);
% soccer goal no.1
rectangle('Position',[-200 -1065 200 2150],'EdgeColor','k',...
    'LineWidth',0.1);
% soccer goal no.2
rectangle('Position',[12100 -1065 200 2150],'EdgeColor','k',...
    'LineWidth',0.1);
%% Lines
line([100 1700 10400 12000],[7030-3515 3065 3065 7030-3515],'LineWidth',.1,...
   'Color',[0 0 0]);
line([100 1700 10400 12000],[0-3515 -3065 -3065 0-3515],'LineWidth',.1,...
   'Color',[0 0 0]);
line([1700 0 0 1700],[450-3515 2550-3515 4500-3515 3065],'LineWidth',.1,...
   'Color',[0 0 0]);
line([10400 12100 12100 10400],[450-3515 2550-3515 4500-3515 3065],'LineWidth',.1,...
   'Color',[0 0 0]);
%% Levers of dummies - computer(B&R)
% goalkeeper
line([800 800],[0-3515 7030-3515],'LineWidth',2,...
   'Color',[0 0 0]);
rectangle('Position',[740 3415-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
% defender
line([2300 2300],[0-3515 7030-3515],'LineWidth',2,...
   'Color',[0 0 0]);
rectangle('Position',[2240 4615-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[2240 2215-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
% midfielder
line([5300 5300],[0-3515 7030-3515],'LineWidth',2,...
   'Color',[0 0 0]);
rectangle('Position',[5240 3415-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[5240 4615-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[5240 5815-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[5240 2215-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[5240 1015-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
% forward
line([8300 8300],[0-3515 7030-3515],'LineWidth',2,...
   'Color',[0 0 0]);
rectangle('Position',[8240 3415-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[8240 5515-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[8240 1315-3515 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
    'LineWidth',0.1);
%% Levers of dummies - human
% goalkeeper
line([11300 11300],[0-3515 7030-3515],'LineWidth',2,...
   'Color',[0 0 0]);
rectangle('Position',[11240 3415-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);
% defender
line([9800 9800],[0-3515 7030-3515],'LineWidth',2,...
   'Color',[0 0 0]);
rectangle('Position',[9740 4615-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[9740 2215-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);
% midfielder
line([6800 6800],[0-3515 7030-3515],'LineWidth',2,...
   'Color',[0 0 0]);
rectangle('Position',[6740 3415-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[6740 4615-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[6740 5815-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1)
rectangle('Position',[6740 2215-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[6740 1015-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);
% forward
line([3800 3800],[0-3515 7030-3515],'LineWidth',2,...
   'Color',[0 0 0]);
rectangle('Position',[3740 3415-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[3740 5515-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);
rectangle('Position',[3740 1315-3515 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
    'LineWidth',0.1);

%% Forecast direction and plotting
hold on
param_ballNo1 = [3500 1200];
param_ballNo2 = [nan nan];
time_B2B      = nan;

[specific_direction,direction,s_x,s_y,f_x,f_y] = calculation_forecastDirectionBall(param_ballNo1,param_ballNo2);
%% Calculation positions of the dummies {defense}
% CPU
CPU_pos = [800 2300 5300 8300];
[c_dCPU,time_axisIntersection_CPU,overall_velocity_CPU,x_posOfD_CPU,y_posOfD_CPU] = calculation_crossingBall(CPU_pos,time_B2B,direction,...
    param_ballNo1(1),param_ballNo1(2),...
    param_ballNo2(1),param_ballNo2(2),...
    f_x,f_y,...
    s_x,s_y);
% HUMAN
HUMAN_pos = [3800 6800 9800 11300];
[c_dHUM,time_axisIntersection_HUMAN,overall_velocity_HUMAN,x_posOfD_HUMAN,y_posOfD_HUMAN] = calculation_crossingBall(HUMAN_pos,time_B2B,direction,...
    param_ballNo1(1),param_ballNo1(2),...
    param_ballNo2(1),param_ballNo2(2),...
    f_x,f_y,...
    s_x,s_y);
hold off
%% Plot actual positions
cla reset;
hold on
%% calculation positions of the dummies opponent
% input parameters
% displacement
dispH_gk = 0; % max 1000, min -1000
dispH_df = 0; % max 1850, min -1850
dispH_md = 0; % max 650, min -650
dispH_fw = 0; % max 975, min -975
% reversed {1/0}
r_gk = 1;
r_df = 1;
r_md = 1;
r_fw = 1;
reversed_HUMAN = [r_gk r_df r_md r_fw];
% calculation 
displacemet_HUMAN                            = [dispH_gk dispH_df dispH_md dispH_fw];
[r_disp,gk_posOD,df_posOD,md_posOD,fw_posOD] = calculation_posDummies(displacemet_HUMAN);
pos_dummiesHUMAN = [gk_posOD df_posOD md_posOD fw_posOD];
%% calculation displacement of the individual axes CPU
% input
act_displacementGK      = 0;
act_dispdisplacementDF  = 0;
act_dispdisplacementMD  = 0;
act_dispdisplacementFW  = 0;
act_displacementCPU     = [act_displacementGK act_dispdisplacementDF act_dispdisplacementMD act_dispdisplacementMD];
% calculation
x_posOfBall = [param_ballNo1(1) param_ballNo2(1)];
t_n = time_axisIntersection_CPU*0.2; %% supplement into the ansi C program
[displacement_CPU,velocity_CPU,acceleration_CPU,deceleration_CPU] = calculation_displacementAxesCPU(direction,specific_direction,c_dCPU,c_dHUM,y_posOfD_CPU,t_n,...
    act_displacementCPU,reversed_HUMAN,pos_dummiesHUMAN,flip(y_posOfD_HUMAN),x_posOfBall);
angle_ofRot = [-300 -300 -300 -300];
[attack_mode,idxOfAxis] = check_attack_mode(displacement_CPU,angle_ofRot,param_ballNo1, param_ballNo2);
%% Actual plot
% input
CPU_BR = [displacement_CPU(1) displacement_CPU(2) displacement_CPU(3) displacement_CPU(4)];
HUMAN  = [r_disp(1) r_disp(2) r_disp(3) r_disp(4)];
% plot
draw_actual_state(CPU_BR,HUMAN,param_ballNo1,param_ballNo2,f_x,f_y,s_x,s_y,x_posOfD_CPU,y_posOfD_CPU,x_posOfD_HUMAN,y_posOfD_HUMAN);
hold off


