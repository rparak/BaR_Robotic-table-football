function varargout = Masters_Thesis_Roman_Parak_SIMULATION(varargin)

gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Masters_Thesis_Roman_Parak_SIMULATION_OpeningFcn, ...
                   'gui_OutputFcn',  @Masters_Thesis_Roman_Parak_SIMULATION_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end


% --- Executes just before Masters_Thesis_Roman_Parak_SIMULATION is made visible.
function Masters_Thesis_Roman_Parak_SIMULATION_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Masters_Thesis_Roman_Parak_SIMULATION (see VARARGIN)

% Choose default command line output for Masters_Thesis_Roman_Parak_SIMULATION
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

data_CPU = [0 0 0 0; 0 0 0 0; 0 0 0 0; 0 0 0 0];
set(handles.uitable3,'data',data_CPU);

data_HUMAN = [0 0 0 0; 0 0 0 0; 0 0 0 0; 0 0 0 0];
set(handles.uitable5,'data',data_HUMAN);

data_disp = [0 0 0 0; 0 0 0 0; 0 0 0 0; 0 0 0 0];
set(handles.uitable8,'data',data_disp);

data_posD = [0 0 0 0 0; 0 0 0 0 0; 0 0 0 0 0; 0 0 0 0 0];
set(handles.uitable9,'data',data_posD);
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

