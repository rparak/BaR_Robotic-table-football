%% Matlab simulation
% Author Name  : Roman Parak 
% University   : Brno University of Technology
% Faculty      : Faculty of Mechanical Engineering
% Institute    : Institute of Automation and Computer Science
% Project Name : Master's Thesis - Robotic table football - game strategy

function [attack_mode,idxOfAxis] = check_attack_mode(disp,angle_ofRot,ball_old, ball_new)
    % ball_old = ball1, ball_new = ball2
    [r_disp,gk_posOD,df_posOD,md_posOD,fw_posOD] = calculation_posDummies(disp);
    [axis_num] = detect_axisNum(ball_old,ball_new);
    
    if axis_num ~= 5
        if angle_ofRot(axis_num) > 0
            % stand before the ball
            behind_pos = -100;
            before_pos = 100;
            stand_mode = 1;
        else
            % stand behind the ball
            behind_pos = -100;
            before_pos = 370;
            stand_mode = 2;
        end
        
        [mode]       = choose_attack_mode(axis_num,behind_pos,before_pos,ball_old,ball_new, gk_posOD,df_posOD,md_posOD,fw_posOD);
        if mode == 1 && stand_mode == 1
            attack_mode = 1; % attack mode If ball is before of dummy
        elseif mode == 1 && stand_mode == 2
            attack_mode = 2; % attack mode If ball is behind of dummy
        else
            attack_mode = 0; % If ball it isn't near of dummy
        end
        idxOfAxis    = axis_num;
    else
        attack_mode  = 0;
        idxOfAxis    = 0;
    end
end

function [axis_num] = detect_axisNum(ball_old,ball_new)

    x_posOfD = [800 2300 5300 8300];
    x = [ball_old(1) ball_new(1)];
    
    for i=1:length(x)
        if x(i) >= (x_posOfD(4) - 100)
            a_n(i) = 4;
        elseif x(i) >= (x_posOfD(3) - 100) && x(i) <= (x_posOfD(4) - 100)
            a_n(i) = 3;
        elseif x(i) >= (x_posOfD(2) - 100) && x(i) <= (x_posOfD(3) - 100)
            a_n(i) = 2;
        elseif x(i) >= (x_posOfD(1) - 100) && x(i) <= (x_posOfD(2) - 100)
            a_n(i) = 1;
        else
            a_n(i) = 5;
        end
    end
    
    if (a_n(1) == a_n(2)) || isnan(ball_new(1))
        axis_num = a_n(1);
    else
        axis_num = a_n(2);
    end
end

function [mode] = choose_attack_mode(axis_num,behind_pos,before_pos,ball_old,ball_new, gk_posOD,df_posOD,md_posOD,fw_posOD)
% supplement
    aux_mode = 0;
    x_posOfD = [800 2300 5300 8300];
    switch(axis_num)
        case 1
            % goalkeeper
            for i=1:length(gk_posOD)
                if ((((ball_old(1) <= x_posOfD(axis_num)+before_pos && ball_old(1) >= x_posOfD(axis_num)+behind_pos)...
                        || (ball_new(1) <= x_posOfD(axis_num)+before_pos && ball_new(1) >= x_posOfD(axis_num)+behind_pos))...
                        &&((ball_old(2) <= gk_posOD(i)+100 && ball_old(2) >= gk_posOD(i)-100)...
                        || (ball_new(2) <= gk_posOD(i)+100 && ball_new(2) >= gk_posOD(i)-100))))
                    aux_mode = 1;
                end
            end
            if aux_mode == 1
                mode = aux_mode;
            else
                mode = 0;
            end
        case 2
            % defender
            for i=1:length(df_posOD)
                if ((((ball_old(1) <= x_posOfD(axis_num)+before_pos && ball_old(1) >= x_posOfD(axis_num)+behind_pos)...
                        || (ball_new(1) <= x_posOfD(axis_num)+before_pos && ball_new(1) >= x_posOfD(axis_num)+behind_pos))...
                        &&((ball_old(2) <= df_posOD(i)+100 && ball_old(2) >= df_posOD(i)-100)...
                        || (ball_new(2) <= df_posOD(i)+100 && ball_new(2) >= df_posOD(i)-100))))
                    aux_mode = 1;
                end
            end
            if aux_mode == 1
                mode = aux_mode;
            else
                mode = 0;
            end
        case 3
            % midfielder
            for i=1:length(md_posOD)
                if ((((ball_old(1) <= x_posOfD(axis_num)+before_pos && ball_old(1) >= x_posOfD(axis_num)+behind_pos)...
                        || (ball_new(1) <= x_posOfD(axis_num)+before_pos && ball_new(1) >= x_posOfD(axis_num)+behind_pos))...
                        &&((ball_old(2) <= md_posOD(i)+100 && ball_old(2) >= md_posOD(i)-100)...
                        || (ball_new(2) <= md_posOD(i)+100 && ball_new(2) >= md_posOD(i)-100))))
                    aux_mode = 1;
                end
            end
            if aux_mode == 1
                mode = aux_mode;
            else
                mode = 0;
            end
        case 4
            % forward
            for i=1:length(fw_posOD)
                if ((((ball_old(1) <= x_posOfD(axis_num)+before_pos && ball_old(1) >= x_posOfD(axis_num)+behind_pos)...
                        || (ball_new(1) <= x_posOfD(axis_num)+before_pos && ball_new(1) >= x_posOfD(axis_num)+behind_pos))...
                        &&((ball_old(2) <= fw_posOD(i)+100 && ball_old(2) >= fw_posOD(i)-100)...
                        || (ball_new(2) <= fw_posOD(i)+100 && ball_new(2) >= fw_posOD(i)-100))))
                    aux_mode = 1;
                end
            end
            if aux_mode == 1
                mode = aux_mode;
            else
                mode = 0;
            end
    end
end