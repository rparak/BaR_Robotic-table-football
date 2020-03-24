%% Matlab simulation
% Author Name  : Roman Parak 
% University   : Brno University of Technology
% Faculty      : Faculty of Mechanical Engineering
% Institute    : Institute of Automation and Computer Science
% Project Name : Master's Thesis - Robotic table football - game strategy

function [real_disp,gk_pos,df_pos,md_pos,fw_pos] = calculation_posDummies(disp)
%% Description of function
% < input >
% disp -> displacement of axes {opponent or CPU} 
% < output >
% real_disp  -> real displacement
% gk_pos -> array [position dummies of goalkeeper axis] 
% df_pos -> array [position dummies of defencer axis]
% md_pos -> array [position dummies of midfielnder axis]
% fw_pos -> array [position dummies of forward axis]
%% Parameters
    max_pos = [1000 1850 650 955]; % maximum displacements of individual axes
    min_pos = [-1000 -1850 -650 -955]; % minimum displacements
    % matrix of displacements opponent at the invdividual axes
    matrix_posOfOpponent = [0 0 0 0 0;...
        -1200 1200 0 0 0;...
        -2400 -1200 0 1200 2400;...
        -2100 0 2100 0 0];
    
%% Calculation
    for i = 1:length(disp)
        for j = 1:(length(disp)+1)
            if disp(i) > max_pos(i)
                pos(i,j)       = max_pos(i) + matrix_posOfOpponent(i,j);
                real_disp(i)   = max_pos(i);
            elseif disp(i) < min_pos(i)
                pos(i,j)       = min_pos(i) + matrix_posOfOpponent(i,j);
                real_disp(i)   = min_pos(i);
            else
                pos(i,j)       = disp(i) + matrix_posOfOpponent(i,j);
                real_disp(i)   = disp(i);
            end
        end   
    end 
    
%% output real values
    gk_pos = pos(1,(1:1));
    df_pos = pos(2,(1:2));
    md_pos = pos(3,(1:5));
    fw_pos = pos(4,(1:3));
end