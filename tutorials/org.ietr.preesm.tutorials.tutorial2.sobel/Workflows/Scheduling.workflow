<?xml version="1.0" encoding="UTF-8"?>
<dftools:workflow xmlns:dftools="http://net.sf.dftools">
    <dftools:scenario pluginId="org.ietr.preesm.scenario.task"/>
    <dftools:task
        pluginId="org.ietr.preesm.experiment.pimm2sdf.PiMM2SDFTask" taskId="PiMM2SDF">
        <dftools:data key="variables"/>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.algorithm.exportXml.MultiSDFExporter" taskId="SDF Exporter">
        <dftools:data key="variables">
            <dftools:variable name="path" value="Algo/generated/ibsdf"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.algorithm.transforms.MultiHierarchyFlattening" taskId="Hierarchy Flattening">
        <dftools:data key="variables">
            <dftools:variable name="depth" value="3"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.algorithm.transforms.MultiHSDFTransformation" taskId="Single-rate transformation">
        <dftools:data key="variables">
            <dftools:variable name="ExplodeImplodeSuppr" value="false"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.algorithm.exportXml.MultiSDFExporter" taskId="srSDF Exporter">
        <dftools:data key="variables">
            <dftools:variable name="path" value="Algo/generated/HSDF/"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.experiment.pimm.mapper.MultiSDFListSchedulingMapping" taskId="Scheduling">
        <dftools:data key="variables">
            <dftools:variable name="balanceLoads" value="true"/>
            <dftools:variable name="edgeSchedType" value="Simple"/>
            <dftools:variable name="simulatorType" value="LooselyTimed"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.experiment.pimm.mapper.MultiStatEditorTransform" taskId="Display Gantt">
        <dftools:data key="variables"/>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.experiment.pimm.mapper.MultiDAGExportTransform" taskId="DAG Exporter">
        <dftools:data key="variables">
            <dftools:variable name="path" value="Algo/dag/"/>
        </dftools:data>
    </dftools:task>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="PiMM2SDF"/>
    <dftools:dataTransfer from="PiMM2SDF" sourceport="SDFs"
        targetport="SDFs" to="SDF Exporter"/>
    <dftools:dataTransfer from="PiMM2SDF" sourceport="SDFs"
        targetport="SDFs" to="Hierarchy Flattening"/>
    <dftools:dataTransfer from="Hierarchy Flattening" sourceport="SDFs"
        targetport="SDFs" to="Single-rate transformation"/>
    <dftools:dataTransfer from="Single-rate transformation"
        sourceport="SDFs" targetport="SDFs" to="srSDF Exporter"/>
    <dftools:dataTransfer from="scenario" sourceport="PiMM"
        targetport="PiMM" to="PiMM2SDF"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Scheduling"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture"
        targetport="architecture" to="Scheduling"/>
    <dftools:dataTransfer from="Single-rate transformation"
        sourceport="SDFs" targetport="SDFs" to="Scheduling"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABCs"
        targetport="ABCs" to="Display Gantt"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Display Gantt"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAGs"
        targetport="DAGs" to="DAG Exporter"/>
</dftools:workflow>
