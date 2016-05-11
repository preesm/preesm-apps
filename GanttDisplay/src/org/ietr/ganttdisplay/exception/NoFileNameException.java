/**
 * 
 */
package org.ietr.ganttdisplay.exception;

/**
 * Exception thrown when no file name was found in the command line
 * 
 * @author mpelcat
 */
public class NoFileNameException extends Exception {

	private static final long serialVersionUID = -7306885684800763239L;

	@Override
	public String getMessage() {
		return "No file name was found in the command line. Use -f fileName";
	}

	
}
