%% Matlab simulation
% Author Name  : Roman Parak 
% University   : Brno University of Technology
% Faculty      : Faculty of Mechanical Engineering
% Institute    : Institute of Automation and Computer Science
% Project Name : Master's Thesis - Robotic table football - game strategy

function [c_d,time_aI,velocity,x_N,y_N] = calculation_crossingBall(positions_XD,time_B2B,dir,x0,y0,x1,y1,x2,y2,x3,y3)
    %% Description of function
    % < input >
    % time_B2B -> time between 2 balls
    % dir -> direction {1 = tilt; 0 = straight}
    % x0 -> x position of the ball1
    % y0 -> y position of the ball1
    % x1 -> x position of the ball2
    % y1 -> y position of the ball2
    % x2 -> x position of the first prediction
    % y2 -> y position of the first prediction
    % x3 -> x position of the second prediction
    % y3 -> y position of the second prediction
    % < output >
    % time_aI -> array of times { individual axes => axis intersection }
    % velocity -> velocity of ball
    % x_N -> array of x parameters
    % y_N -> array of y parameters, where intersects of ball some axis
    %% Parameters
    % Max X position of the dummies
    x_posOfD = [positions_XD(1) positions_XD(2) positions_XD(3) positions_XD(4)];
    % Y position of the dummies
    y_posOfD = [0 0 0 0];
    % other
    initial_state = nan; % initial state
    both_ball = false; % both of them were detected
    c_d = 0; % count dummies
    max_d = 4; % maximum dummies
    time_f = false;
    x = [x0 x2];
    %% Calculation
    if abs(x3-x2) < 1500 && abs(x2 - x1) < 1500
        initial_state = 0;
    else
        initial_state = dir; % straight or tilt
    end
    % condition {detected second ball or not ?}
    % x1,y1 == nan{ball 2 is not detected}
    if (isnan(x1) & isnan(y1))
        both_ball = false;
    else
        both_ball = true;
    end
        
    % conditions {detected count of dummies, through which passes of the ball}
    for i=1:length(x)
        if x(i) >= x_posOfD(4)
            c_d(i) = 4;
        elseif x(i) >= x_posOfD(3) && x(i) <= x_posOfD(4)
            c_d(i) = 3;
        elseif x(i) >= x_posOfD(2) && x(i) <= x_posOfD(3)
            c_d(i) = 2;
        elseif x(i) >= x_posOfD(1) && x(i) <= x_posOfD(2)
            c_d(i) = 1;
        else
            c_d(i) = 0;
        end
    end

    switch initial_state
        case 0
            %% straight {defense of shot}
            for i = 1:max_d
                if both_ball == true
                    y_posOfD(i) = y1;
                else
                    y_posOfD(i) = y0;
                end
            end

            x_N = x_posOfD(1:max_d);
            y_N = y_posOfD(1:max_d);
        case 1
            %% tilt {defense of shot}           
           if x0 > x1
               for i = 1:c_d(1)
                 if i <= c_d(2)
                    y_posOfD(i) = y2 - (y2-y3)/((x2 - x3)/(x2-x_posOfD(i))); % up
                 else
                    y_posOfD(i) = y1 + (y2-y1)/((x1 - x2)/(x1-x_posOfD(i))); % down
                 end
               end 

               for i = c_d(1)+1:max_d
                   y_posOfD(i) = y1;
               end
           else
               for i = c_d(1)+1:max_d
                   if i <= c_d(2)
                       y_posOfD(i) = y1 + (y2-y1)/((x1 - x2)/(x1-x_posOfD(i)));
                   else
                       y_posOfD(i) = y2 - (y2-y3)/((x2 - x3)/(x2-x_posOfD(i)));
                   end
               end 

               for i = 1:c_d(1)
                   y_posOfD(i) = y1;
               end
           end
           
           for i = 1:max_d
               if y_posOfD(i) < -3515 || y_posOfD(i) > 3515
                   y_posOfD(i) = y1;
                   time_f      = true;
               end
           end
           x_N = x_posOfD(1:max_d);
           y_N = y_posOfD(1:max_d);
    end
    
    if ((both_ball == true && c_d(1) ~= 0 || c_d(2) ~= 0) || (x_N(1) ~= 3800))
        [time_aI,velocity] = arrival_timeOfBall(c_d,time_B2B,dir,x_N,y_N,x0,y0,x1,y1,x2,y2);
    else
        velocity = nan; 
        time_aI  = [nan nan nan nan];
    end
    if positions_XD(1) == 800
        plot(x_N,y_N,'*',...
            'LineWidth',1.5,...
            'MarkerSize',8,...
            'MarkerEdgeColor','g',...
            'MarkerFaceColor',[0.5,0.5,0.5])
    else
         plot(x_N,y_N,'*',...
            'LineWidth',1.5,...
            'MarkerSize',8,...
            'MarkerEdgeColor','m',...
            'MarkerFaceColor',[0.5,0.5,0.5])       
    end
