/**
 * 
 */
package org.ietr.ganttdisplay;

import java.awt.BorderLayout;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

import org.ietr.ganttdisplay.exception.NoFileNameException;
import org.ietr.ganttdisplay.ui.RefreshActionListener;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;

/**
 * Displaying in a swing frame the Gantt chart corresponding to the xml data
 * entered in the command line.
 * 
 * @author mpelcat
 */
public class GanttDisplay {

	/**
	 * Main method. Parses the xml file name in the command line and displays
	 * data in a Gantt chart if data is correctly formatted
	 * 
	 * @param args
	 */
	public static void main(String[] args) {

		String fileName = null;

		try {
			fileName = parseFileName(args);
		} catch (NoFileNameException e) {
			System.out.println(e.getMessage());
			JOptionPane.showMessageDialog(new JFrame(), e.getMessage(),
					"Error", JOptionPane.ERROR_MESSAGE);
			System.exit(2);
		}

		File file = new File(fileName);
		JFrame frame = new JFrame("Gantt Chart Plotter");

		JButton button = new JButton("Refresh");
		frame.add(button, BorderLayout.SOUTH);

		ChartPanel chartPanel = new ChartPanel(ChartFactory.createGanttChart(
				"Solution Gantt", "Operators", "Time", null, true, true, false));
		chartPanel.setPreferredSize(new java.awt.Dimension(
				GanttPlotter.xDimension, GanttPlotter.yDimension));
		chartPanel.setMouseZoomable(true, false);
		frame.add(chartPanel);

		// Set the default close operation for the window, or else the
		// program won't exit when clicking close button
		// (The default is HIDE_ON_CLOSE, which just makes the window
		// invisible, and thus doesn't exit the app)
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

		// Set the visibility as true, thereby displaying it
		frame.setVisible(true);
		frame.pack();

		button.addActionListener(new RefreshActionListener(chartPanel, file));
	}

	/**
	 * Parses the file name in the command line.
	 * 
	 * @param args
	 */
	private static String parseFileName(String[] args)
			throws NoFileNameException {
		String fileName = null;
		boolean fileNameArg = false;

		for (String arg : args) {
			if (fileNameArg) {
				fileName = arg;
			}
			if (arg.equalsIgnoreCase("-f")) {
				fileNameArg = true;
			}
		}

		if (fileName == null) {
			throw (new NoFileNameException());
		}

		return fileName;
	}

}
