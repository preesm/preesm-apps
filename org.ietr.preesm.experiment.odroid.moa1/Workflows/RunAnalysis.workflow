<?xml version="1.0" encoding="UTF-8"?>
<dftools:workflow errorOnWarning="true" verboseLevel="INFO" xmlns:dftools="http://net.sf.dftools">
    <dftools:scenario pluginId="org.ietr.preesm.scenario.task"/>
    <dftools:task pluginId="pisdf-srdag" taskId="pisdf-srdag">
        <dftools:data key="variables">
            <dftools:variable name="Consistency_Method" value="LCM"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="pisdf-mapper.list" taskId="Scheduling">
        <dftools:data key="variables">
            <dftools:variable name="Check" value="True"/>
            <dftools:variable name="Optimize synchronization" value="False"/>
            <dftools:variable name="balanceLoads" value="true"/>
            <dftools:variable name="edgeSchedType" value="Simple"/>
            <dftools:variable name="simulatorType" value="ApproximatelyTimed"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.stats.exporter.StatsExporterTask" taskId="Stat Exporter">
        <dftools:data key="variables">
            <dftools:variable name="path" value="/stats/xml/"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.algorithm.moa.activity.ActivityExporter" taskId="Activity Exporter">
        <dftools:data key="variables">
            <dftools:variable name="human_readable" value="No"/>
            <dftools:variable name="path" value="stats/mat/activity"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.algorithm.moa.activity.CustomQuantaExporter" taskId="Custom Activity Exporter">
        <dftools:data key="variables">
            <dftools:variable name="human_readable" value="No"/>
            <dftools:variable name="path" value="stats/mat/activity"/>
            <dftools:variable name="xls_file" value="stats/mat/custom_quanta_in/quanta_in_$SCENARIO$.xls"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.algorithm.moa.activity.MonoActivityExporter" taskId="MonoActivity Exporter">
        <dftools:data key="variables">
            <dftools:variable name="human_readable" value="No"/>
            <dftools:variable name="path" value="stats/mat/activity"/>
        </dftools:data>
    </dftools:task>
    <dftools:dataTransfer from="scenario" sourceport="PiMM"
        targetport="PiMM" to="pisdf-srdag"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Scheduling"/>
    <dftools:dataTransfer from="scenario"
        sourceport="architecture" targetport="architecture" to="Scheduling"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Stat Exporter"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="Stat Exporter"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="Custom Activity Exporter"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="Activity Exporter"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="MonoActivity Exporter"/>
    <dftools:dataTransfer from="pisdf-srdag" sourceport="PiMM"
        targetport="PiMM" to="Scheduling"/>
</dftools:workflow>
