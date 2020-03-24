%% Matlab simulation
% Author Name  : Roman Parak 
% University   : Brno University of Technology
% Faculty      : Faculty of Mechanical Engineering
% Institute    : Institute of Automation and Computer Science
% Project Name : Master's Thesis - Robotic table football - game strategy

function [disp,v,a,d] = calculation_displacementAxesCPU(direction,specific_direction,c_dCPU,c_dHUM,y_posCrossing,t_posCrossing,act_dispCPU,reversed_human,pos_dummiesHUMAN,y_posCrossingH,x_posOfBall)
%%% Description of function
%% < input >
% y_posCrossing    -> y positions of dummies at the crossing with the ball
% t_posCrossing    -> time at the crossing with the ball
% act_dispCPU      -> actual displacement of the goalkeeper
% reversed_human   -> reversed of axes {1/0} : bool function
% pos_dummiesHUMAN -> positions of dummies(Human player) individual axes
% y_posCrossingH   -> y positions of crossing Human axes
% direction        -> direction of ball
%% < output >
% disp             -> displacement of individual axes(CPU)
% v                -> velocity 
% a                -> acceleration
% d                -> deceleration
%% Parameters
    auxiliary_disp = [0 0 0 0]; % auxiliary variable for displacements
    % Ceilings of the axes
    % Axes
    max_pos = [820 3050 3050 3055]; % maximum displacements of individual axes
    min_pos = [-950 -3050 -3050 -3055]; % minimum displacements of individual axes
    % Dummies
    max_posDummies = [820 1850 650 955]; % maximum displacements of individual axes
    min_posDummies = [-950 -1850 -650 -955]; % minimum displacements of individual axes
    % matrix of the actual positions at the individual axes
    % CPU
    matrix_posOfCPU = [0+act_dispCPU(1) 0 0 0 0;...
        -1200+act_dispCPU(2) 1200+act_dispCPU(2) 0 0 0;...
        -2400+act_dispCPU(3) -1200+act_dispCPU(3) 0+act_dispCPU(3) 1200+act_dispCPU(3) 2400+act_dispCPU(3);...
        -2100+act_dispCPU(4) 0+act_dispCPU(4) 2100+act_dispCPU(4) 0 0];
    
%% Calculation

    real_cross = calculation_realCrossing(direction,specific_direction,c_dCPU,c_dHUM,y_posCrossing,reversed_human,pos_dummiesHUMAN,y_posCrossingH,x_posOfBall);
    
    for i = 1:length(real_cross)
        for j = 1:length(matrix_posOfCPU(1,:))
            if real_cross(i) > max_pos(i)
               act_disp(i) = max_posDummies(i);       
            elseif real_cross(i) < min_pos(i)
               act_disp(i) = min_posDummies(i);
            else
              [aux_disp] = calculation_actual_valuesOfAxes(i,real_cross(i),max_pos,min_pos,...
                  max_posDummies,min_posDummies,matrix_posOfCPU);              
              act_disp(i) = aux_disp(i);
            end
        end
    end 
    
%% real disp
    disp  = [act_disp(1) act_disp(2) act_disp(3) act_disp(4)];
    
    for i = 1:length(y_posCrossing)
        if (isnan(t_posCrossing(i)))
            % supplement
            v(i) = abs(abs(disp(i)) - abs(act_dispCPU(i))) / 0.019;
            a(i) = v(i)/0.019;
            d(i) = a(i);
        else
            v(i) = abs(abs(disp(i)) - abs(act_dispCPU(i))) / t_posCrossing(i);
            a(i) = v(i)/t_posCrossing(i);
            d(i) = a(i);
        end
    end
end

function [act_disp] = calculation_actual_valuesOfAxes(index,y_crossing,max_p,min_p,max_pDummies,min_pDummies,matrix_posDummies)
%%% Description of function
%% < input >
% index             ->
% y_crossing        ->
% max_p             ->
% min_p             ->
% max_pDummies      ->
% min_pDummies      ->
% matrix_posDummies ->
%% < output >
% act_disp          -> displacement of individual axes(CPU)
%% Parameters
    initial_state = index;
