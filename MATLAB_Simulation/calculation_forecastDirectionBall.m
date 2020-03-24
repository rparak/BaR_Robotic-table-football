%% Matlab simulation
% Author Name  : Roman Parak 
% University   : Brno University of Technology
% Faculty      : Faculty of Mechanical Engineering
% Institute    : Institute of Automation and Computer Science
% Project Name : Master's Thesis - Robotic table football - game strategy

function [specific_direction,dir,x_p2,y_p2,x_p1,y_p1] = calculation_forecastDirectionBall(ball1_xy,ball2_xy)
%% Description of function
% < input >
% ball1_xy -> x,y parameters of ball1
% ball2_xy -> x,y parameters of ball2
% < output >
% dir  -> direction {straight = 0, tilt = 1)
% specific_direction -> ({right,left},straight{forward,backward},tilt{up,down})
% x_p2 -> first reflection of ball { axis x }
% y_p2 -> first reflection of ball { axis y }
% x_p1 -> second reflection of ball { axis x }
% y_p2 -> second reflection of ball { axis y }
%% Parameters
    % playground
    pos_xmin = 0;
    pos_xmax = 12100;
    pos_ymin = -3515;
    pos_ymax = 3515;
    % other 
    r   = 170; % the diameter of the ball
    dir = false; % direction
    initial_state = NaN;
    
%% Drawing balls
    draw_posBall1 = rectangle('Curvature',[1 1]);
    draw_posBall2 = rectangle('Curvature',[1 1]);
    
    if ((isnan(ball2_xy(1))) && (isnan(ball2_xy(2))))
        initial_state = 0;
    else
        initial_state = 1;
    end
    
    switch initial_state
        case 0
            %% initialization first ball, second is 'None'
            specific_direction = 'straight';
            
            ball1_param_x = ball1_xy(1);
            ball1_param_y = ball1_xy(2);
            
            draw_posBall1.Position = [ball1_param_x - r ball1_param_y - r, r*2, r*2];
            draw_posBall1.EdgeColor = 'k';
            draw_posBall1.FaceColor = 'none';
            
            dir = false;
            
            direction = line([ball1_param_x pos_xmin],[ball1_param_y ball1_param_y],'LineWidth',1,...
                    'LineStyle','--','Color',[0 0 0]);
                
             x_p2 = NaN;
             y_p2 = NaN;
             x_p1 = 0;
             y_p1 = ball1_param_y;
        case 1
            %% initialization first and second ball
            for i = 1:length(ball1_xy)
                if i == 1
                    ball1_param_x = ball1_xy(i);
                    ball2_param_x = ball2_xy(i);
                else
                    ball1_param_y = ball1_xy(i);
                    ball2_param_y = ball2_xy(i);
                end
            end

            draw_posBall1.Position = [ball1_param_x - r ball1_param_y - r, r*2, r*2];
            draw_posBall1.EdgeColor = 'k';
            draw_posBall1.FaceColor = 'none';

            draw_posBall2.Position = [ball2_param_x - r ball2_param_y - r, r*2, r*2];
            draw_posBall2.EdgeColor = 'b';
            draw_posBall2.FaceColor = 'none';

            drawDirectionBetweenBalls = line([ball1_param_x ball2_param_x],[ball1_param_y ball2_param_y],...
            'LineWidth',1,'LineStyle','--','Color',[0 0 0]);

        %% Conditions for finding out direction
            if ball1_param_y == ball2_param_y
                % direct way of the ball
                dir = false;
                if ball1_param_x > ball2_param_x
                    specific_direction = 'straight-backward';
                    % direction is backward(left in the simulation)
                    direction = line([ball2_param_x pos_xmin],[ball2_param_y ball2_param_y],'LineWidth',1,...
                    'LineStyle','--','Color',[0 0 0]);
                    x_p2 = NaN;
                    y_p2 = NaN;
                    x_p1 = 0;
                    y_p1 = ball2_param_y;
                elseif ball1_param_x < ball2_param_x
                    specific_direction = 'straight-forward';
                    % direction is forward(right in the simulation)
                    direction = line([ball2_param_x pos_xmax],[ball2_param_y ball2_param_y],'LineWidth',1,...
                    'LineStyle','--','Color',[0 0 0]);
                    x_p2 = NaN;
                    y_p2 = NaN;
                    x_p1 = 12100;
                    y_p1 = ball2_param_y;
                elseif ball1_param_x == ball2_param_x
                    specific_direction = 'stopped';
                    % ball is stopped
                    direction = line([ball1_param_x ball2_param_x],[ball1_param_y ball2_param_y],'LineWidth',1,...
                    'LineStyle','--','Color',[0 0 0]);
                    x_p2 = ball2_param_x;
                    y_p2 = ball2_param_y;
                    x_p1 = ball1_param_x;
                    y_p1 = ball1_param_y;
                end
            else
                if ball1_param_x == ball2_param_x
                    if ball2_param_y > ball1_param_y
                        specific_direction = 'left';
                    else
                        specific_direction = 'right';
                    end
                    % direction is right or left
                    direction = line([ball1_param_x ball2_param_x],[ball1_param_y ball2_param_y],'LineWidth',1,...
                    'LineStyle','--','Color',[0 0 0]);
                    x_p2 = ball2_param_x;
                    y_p2 = ball2_param_y;
                    x_p1 = ball1_param_x;
                    y_p1 = ball1_param_y;
                else
                    dir = true;
                    % indirect way of the ball
                    [specific_direction,state_ofDirection,x_p1,y_p1] = calculate_directionOfTilt(ball1_param_x,ball1_param_y,ball2_param_x,ball2_param_y);
                    [x_p2,y_p2]                   = calculate_nextDirection(state_ofDirection,x_p1,y_p1,ball2_param_x,ball2_param_y);
                end
            end
    end
