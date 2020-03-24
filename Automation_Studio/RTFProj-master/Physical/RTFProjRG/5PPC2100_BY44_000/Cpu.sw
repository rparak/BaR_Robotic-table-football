<?xml version="1.0" encoding="utf-8"?>
<?AutomationStudio Version=4.2.8.54 SP?>
<SwConfiguration CpuAddress="SL1" xmlns="http://br-automation.co.at/AS/SwConfiguration">
  <TaskClass Name="Cyclic#1">
    <Task Name="table_foot" Source="Real_Game.Technology.table_football.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
  </TaskClass>
  <TaskClass Name="Cyclic#2" />
  <TaskClass Name="Cyclic#3" />
  <TaskClass Name="Cyclic#4">
    <Task Name="Client" Source="Connection.Client.prg" Memory="UserROM" Language="IEC" Debugging="true" />
  </TaskClass>
  <TaskClass Name="Cyclic#5" />
  <TaskClass Name="Cyclic#6" />
  <TaskClass Name="Cyclic#7" />
  <TaskClass Name="Cyclic#8" />
  <DataObjects>
    <DataObject Name="assl1" Source="" Memory="UserROM" Language="Binary" />
    <DataObject Name="Arnc0sys" Source="" Memory="UserROM" Language="Binary" />
    <DataObject Name="Acp10sys" Source="" Memory="UserROM" Language="Binary" />
  </DataObjects>
  <NcDataObjects>
    <NcDataObject Name="acp10etxen" Source="ACP10_ETXEN.acp10etxen.dob" Memory="UserROM" Language="Ett" />
    <NcDataObject Name="rotaryFWa" Source="Real_Game.Motion.rotaryFWobj.rotaryFWa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="rotaryFWi" Source="Real_Game.Motion.rotaryFWobj.rotaryFWi.dob" Memory="UserROM" Language="Ax" />
    <NcDataObject Name="rotaryMDa" Source="Real_Game.Motion.rotaryMDobj.rotaryMDa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="rotaryMDi" Source="Real_Game.Motion.rotaryMDobj.rotaryMDi.dob" Memory="UserROM" Language="Ax" />
    <NcDataObject Name="linearFWa" Source="Real_Game.Motion.linearFWobj.linearFWa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="linearFWi" Source="Real_Game.Motion.linearFWobj.linearFWi.dob" Memory="UserROM" Language="Ax" />
    <NcDataObject Name="linearMDa" Source="Real_Game.Motion.linearMDobj.linearMDa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="linearMDi" Source="Real_Game.Motion.linearMDobj.linearMDi.dob" Memory="UserROM" Language="Ax" />
    <NcDataObject Name="rotDFa" Source="Real_Game.Motion.rotDFobj.rotDFa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="rotDFi" Source="Real_Game.Motion.rotDFobj.rotDFi.dob" Memory="UserROM" Language="Ax" />
    <NcDataObject Name="rotDFVa" Source="Real_Game.Motion.rotDFVobj.rotDFVa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="rotDFVi" Source="Real_Game.Motion.rotDFVobj.rotDFVi.dob" Memory="UserROM" Language="Vax" />
    <NcDataObject Name="rotGKa" Source="Real_Game.Motion.rotGKobj.rotGKa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="rotGKi" Source="Real_Game.Motion.rotGKobj.rotGKi.dob" Memory="UserROM" Language="Ax" />
    <NcDataObject Name="linDFa" Source="Real_Game.Motion.linDFobj.linDFa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="linDFi" Source="Real_Game.Motion.linDFobj.linDFi.dob" Memory="UserROM" Language="Ax" />
    <NcDataObject Name="linDFVa" Source="Real_Game.Motion.linDFVobj.linDFVa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="linDFVi" Source="Real_Game.Motion.linDFVobj.linDFVi.dob" Memory="UserROM" Language="Vax" />
    <NcDataObject Name="linGKa" Source="Real_Game.Motion.linGKobj.linGKa.dob" Memory="UserROM" Language="Apt" />
    <NcDataObject Name="linGKi" Source="Real_Game.Motion.linGKobj.linGKi.dob" Memory="UserROM" Language="Ax" />
  </NcDataObjects>
  <Binaries>
    <BinaryObject Name="arsvcreg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="mvLoader" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="TCData" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="udbdef" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Linear" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="iomap" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="OpcUaMap" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="sysconf" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="Config" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="TC" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Config_1" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="ashwd" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="asfw" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="User" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="arconfig" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="Role" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Rotary" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Acp10map" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="acp10cfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Arnc0map" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="arnc0cfg" Source="" Memory="UserROM" Language="Binary" />
  </Binaries>
  <Libraries>
    <LibraryObject Name="operator" Source="Libraries.operator.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="runtime" Source="Libraries.runtime.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsIecCon" Source="Libraries.AsIecCon.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="sys_lib" Source="Libraries.sys_lib.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="astime" Source="Libraries.astime.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsArSdm" Source="Libraries.AsArSdm.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsWStr" Source="Libraries.AsWStr.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="asstring" Source="Libraries.asstring.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="DataObj" Source="Libraries.DataObj.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsArLog" Source="Libraries.AsArLog.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="FileIO" Source="Libraries.FileIO.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsArProf" Source="Libraries.AsArProf.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsMem" Source="Libraries.AsMem.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="brsystem" Source="Libraries.brsystem.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="standard" Source="Libraries.standard.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="rp_funcx1" Source="Libraries.rp_library.rp_funcx1.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="GoalKeeper" Source="Libraries.RO_LB_ScoreDetection.GoalKeeper.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="AsBrStr" Source="Libraries.AsBrStr.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="IecCheck" Source="Libraries.IecCheck.lby" Memory="UserROM" Language="IEC" Debugging="true" />
    <LibraryObject Name="MTTypes" Source="Libraries.MTTypes.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="MpCom" Source="Libraries.MpCom.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="MpAlarmX" Source="Libraries.MpAlarmX.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="MTBasics" Source="Libraries.MTBasics.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsSafety" Source="Libraries.AsSafety.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsXml" Source="Libraries.AsXml.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="MpAxis" Source="Libraries.MpAxis.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="Acp10_MC" Source="Libraries.Acp10_MC.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="Acp10man" Source="Libraries.Acp10man.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="NcGlobal" Source="Libraries.NcGlobal.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="Acp10par" Source="Libraries.Acp10par.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="RO_Sensors" Source="Libraries.RO_Sensors.lby" Memory="UserROM" Language="IEC" Debugging="true" />
    <LibraryObject Name="Camera" Source="Libraries.Camera.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="Bar_Light" Source="Libraries.Bar_Light.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="AsUDP" Source="Libraries.AsUDP.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="powerlnk" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="areventlog" Source="" Memory="UserROM" Language="Binary" Debugging="true" />
  </Libraries>
</SwConfiguration>