% end function
end

function [time_aI,velocity] = arrival_timeOfBall(c_d,t,dir,x_posOfDummies,y_posOfDummies,xpos_B1,ypos_B1,xpos_B2,ypos_B2,...
    xref_1,yref_1)
%% Description of function
% < input >
% c_d -> count dummies
% t -> time between 2 balls
% dir -> direction {1 = tilt; 0 = straight}
% x_posOfDummies -> array of x parameters
% y_posOfDummies -> array of y parameters, where intersects of ball some axis
% xpos_B1 -> x position of ball1
% ypos_B1 -> y position of ball1
% xpos_B2 -> x position of ball2
% ypos_B2 -> y position of ball2
% xref_1 -> first x reflection
% yref_1 -> first y reflection
% < output > 
% time_aI -> array of times { individual axes => axis intersection }
% velocity -> velocity of ball
%% Parameters
initial_state = nan;
%% Calculation
    initial_state = dir;
    switch dir
        case 0
            if xpos_B1 == xpos_B2
                velocity = abs((ypos_B1-ypos_B2))/t;
                
                for i=1:length(x_posOfDummies)
                    time_aI(i) = abs((ypos_B1-ypos_B2))/velocity; 
                end
            elseif xpos_B1 > xpos_B2
                velocity = abs((xpos_B1-xpos_B2))/t;
                
                for i=1:c_d(1)
                    time_f(i) = abs((xpos_B2 - x_posOfDummies(i)))/velocity; 
                end
                
                time_aI(1:c_d(1)) = sort(time_f,'descend');
                time_aI(c_d(1)+1:length(x_posOfDummies)) = t;
            else
                velocity = abs((xpos_B1-xpos_B2))/t;
                if xpos_B2 < 8300
                    for i=c_d(1)+1:length(x_posOfDummies)
                        time_aI(i) = abs((xpos_B2 - x_posOfDummies(i)))/velocity; 
                    end
                else
                    time_aI = [t t t t]; 
                end
            end
            
        case 1
            velocity = sqrt(((xpos_B1-xpos_B2)^2) + ((ypos_B2 - ypos_B1)^2))/t;
            
            if xpos_B1 > xpos_B2
                for j = 1:c_d(1)
                   if j <= c_d(2)
                       previous_time = sqrt(((xpos_B2-xref_1)^2) + ((ypos_B2 - yref_1)^2))/velocity;
                       time_f(j) = sqrt(((xref_1-x_posOfDummies(j))^2) + ((yref_1 - y_posOfDummies(j))^2))/velocity + previous_time;
                   else
                       time_f(j) = sqrt(((xpos_B2-x_posOfDummies(j))^2) + ((ypos_B2 - y_posOfDummies(j))^2))/velocity;
                   end
                end
                
                time_aI(1:c_d(1)) = sort(time_f,'descend');
                time_aI(c_d(1)+1:length(x_posOfDummies)) = t;
            else
                for i = c_d(1)+1:length(x_posOfDummies)
                   if i <= c_d(2)
                       time_aI(i) = sqrt(((xpos_B2-x_posOfDummies(i))^2) + ((ypos_B2 - y_posOfDummies(i))^2))/velocity;
                   else
                       previous_time = sqrt(((xpos_B2-xref_1)^2) + ((ypos_B2 - yref_1)^2))/velocity;
                       time_aI(i) = sqrt(((xref_1-x_posOfDummies(i))^2) + ((yref_1 - y_posOfDummies(i))^2))/velocity + previous_time;
                   end
                end
                
                time_aI(c_d(1)) = t;
            end
    end
% end function
end