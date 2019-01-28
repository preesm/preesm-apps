<?xml version="1.0" encoding="UTF-8"?>
<dftools:workflow errorOnWarning="true" verboseLevel="INFO" xmlns:dftools="http://net.sf.dftools">
    <dftools:scenario pluginId="org.ietr.preesm.scenario.task"/>
    <dftools:task
        pluginId="org.ietr.preesm.experiment.pimm2sdf.StaticPiMM2SDFTask" taskId="PiMM2SDF">
        <dftools:data key="variables"/>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.plugin.transforms.flathierarchy" taskId="Hierarchy Flattening">
        <dftools:data key="variables">
            <dftools:variable name="depth" value="3"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.plugin.transforms.sdf2hsdf" taskId="Single-rate transformation">
        <dftools:data key="variables">
            <dftools:variable name="ExplodeImplodeSuppr" value="false"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.plugin.mapper.listscheduling" taskId="Scheduling">
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
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="PiMM2SDF"/>
    <dftools:dataTransfer from="scenario" sourceport="PiMM"
        targetport="PiMM" to="PiMM2SDF"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Scheduling"/>
    <dftools:dataTransfer from="scenario"
        sourceport="architecture" targetport="architecture" to="Scheduling"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Stat Exporter"/>
    <dftools:dataTransfer from="PiMM2SDF" sourceport="SDF"
        targetport="SDF" to="Hierarchy Flattening"/>
    <dftools:dataTransfer from="Hierarchy Flattening"
        sourceport="SDF" targetport="SDF" to="Single-rate transformation"/>
    <dftools:dataTransfer from="Single-rate transformation"
        sourceport="SDF" targetport="SDF" to="Scheduling"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="Stat Exporter"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="Custom Activity Exporter"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="Activity Exporter"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="MonoActivity Exporter"/>
</dftools:workflow>
