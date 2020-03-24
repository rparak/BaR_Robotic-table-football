%% Matlab simulation
% Author Name  : Roman Parak 
% University   : Brno University of Technology
% Faculty      : Faculty of Mechanical Engineering
% Institute    : Institute of Automation and Computer Science
% Project Name : Master's Thesis - Robotic table football - game strategy

function draw_actual_state(CPU,HUMAN,ball1,ball2,f_x,f_y,s_x,s_y,x_posOfD_CPU,y_posOfD_CPU,x_posOfD_HUMAN,y_posOfD_HUMAN)
%% Description of function
% actual plotting {after calculating all of components}
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
    rectangle('Position',[740 3415-3515+(CPU(1)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    % defender
    line([2300 2300],[0-3515 7030-3515],'LineWidth',2,...
       'Color',[0 0 0]);
    rectangle('Position',[2240 4615-3515+(CPU(2)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[2240 2215-3515+(CPU(2)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    % midfielder
    line([5300 5300],[0-3515 7030-3515],'LineWidth',2,...
       'Color',[0 0 0]);
    rectangle('Position',[5240 3415-3515+(CPU(3)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[5240 4615-3515+(CPU(3)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[5240 5815-3515+(CPU(3)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[5240 2215-3515+(CPU(3)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[5240 1015-3515+(CPU(3)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    % forward
    line([8300 8300],[0-3515 7030-3515],'LineWidth',2,...
       'Color',[0 0 0]);
    rectangle('Position',[8240 3415-3515+(CPU(4)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[8240 5515-3515+(CPU(4)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[8240 1315-3515+(CPU(4)) 120 200],'FaceColor',[1 0 0],'EdgeColor','none',...
        'LineWidth',0.1);
%% Levers of dummies - human
    % goalkeeper
    line([11300 11300],[0-3515 7030-3515],'LineWidth',2,...
       'Color',[0 0 0]);
    rectangle('Position',[11240 3415-3515+(HUMAN(1)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);
    % defender
    line([9800 9800],[0-3515 7030-3515],'LineWidth',2,...
       'Color',[0 0 0]);
    rectangle('Position',[9740 4615-3515+(HUMAN(2)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[9740 2215-3515+(HUMAN(2)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);
    % midfielder
    line([6800 6800],[0-3515 7030-3515],'LineWidth',2,...
       'Color',[0 0 0]);
    rectangle('Position',[6740 3415-3515+(HUMAN(3)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[6740 4615-3515+(HUMAN(3)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[6740 5815-3515+(HUMAN(3)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1)
    rectangle('Position',[6740 2215-3515+(HUMAN(3)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[6740 1015-3515+(HUMAN(3)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);
    % forward
    line([3800 3800],[0-3515 7030-3515],'LineWidth',2,...
       'Color',[0 0 0]);
    rectangle('Position',[3740 3415-3515+(HUMAN(4)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[3740 5515-3515+(HUMAN(4)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);
    rectangle('Position',[3740 1315-3515+(HUMAN(4)) 120 200],'FaceColor',[0 0 1],'EdgeColor','none',...
        'LineWidth',0.1);

%% Draw balls
    r   = 170;
    draw_posBall1 = rectangle('Curvature',[1 1]);
    draw_posBall2 = rectangle('Curvature',[1 1]);

    if ((isnan(ball2(1))) && (isnan(ball2(2))))

        draw_posBall1.Position = [ball1(1) - r ball1(2) - r, r*2, r*2];
        draw_posBall1.EdgeColor = 'k';
        draw_posBall1.FaceColor = 'none';

        line([ball1(1) 0],[ball1(2) ball1(2)],'LineWidth',1,...
            'LineStyle','--','Color',[0 0 0]);
    else
         draw_posBall1.Position = [ball1(1) - r ball1(2) - r, r*2, r*2];
         draw_posBall1.EdgeColor = 'k';
         draw_posBall1.FaceColor = 'none';

         draw_posBall2.Position = [ball2(1) - r ball2(2) - r, r*2, r*2];
         draw_posBall2.EdgeColor = 'b';
         draw_posBall2.FaceColor = 'none';

         line([ball1(1) ball2(1)],[ball1(2) ball2(2)],...
            'LineWidth',1,'LineStyle','--','Color',[0 0 0]);
         line([ball2(1) f_x],[ball2(2) f_y],'LineWidth',1,...
            'LineStyle','--','Color',[0 0 0]); 
        if s_x ~= 'None'
             line([f_x s_x],[f_y s_y],'LineWidth',1,...
                'LineStyle','--','Color',[0 0 0]);
        end
    end
%% Draw directions
  plot(x_posOfD_CPU,y_posOfD_CPU,'*',...
      'LineWidth',1.5,...
      'MarkerSize',8,...
      'MarkerEdgeColor','g',...
      'MarkerFaceColor',[0.5,0.5,0.5])
  plot(x_posOfD_HUMAN,y_posOfD_HUMAN,'*',...
      'LineWidth',1.5,...
      'MarkerSize',8,...
      'MarkerEdgeColor','m',...
      'MarkerFaceColor',[0.5,0.5,0.5])
end