%% Calculation
    switch initial_state
        case 1
            %% calculation for GK(goalkeeper)
            act_disp(index) = y_crossing;
        case 2
            %% calculation for DF(defender)
            df_d1 = matrix_posDummies(2,1);
            df_d2 = matrix_posDummies(2,2);
            
            d_DFD1 = abs(df_d1) + y_crossing;
            d_DFD2 = df_d2 - y_crossing;
            
            [d_DFD,idDF] = calculate_min(abs([d_DFD1 d_DFD2]));
            
            if d_DFD > max_pDummies(index)
                d_DFD = max_pDummies(index)
            elseif d_DFD < min_pDummies(index)
                d_DFD = min_pDummies(index)
            end
            
            switch idDF
                case 1
                    if y_crossing > matrix_posDummies(2,idDF)
                        act_disp(index) = d_DFD;
                    else
                        act_disp(index) = -d_DFD;
                    end
                case 2
                    if y_crossing > matrix_posDummies(2,idDF)
                        act_disp(index) = d_DFD;
                    else
                        act_disp(index) = -d_DFD;
                    end
            end
            
        case 3
            %% calculation for MD(mildfielder)
            md_d1 = matrix_posDummies(3,1);
            md_d2 = matrix_posDummies(3,2);
            md_d3 = matrix_posDummies(3,3);
            md_d4 = matrix_posDummies(3,4);
            md_d5 = matrix_posDummies(3,5);
            
            d_MDD1 = abs(md_d1) + y_crossing;
            d_MDD2 = abs(md_d2) + y_crossing;
            d_MDD3 = y_crossing;
            d_MDD4 = md_d4 - y_crossing;
            d_MDD5 = md_d5 - y_crossing;
            
            [d_MDD,idMD] = calculate_min(abs([d_MDD1 d_MDD2 d_MDD3 d_MDD4 d_MDD5]));
            
            if d_MDD > max_pDummies(index)
                d_MDD = max_pDummies(index);
            elseif d_MDD < min_pDummies(index)
                d_MDD = min_pDummies(index);
            end
            
            switch idMD
                case 1
                    if y_crossing > matrix_posDummies(3,idMD)
                        act_disp(index) = d_MDD;
                    else
                        act_disp(index) = -d_MDD;
                    end
                case 2
                    if y_crossing > matrix_posDummies(3,idMD)
                        act_disp(index) = d_MDD;
                    else
                        act_disp(index) = -d_MDD;
                    end
                case 3
                    if y_crossing > matrix_posDummies(3,idMD)
                        act_disp(index) = d_MDD;
                    else
                        act_disp(index) = -d_MDD;
                    end
                case 4
                    if y_crossing > matrix_posDummies(3,idMD)
                        act_disp(index) = d_MDD;
                    else
                        act_disp(index) = -d_MDD;
                    end
                case 5
                    if y_crossing > matrix_posDummies(3,idMD)
                        act_disp(index) = d_MDD;
                    else
                        act_disp(index) = -d_MDD;
                    end
            end
            
        case 4
            %% calculation for FW(forward)
            fw_d1 = matrix_posDummies(4,1);
            fw_d2 = matrix_posDummies(4,2);
            fw_d3 = matrix_posDummies(4,3);
            
            d_FWD1 = abs(fw_d1) + y_crossing;
            d_FWD2 = y_crossing;
            d_FWD3 = fw_d3 - y_crossing;         
            
            [d_FWD,idFW] = calculate_min(abs([d_FWD1 d_FWD2 d_FWD3]));
            
            if d_FWD > max_pDummies(index)
                d_FWD = max_pDummies(index);
            elseif d_FWD < min_pDummies(index)
                d_FWD = min_pDummies(index);
            end
            
            switch idFW
                case 1
                    if y_crossing > matrix_posDummies(4,idFW)
                        act_disp(index) = d_FWD;
                    else
                        act_disp(index) = -d_FWD;
                    end
                case 2
                    if y_crossing > matrix_posDummies(4,idFW)
                        act_disp(index) = d_FWD;
                    else
                        act_disp(index) = -d_FWD;
                    end
                case 3
                    if y_crossing > matrix_posDummies(4,idFW)
                        act_disp(index) = d_FWD;
                    else
                        act_disp(index) = -d_FWD;
                    end
            end
    end
end

function [m,index] = calculate_min(numbers)
    min = 99999;
    idx = 555;
    
    for i = 1:length(numbers)
        if numbers(i) < min
            min = numbers(i);
            idx = i;
        end
    end    
    m     = min;
    index = idx;
end

