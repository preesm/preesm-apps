<?xml version="1.0" encoding="UTF-8"?>
<dftools:workflow xmlns:dftools="http://net.sf.dftools" errorOnWarning="true" verboseLevel="INFO">
    <dftools:scenario pluginId="org.ietr.preesm.scenario.task"/>
    <dftools:task pluginId="codegen2" taskId="Code Generation">
        <dftools:data key="variables">
            <dftools:variable name="Papify" value="false"/>
            <dftools:variable name="Printer" value="C"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="heterogeneous-synthesis" taskId="Synthesis ">
        <dftools:data key="variables">
            <dftools:variable name="allocation" value="legacy"/>
            <dftools:variable name="clusterize" value="true"/>
            <dftools:variable name="scheduler" value="legacy"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="gantt-output-cluster" taskId="gantt Generation">
        <dftools:data key="variables">
            <dftools:variable name="display" value="true"/>
            <dftools:variable name="file path" value="gantt"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="pisdf-export" taskId="PiSDF Exporter">
        <dftools:data key="variables">
            <dftools:variable name="hierarchical" value="true"/>
            <dftools:variable name="path" value="/Algo/generated/pisdf/"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="heterogeneous-pisdf-srdag" taskId="PiMM2SrDAG">
        <dftools:data key="variables">
            <dftools:variable name="Consistency_Method" value="LCM"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="clustering" taskId="Clustering">
        <dftools:data key="variables">
            <dftools:variable name="clusterize" value="true"/>
            <dftools:variable name="heuristic" value="minimal"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="localcodegen" taskId="Local Code Generation">
        <dftools:data key="variables">
            <dftools:variable name="Papify" value="false"/>
            <dftools:variable name="Printer" value="C"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="pisdf-export" taskId="SRDAG Exporter">
        <dftools:data key="variables">
            <dftools:variable name="hierarchical" value="true"/>
            <dftools:variable name="path" value="/Algo/generated/pisdf/"/>
        </dftools:data>
    </dftools:task>
    <dftools:dataTransfer from="Synthesis " sourceport="Allocation" targetport="Allocation" to="Code Generation"/>
    <dftools:dataTransfer from="Synthesis " sourceport="Mapping" targetport="Mapping" to="Code Generation"/>
    <dftools:dataTransfer from="Synthesis " sourceport="Schedule" targetport="Schedule" to="Code Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture" targetport="architecture" to="Code Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario" targetport="scenario" to="Code Generation"/>
    <dftools:dataTransfer from="Synthesis " sourceport="HPiSDF" targetport="PiMM" to="gantt Generation"/>
    <dftools:dataTransfer from="Synthesis " sourceport="Allocation" targetport="Allocation" to="gantt Generation"/>
    <dftools:dataTransfer from="Synthesis " sourceport="Mapping" targetport="Mapping" to="gantt Generation"/>
    <dftools:dataTransfer from="Synthesis " sourceport="Schedule" targetport="Schedule" to="gantt Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario" targetport="scenario" to="gantt Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture" targetport="architecture" to="gantt Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture" targetport="architecture" to="Synthesis "/>
    <dftools:dataTransfer from="scenario" sourceport="scenario" targetport="scenario" to="Clustering"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture" targetport="architecture" to="Clustering"/>
    <dftools:dataTransfer from="scenario" sourceport="PiMM" targetport="PiMM" to="Clustering"/>
    <dftools:dataTransfer from="Clustering" sourceport="subgraphs" targetport="subgraphs" to="Synthesis "/>
    <dftools:dataTransfer from="Clustering" sourceport="PiMM" targetport="PiMM" to="PiMM2SrDAG"/>
    <dftools:dataTransfer from="Clustering" sourceport="scenario" targetport="scenario" to="Synthesis "/>
    <dftools:dataTransfer from="Clustering" sourceport="PiMM" targetport="PiMM" to="PiSDF Exporter"/>
    <dftools:dataTransfer from="Synthesis " sourceport="localSyntheses" targetport="localSyntheses" to="gantt Generation"/>
    <dftools:dataTransfer from="Synthesis " sourceport="localSyntheses" targetport="localSyntheses" to="Local Code Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture" targetport="architecture" to="Local Code Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario" targetport="scenario" to="Local Code Generation"/>
    <dftools:dataTransfer from="Local Code Generation" sourceport="PiMM" targetport="PiMM" to="Code Generation"/>
    <dftools:dataTransfer from="PiMM2SrDAG" sourceport="PiMM" targetport="PiMM" to="Synthesis "/>
    <dftools:dataTransfer from="Synthesis " sourceport="HPiSDF" targetport="PiMM" to="Local Code Generation"/>
    <dftools:dataTransfer from="PiMM2SrDAG" sourceport="PiMM" targetport="PiMM" to="SRDAG Exporter"/>
</dftools:workflow>
