/**
 * 
 */
package org.ietr.ganttdisplay.model;

import java.awt.Color;

/**
 * @author mpelcat
 *
 */
public class GanttElement {
	
	/**
	 * Starting date
	 */
	private Long start = 0l;

	/**
	 * End date
	 */
	private Long end = 0l;

	/**
	 * Display name of the Gantt element
	 */
	private String title = null;

	/**
	 * Display name of the mapping line of the Gantt element
	 */
	private String mapping = null;

	/**
	 * Color of the Gantt element
	 */
	private Color color = null;
	
	public GanttElement(Long start, Long end, String title, Color color, String mapping) {
		this.start = start;
		this.end = end;
		this.title = title;
		this.color = color;
		this.mapping = mapping;
	}

	public Long getStart() {
		return start;
	}

	public Long getEnd() {
		return end;
	}

	public String getTitle() {
		return title;
	}

	public Color getColor() {
		return color;
	}

	public String getMapping() {
		return mapping;
	}

	@Override
	public String toString() {
		return "GanttElement [start=" + start + ", end=" + end + ", title="
				+ title + ", mapping=" + mapping + ", color=" + color + "]";
	}
}
