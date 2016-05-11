/**
 * 
 */
package org.ietr.ganttdisplay.ui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import org.ietr.ganttdisplay.GanttPlotter;
import org.ietr.ganttdisplay.model.Gantt;
import org.ietr.ganttdisplay.parser.GanttParser;
import org.jfree.chart.ChartPanel;



/**
 * Action called when the refresh button is pressed
 * @author mpelcat
 */
public class RefreshActionListener implements ActionListener {

	private ChartPanel chartPanel;
	private File file;
	
	public RefreshActionListener(ChartPanel chartPanel, File file) {
		super();
		this.chartPanel = chartPanel;
		this.file = file;
	}

	@Override
	  public void actionPerformed(ActionEvent actionEvent) {
			GanttPlotter plotter = new GanttPlotter();
			GanttParser parser = new GanttParser();
			Gantt gantt = parser.parseXmlFile(file);
			
			plotter.plot(gantt,chartPanel);
			
			// "Packs" the window, making it "just big enough".
			//frame.pack();
	  }

}