% end function
end

function [spec_d,state,x_new,y_new] = calculate_directionOfTilt(x1,y1,x2,y2)
%% Description of function
% < input >
% x1 -> x parameters of ball1
% y1 -> y parameters of ball1
% x2 -> x parameters of ball2
% y2 -> y parameters of ball2
% < output >
% spec_d -> specific direction
% state -> direction of ball { eg. up, backward = 1 etc. }
% x_new -> position of x axis after the reflection
% y_new -> position of y axis after the reflection
%% Parameters
    % directions
    ball_ub = false; % ball direction -> up, backward
    ball_db = false; % ball direction -> down, backward
    ball_uf = false; % ball direction -> up, forward
    ball_df = false; % ball direction -> down, forward
    state   = 0;     % initial state of direction
    
%% Determine of direction
    if y2 > y1 && x2 < x1
       % up, backward
       ball_ub = true;
       spec_d  = 'up_backward';
    elseif y2 < y1 && x2 < x1
       % down, backward
       ball_db = true;
       spec_d  = 'down_backward';
    elseif y2 > y1 && x2 > x1
        % up, forward
       ball_uf = true;
       spec_d  = 'up_forward';
    elseif y2 < y1 && x2 > x1
        % down, forward
       ball_df = true;
       spec_d  = 'down_forward';
    end 
       
%% Calculation and drawing direction
    if ball_ub == true
        % 3515 -> maximum of [ y ]
        % 0   -> minimum of [ x ]
        distanceOfRatio_y = ((3515-y1)/(abs(y1-y2)));
        distanceOfRatio_x = ((x1)/(abs(x1-x2)));
        state             = 1;
        
        x_new = x1 - ((distanceOfRatio_y)*abs(x1-x2)); 
        y_new = 3515;
        if x_new >= 0 & y_new <= 3515
            draw_goalState = line([x2 x_new],[y2 y_new],'LineWidth',1,...
            'LineStyle','--','Color',[0 0 0]);
        else
            x_new = 0;
            y_new = y1 + ((distanceOfRatio_x)*abs(y1-y2));
            draw_goalState = line([x2 x_new],[y2 y_new],'LineWidth',1,...
            'LineStyle','--','Color',[0 0 0]);
        end
    elseif ball_db == true
        % -3515 -> minumum of [ y ]
        % 0 -> minimum of [ x ]
        distanceOfRatio_y = ((y1+3515)/(abs(y1-y2)));
        distanceOfRatio_x = ((x1)/(abs(x1-x2)));
        state             = 2;
        
        x_new = x1 - ((distanceOfRatio_y)*abs(x1-x2));
        y_new = -3515;
        if x_new >= 0 & y_new >= -3515
             draw_goalState = line([x2 x_new],[y2 y_new],'LineWidth',1,...
             'LineStyle','--','Color',[0 0 0]);
        else
            x_new = 0;
            y_new = y1 - ((distanceOfRatio_x)*abs(y1-y2));
            draw_goalState = line([x2 x_new],[y2 y_new],'LineWidth',1,...
            'LineStyle','--','Color',[0 0 0]);
        end
    elseif ball_uf == true
        % 3515  -> maximum of [ y ]
        % 12100 -> maximum of [ x ]
        distanceOfRatio_y = ((3515-y1)/(abs(y1-y2)));
        distanceOfRatio_x = ((12100 - x1)/(abs(x1-x2)));
        state             = 3;
        
        x_new = x1 + ((distanceOfRatio_y)*abs(x1-x2));
        y_new = 3515;
        if x_new <= 12100 & y_new <= 3515
             draw_goalState = line([x2 x_new],[y2 y_new],'LineWidth',1,...
             'LineStyle','--','Color',[0 0 0]);
        else
            x_new = 12100;
            y_new = y1 + ((distanceOfRatio_x)*abs(y1-y2));
            draw_goalState = line([x2 x_new],[y2 y_new],'LineWidth',1,...
            'LineStyle','--','Color',[0 0 0]);
        end
    elseif ball_df == true
        % -3515    -> minumum of [ y ]
        % 12100 -> maximum of [ x ]
        distanceOfRatio_y = ((y1+3515)/(abs(y1-y2)));
        distanceOfRatio_x = ((12100 - x1)/(abs(x1-x2)));
        state             = 4;
        
        x_new = x1 + ((distanceOfRatio_y)*abs(x1-x2));
        y_new = -3515;

        if x_new <= 12100 & y_new >= -3515
             draw_goalState = line([x2 x_new],[y2 y_new],'LineWidth',1,...
             'LineStyle','--','Color',[0 0 0]);
        else
            x_new = 12100;
            y_new = y1 - ((distanceOfRatio_x)*abs(y1-y2));
            draw_goalState = line([x2 x_new],[y2 y_new],'LineWidth',1,...
            'LineStyle','--','Color',[0 0 0]);
        end
    end