function real_cross = calculation_realCrossing(dir,specific_direction,c_s,c_sH,y_posCrossing,reversed_human,pos_dummiesHUMAN,y_posCrossingH,x_posOfBall)
    
    gk_posH = pos_dummiesHUMAN(1);
    df_posH = pos_dummiesHUMAN(2:3);
    md_posH = pos_dummiesHUMAN(4:8);
    fw_posH = pos_dummiesHUMAN(9:11);
    a          = 0;
    reversed_d = 1;
    num_of_d       = [1 2 5 3];
    count_crossCPU = c_s(1); % calculate
    count_crossH   = c_sH(1);
    
    count_calculateH = 5 - count_crossH;
    % supplement 
    matrix_posOfHUMAN = [gk_posH(1) 0 0 0 0;...
                         df_posH(1) df_posH(2) 0 0 0;...
                         md_posH(1) md_posH(2) md_posH(3) md_posH(4) md_posH(5);...
                         fw_posH(1) fw_posH(2) fw_posH(3) 0 0];
    iter = count_calculateH;

    if iter == 0
       iter = 1;
    end

    if count_calculateH < 5
        for i = count_calculateH:count_calculateH
            N = num_of_d(i);
            for j = 1:N
                if (reversed_human(i) == 0)
                   if ((matrix_posOfHUMAN(i,j) <= (y_posCrossingH(i) + 100) && (matrix_posOfHUMAN(i,j) >= y_posCrossingH(i))) && (matrix_posOfHUMAN(i,j) ~= y_posCrossingH(i)))
                       matrix_crossH_Iter(i,j) = i;
                       matrix_crossH_Pos(i,j)  = abs(abs(matrix_posOfHUMAN(i,j)) - abs(y_posCrossingH(i)));
                   elseif ((matrix_posOfHUMAN(i,j) >= (y_posCrossingH(i) - 100) && (matrix_posOfHUMAN(i,j) <= y_posCrossingH(i))) && (matrix_posOfHUMAN(i,j) ~= y_posCrossingH(i)))
                       matrix_crossH_Iter(i,j) = i;
                       matrix_crossH_Pos(i,j)  = (-1)*abs(abs(matrix_posOfHUMAN(i,j)) - abs(y_posCrossingH(i)));
                   elseif (matrix_posOfHUMAN(i,j) == y_posCrossingH(i))
                       matrix_crossH_Iter(i,j) = i;
                       matrix_crossH_Pos(i,j)  = 0;
                   else
                       matrix_crossH_Iter(i,j) = 0;
                       matrix_crossH_Pos(i,j)  = 0;
                   end
                else
                   matrix_crossH_Iter(i,j) = 0;
                   matrix_crossH_Pos(i,j)  = 0;
                end
            end
        end
        
        for i = count_calculateH:count_calculateH
            for j = 1:N
                if matrix_crossH_Iter(i,j) ~= 0
                    reversed_d = 0;
                end
            end
        end

        for k = (count_calculateH+1):length(y_posCrossing)
            for l = 1:length(matrix_crossH_Iter(1,:))
               matrix_crossH_Iter(k,l) = 0;
               matrix_crossH_Pos(k,l)  = 0;
            end
        end

        for i = 1:length(y_posCrossing)
           for j = 1:length(matrix_crossH_Iter(1,:))
              if matrix_crossH_Iter(i,j) ~= 0
                  a = 1;
                  y_newCrossing = calc_newCross(specific_direction,matrix_posOfHUMAN,reversed_d,matrix_crossH_Iter(i,j),matrix_crossH_Pos(i,j),y_posCrossing,y_posCrossingH,x_posOfBall);
              end   
           end
        end

        if a == 0
            if dir == 0
              predicted_pos = 0;
              y_nCross      = calc_newCross(specific_direction,matrix_posOfHUMAN,reversed_d,iter,predicted_pos,y_posCrossing,y_posCrossingH,x_posOfBall);
              real_cross    = [y_nCross(1) y_nCross(2) y_nCross(3) y_nCross(4)];
            else
              real_cross = [y_posCrossing(1) y_posCrossing(2) y_posCrossing(3) y_posCrossing(4)];
            end
        else 
             real_cross = [y_newCrossing(1) y_newCrossing(2) y_newCrossing(3) y_newCrossing(4)] ;
        end
    else
        if dir == 0
           reversed_d    = 0;
           predicted_pos = 0;
           y_nCross      = calc_newCross(specific_direction,matrix_posOfHUMAN,reversed_d,count_calculateH,predicted_pos,y_posCrossing,y_posCrossingH,x_posOfBall);
           real_cross    = [y_nCross(1) y_nCross(2) y_nCross(3) y_nCross(4)];
        else
           real_cross = [y_posCrossing(1) y_posCrossing(2) y_posCrossing(3) y_posCrossing(4)];
        end
        
    end
end