% --- Outputs from this function are returned to the command line.
function varargout = Masters_Thesis_Roman_Parak_SIMULATION_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in reset_calc.
function reset_calc_Callback(hObject, eventdata, handles)
% hObject    handle to reset_calc (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%% reset layout
cla reset;

data_CPU = [0 0 0 0; 0 0 0 0; 0 0 0 0; 0 0 0 0];
set(handles.uitable3,'data',data_CPU);

data_HUMAN = [0 0 0 0; 0 0 0 0; 0 0 0 0; 0 0 0 0];
set(handles.uitable5,'data',data_HUMAN);

data_disp = [0 0 0 0; 0 0 0 0; 0 0 0 0; 0 0 0 0];
set(handles.uitable8,'data',data_disp);

data_posD = [0 0 0 0 0; 0 0 0 0 0; 0 0 0 0 0; 0 0 0 0 0];
set(handles.uitable9,'data',data_posD);
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

% --- Executes on button press in start_calc.
function start_calc_Callback(hObject, eventdata, handles)
% hObject    handle to start_calc (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%set(handles.uipanel43,'visible','on');

b1_x  = str2double(get(handles.ball1_X,'String'));
b1_y  = str2double(get(handles.ball1_Y,'String'));
b2_x  = str2double(get(handles.ball2_X,'String'));
b2_y  = str2double(get(handles.ball2_Y,'String'));

r_gk  = str2double(get(handles.edit46,'String'));
r_df  = str2double(get(handles.edit48,'String'));
r_md  = str2double(get(handles.edit53,'String'));
r_fw  = str2double(get(handles.edit51,'String'));

dispH_gk = str2double(get(handles.human_YGK,'String'));
dispH_df = str2double(get(handles.human_YDF,'String'));
dispH_md = str2double(get(handles.human_YMD,'String'));
dispH_fw = str2double(get(handles.human_YFW,'String'));

t_b2b  = str2double(get(handles.time_B2B,'String'));
%% Forecast direction and plotting
hold on
param_ballNo1 = [b1_x b1_y];
param_ballNo2 = [b2_x b2_y];
time_B2B      = t_b2b;

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


data_CPU(:,1) = x_posOfD_CPU;
data_CPU(:,2) = y_posOfD_CPU;
data_CPU(:,3) = time_axisIntersection_CPU;
data_CPU(:,4) = overall_velocity_CPU;

set(handles.uitable3,'data',data_CPU);

sort_timeAxisI_H(1) = time_axisIntersection_HUMAN(4);
sort_timeAxisI_H(2) = time_axisIntersection_HUMAN(3);
sort_timeAxisI_H(3) = time_axisIntersection_HUMAN(2);
sort_timeAxisI_H(4) = time_axisIntersection_HUMAN(1);
sort_x_posOfD_H = sort(x_posOfD_HUMAN,'descend');
sort_y_posOfD_H(1) = y_posOfD_HUMAN(4);
sort_y_posOfD_H(2) = y_posOfD_HUMAN(3);
sort_y_posOfD_H(3) = y_posOfD_HUMAN(2);
sort_y_posOfD_H(4) = y_posOfD_HUMAN(1);
data_HUMAN(:,1) = sort_x_posOfD_H;
data_HUMAN(:,2) = sort_y_posOfD_H;
data_HUMAN(:,3) = sort_timeAxisI_H;
data_HUMAN(:,4) = overall_velocity_HUMAN;

set(handles.uitable5,'data',data_HUMAN);
hold off

%% Plot actual positions
cla reset;
hold on

displacemet_HUMAN                            = [dispH_gk dispH_df dispH_md dispH_fw];
[r_disp,gk_posOD,df_posOD,md_posOD,fw_posOD] = calculation_posDummies(displacemet_HUMAN);

pos_dummiesHUMAN = [gk_posOD df_posOD md_posOD fw_posOD];
act_displacementGK      = 0;
act_dispdisplacementDF  = 0;
act_dispdisplacementMD  = 0;
act_dispdisplacementFW  = 0;
% reversed {1/0}
reversed_HUMAN = [r_gk r_df r_md r_fw];
act_displacementCPU     = [act_displacementGK act_dispdisplacementDF act_dispdisplacementMD act_dispdisplacementMD];
% calculation
x_posOfBall = [param_ballNo1(1) param_ballNo2(1)];
[displacement_CPU,velocity_CPU,acceleration_CPU,deceleration_CPU] = calculation_displacementAxesCPU(direction,specific_direction,c_dCPU,c_dHUM,y_posOfD_CPU,time_axisIntersection_CPU,...
    act_displacementCPU,reversed_HUMAN,pos_dummiesHUMAN,flip(y_posOfD_HUMAN),x_posOfBall);

CPU_BR = [displacement_CPU(1) displacement_CPU(2) displacement_CPU(3) displacement_CPU(4)];
HUMAN  = [r_disp(1) r_disp(2) r_disp(3) r_disp(4)];

data_posD(1,1)     = [gk_posOD];
data_posD(1,(2:5)) = [nan nan nan nan];
data_posD(2,(1:2)) = [df_posOD(1) df_posOD(2)];
data_posD(2,(3:5)) = [nan nan nan];
data_posD(3,(1:5)) = [md_posOD(1) md_posOD(2) md_posOD(3) md_posOD(4) md_posOD(5)];
data_posD(4,(1:3)) = [fw_posOD(1) fw_posOD(2) fw_posOD(3)];
data_posD(4,(4:5)) = [nan nan];

set(handles.uitable9,'data',data_posD);

data_disp(1,:) = [displacement_CPU(1) velocity_CPU(1) acceleration_CPU(1) deceleration_CPU(1)];
data_disp(2,:) = [displacement_CPU(2) velocity_CPU(2) acceleration_CPU(2) deceleration_CPU(2)];
data_disp(3,:) = [displacement_CPU(3) velocity_CPU(3) acceleration_CPU(3) deceleration_CPU(3)];
data_disp(4,:) = [displacement_CPU(4) velocity_CPU(4) acceleration_CPU(4) deceleration_CPU(4)];

set(handles.uitable8,'data',data_disp);

draw_actual_state(CPU_BR,HUMAN,param_ballNo1,param_ballNo2,f_x,f_y,s_x,s_y,x_posOfD_CPU,y_posOfD_CPU,x_posOfD_HUMAN,y_posOfD_HUMAN);
hold off

function ball2_X_Callback(hObject, eventdata, handles)
% hObject    handle to ball2_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ball2_X as text
%        str2double(get(hObject,'String')) returns contents of ball2_X as a double

% --- Executes during object creation, after setting all properties.
function ball2_X_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ball2_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ball2_Y_Callback(hObject, eventdata, handles)
% hObject    handle to ball2_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ball2_Y as text
%        str2double(get(hObject,'String')) returns contents of ball2_Y as a double


% --- Executes during object creation, after setting all properties.
function ball2_Y_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ball2_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ball1_Y_Callback(hObject, eventdata, handles)
% hObject    handle to ball1_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ball1_Y as text
%        str2double(get(hObject,'String')) returns contents of ball1_Y as a double


% --- Executes during object creation, after setting all properties.
function ball1_Y_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ball1_Y (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ball1_X_Callback(hObject, eventdata, handles)
% hObject    handle to ball1_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ball1_X as text
%        str2double(get(hObject,'String')) returns contents of ball1_X as a double

% --- Executes during object creation, after setting all properties.
function ball1_X_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ball1_X (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function time_B2B_Callback(hObject, eventdata, handles)
% hObject    handle to time_B2B (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of time_B2B as text
%        str2double(get(hObject,'String')) returns contents of time_B2B as a double

% --- Executes during object creation, after setting all properties.
function time_B2B_CreateFcn(hObject, eventdata, handles)
% hObject    handle to time_B2B (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit38_Callback(hObject, eventdata, handles)
% hObject    handle to edit38 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit38 as text
%        str2double(get(hObject,'String')) returns contents of edit38 as a double


% --- Executes during object creation, after setting all properties.
function edit38_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit38 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit40_Callback(hObject, eventdata, handles)
% hObject    handle to edit40 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit40 as text
%        str2double(get(hObject,'String')) returns contents of edit40 as a double


% --- Executes during object creation, after setting all properties.
function edit40_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit40 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit31_Callback(hObject, eventdata, handles)
% hObject    handle to edit31 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit31 as text
%        str2double(get(hObject,'String')) returns contents of edit31 as a double


% --- Executes during object creation, after setting all properties.
function edit31_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit31 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit33_Callback(hObject, eventdata, handles)
% hObject    handle to edit33 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit33 as text
%        str2double(get(hObject,'String')) returns contents of edit33 as a double


% --- Executes during object creation, after setting all properties.
function edit33_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit33 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function human_YMD_Callback(hObject, eventdata, handles)
% hObject    handle to human_YMD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of human_YMD as text
%        str2double(get(hObject,'String')) returns contents of human_YMD as a double


% --- Executes during object creation, after setting all properties.
function human_YMD_CreateFcn(hObject, eventdata, handles)
% hObject    handle to human_YMD (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit53_Callback(hObject, eventdata, handles)
% hObject    handle to edit53 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit53 as text
%        str2double(get(hObject,'String')) returns contents of edit53 as a double


% --- Executes during object creation, after setting all properties.
function edit53_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit53 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function human_YFW_Callback(hObject, eventdata, handles)
% hObject    handle to human_YFW (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of human_YFW as text
%        str2double(get(hObject,'String')) returns contents of human_YFW as a double


% --- Executes during object creation, after setting all properties.
function human_YFW_CreateFcn(hObject, eventdata, handles)
% hObject    handle to human_YFW (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit51_Callback(hObject, eventdata, handles)
% hObject    handle to edit51 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit51 as text
%        str2double(get(hObject,'String')) returns contents of edit51 as a double


% --- Executes during object creation, after setting all properties.
function edit51_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit51 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function human_YGK_Callback(hObject, eventdata, handles)
% hObject    handle to human_YGK (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of human_YGK as text
%        str2double(get(hObject,'String')) returns contents of human_YGK as a double


% --- Executes during object creation, after setting all properties.
function human_YGK_CreateFcn(hObject, eventdata, handles)
% hObject    handle to human_YGK (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit46_Callback(hObject, eventdata, handles)
% hObject    handle to edit46 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit46 as text
%        str2double(get(hObject,'String')) returns contents of edit46 as a double


% --- Executes during object creation, after setting all properties.
function edit46_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit46 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function human_YDF_Callback(hObject, eventdata, handles)
% hObject    handle to human_YDF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of human_YDF as text
%        str2double(get(hObject,'String')) returns contents of human_YDF as a double


% --- Executes during object creation, after setting all properties.
function human_YDF_CreateFcn(hObject, eventdata, handles)
% hObject    handle to human_YDF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit48_Callback(hObject, eventdata, handles)
% hObject    handle to edit48 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit48 as text
%        str2double(get(hObject,'String')) returns contents of edit48 as a double


% --- Executes during object creation, after setting all properties.
function edit48_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit48 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on key press with focus on start_calc and none of its controls.
function start_calc_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to start_calc (see GCBO)
% eventdata  structure with the following fields (see MATLAB.UI.CONTROL.UICONTROL)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)



function edit54_Callback(hObject, eventdata, handles)
% hObject    handle to edit54 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit54 as text
%        str2double(get(hObject,'String')) returns contents of edit54 as a double


% --- Executes during object creation, after setting all properties.
function edit54_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit54 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit55_Callback(hObject, eventdata, handles)
% hObject    handle to edit55 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit55 as text
%        str2double(get(hObject,'String')) returns contents of edit55 as a double


% --- Executes during object creation, after setting all properties.
function edit55_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit55 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit56_Callback(hObject, eventdata, handles)
% hObject    handle to edit56 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit56 as text
%        str2double(get(hObject,'String')) returns contents of edit56 as a double


% --- Executes during object creation, after setting all properties.
function edit56_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit56 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes when figure1 is resized.
function figure1_SizeChangedFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function input_paramMenu_Callback(hObject, eventdata, handles)
% hObject    handle to input_paramMenu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function plotMenu_Callback(hObject, eventdata, handles)
% hObject    handle to plotMenu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_1_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes on button press in pushbutton8.
function pushbutton8_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_2_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