% end function  
end

function [x_p2,y_p2] = calculate_nextDirection(state_ofDirection,x1_n,y1_n,x2,y2)
%% Description of function
% < input >
% state -> direction of ball { eg. up, backward = 1 etc. }
% x1_n -> position of x axis after the reflection < output from : calculate_directionOfTilt >
% y1_n -> position of y axis after the reflection < output from : calculate_directionOfTilt >
% x2 -> x parameters of ball2
% y2 -> y parameters of ball2
% < output >
% x_p2 -> position of x axis after the reflection{ second } < input from : calculate_directionOfTilt >
% y_p2 -> position of y axis after the reflection{ second } < input from : calculate_directionOfTilt >
%% Parameters
    initial_state = 0;
    xn            = 0; % new parameter of x
    yn            = 0; % new parameter of y
    yMax          = 3515;
    yMin          = -3515;
    
%% State machine for calculation next directions
    initial_state = state_ofDirection;
    
    switch initial_state
        case 1
            % direction -> up, forward
            if x1_n == 0
                xn = (x1_n + (abs(x1_n - x2)*(0.01)));
                yn = y1_n + (abs(y1_n - y2)*0.01);
            else
                xn = (x1_n - (abs(x1_n - x2)*(0.01)));
                yn = y1_n - (abs(y1_n - y2)*0.01);
            end
           [specific_direction,state,x_p2,y_p2] = calculate_directionOfTilt(x1_n,y1_n,xn,yn);
        case 2
            % direction -> down, forward
            if x1_n == 0
                xn = (x1_n + (abs(x1_n - x2)*(0.01)));
                yn = y1_n - (abs(y1_n - y2)*0.01);
            else
                xn = (x1_n - (abs(x1_n - x2)*(0.01)));
                yn = y1_n + (abs(y1_n - y2)*0.01);
            end
           [specific_direction,state,x_p2,y_p2] = calculate_directionOfTilt(x1_n,y1_n,xn,yn);
        case 3
            % direction -> up, backward
            if x1_n == 12100
                xn = (x1_n - (abs(x1_n - x2)*(0.01)));
                yn = y1_n + (abs(y1_n - y2)*0.01);
            else
                xn = (x1_n + (abs(x1_n - x2)*(0.01)));
                yn = y1_n - (abs(y1_n - y2)*0.01);
            end
           [specific_direction,state,x_p2,y_p2] = calculate_directionOfTilt(x1_n,y1_n,xn,yn);
        case 4
            % direction -> down, backward
            if x1_n == 12100
                xn = (x1_n - (abs(x1_n - x2)*(0.01)));
                yn = y1_n - (abs(y1_n - y2)*0.01);
            else
                xn = (x1_n + (abs(x1_n - x2)*(0.01)));
                yn = y1_n + (abs(y1_n - y2)*0.01);
            end
           [specific_direction,state,x_p2,y_p2] = calculate_directionOfTilt(x1_n,y1_n,xn,yn)
    end
% end function   
end

