<?xml version="1.0" encoding="UTF-8"?>
<dftools:workflow xmlns:dftools="http://net.sf.dftools">
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
    <dftools:task pluginId="org.ietr.preesm.plugin.transforms.sdf2hsdf" taskId="Single-rate transformation">
        <dftools:data key="variables">
            <dftools:variable name="ExplodeImplodeSuppr" value="false"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.plugin.mapper.listscheduling" taskId="Scheduling">
        <dftools:data key="variables">
            <dftools:variable name="Check" value="True"/>
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
    <dftools:task
        pluginId="org.ietr.preesm.memory.exclusiongraph.MemoryExclusionGraphBuilder" taskId="MEG Builder">
        <dftools:data key="variables">
            <dftools:variable name="Suppr Fork/Join" value="? C {True, False}"/>
            <dftools:variable name="Verbose" value="? C {True, False}"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.memory.script.MemoryScriptTask" taskId="Script">
        <dftools:data key="variables">
            <dftools:variable name="Check" value="Thorough"/>
            <dftools:variable name="Data alignment" value="Fixed:=4"/>
            <dftools:variable name="Log Path" value="log_memoryScripts"/>
            <dftools:variable name="Verbose" value="True"/>
        </dftools:data>
    </dftools:task>
    <dftools:task
        pluginId="org.ietr.preesm.memory.allocation.MemoryAllocatorTask" taskId="Memory Allocation">
        <dftools:data key="variables">
            <dftools:variable name="Allocator(s)" value="Basic"/>
            <dftools:variable name="Best/First Fit order" value="LargestFirst"/>
            <dftools:variable name="Data alignment" value="Fixed:=4"/>
            <dftools:variable name="Merge broadcasts" value="True"/>
            <dftools:variable name="Nb of Shuffling Tested" value="10"/>
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
        pluginId="org.ietr.preesm.memory.exclusiongraph.MemExUpdater" taskId="MemEx Update">
        <dftools:data key="variables"/>
    </dftools:task>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="PiMM2SDF"/>
    <dftools:dataTransfer from="scenario" sourceport="PiMM"
        targetport="PiMM" to="PiMM2SDF"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Scheduling"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture"
        targetport="architecture" to="Scheduling"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Stat Exporter"/>
    <dftools:dataTransfer from="PiMM2SDF" sourceport="SDF"
        targetport="SDF" to="Hierarchy Flattening"/>
    <dftools:dataTransfer from="Hierarchy Flattening" sourceport="SDF"
        targetport="SDF" to="Single-rate transformation"/>
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
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="MEG Builder"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="MEG Builder"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="MemEx Update"/>
    <dftools:dataTransfer from="MEG Builder" sourceport="MemEx"
        targetport="MemEx" to="MemEx Update"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="Script"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Script"/>
    <dftools:dataTransfer from="MemEx Update" sourceport="MemEx"
        targetport="MemEx" to="Script"/>
    <dftools:dataTransfer from="Script" sourceport="MemEx"
        targetport="MemEx" to="Memory Allocation"/>
    <dftools:dataTransfer from="Memory Allocation" sourceport="MEGs"
        targetport="MEGs" to="Code Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="scenario"
        targetport="scenario" to="Code Generation"/>
    <dftools:dataTransfer from="scenario" sourceport="architecture"
        targetport="architecture" to="Code Generation"/>
    <dftools:dataTransfer from="Scheduling" sourceport="DAG"
        targetport="DAG" to="Code Generation"/>
</dftools:workflow>
