/**
 * 
 */
package org.ietr.ganttdisplay.model;

import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.ConcurrentSkipListSet;

/**
 * Data structure representing a Gantt chart.
 * 
 * @author mpelcat
 */
public class Gantt {

	/**
	 * Set of Gantt chart elements.
	 * Each element has a mapping, a start date and a end date that determine
	 * how it is drawn.
	 */
	private Set<GanttElement> elementSet;

	public Gantt() {
		elementSet = new HashSet<GanttElement>();
	}
	
	public void add(GanttElement element){
		elementSet.add(element);
	}

	@Override
	public String toString() {
		return "Gantt [elementSet=" + elementSet + "]";
	}

	public Set<GanttElement> getElementSet() {
		return Collections.unmodifiableSet(elementSet);
	}

	/**
	 * Returns all mappings in alphabetic order
	 */
	public Set<String> getMappings(){
		
		// Orders mappings in alphabetic order
		class myComparator implements Comparator<String>{
			@Override
			public int compare(String arg0, String arg1) {
				return arg0.compareTo(arg1);
			}
		}
		Set<String> mappings = new ConcurrentSkipListSet<String>(new myComparator());
		
		for(GanttElement element : elementSet){
			if(!mappings.contains(element.getMapping())){
				mappings.add(element.getMapping());
			}
		}
		
		return mappings;
	}
}
