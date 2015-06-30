<?xml version="1.0" encoding="UTF-8"?>
<dftools:workflow xmlns:dftools="http://net.sf.dftools">
    <dftools:scenario pluginId="org.ietr.preesm.scenario.task"/>
    <dftools:task pluginId="org.ietr.preesm.plugin.mapper.plot" taskId="Display Gantt">
        <dftools:data key="variables">
            <dftools:variable name="path" value="/stats/xml/"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.plugin.mapper.listscheduling" taskId="Scheduling">
        <dftools:data key="variables">
            <dftools:variable name="balanceLoads" value="true"/>
            <dftools:variable name="displaySolutions" value="true"/>
            <dftools:variable name="edgeSchedType" value="Simple"/>
            <dftools:variable name="fastLocalSearchTime" value="10"/>
            <dftools:variable name="fastTime" value="100"/>
            <dftools:variable name="iterationNr" value="0"/>
            <dftools:variable name="iterationPeriod" value="0"/>
            <dftools:variable name="listType" value="optimised"/>
            <dftools:variable name="simulatorType" value="LooselyTimed"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="org.ietr.preesm.plugin.transforms.sdf2hsdf" taskId="Single-rate Transformation">
        <dftools:data key="variables">
            <dftools:variable name="ExplodeImplodeSuppr" value="false"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.plugin.transforms.flathierarchy" taskId="HierarchyFlattening">
        <dftools:data key="variables">
            <dftools:variable name="depth" value="100"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="org.ietr.preesm.plugin.exportXml.sdf4jgml" taskId="srSDF Exporter">
        <dftools:data key="variables">
            <dftools:variable name="openFile" value="false"/>
            <dftools:variable name="path" value="Algo/generated/singlerate/"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.mapper.exporter.DAGExportTransform" taskId="DAG Exporter">
        <dftools:data key="variables">
            <dftools:variable name="openFile" value="false"/>
            <dftools:variable name="path" value="Algo/generated/DAG/dag.graphml"/>
        </dftools:data>
    </dftools:task>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Display Gantt"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="Display Gantt"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture"
        targetport="architecture" to="Scheduling"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Scheduling"/>
    <dftools:dataTransfer from="HierarchyFlattening" sourceport="SDF"
        targetport="SDF" to="Single-rate Transformation"/>
    <dftools:dataTransfer from="Single-rate Transformation"
        sourceport="SDF" targetport="SDF" to="srSDF Exporter"/>
    <dftools:dataTransfer from="Single-rate Transformation"
        sourceport="SDF" targetport="SDF" to="Scheduling"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="DAG Exporter"/>
    <dftools:dataTransfer from="scenario" sourceport="SDF"
        targetport="SDF" to="HierarchyFlattening"/>
</dftools:workflow>
