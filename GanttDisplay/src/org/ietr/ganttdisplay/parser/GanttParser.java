/*********************************************************
Copyright or © or Copr. IETR/INSA: Matthieu Wipliez, Jonathan Piat,
Maxime Pelcat, Peng Cheng Mu, Jean-François Nezan, Mickaël Raulet

[mwipliez,jpiat,mpelcat,pmu,jnezan,mraulet]@insa-rennes.fr

This software is a computer program whose purpose is to prototype
parallel applications.

This software is governed by the CeCILL-C license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-C
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-C license and that you accept its terms.
 *********************************************************/

package org.ietr.ganttdisplay.parser;

import java.awt.Color;
import java.io.File;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.ietr.ganttdisplay.exception.WrongColorFormatException;
import org.ietr.ganttdisplay.model.Gantt;
import org.ietr.ganttdisplay.model.GanttElement;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

/**
 * An xml parser retrieving gantt data
 * 
 * @author mpelcat
 */
public class GanttParser {

	/**
	 * xml tree
	 */
	private Document dom = null;

	public GanttParser() {

	}

	public Document getDom() {
		return dom;
	}

	/**
	 * Retrieves the DOM document
	 */
	public Gantt parseXmlFile(File file) {
		// get the factory
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();

		try {

			// Using factory get an instance of document builder
			DocumentBuilder db = dbf.newDocumentBuilder();

			// parse using builder to get DOM representation of the XML file
			dom = db.parse(file);
			
			return parseDocument();

		} catch (Exception e) {
			System.out.println(e.getMessage());
			JOptionPane.showMessageDialog(new JFrame(), e.getMessage(),
					"Error", JOptionPane.ERROR_MESSAGE);
			System.exit(2);
		}
		
		return null;
	}

	/**
	 * Parses the first level of hierarchy
	 */
	public Gantt parseDocument() throws NumberFormatException,WrongColorFormatException {

		Gantt gantt = new Gantt();

		if (dom != null) {
			// get the root elememt
			Element docElt = dom.getDocumentElement();

			Node node = docElt.getFirstChild();

			while (node != null) {

				if (node instanceof Element) {
					Element elt = (Element) node;
					String type = elt.getTagName();
					if (type.equals("event")) {
						parseData(gantt, elt);
					}
				}

				node = node.getNextSibling();
			}
		}

		return gantt;
	}

	/**
	 * Retrieves a Gantt element
	 */
	private void parseData(Gantt gantt, Element elt)
			throws NumberFormatException, WrongColorFormatException {

		Long start = Long.valueOf(elt.getAttribute("start"));
		Long end = Long.valueOf(elt.getAttribute("end"));
		// String isDuration = elt.getAttribute("isDuration");
		String title = elt.getAttribute("title");
		String mapping = elt.getAttribute("mapping");
		// String image = elt.getAttribute("image");
		Color color = parseColor(elt.getAttribute("color"));

		GanttElement element = new GanttElement(start, end, title,
				color, mapping);
		gantt.add(element);
	}

	/**
	 * parses the color in #rrggbb hexadecimal format
	 */
	private Color parseColor(String stringToParse)
			throws NumberFormatException, WrongColorFormatException {

		if(stringToParse.length() != 7 || (stringToParse.charAt(0) != '#')){
			throw new WrongColorFormatException(stringToParse);
		}
		
		Integer r = Integer.valueOf(stringToParse.substring(1, 3),16);
		Integer g = Integer.valueOf(stringToParse.substring(3, 5),16);
		Integer b = Integer.valueOf(stringToParse.substring(5, 7),16);
		
		return new Color(r,g,b);
	}
}
