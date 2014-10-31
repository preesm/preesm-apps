<?xml version="1.0" encoding="UTF-8"?>
<dftools:workflow xmlns:dftools="http://net.sf.dftools">
    <dftools:scenario pluginId="org.ietr.preesm.scenario.task"/>
    <dftools:task
        pluginId="org.ietr.preesm.plugin.mapper.listscheduling" taskId="Scheduling">
        <dftools:data key="variables">
            <dftools:variable name="balanceLoads" value="true"/>
            <dftools:variable name="displaySolutions" value="true"/>
            <dftools:variable name="edgeSchedType" value="Simple"/>
            <dftools:variable name="simulatorType" value="LooselyTimed"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="org.ietr.preesm.plugin.transforms.sdf2hsdf" taskId="Single-rate Transformation">
        <dftools:data key="variables">
            <dftools:variable name="ExplodeImplodeSuppr" value="false"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.plugin.transforms.flathierarchy" taskId="Hierarchy Flattening">
        <dftools:data key="variables">
            <dftools:variable name="depth" value="1"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="org.ietr.preesm.plugin.exportXml.sdf4jgml" taskId="srSDF Exporter">
        <dftools:data key="variables">
            <dftools:variable name="openFile" value="false"/>
            <dftools:variable name="path" value="Algo/generated/singlerate"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="org.ietr.preesm.plugin.exportXml.sdf4jgml" taskId="SDF Exporter">
        <dftools:data key="variables">
            <dftools:variable name="openFile" value="false"/>
            <dftools:variable name="path" value="Algo/generated"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.mapper.exporter.DAGExportTransform" taskId="DAG Exporter">
        <dftools:data key="variables">
            <dftools:variable name="openFile" value="false"/>
            <dftools:variable name="path" value="DAG/dag.graphml"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.memory.script.MemoryScriptTask" taskId="Memory Scripts">
        <dftools:data key="variables">
            <dftools:variable name="Check" value="Fast"/>
            <dftools:variable name="Data alignment" value="None"/>
            <dftools:variable name="Log Path" value="log_memoryScripts.txt"/>
            <dftools:variable name="Verbose" value="True"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.memory.allocation.MemoryAllocatorTask" taskId="Memory Allocation">
        <dftools:data key="variables">
            <dftools:variable name="Allocator(s)" value="BestFit"/>
            <dftools:variable name="Best/First Fit order" value="LargestFirst"/>
            <dftools:variable name="Data alignment" value="None"/>
            <dftools:variable name="Merge broadcasts" value="False"/>
            <dftools:variable name="Nb of Shuffling Tested" value="10"/>
            <dftools:variable name="Verbose" value="True"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.memory.exclusiongraph.MemoryExclusionGraphBuilder" taskId="MEG Builder">
        <dftools:data key="variables">
            <dftools:variable name="Suppr Fork/Join" value="False"/>
            <dftools:variable name="Verbose" value="True"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.codegen.xtend.task.CodegenTask" taskId="Code Generation">
        <dftools:data key="variables">
            <dftools:variable name="Printer" value="C"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.memory.exclusiongraph.MemExUpdater" taskId="MEG Updater">
        <dftools:data key="variables">
            <dftools:variable name="Suppr Fork/Join" value="False"/>
            <dftools:variable name="Update with MemObject lifetime" value="False"/>
            <dftools:variable name="Verbose" value="True"/>
        </dftools:data>
    </dftools:task>
    <dftools:task pluginId="org.ietr.preesm.plugin.mapper.plot" taskId="Gantt Plotter">
        <dftools:data key="variables"/>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.experiment.pimm2sdf.StaticPiMM2SDFTask" taskId="StaticPiMM2SDF">
        <dftools:data key="variables"/>
    </dftools:task>
    <dftools:dataTransfer from="scenario" sourceport="architecture"
        targetport="architecture" to="Scheduling"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Scheduling"/>
    <dftools:dataTransfer from="Hierarchy Flattening" sourceport="SDF"
        targetport="SDF" to="Single-rate Transformation"/>
    <dftools:dataTransfer from="Single-rate Transformation"
        sourceport="SDF" targetport="SDF" to="srSDF Exporter"/>
    <dftools:dataTransfer from="Single-rate Transformation"
        sourceport="SDF" targetport="SDF" to="Scheduling"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="DAG Exporter"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="Memory Scripts"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Memory Scripts"/>
    <dftools:dataTransfer from="Memory Scripts" sourceport="MemEx"
        targetport="MemEx" to="Memory Allocation"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="MEG Builder"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="MEG Builder"/>
    <dftools:dataTransfer from="Memory Allocation" sourceport="MemEx"
        targetport="MemEx" to="Code Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Code Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture"
        targetport="architecture" to="Code Generation"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="Code Generation"/>
    <dftools:dataTransfer from="MEG Builder" sourceport="MemEx"
        targetport="MemEx" to="MEG Updater"/>
    <dftools:dataTransfer from="MEG Updater" sourceport="MemEx"
        targetport="MemEx" to="Memory Scripts"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="MEG Updater"/>
    <dftools:dataTransfer from="Scheduling" sourceport="ABC"
        targetport="ABC" to="Gantt Plotter"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Gantt Plotter"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="StaticPiMM2SDF"/>
    <dftools:dataTransfer from="scenario" sourceport="PiMM"
        targetport="PiMM" to="StaticPiMM2SDF"/>
    <dftools:dataTransfer from="StaticPiMM2SDF" sourceport="SDF"
        targetport="SDF" to="Hierarchy Flattening"/>
    <dftools:dataTransfer from="StaticPiMM2SDF" sourceport="SDF"
        targetport="SDF" to="SDF Exporter"/>
</dftools:workflow>