function y_nCross = calc_newCross(specific_direction,matrix_posOfHUMAN,reversed_d,iteration,predicted_pos,y_posCrossing,y_posCrossingH,x_posOfBall)
    
    gk_max = 1000;
    gk_min = -1000;
    if isequal(specific_direction,'up_backward') || isequal(specific_direction,'left')
        value = 200;
    elseif isequal(specific_direction,'down_backward') || isequal(specific_direction,'right')
        value = -200;
    else
        value = 200;
    end
    
    if iteration > 4
        iteration = 4;
    end
    
    switch(iteration)
        case 1
            y_cross_fw = y_posCrossing(4);
            y_cross_md = y_cross_fw + value;
            y_cross_df = y_cross_md + value;
            y_cross_gk = y_cross_fw + value;
                
            if abs(y_cross_gk) > abs(y_cross_fw)
                y_cross_df = y_cross_fw - value;
            end
            
            if abs(y_cross_md) < abs(y_cross_fw)
                y_cross_md = y_cross_fw - value;
                y_cross_df = y_cross_md - value;
            end
        case 2
            if ((x_posOfBall(1)) > 9800)
                y_cross_fw = y_posCrossingH(iteration) - predicted_pos;
                y_cross_md = y_cross_fw + value;
                y_cross_df = y_cross_md + value;
                y_cross_gk = y_cross_fw + value;
                
                if abs(y_cross_gk) > abs(y_cross_fw)
                    y_cross_gk = y_cross_fw - value;
                end
                if abs(y_cross_md) < abs(y_cross_fw)
                    y_cross_md = y_cross_fw - value;
                    y_cross_df = y_cross_md - value;
                end
            else
                y_cross_fw = y_posCrossing(4) - predicted_pos;
                y_cross_md = y_cross_fw + value;
                y_cross_df = y_cross_md + value;
                y_cross_gk = y_cross_fw + value;
                if abs(y_cross_gk) > abs(y_cross_fw)
                    y_cross_gk = y_cross_fw - value;
                end
                if abs(y_cross_md) < abs(y_cross_fw)
                    y_cross_md = y_cross_fw - value;
                    y_cross_df = y_cross_md - value;
                end
                
            end
            
        case 3
            if reversed_d == 1
                y_cross_fw = y_posCrossing(4) - predicted_pos;
                y_cross_md = y_cross_fw + value;
            else
                y_cross_fw = y_posCrossing(4) - predicted_pos;
                y_cross_md = y_posCrossing(3) - predicted_pos;
            end

            y_cross_df = y_cross_md + value;
            y_cross_gk = y_cross_fw + value;
                
            if abs(y_cross_gk) > abs(y_cross_fw)
                y_cross_gk = y_cross_fw - value;
            end
            
            if abs(y_cross_df) < abs(y_cross_md)
                y_cross_md = y_cross_fw - value;
                y_cross_df = y_cross_md - value;
            end
        case 4
            if ((x_posOfBall(1)) > 5300)
                if reversed_d == 1
                    y_cross_fw = y_posCrossing(4) - predicted_pos;
                    y_cross_md = y_posCrossing(3) - predicted_pos;
                    y_cross_df = y_cross_md + value;
                    y_cross_gk = y_cross_fw + value;
                else
                    y_cross_fw = y_posCrossing(4) - predicted_pos;
                    y_cross_md = y_posCrossing(3) - predicted_pos;
                    y_cross_df = y_cross_md - predicted_pos;
                    y_cross_gk = y_cross_fw + value;
                end

                if abs(y_cross_gk) > abs(y_cross_fw)
                    y_cross_gk = y_cross_fw - value;
                end

                if abs(y_cross_df) < abs(y_cross_md)
                    y_cross_df = y_cross_md - value;
                end
                if x_posOfBall(1) <= 2300
                    y_cross_gk = y_posCrossing(1);
                end
            else
                y_cross_fw = y_posCrossing(4) - predicted_pos;
                y_cross_md = y_posCrossing(3) - predicted_pos;
                y_cross_df = y_cross_md - predicted_pos;
                y_cross_gk = y_cross_fw + value;

                if x_posOfBall(1) <= 2300
                    y_cross_gk = y_posCrossing(1);
                end
            end
    end
    
    if y_cross_gk > gk_max
        y_cross_gk = y_cross_df - 200;
    elseif y_cross_gk < gk_min
        y_cross_gk = y_cross_df + 200;
    end
    
    y_nCross = [y_cross_gk y_cross_df y_cross_md y_cross_fw]; 
end